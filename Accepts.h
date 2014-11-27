#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include <signals/Callback.h>
#include "detail/AcceptsImpl.h"
#include "Signals.h"

namespace sg {

// accept all user-requested Signals and a few internal ones
template <typename ... Signals>
class Accepts : public detail::AcceptsImpl<sg::AddAgent, Signals...> {};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

