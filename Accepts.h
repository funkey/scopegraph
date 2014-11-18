#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include <signals/Callback.h>

namespace sg {

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

	void onSignal(const SignalType&) {}

private:

	signals::Callback<SignalType> _callback;
};

// base case
template <typename SignalType>
class Accepts<SignalType> {

public:

	typedef Accepts<SignalType> MyType;

	Accepts() :
			_callback(boost::bind(&MyType::onSignal, this, _1)) {

		_receiver.registerCallback(_callback);
	}

protected:

	virtual void onSignal(const SignalType&) = 0;

	signals::Receiver& getReceiver() { return _receiver; }

private:

	signals::Callback<SignalType> _callback;

	signals::Receiver _receiver;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

