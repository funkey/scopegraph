#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

namespace sg {
namespace detail {

// for each SignalType in AcceptsTypes
template <typename Derived, typename AcceptsTypes>
class AcceptsImpl : public AcceptsImpl<Derived, typename AcceptsTypes::Tail> {

protected:

	typedef typename AcceptsTypes::Head SignalType;

#ifdef __clang__
	AcceptsImpl() {

		// clang doesn't like function pointers to derived classes as template 
		// arguments (yet) -- therefore, we need to pass to __onSignal, a member 
		// of this class, which does the work.
		static_cast<Derived*>(this)->getReceiver().template registerCallback<SignalType, AcceptsImpl<Derived, AcceptsTypes>, &AcceptsImpl<Derived, AcceptsTypes>::__onSignal>(this);
	}

private:

	inline void __onSignal(SignalType& signal) {

		// directly forward to the Derived::onSignal method
		static_cast<Derived*>(this)->onSignal(signal);
	}
#else
	AcceptsImpl() {

		static_cast<Derived*>(this)->getReceiver().template registerCallback<SignalType, Derived, &Derived::onSignal>(static_cast<Derived*>(this));
	}
#endif
};

// last on in inheritance chain
template <typename Derived>
class AcceptsImpl<Derived, Accepts<Nothing>> {};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

