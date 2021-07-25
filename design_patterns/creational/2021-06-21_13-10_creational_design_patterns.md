# factory-method
A method that gives you back an instance of a type.
the implementation speaks for it's self since creational pattern rely heavily on how they are implemented.
We need to create an abstract factory class that can instantiate an abstract class of type X that is the supper class for a number of concrete X-es
Then we create an implementation corresponding to each concrete X as concrete factory that return new of that object.

You create decoupling.
The client (or dev that uses the code) doesn't care about the specific X that will be create since they will have similar behaviors but separate implementations.

# abstract factory
You can create some of logical grouping out objects, for example buttons:
    - windows buttons
    - mac buttons 
When you create a mac application you know you only want mac buttons, but you don't have to look for them all the time.
You can create an abstract factory that can give you back all button of type mac - why?
Because all mac buttons will be of a specific interface.
The factory will be a ButtonFactory and Each concrete implementation will be MacButtonFactory or WinButtonFactory.
Each concrete implementation will create a specific type of button.

# builder
The intent is to create complex objects step by step.
you have create a static class inner to your original class that will access the elements need to initialized.
(don't use this one much since in C++ we can create a simple initializer list)

# prototype
It is a copy constructor and a copy assignment operator.
Or a clone function in Java that returns a new object that will be the same as the one is cloned from.

Reiterate existing design.
Cloning can be made via a Factory.

A partially initialized object that you copy.

# singleton
Just one object that can be use as a global one for the app