#ifndef SCOPEGRAPH_ACCEPTS_INNER_H__
#define SCOPEGRAPH_ACCEPTS_INNER_H__

#include "detail/AcceptsInnerImpl.h"

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
template <typename Derived, typename ... Signals>
class AcceptsInner : public detail::AcceptsInnerRec<Derived, Signals...> {

protected:

	template <typename SpyType>
	void init(SpyType& spy) { detail::AcceptsInnerRec<Derived, Signals...>::collectCallbacks(spy.getReceiver()); }
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_INNER_H__


