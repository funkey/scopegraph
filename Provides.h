#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include <signals/Slot.h>
#include "detail/ProvidesImpl.h"

namespace sg {

// provide all user-requested Signals and a few internal ones
template <typename ... Signals>
class Provides : public detail::ProvidesRec<Signals...> {

public:

	Provides() {

		detail::ProvidesRec<Signals...>::collectSlots(_sender);
	}

protected:

	signals::Sender& getSender() {

		return _sender;
	}

	using detail::ProvidesRec<Signals...>::send;

private:

	signals::Sender _sender;
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

