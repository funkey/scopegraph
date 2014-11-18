#ifndef SCOPEGRAPH_SCOPE_H__
#define SCOPEGRAPH_SCOPE_H__

#include <signals/PassThroughCallback.h>
#include <signals/PassThroughSlot.h>
#include "detail/Spy.h"
#include "Agent.h"

namespace sg {

template <typename ProvideSignals = Provides<Nothing>, typename AcceptSignals = Accepts<Nothing> >
class Scope : public Agent<ProvideSignals, AcceptSignals> {

public:

	Scope() :
			_spy(std::make_shared<detail::Spy>()) {

		// register the spy's pass-through callback in the parent scope
		Agent<ProvideSignals, AcceptSignals>::getReceiver().registerCallback(_spy->getOuterCallback());

		// establish the spy connection to our scope
		_agents.insert(_spy);
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

private:

	// connect an agent to all agents contained in this scope
	void connect(detail::AgentBase& agent) {

		for (auto const& other : _agents)
			other->connect(agent);
	}

	std::set<std::shared_ptr<detail::AgentBase> > _agents;

	// an agent that sends and receives signals in this scope for communication 
	// with the parent scope
	std::shared_ptr<detail::Spy> _spy;
};

} // namespace sg

#endif // SCOPEGRAPH_SCOPE_H__

