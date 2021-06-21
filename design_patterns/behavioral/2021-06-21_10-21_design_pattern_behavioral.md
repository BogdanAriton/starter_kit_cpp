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

