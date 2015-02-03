#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

#include <cohear/Receiver.h>

namespace sg {
namespace detail {

template <typename Derived, typename SignalType>
class AcceptsInnerImpl {

protected:

	void collectCallbacks(chr::Receiver& receiver) {

		receiver.registerCallback<SignalType, AcceptsInnerImpl<Derived, SignalType>, &AcceptsInnerImpl<Derived, SignalType>::__onInnerSignal>(this);
	}

private:

	inline void __onInnerSignal(SignalType& signal) {

		// directly forward to the Derived::onInnerSignal method
		static_cast<Derived*>(this)->onInnerSignal(signal);
	}
};

// recursive inheritance
template <typename Derived, typename SignalType, typename ... Rest>
class AcceptsInnerRec : public AcceptsInnerImpl<Derived, SignalType>, public AcceptsInnerRec<Derived, Rest...> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsInnerImpl<Derived, SignalType>::collectCallbacks(reciever);
		AcceptsInnerRec<Derived, Rest...>::collectCallbacks(reciever);
	}
};

// last on in inheritance chain
template <typename Derived, typename SignalType>
class AcceptsInnerRec<Derived, SignalType> : public AcceptsInnerImpl<Derived, SignalType> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsInnerImpl<Derived, SignalType>::collectCallbacks(reciever);
	}
};

// specialisation
template <typename Derived>
class AcceptsInnerRec<Derived, Nothing> {

protected:

	void collectCallbacks(chr::Receiver&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

