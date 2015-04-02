<!--- vim:spell:tw=80:fo=tawn
--->
scopegraph
==========

**scopegraph** is a C++ library for scoped signalling between agents. For that,
scopes can be defined in a directed acyclic graph that indicates subscope
relations. Each scope can be populated with agents who communicate by sending
and receiving signals. By default, agents send signals to all agents in their
own and lower scopes and receive signals from all agents in their own and
higher scopes.

**scopegraph** is build around [cohear](http://github.com/funkey/cohear), which
ensures very fast signalling and features automatic matching of compatible
signals.

Usage Example
-------------

### Creating Signals

Signals are just class instances (and are therefore encouraged to have state).
In order to take advantage of the automatic matching of inherited types (see
[cohear](http://github.com/funkey/cohear) for details), a parent type cue has
to be provided.

```c++
class A {};

class B {};

// invasive parent type cue
class B1 : public B { public: typedef B parent_type; };

class B2 : public B {};

// non-invasive parent type cue
namespace chr {
template <>
struct parent_of<B2> { typedef B value; };
}
```

### Creating Agents

New agents are created by inheriting from the class template `sg::Agent`, which
is refined by policies `sg::Accepts` and `sg::Provides`:

```c++
class MrSmith :
  public sg::Agent<
    MrSmith,
    sg::Provides<A, B1>,
    sg::Accepts<A, B>> {

public:

  // callbacks

  void onSignal(A&) { std::cout << "received signal A" << std::endl; }
  void onSignal(B&) { std::cout << "received signal B" << std::endl; }

  // example method sending signals

  void reveal() {

    // send default constructed signal
    send<A>();

    // send self-made signal by reference
    B1 b1;
    send(b1);
  }
};
```

### Connecting Agents

Agents are automatically connected when they are added to a scope:

```c++
auto smith1 = std::make_shared<MrSmith>();
auto smith2 = std::make_shared<MrSmith>();
auto scope  = std::make_shared<sg::Scope>();

scope.add(smith1);
scope.add(smith2);

smith1->reveal();
```

By calling `reveal()` on `smith1`, `smith2` receives signals `A` and `B`, where signal `B1` was automatically
cast to the callback of signal `B`:

```
received signal A
received signal B
```

Scopes are also agents, and can therefore be nested. By default, scopes forward
signals downwards. The following snippet produces the same output as above:

```c++
auto smith1 = std::make_shared<MrSmith>();
auto smith2 = std::make_shared<MrSmith>();
auto scope1 = std::make_shared<sg::Scope>();
auto scope2 = std::make_shared<sg::Scope>();

scope1.add(smith1);
scope1.add(scope2);
scope2.add(smith2);

smith1->reveal();
```
