# adapter
Adapt some code to work with another code - basically if you have two interfaces that you don't want to change you can adapt the call from one interface to work with the other and adapt the response to work with the caller.


# bridge
Splitting large inheritance into different inheritance based on types:
    Shapes vs colors - a red square doesn't have to be a class on it's own, but the color can be injected into the class
The bridge is the relationship created between the Shape Superclass and the Color superclass.


# composite
Create trees and graphs out objects to be able to work as a composite.
For example you can have people and each people can be the boss of another person - now each title can differ and traversing a list of all hierarchies could be difficult, but not in a tree.
With BFS you can find out the hierarchy in an institution in just one go.


# decorator
Having a pizza you want to add topping to it - you can create a class of toppings that will be injected to pizza so you can access the toppings directly from the pizza object.


# facade
It's a class that will expose a limited functionality of a library (or simplified)
You might have 20 operations for extracting money from the bank, but you only expose 3 steps - this is similar to adapter but solved a different problem.

# flyweight
Changes the structure of o program from lots of parts to just one common part and lot's of smaller parts.
The common part keeps the state for each smaller part thus saving the memory that would be lost if you keep state for each individual component.


# proxy
Similar to decorator and facade .. but it keep the interface exact structure so the service and the proxy can be interchangeable
A proxy is an intermediary between clients and service.
The proxy will instantiate a specific service and will keep it alive as long as it's necessary.

