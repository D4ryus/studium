build:
        make

run:
        ./main (will print further info)

clean:
        make clean


info about table.txt:

        table.txt contains all test results, splitted in 3 tables (the 3 tests).

column explanation:

        hashes:
                each row stands for a different hash kombination.

        k:
                amount of hashfunctions.

        ins time:
                insertion time for 2^26 elements, time is in seconds.

        false pos %:
                percentage of false positives after testing with 2^26
                different keys.

        false pos count:
                amount of false positive keys.

        fill factor %:
                raw fill factor of bloomfilter.

        fill factor count:
                raw bits set inside the bloomfilter.

        err rate %:
                percentage of how many bits are not set, but should be
                set. for example, if err rate is 50.00% on a
                bloomfilter with 100 elements and 10.00% fill factor,
                20 elements should be set, but instead only 10 are set.

        err rate count:
                amount of bits which should be set in case of 0
                collisions.


table explanation:

        counting test:
                keys from 0 .. 2^26 have been inserted, then tested from
                2^26 .. 2^27.

        random test:
                2^26 random keys have been inserted, then 2^26 random
                keys where tested.

        uneven even test:
                2^26 uneven keys have been inserted, then 2^26 even
                keys where used as test.
