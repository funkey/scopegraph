#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__

#include <signals/VirtualCallback.h>
#include "AcceptsImpl.h"

namespace sg {
namespace detail {

template <typename SignalType>
class AcceptsInnerImpl : public AcceptsImpl<SignalType> {

public:

	void onSignal(SignalType& signal) override final { onInnerSignal(signal); }

	virtual void onInnerSignal(SignalType&) = 0;

protected:

	void collectCallbacks(signals::Receiver& receiver) {

		AcceptsImpl<SignalType>::collectCallbacks(receiver);
	}
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class AcceptsInnerRec : public AcceptsInnerImpl<SignalType>, public AcceptsInnerRec<Rest...> {

protected:

	void collectCallbacks(signals::Receiver& reciever) {

		AcceptsInnerImpl<SignalType>::collectCallbacks(reciever);
		AcceptsInnerRec<Rest...>::collectCallbacks(reciever);
	}
};

// last on in inheritance chain
template <typename SignalType>
class AcceptsInnerRec<SignalType> : public AcceptsInnerImpl<SignalType> {

protected:

	void collectCallbacks(signals::Receiver& reciever) {

		AcceptsInnerImpl<SignalType>::collectCallbacks(reciever);
	}
};

// specialisation
template <>
class AcceptsInnerRec<Nothing> {

protected:

	void collectCallbacks(signals::Receiver&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_INNER_IMPL_H__


