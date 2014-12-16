#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include <signals/Slot.h>
#include "detail/ProvidesImpl.h"

namespace sg {

// provide all user-requested Signals and a few internal ones
template <typename ... Signals>
class Provides : public detail::ProvidesImpl<Signals...> {};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

