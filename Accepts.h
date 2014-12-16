#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include <signals/Callback.h>
#include "detail/AcceptsImpl.h"

namespace sg {

// accept all user-requested Signals and a few internal ones
template <typename ... Signals>
class Accepts : public detail::AcceptsRec<Signals...> {

public:

	Accepts() {

		detail::AcceptsRec<Signals...>::collectCallbacks(_receiver);
	}

protected:

	signals::Receiver& getReceiver() { return _receiver; }

private:

	signals::Receiver _receiver;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

