#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

#include <signals/VirtualCallback.h>

namespace sg {
namespace detail {

// base class for all AcceptImpls
class AcceptsImplBase {};

template <typename SignalType>
class AcceptsImpl : public AcceptsImplBase {

public:

	typedef AcceptsImplBase HandlerBaseType;

	virtual void onSignal(const SignalType&) = 0;

protected:

	void collectCallbacks(signals::Receiver& receiver) {

		receiver.registerCallback(new signals::VirtualCallback<SignalType,AcceptsImpl<SignalType>>(this));
	}
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class AcceptsRec: public AcceptsImpl<SignalType>, public AcceptsRec<Rest...> {

protected:

	void collectCallbacks(signals::Receiver& reciever) {

		AcceptsImpl<SignalType>::collectCallbacks(reciever);
		AcceptsRec<Rest...>::collectCallbacks(reciever);
	}
};

// last on in inheritance chain
template <typename SignalType>
class AcceptsRec<SignalType> : public AcceptsImpl<SignalType> {

protected:

	void collectCallbacks(signals::Receiver& reciever) {

		AcceptsImpl<SignalType>::collectCallbacks(reciever);
	}
};

// specialisation
template <>
class AcceptsRec<Nothing> {

protected:

	void collectCallbacks(signals::Receiver&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

