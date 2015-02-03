#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

namespace sg {
namespace detail {

// for each SignalType in AcceptsTypes
template <typename Derived, typename AcceptsTypes>
class AcceptsInnerImpl : public AcceptsInnerImpl<Derived, typename AcceptsTypes::Tail> {

protected:

	typedef typename AcceptsTypes::Head SignalType;

#ifdef __clang__
	template <typename SpyType>
	void init(SpyType& spy) {

		// clang doesn't like function pointers to derived classes as template 
		// arguments (yet) -- therefore, we need to pass to __onInnerSignal, a 
		// member of this class, which does the work.
		spy.getReceiver().template registerCallback<SignalType, AcceptsInnerImpl<Derived, AcceptsTypes>, &AcceptsInnerImpl<Derived, AcceptsTypes>::__onInnerSignal>(this);

		AcceptsInnerImpl<Derived, typename AcceptsTypes::Tail>::init(spy);
	}

private:

	inline void __onInnerSignal(SignalType& signal) {

		// directly forward to the Derived::onInnerSignal method
		static_cast<Derived*>(this)->onInnerSignal(signal);
	}
#else
	template <typename SpyType>
	void init(SpyType& spy) {

		spy.getReceiver().template registerCallback<SignalType, Derived, &Derived::onInnerSignal>(static_cast<Derived*>(this));

		AcceptsInnerImpl<Derived, typename AcceptsTypes::Tail>::init(spy);
	}
#endif
};

// last on in inheritance chain
template <typename Derived>
class AcceptsInnerImpl<Derived, AcceptsInner<>> {

protected:

	template <typename SpyType>
	void init(SpyType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

