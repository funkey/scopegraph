#ifndef SCOPEGRAPH_SCOPE_H__
#define SCOPEGRAPH_SCOPE_H__

#include <signals/PassThroughCallback.h>
#include <signals/PassThroughSlot.h>
#include "detail/Spy.h"
#include "Agent.h"
#include "Backwards.h"
#include "Forwards.h"

namespace sg {

template <
		typename BackwardSignals = Backwards<Nothing>,
		typename ForwardSignals  = Forwards<signals::Signal>,
		typename ProvideSignals  = Provides<Nothing>,
		typename AcceptSignals   = Accepts<Nothing>
>
class Scope : public BackwardSignals, public ForwardSignals, public Agent<ProvideSignals, AcceptSignals> {

public:

	Scope() {

		ForwardSignals::init(*this);
	}

	/**
	 * Add an agent to this scope. Returns true, if the agent was not added 
	 * before already.
	 */
	bool add(std::shared_ptr<detail::AgentBase> agent) {

		if (_agents.count(agent))
			return false;

		connect(*agent);
		_agents.insert(agent);

		return true;
	}

	using Agent<ProvideSignals, AcceptSignals>::getReceiver;

private:

	// connect an agent to all agents contained in this scope
	void connect(detail::AgentBase& agent) {

		for (auto const& other : _agents)
			other->connect(agent);
	}

	std::set<std::shared_ptr<detail::AgentBase> > _agents;
};

} // namespace sg

#endif // SCOPEGRAPH_SCOPE_H__

