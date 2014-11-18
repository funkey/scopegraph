#ifndef SCOPEGRAPH_AGENT_H__
#define SCOPEGRAPH_AGENT_H__

#include <signals/Sender.h>
#include <signals/Receiver.h>
#include "Provides.h"
#include "Accepts.h"

namespace sg {

template <typename ProvideSignals, typename AcceptSignals>
class Agent : public ProvideSignals, public AcceptSignals {

public:

	void connect(Agent& other) {

		getSender().connect(other._receiver);
		other.getSender().connect(_receiver);
	}

	void disconnect(Agent& other) {

		getSender().disconnect(other._receiver);
		other.getSender().disconnect(_receiver);
	}

protected:

	using ProvideSignals::getSender;

private:

	signals::Receiver _receiver;
};

} // namespace sg

#endif // SCOPEGRAPH_AGENT_H__

