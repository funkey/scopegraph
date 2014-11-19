#ifndef SCOPEGRAPH_SCOPE_H__
#define SCOPEGRAPH_SCOPE_H__

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

	typedef Agent<> SpyType;

	Scope() :
		_spy(std::make_shared<SpyType>()) {

		ForwardSignals::init(*this);
		BackwardSignals::init(*this);

		add(_spy);
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

	/**
	 * Get the spy of this scope. This is an agent that lives in this scope and 
	 * provides communication with the outside world, e.g., the parent scope.
	 */
	SpyType& getSpy() {

		return *_spy;
	}

	using Agent<ProvideSignals, AcceptSignals>::getReceiver;
	using Agent<ProvideSignals, AcceptSignals>::getSender;

private:

	// connect an agent to all agents contained in this scope
	void connect(detail::AgentBase& agent) {

		for (auto const& other : _agents)
			other->connect(agent);
	}

	std::set<std::shared_ptr<detail::AgentBase> > _agents;

	std::shared_ptr<SpyType> _spy;
};

} // namespace sg

#endif // SCOPEGRAPH_SCOPE_H__

