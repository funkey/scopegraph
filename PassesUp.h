#ifndef SCOPEGRAPH_PASSES_UP_H__
#define SCOPEGRAPH_PASSES_UP_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for scopes to backward user specified signals. Each signal compatible 
 * to any of the given signals will be passed from this scope to the parent 
 * scope.
 *
 *   class PainterSet : public Scope<
 *     PainterSet,
 *     PassesUp<NeedRedraw>
 *   > {};
 */
template <typename SignalType = Nothing, typename ... Rest>
class PassesUp {

public:

	typedef SignalType         Head;
	typedef PassesUp<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_PASSES_UP_H__

