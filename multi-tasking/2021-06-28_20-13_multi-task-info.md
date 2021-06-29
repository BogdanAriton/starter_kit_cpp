# Parallel computing architectures:

Widely used system for for classifying multiprocessor architecture is Flynn's Taxonomy:
It's based on the number of concurrent instructions or instruction streams and the number of data streams.

                # instruction stream
            #      SISD       MISD
            d
            s      SIMD       MIMD

# SISD - single instruction single data
    Can execute only one thing at a time.
# SIMD - single instruction multiple data
    Is used
# MISD - multiple instructions singe data
    Not practical
# MIMD - multiple instructions multiple data
    Most used.

# Memory
    !! shared memory !!
    all processors should be able to see if another processor is changing its memory space

Architecture:
    UMP - uniform memory access or NUMA - non uniform 
        - all processes have equal access to memory
    Types of UMA -> SMP (symmetric multiprocessor system)

## SMP
    Processors are connected to the memory through the System Bus
    This is the most common and important to learn architecture

# Cache coherency
    - each core has it's own cache (a very fast piece of memory that only that specific processor can access)

    The problem when a processor write something into it's local cache based on data from the shared memory then that data needs to be updated in the shared memory before other processors can grab it to make their changes.

    This is handled by the hardware! (inside the computer! :-))

# process
    Independent

# threads
    Independent path of execution through the program
    