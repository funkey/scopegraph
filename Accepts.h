#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include <signals/Callback.h>
#include "Nothing.h"

namespace sg {

// base class for all Accepts
class AcceptBase {

protected:

	signals::Receiver& getReceiver() { return _receiver; }

private:

	signals::Receiver _receiver;
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Accepts : public Accepts<Rest...> {

public:

	typedef Accepts<SignalType, Rest...> MyType;

	Accepts() :
			_callback(boost::bind(&MyType::onSignal, this, _1)) {

		getReceiver().registerCallback(_callback);
	}

protected:

	using Accepts<Rest...>::getReceiver;

	virtual void onSignal(const SignalType&) = 0;

private:

	signals::Callback<SignalType> _callback;
};

// base case
template <typename SignalType>
class Accepts<SignalType> : public AcceptBase {

public:

	typedef Accepts<SignalType> MyType;

	Accepts() :
			_callback(boost::bind(&MyType::onSignal, this, _1)) {

		getReceiver().registerCallback(_callback);
	}

protected:

	virtual void onSignal(const SignalType&) = 0;

private:

	signals::Callback<SignalType> _callback;
};

// specialisation
template <>
class Accepts<Nothing> : public AcceptBase {};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

