# Clean architecture

## What is bad architecture?
    Complex - Architecture that got complex accidentally
    Incoherent
    Rigid

## What is clean architecture?
    Simple
    Understandable
    Flexible
    Emergent
    Testable

## Statements
    Focus on the essentials
    Build only what is necessary
    Context is king
    All decisions are a tradeoff
    Align with business goals

## Domain-centric Architecture
    - Classical Three-layer database-centric architecture
    - in domain we put domain in center and database is just a detail
        - Uncle Bob - "Make sure the house is usable not that is made out of brick"
    
### Essential vs Detail
    - Domain is essential
    - Use cases are essential
    - Presentation is detail
    - Persistance is a detail

### Types of domain driven architecture
    - Hexagonal Architecture
    - Onion Architecture
    - Clean Architecture by Uncle Bob


    They all kind of express the same thing:
    Pros:
        1. They all put the domain model at the center
        2. Focus is on the domain - cost reduction
        3. Less coupling
        4. Allow for DDD

    Cons:
        1. Change is difficult
        2. RRequires more though
        3. Higher initial cost


# Notes:
    The domain bubble contains only classes that are domain specific and should not contain things related to application - like connectivity or other things like that