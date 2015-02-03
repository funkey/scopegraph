#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include "Signals.h"

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
template <typename SignalType = Nothing, typename ... Rest>
class Accepts {

public:

	typedef SignalType       Head;
	typedef Accepts<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

