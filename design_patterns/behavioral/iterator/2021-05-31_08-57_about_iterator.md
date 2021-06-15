---
tags:
design_pattern
iterator
---

# What is an iterator?
Iterator provides a way to access elements of an aggregate without exposing its underlining representation.
Now what does "exposing its underlining representation" mean?
    - it means that the iterator is not part of the aggregate definition
    - the iterator will return specific positions of the aggregate
    - the same iterator implementation should sufficient to be applied to other containers

# Properties of iterators
