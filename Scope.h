#ifndef SCOPEGRAPH_SCOPE_H__
#define SCOPEGRAPH_SCOPE_H__

#include <signals/PassThroughCallback.h>
#include <signals/PassThroughSlot.h>
#include "Agent.h"

namespace sg {

template <typename ProvideSignals = Provides<Nothing>, typename AcceptSignals = Accepts<Nothing> >
class Scope : public Agent<ProvideSignals, AcceptSignals> {

public:

	Scope() :
			_spy(std::make_shared<Agent<>>) {

		// couple the pass-through callback and slot
		_parentCallback.forwardTo(_spySlot);

		// register the pass-through callback and slot in our parent and spy
		Agent<ProvideSignals, AcceptSignals>::getReceiver().registerCallback(_parentCallback);
		_spy->getSender().registerSlot(_spySlot);

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
	std::shared_ptr<Agent<>> _spy;

	// a pass-through callback and slot to forward signals from the parent scope 
	// to the spy
	signals::PassThroughCallback<signals::Signal> _parentCallback;
	signals::PassThroughSlot<signals::Signal>     _spySlot;
};

} // namespace sg

#endif // SCOPEGRAPH_SCOPE_H__

