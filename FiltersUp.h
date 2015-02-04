#ifndef SCOPEGRAPH_FILTERS_UP_H__
#define SCOPEGRAPH_FILTERS_UP_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for scopes to filter user specified signals. Each signal compatible to 
 * any of the given signals will be filtered via user provided methods and 
 * passed from this scope to the parent scope.
 *
 *   class PainterSet : public Scope<
 *     PainterSet,
 *     FiltersUp<NeedRedraw>
 *   > {
 *
 *   public:
 *
 *     bool filterUp(NeedRedraw& signal)   { [apply filter to signal]     }
 *     void unfilterUp(NeedRedraw& signal) { [reverse filter from signal] }
 *   };
 *
 * The user provided method filterUp() implements the signal filter. If this 
 * method returns true, the signal is passed to the parent scope. Once returned, 
 * unfilterUp() is called to remove the filter from the signal for further 
 * unfiltered processing in this or lower scopes. unfilterUp() is not called, if 
 * filterUp() returned false.
 */
template <typename SignalType = Nothing, typename ... Rest>
class FiltersUp {

public:

	typedef SignalType         Head;
	typedef FiltersUp<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_FILTERS_UP_H__


