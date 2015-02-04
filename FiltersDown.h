#ifndef SCOPEGRAPH_FILTERS_DOWN_H__
#define SCOPEGRAPH_FILTERS_DOWN_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for scopes to filter user specified signals. Each signal compatible to 
 * any of the given signals in the parent scope will be filtered via user 
 * provided methods and passed to this scope.
 *
 *   class PainterSet : public Scope<
 *     PainterSet,
 *     FiltersDown<NeedRedraw>
 *   > {
 *
 *   public:
 *
 *     bool filterDown(NeedRedraw& signal)   { [apply filter to signal]     }
 *     void unfilterDown(NeedRedraw& signal) { [reverse filter from signal] }
 *   };
 *
 * The user provided method filterDown() implements the signal filter. If this 
 * method returns true, the signal is passed to this scope. Once processed by 
 * this scope, unfilterDown() is called to remove the filter from the signal for 
 * further unfiltered processing in higher scopes. unfilterDown() is not called, 
 * if filterDown() returned false.
 */
template <typename SignalType = Nothing, typename ... Rest>
class FiltersDown {

public:

	typedef SignalType           Head;
	typedef FiltersDown<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_FILTERS_DOWN_H__


