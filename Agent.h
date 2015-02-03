#ifndef SCOPEGRAPH_AGENT_H__
#define SCOPEGRAPH_AGENT_H__

#include "Provides.h"
#include "Accepts.h"
#include "detail/ProvidesImpl.h"
#include "detail/AcceptsImpl.h"
#include "detail/AgentBase.h"
#include "detail/ParamDefault.h"

namespace sg {

template <typename Derived, typename ... Params>
class Agent :
	public detail::AgentBase,
	public detail::ProvidesImpl<Derived, typename detail::ParamDefault<Provides<>, Params...>::Value>,
	public detail::AcceptsImpl<Derived, typename detail::ParamDefault<Accepts<>, Params...>::Value> {

private:

	typedef detail::ProvidesImpl<Derived, typename detail::ParamDefault<Provides<>, Params...>::Value> ProvideSignals;
	typedef detail::AcceptsImpl<Derived, typename detail::ParamDefault<Accepts<>, Params...>::Value>   AcceptSignals;

protected:

	using ProvideSignals::send;

	/**
	 * Convenience method for sending signals by passing their constructor 
	 * arguments.
	 */
	template <typename SignalType, typename ... Args>
	void send(Args ... args) {

		SignalType signal(args ...);
		send(signal);
	}
};

} // namespace sg

#endif // SCOPEGRAPH_AGENT_H__

