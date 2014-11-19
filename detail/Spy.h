#ifndef SCOPEGRAPH_DETAIL_SPY_H__
#define SCOPEGRAPH_DETAIL_SPY_H__

#include <signals/PassThroughCallback.h>
#include <signals/PassThroughSlot.h>
#include <scopegraph/Agent.h>

namespace sg {
namespace detail {

/**
 * Passes signals between scopes. Put the spy in the target scope and register 
 * the outer callback (via getOuterCallback()) in the scope you want to spy on.
 */
template <typename SignalType>
class Spy : public Agent<> {

public:

	Spy() {

		_outerCallback.forwardTo(_innerSlot);
		_innerCallback.forwardTo(_outerSlot);

		Agent<>::getSender().registerSlot(_innerSlot);
		Agent<>::getReceiver().registerCallback(_innerCallback);
	}

	signals::PassThroughCallback<SignalType>& getOuterCallback() { return _outerCallback; }
	signals::PassThroughSlot<SignalType>&     getOuterSlot()     { return _outerSlot; }

private:

	// a pass-through callback and slot to forward signals from the outer scope 
	// to the spy's scope
	signals::PassThroughCallback<SignalType> _outerCallback;
	signals::PassThroughCallback<SignalType> _innerCallback;
	signals::PassThroughSlot<SignalType>     _outerSlot;
	signals::PassThroughSlot<SignalType>     _innerSlot;
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_SPY_H__

