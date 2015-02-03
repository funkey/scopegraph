#ifndef SCOPEGRAPH_AGENT_H__
#define SCOPEGRAPH_AGENT_H__

#include "Provides.h"
#include "Accepts.h"
#include "detail/AcceptsImpl.h"
#include "detail/AgentBase.h"
#include "detail/ParamDefault.h"

namespace sg {

template <typename Derived, typename ... Params>
class Agent :
	public detail::AgentBase,
	public detail::ParamDefault<Provides<Nothing>, Params...>::Value,
	public detail::AcceptsImpl<Derived, typename detail::ParamDefault<Accepts<>, Params...>::Value> {

private:

	typedef typename detail::ParamDefault<Provides<Nothing>, Params...>::Value                       ProvideSignals;
	typedef detail::AcceptsImpl<Derived, typename detail::ParamDefault<Accepts<>, Params...>::Value> AcceptSignals;

public:

	chr::Sender& getSender() {

		return ProvideSignals::getSender();
	}

	chr::Receiver& getReceiver() {

		return AcceptSignals::getReceiver();
	}

protected:

	using ProvideSignals::send;
};

} // namespace sg

#endif // SCOPEGRAPH_AGENT_H__

