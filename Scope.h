#ifndef SCOPEGRAPH_SCOPE_H__
#define SCOPEGRAPH_SCOPE_H__

#include "Agent.h"
#include "Backwards.h"
#include "Forwards.h"
#include "ProvidesInner.h"
#include "detail/Spy.h"
#include "detail/ParamDefault.h"

namespace sg {

template <typename ... Params>
class Scope :
	public detail::ParamDefault<Backwards<Nothing>,Params...>::Value,
	public detail::ParamDefault<Forwards<signals::Signal>,Params...>::Value,
	public detail::ParamDefault<ProvidesInner<Nothing>,Params...>::Value,
	//public detail::ParamDefault<AcceptsInner<Nothing>,Params...>::Value,
	public Agent<
		typename detail::ParamDefault<Provides<Nothing>,Params...>::Value,
		typename detail::ParamDefault<Accepts<Nothing>,Params...>::Value
	>
	{

private:

	typedef typename detail::ParamDefault<Forwards<signals::Signal>,Params...>::Value  ForwardsType;
	typedef typename detail::ParamDefault<Backwards<Nothing>,Params...>::Value         BackwardsType;
	typedef typename detail::ParamDefault<ProvidesInner<Nothing>,Params...>::Value     ProvidesInnerType;

	typedef detail::Spy<ProvidesInnerType> SpyType;

public:

	Scope() {

		ForwardsType::init(*this);
		BackwardsType::init(*this);
		ProvidesInnerType::init(_spy);
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
	 * Remove an agent from this scope. Returns false, if the agent was not part 
	 * of this scope.
	 */
	bool remove(std::shared_ptr<detail::AgentBase> agent) {

		auto iterator = std::find(_agents.begin(), _agents.end(), agent);

		if (iterator == _agents.end())
			return false;

		disconnect(*agent);
		_agents.erase(iterator);

		return true;
	}

	/**
	 * Get the spy of this scope. This is an agent that lives in this scope and 
	 * provides communication with the outside world, e.g., the parent scope.
	 */
	SpyType& getSpy() {

		return _spy;
	}

protected:

	using ProvidesInnerType::sendInner;

private:

	// connect an agent to all agents contained in this scope and the spy
	void connect(detail::AgentBase& agent) {

		for (auto const& other : _agents)
			other->connect(agent);

		_spy.connect(agent);
	}

	// disconnect an agent from all agents contained in this scope and the spy
	void disconnect(detail::AgentBase& agent) {

		for (auto const& other : _agents)
			other->disconnect(agent);

		_spy.disconnect(agent);
	}

	std::set<std::shared_ptr<detail::AgentBase> > _agents;

	SpyType _spy;
};

} // namespace sg

#endif // SCOPEGRAPH_SCOPE_H__

