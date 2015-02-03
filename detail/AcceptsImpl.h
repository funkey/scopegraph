#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

#include <cohear/Receiver.h>

namespace sg {
namespace detail {

template <typename Derived, typename SignalType>
class AcceptsImpl {

protected:

	void collectCallbacks(chr::Receiver& receiver) {

		receiver.registerCallback<SignalType, AcceptsImpl<Derived, SignalType>, &AcceptsImpl<Derived, SignalType>::__onSignal>(this);
	}

private:

	inline void __onSignal(SignalType& signal) {

		// directly forward to the Derived::onSignal method
		static_cast<Derived*>(this)->onSignal(signal);
	}
};

// recursive inheritance
template <typename Derived, typename SignalType, typename ... Rest>
class AcceptsRec : public AcceptsImpl<Derived, SignalType>, public AcceptsRec<Derived, Rest...> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsImpl<Derived, SignalType>::collectCallbacks(reciever);
		AcceptsRec<Derived, Rest...>::collectCallbacks(reciever);
	}
};

// last on in inheritance chain
template <typename Derived, typename SignalType>
class AcceptsRec<Derived, SignalType> : public AcceptsImpl<Derived, SignalType> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsImpl<Derived, SignalType>::collectCallbacks(reciever);
	}
};

// specialisation
template <typename Derived>
class AcceptsRec<Derived, Nothing> {

protected:

	void collectCallbacks(chr::Receiver&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

