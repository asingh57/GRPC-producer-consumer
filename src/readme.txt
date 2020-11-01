Abhijit Singh
asingh811@gatech.edu 

This is an asynchronous grpc implementation of the store defined for assignment 3 of AOS
It is largely based on the async hello world example of grpc from github
The threadpool is a generic function pointer based pool where threads pick up jobs from pool as they come

requests made to the vendors are split into "sender" and "receiver" jobs on the thread pool in order to maintain the async nature of the project


This is fully compatible with the CMakelists.txt supplied by the instructor for the assignment but mine is supplied alongside anyway
There is only one extra file namely, store.h

to build, do "make" in the build directory

once cmake build is done, simply execute:

./store vendor_addresses.txt PORT THREADCOUNT

where PORT is the server's port and threadcount is number of threads in the pool


example:

./store vendor_addresses.txt 6969 8

will run server at 0.0.0.0:6969 and have a threadpool of 8 threads
