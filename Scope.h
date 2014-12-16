#ifndef SCOPEGRAPH_SCOPE_H__
#define SCOPEGRAPH_SCOPE_H__

#include "Agent.h"
#include "Backwards.h"
#include "Forwards.h"
#include "detail/ParamDefault.h"

namespace sg {

template <typename ... Params>
class Scope :
	public detail::ParamDefault<Backwards<Nothing>,Params...>::Value,
	public detail::ParamDefault<Forwards<signals::Signal>,Params...>::Value,
	public Agent<
		typename detail::ParamDefault<Provides<Nothing>,Params...>::Value,
		typename detail::ParamDefault<Accepts<Nothing>,Params...>::Value
	>
	{

private:

	typedef typename detail::ParamDefault<Backwards<Nothing>,Params...>::Value         ForwardSignals;
	typedef typename detail::ParamDefault<Forwards<signals::Signal>,Params...>::Value  BackwardSignals;

public:

	class Spy : public Agent<Accepts<AddAgent>> {

	private:

		void onSignal(AddAgent& /*signal*/) {/*TODO*/}
	};

	Scope() :
		_spy(std::make_shared<Spy>()) {

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
	Spy& getSpy() {

		return *_spy;
	}

	//using Agent<ProvideSignals, AcceptSignals>::getReceiver;
	//using Agent<ProvideSignals, AcceptSignals>::getSender;

private:

	// connect an agent to all agents contained in this scope
	void connect(detail::AgentBase& agent) {

		for (auto const& other : _agents)
			other->connect(agent);
	}

	std::set<std::shared_ptr<detail::AgentBase> > _agents;

	std::shared_ptr<Spy> _spy;
};

} // namespace sg

#endif // SCOPEGRAPH_SCOPE_H__

