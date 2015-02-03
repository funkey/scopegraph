#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include <cohear/Receiver.h>
#include "detail/AcceptsImpl.h"

namespace sg {

/**
 * Mix-in to accept user specified signals. For each signal type provided, the 
 * mix-in connects a user provided method
 *
 *   Derived::onSignal(SignalType& signal)
 *
 * which a concrete class should implement. The mix-in holds a receiver that 
 * provides a description of all the callbacks.
 */
template <typename Derived, typename ... Signals>
class Accepts : public detail::AcceptsRec<Derived, Signals...> {

protected:

	Accepts() {

		detail::AcceptsRec<Derived, Signals...>::collectCallbacks(_receiver);
	}

	chr::Receiver& getReceiver() { return _receiver; }

private:

	chr::Receiver _receiver;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

