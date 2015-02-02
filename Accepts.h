#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include <cohear/Receiver.h>
#include "detail/AcceptsImpl.h"

namespace sg {

/**
 * Mix-in to accept user specified signals. For each signal type provided, the 
 * mix-in declares a pure virtual function
 *
 *   onSignal(SignalType& signal) = 0;
 *
 * which an implementation should override. The mix-in holds a receiver that 
 * provides a description of all the callbacks. For each specified signal type, 
 * a class derived from this mix-in can be cast to 
 * sg::detail::AcceptsImpl<SignalType>. For efficient signalling, a slot that is 
 * to be connected to the receiver of this mix-in should be instantiated with 
 * the VirtualCallbackInvoker for AcceptsImpl. The mix-in Provides<...> does 
 * that already.
 */
template <typename ... Signals>
class Accepts : public detail::AcceptsRec<Signals...> {

protected:

	Accepts() {

		detail::AcceptsRec<Signals...>::collectCallbacks(_receiver);
	}

	chr::Receiver& getReceiver() { return _receiver; }

private:

	chr::Receiver _receiver;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

