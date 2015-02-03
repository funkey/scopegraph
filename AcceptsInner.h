#ifndef SCOPEGRAPH_ACCEPTS_INNER_H__
#define SCOPEGRAPH_ACCEPTS_INNER_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for scopes to accept user specified signals from agents of the scope.  
 * For each signal type provided, the mix-in connects a user provided method
 *
 *   Derived::onInnerSignal(SignalType& signal);
 *
 * which a concrete class should implement. The mix-in uses the receiver of the 
 * scope's spy, which is introduced via init().
 */
template <typename SignalType = Nothing, typename ... Rest>
class AcceptsInner {

public:

	typedef SignalType       Head;
	typedef AcceptsInner<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_INNER_H__


