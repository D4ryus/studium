Files:
    cb.c:
        callback functionality and thread abstraction.

    data.c:
        data constructs (linked lists) and functions to add, remove, ...

    helper.c:
        helper functions like starts_with(), die(), ...

    main.c:
        implementation of algorithm, init, cleanup, start of threads, ...

    multicast.c:
        layer to recv and send data via multicast socket.

    simulate.sh:
        bash script to simulate given sequence of requests.

    simu_log.txt:
        since simluate.sh runs four programs the log wont be in sequence.
        simu_log.txt is a synchornized (per hand) example log file.

Code description:
    On start a multicast socket will be opened with the given address and port,
    then a thread is created to handle all incomming requests. The main thread
    will then handle input form stdin. On successfull request (all clients
    responded with ok) a callback thread is kicked off which will sleep for the
    given block time, after that time the resource is removed from the block
    list and all queued requests are informed.
