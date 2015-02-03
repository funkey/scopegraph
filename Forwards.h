#ifndef SCOPEGRAPH_FORWARDS_H__
#define SCOPEGRAPH_FORWARDS_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for scopes to forward user specified signals. Each signal compatible 
 * with any of the given signals will be passed on from the parent scope to the 
 * agents (and therefore also scopes) of this scope. Example usage:
 *
 *   class TunnelScope : public Scope<
 *     TunnelScope,
 *     Forwards<Signal> // i.e., all signals
 *   > {};
 */
template <typename SignalType = Nothing, typename ... Rest>
class Forwards {

public:

	typedef SignalType        Head;
	typedef Forwards<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_FORWARDS_H__

