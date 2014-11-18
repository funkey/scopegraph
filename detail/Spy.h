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
class Spy : public Agent<> {

public:

	Spy() {

		_outerCallback.forwardTo(_innerSlot);

		Agent<>::getSender().registerSlot(_innerSlot);
	}

	signals::PassThroughCallback<signals::Signal>& getOuterCallback() { return _outerCallback; }

private:

	// a pass-through callback and slot to forward signals from the outer scope 
	// to the spy's scope
	signals::PassThroughCallback<signals::Signal> _outerCallback;
	signals::PassThroughSlot<signals::Signal>     _innerSlot;
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_SPY_H__

