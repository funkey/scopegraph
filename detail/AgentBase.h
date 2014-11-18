#ifndef SCOPEGRAPH_AGENT_BASE_H__
#define SCOPEGRAPH_AGENT_BASE_H__

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

	virtual signals::Sender&   getSender()   = 0;
	virtual signals::Receiver& getReceiver() = 0;
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_AGENT_BASE_H__

