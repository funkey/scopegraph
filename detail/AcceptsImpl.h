#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

#include <cohear/Receiver.h>

namespace sg {
namespace detail {

template <typename SignalType>
class AcceptsImpl {

public:

	virtual void onSignal(SignalType&) = 0;

protected:

	void collectCallbacks(chr::Receiver& receiver) {

		receiver.registerCallback<SignalType, AcceptsImpl<SignalType>, &AcceptsImpl<SignalType>::onSignal>(this);
	}
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class AcceptsRec : public AcceptsImpl<SignalType>, public AcceptsRec<Rest...> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsImpl<SignalType>::collectCallbacks(reciever);
		AcceptsRec<Rest...>::collectCallbacks(reciever);
	}
};

// last on in inheritance chain
template <typename SignalType>
class AcceptsRec<SignalType> : public AcceptsImpl<SignalType> {

protected:

	void collectCallbacks(chr::Receiver& reciever) {

		AcceptsImpl<SignalType>::collectCallbacks(reciever);
	}
};

// specialisation
template <>
class AcceptsRec<Nothing> {

protected:

	void collectCallbacks(chr::Receiver&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

