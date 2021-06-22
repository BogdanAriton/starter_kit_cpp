SOLID:
    S: single responsibility principle (SRP)
        - what this refers to is: that you should try to think about your code (either it is a function or a structure of some kind) in a way that each individual component has one responsibility
            - try to avoid writing big functions that do everything - in a legacy environment you could try separating a big function into smaller ones if possible
            - classes/structures should only do things related to their name (avoid having an all-purpose class)
            - you can tell when you have violated this principle when making a change and you have to change more than that specific area of code
            - most of design pattern strive to achieve SRP
    
    O: opened for extension and closed for modification principle (OCP)
        - this refers to the structure of your code and it is meant to make you think about how to organize your code in such a way so that the next time you have to add a new requirement you can do so without having to redesign your code
            - coupling is the problem here - objects and functions should be using each other not depend on each other
            - a good patter that addresses this issue is:
                - Strategy patterns - for a more abstract definition this patters is saying that you can eliminate single targeted actions for similar objects into a bigger strategy that will address those actions for each object individually without having to change the object itself
                    - a good example for this is when you have a shop each item will have a price and other such details and when you want to filter by any of the detail you can just create a collection that will be filled with the items based on the comparison, but what happens when you want to add a new filter you will have to change the code that filters and the items to add the new detail - this is bad, what you can do is:
                        - have details outside of the items
                        - have an abstraction for a filter that checks for is_satisfied given an item
                        - now you can add as many filter implementations as you want and as many new details as you want and you are no longer bound by the item itself and you will not have to change it

    L: Liskov substitution principle (LSP)
        - this is an obscure one, what LSP is trying to say is that you should try to think about inheritance in a better way
        - how I view this is that it may be better to avoid using inheritance if the derived class changes the meaning of what the intent of the base class was
            - for example: when you think about Square and Rectangle - you may say that the square can be derived for Rectangle because it's basically a Rectangle that has width = height, but there are changes particularly to how square functions are implemented and you cannot substitute directly a rectangle for a square
            - so then you can just separate them and have a more particular rectangle may be derived from a rectangle and then the square is just a square
    
    I: Interface segregation principle (ISP)
        - this is probably more of an SRP corner case that refers to interfaces
        - the best way to think about it is: "One all-purpose interface is worse than many single purpose interfaces"
        - a very good counter-example of this is MFC where everything is a CWnd, but you cannot really use CWnd on its own and you cannot replace CWnd with anything

    D: Dependency inversion principle (DIP)
        - this is an important one and is more related to how you architect your code
        - you have to think about this in a way that relates to who hold responsibility for what, for example, in MVC design you should have the model as your business logic that will change less than controllers and view so that they depend directly on Model - this way you have inverted the dependency between view and Model so that model doesn't depend on view, but rather the other way around
        - another important point to that dependencies should be made between abstraction and you should avoid having a higher-level abstraction depend on the implementation