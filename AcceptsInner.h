#ifndef SCOPEGRAPH_ACCEPTS_INNER_H__
#define SCOPEGRAPH_ACCEPTS_INNER_H__

#include <signals/Callback.h>
#include "detail/AcceptsInnerImpl.h"

namespace sg {

/**
 * Mix-in for scopes to accept user specified signals from agents of the scope.  
 * For each signal type provided, the mix-in declares a pure virtual function
 *
 *   onInnerSignal(SignalType& signal) = 0;
 *
 * which an implementation should override. The mix-in uses the receiver of the 
 * scope's spy, which is introduced via init(). For each specified signal type, 
 * a class derived from this mix-in can be cast to 
 * sg::detail::AcceptsImpl<SignalType>.  For efficient signalling, a slot that 
 * is to be connected to the receiver of this mix-in should be instantiated with 
 * the VirtualCallbackInvoker for AcceptsImpl. The mix-in Provides<...> does 
 * that already.
 */
template <typename ... Signals>
class AcceptsInner : public detail::AcceptsInnerRec<Signals...> {

protected:

	template <typename SpyType>
	void init(SpyType& spy) { detail::AcceptsInnerRec<Signals...>::collectCallbacks(spy.getReceiver()); }
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_INNER_H__


