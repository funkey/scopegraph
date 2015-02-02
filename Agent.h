#ifndef SCOPEGRAPH_AGENT_H__
#define SCOPEGRAPH_AGENT_H__

#include "Provides.h"
#include "Accepts.h"
#include "detail/AgentBase.h"
#include "detail/ParamDefault.h"

namespace sg {

template <typename ... Params>
class Agent :
	public detail::AgentBase,
	public detail::ParamDefault<Provides<Nothing>, Params...>::Value,
	public detail::ParamDefault<Accepts<Nothing>, Params...>::Value {

private:

	typedef typename detail::ParamDefault<Provides<Nothing>, Params...>::Value ProvideSignals;
	typedef typename detail::ParamDefault<Accepts<Nothing>, Params...>::Value  AcceptSignals;

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

