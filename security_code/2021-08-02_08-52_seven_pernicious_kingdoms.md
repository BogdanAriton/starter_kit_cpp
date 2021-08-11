# Security features
    - plaintext storage and passwords
    - empty password in config files
    - hard-coded passwords
    - password in config files
    - weak encoding for passwords (sha256 probably the best)
    - least privilege violation
    - improper access control 
    - Improper Authorization
    - Use of insufficient random values
    - exposure of private personal information to unauthorized actors
    - use of hard-coded credentials

# Time and state
    - signal handler race condition - 
# Errors

# Input Validation and Representation

# API Abuse

# Code Quality

# Encapsulation
    Bind together the data and the functions that manipulate the data.
    Creating a class with some data and functions that act on the data.

    Encapsulation leads to data abstraction.

## Problems
    The software does not sufficiently hide the internal representation and implementation details of data or methods, which might allow external components or modules to modify data unexpectedly, invoke unexpected functionality, or introduce dependencies that the programmer did not intend. 

    Encapsulation is achieved using access modifiers.

# Environment