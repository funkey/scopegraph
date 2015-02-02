#ifndef SCOPEGRAPH_AGENT_BASE_H__
#define SCOPEGRAPH_AGENT_BASE_H__

#include <cohear/Sender.h>
#include <cohear/Receiver.h>

namespace sg {
namespace detail {

class AgentBase {

public:

	void connect(AgentBase& other) {

		getSender().connect(other.getReceiver());
		other.getSender().connect(getReceiver());
	}

	void disconnect(AgentBase& other) {

		getSender().disconnect(other.getReceiver());
		other.getSender().disconnect(getReceiver());
	}

protected:

	virtual chr::Sender&   getSender()   = 0;
	virtual chr::Receiver& getReceiver() = 0;
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_AGENT_BASE_H__

