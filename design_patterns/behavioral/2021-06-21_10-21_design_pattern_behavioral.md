# chain of responsibility
The pattern describes a way to separate into different structures all handlers that process a request.
Pros:
    This way you can mix and mach handlers depending on the request.
    If one handler fails it will not pass on the request to the next handler.
    Adheres to the single responsibility principle - because each handler is responsible for only one thing
    Open-closed - adding new handlers will not affect the rest of the code
Cons:
    If a request fails from the first handle it will not be processed


# command
Transforms requests into objects that has the information about the request.
The request will be constructed based on the type of the request so you need to be aware of what request types you can have.
You will need to implement an abstraction of command that can then be passed in wherever and let polymorphism do it job.

Pros:
    adding new requests will not affect the rest of the code - O/C
    each request is doing one thing - SRP
Cons:
    The implementation can be complex


# iterator
Lets you iterate/traverse though all the elements in an aggregate without exposing the representation of that aggregate
Pros:
    Iterator is responsible for it's state - that means you're not affecting the class while iterating
    You can iterate over the same object in multiple ways at the same time
    You can stop and turn
    You can iterate over complex structures like trees or graphs for a given rule - the code for traversing will not have to be written by other devs
Cons:
    Depending on the aggregate you need to chose if you need an iterator or not (some aggregates may not be iterable or it would be an overkill)


# mediator
The pattern can be simply thought as an intermediate point for all communications between components.
Imagine a radio tower for flights in an airport then instead of having each plain communicate with each-other you should have a mediator like a tower that can translate each request and let other plains know of only the necessary information.
Pros:
    The mediator will ease communication between components
    Will help with decoupling
Cons:
    Can get out of hand and can evolve in a god object (which is an anti-pattern)

# memento
Kind of like a history of something.
It lets access a snapshot of the state of an object without having to know the implementation of the object.
Similar to iterator in a sense because an iterator handles it own state, but doesn't remember the previous one.

# observer
Publish subscribe - when an series of objects wait for some info that a publisher like object can obtain then he can let know only those objects that the state has changed
Basically you can have a list of pointers to the subscribers and just call their +execute method when the event has ocurred.
Pros:
    O/C - you can alway add another subscriber without having to affect anything else
    (having an add subscribed method that will update the map of subscribers)
Cons:
    Subscribers order is random - this could be solved via a priority queue - you can define the order of subscribers and then process them in a queue like manner

# state
Kind of like a command really.
If you can imagine a type of scenario when a document can be in Draft, Review or Published let say - then these are states.
You will define different classes for each state that can be injected in an object.
The object will perform all operations as before but the operations content will vary based on the state implementation.
The state object does all the work.

Pros:
    O/C - you can always add more states - given that the original object doesn't suffer changes
    SRP - each state is responsible for it's action
Cons:
    Figure out if this is an overkill or not (if the state doesn't change all that much or if there are a few states - like 1/2)

# strategy
The strategy pattern lets you separate different logics or algorithms that can be switch between at need.
For example a filter on a shop website:
    - for each product you can have different types of filters
    - each product will be injected the strategy specific to that filter
    - if you want to filter a product by color, brand and size - then you will build all of these strategies and apply them when needed - the object will most likely search the database based on these filters

Pros:
    - O/C - you can add new strategies with ease
    - isolation and decoupling - your code will not get bloated with all these algorithms
    - swapping changing strategies at will
Cons:
    - could be hard to implement and hard to follow
    - you could youse lambdas in most cases to achieve the same thing (what I mean is - on a find in a collection you can add a predicate that is considered a filter - and you don't have to create all the classes)

# template method
It's just as the name suggests you can identify a series of common steps in an logic and instead of repeating that logic you can create a class that implements common steps and let subclasses change what they need.
Pros:
    - reduce duplicate code
    - O/C - you can create variants of the algorithm without affecting the code in general
Cons:
    - you might end up changing the implementation of an implemented method from the superclass in the subclass violating Liskov Substitution
    - can be hard to maintain
    - the skeleton can be limited - you can either have a big skeletal that will limit variety or it can be to small and you will end up making duplicate code anyway

# visitor
I'll try an explication - when you have an implementation and you want to add some new logic that can affect a type of class instead of adding it to the class you can externalize it to a visitor class that will be conducting the work - now when I say work I'm referring to some work that only that class would do in different ways.
It's kind of like applying an algorithm for different type of objects each object is different thus the algorithm will vary
But if you can extract the needed info from each class that will be needed by the algo without having to change it then that great!
The visitor does just that, the class will have a new method that will give the algo the necessary stuff so he can go on it's merry way.
The visitor will have to keep track of all classes which is kind of strict coupling.
