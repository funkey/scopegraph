#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

#include <cohear/Receiver.h>

namespace sg {
namespace detail {

template <typename SignalType>
class AcceptsInnerImpl {

public:

	virtual void onInnerSignal(SignalType&) = 0;

protected:

	void collectCallbacks(chr::Receiver& receiver) {

		receiver.registerCallback<SignalType, AcceptsInnerImpl<SignalType>, &AcceptsInnerImpl<SignalType>::onInnerSignal>(this);
	}
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class AcceptsInnerRec : public AcceptsInnerImpl<SignalType>, public AcceptsInnerRec<Rest...> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsInnerImpl<SignalType>::collectCallbacks(reciever);
		AcceptsInnerRec<Rest...>::collectCallbacks(reciever);
	}
};

// last on in inheritance chain
template <typename SignalType>
class AcceptsInnerRec<SignalType> : public AcceptsInnerImpl<SignalType> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsInnerImpl<SignalType>::collectCallbacks(reciever);
	}
};

// specialisation
template <>
class AcceptsInnerRec<Nothing> {

protected:

	void collectCallbacks(chr::Receiver&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

