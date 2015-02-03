#ifndef SCOPEGRAPH_BACKWARDS_H__
#define SCOPEGRAPH_BACKWARDS_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for scopes to backward user specified signals. Each signal compatible 
 * to any of the given signals will be passed from this scope to the parent 
 * scope.
 *
 *   class PainterSet : public Scope<
 *     PainterSet,
 *     Backwards<NeedRedraw>
 *   > {};
 */
template <typename SignalType = Nothing, typename ... Rest>
class Backwards {

public:

	typedef SignalType         Head;
	typedef Backwards<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_BACKWARDS_H__

