#ifndef SCOPEGRAPH_NOTHING_H__
#define SCOPEGRAPH_NOTHING_H__

#include <signals/Signal.h>

namespace sg {

/**
 * A symbol to represent no signal.
 */
class Nothing : public signals::Signal {};

} // namespace sg

#endif // SCOPEGRAPH_NOTHING_H__

