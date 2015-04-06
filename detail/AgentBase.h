#ifndef SCOPEGRAPH_AGENT_BASE_H__
#define SCOPEGRAPH_AGENT_BASE_H__

#include <cohear/Sender.h>
#include <cohear/Receiver.h>

namespace sg {
namespace detail {

class AgentBase {

public:

	AgentBase() {

		_sender.registerSlot(_agendAdded);
	}

	void connect(AgentBase& other) {

		getSender().connect(other.getReceiver());
		other.getSender().connect(getReceiver());
	}

	void disconnect(AgentBase& other) {

		getSender().disconnect(other.getReceiver());
		other.getSender().disconnect(getReceiver());
	}

	chr::Receiver& getReceiver() { return _receiver; }
	chr::Sender&   getSender()   { return _sender; }

	/**
	 * Called by scopes after the agent has been connected to them.
	 */
	void introduceAs(std::shared_ptr<AgentBase> agent) { AgentAdded signal(agent); _agendAdded(signal); }

private:

	chr::Receiver _receiver;
	chr::Sender   _sender;

	chr::Slot<AgentAdded> _agendAdded;
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_AGENT_BASE_H__

