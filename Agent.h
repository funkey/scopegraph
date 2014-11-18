#ifndef SCOPEGRAPH_AGENT_H__
#define SCOPEGRAPH_AGENT_H__

#include <signals/Sender.h>
#include <signals/Receiver.h>
#include "Provides.h"
#include "Accepts.h"
#include "detail/AgentBase.h"

namespace sg {

template <typename ProvideSignals = Provides<Nothing>, typename AcceptSignals = Accepts<Nothing>>
class Agent : public detail::AgentBase, public ProvideSignals, public AcceptSignals {

protected:

	using ProvideSignals::send;

	signals::Sender& getSender() {

		return ProvideSignals::getSender();
	}

	signals::Receiver& getReceiver() {

		return AcceptSignals::getReceiver();
	}

	template <typename SignalType, typename ... Args>
	void send(Args ... args) {

		SignalType signal(args ...);
		send(signal);
	}
};

} // namespace sg

#endif // SCOPEGRAPH_AGENT_H__

