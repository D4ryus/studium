#include <bsd/stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "hashes.h"
#include "bloom.h"

enum test_type {COUNTING, RANDOM, EVEN_UNEVEN};

int main(int, const char**);
uint64_t calculate_K(uint8_t);
void run_test(enum test_type, uint8_t);
uint8_t parse_arguments(int, const char**);
void print_info(uint8_t);
void usage_quit(const char *);

uint64_t filter_size = 1 << 29;
uint64_t insert_size = 1 << 26;

uint64_t K;

int
main(int argc, const char *argv[])
{
        uint8_t use_hashes;

        use_hashes = parse_arguments(argc, argv);
        K = calculate_K(use_hashes);

        print_info(use_hashes);

        run_test(COUNTING, use_hashes);
        run_test(RANDOM, use_hashes);
        run_test(EVEN_UNEVEN, use_hashes);

        return EXIT_SUCCESS;
}

uint64_t calculate_K(uint8_t use_hashes)
{
        uint64_t k =0;

        if (use_hashes & FNV)       k++;
        if (use_hashes & MURMUR64)  k++;
        if (use_hashes & JENKINS)   k++;
        if (use_hashes & ELF)       k++;
        if (use_hashes & BERNSTEIN) k++;

        return k;
}

void
run_test(enum test_type t_type, uint8_t use_hashes)
{
        uint64_t i;
        uint64_t is_member_count;
        uint64_t rnd_nbr;
        char *type;
        uint64_t set_bits;
        struct timeval tval_before, tval_after, tval_result;

        /* insertion */
        create_filter(filter_size, use_hashes);

        gettimeofday(&tval_before, NULL);
        switch (t_type) {
                case EVEN_UNEVEN:
                        type = "un/even";
                        for (i = 1; i < insert_size << 1; i += 2) {
                                insert_key((char *)&i, 8);
                        }
                        break;
                case RANDOM:
                        type = "random";
                        for (i = 0; i < insert_size; i++) {
                                rnd_nbr = arc4random();
                                rnd_nbr = rnd_nbr << 32;
                                rnd_nbr = rnd_nbr | arc4random();
                                insert_key((char *)&rnd_nbr, 8);
                        }
                        break;
                case COUNTING:
                        type = "counting";
                        for (i = 0; i < insert_size; i++) {
                                insert_key((char *)&i, 8);
                        }
                        break;
                default:
                        /* not reached */
                        type = "";
                        break;
        }
        gettimeofday(&tval_after, NULL);
        timersub(&tval_after, &tval_before, &tval_result);

        /* testing */
        is_member_count = 0;
        switch (t_type) {
                case EVEN_UNEVEN:
                        for (i = 0; i < insert_size << 1; i += 2) {
                                if (is_member((char *)&i, 8)) {
                                        is_member_count++;
                                }
                        }
                        break;
                case RANDOM:
                        for (i = 0; i < insert_size; i++) {
                                rnd_nbr = arc4random();
                                rnd_nbr = rnd_nbr << 32;
                                rnd_nbr = rnd_nbr | arc4random();
                                if (is_member((char *)&rnd_nbr, 8)) {
                                        is_member_count++;
                                }
                        }
                        break;
                case COUNTING:
                        for (i = insert_size; i < insert_size << 1; i++) {
                                if (is_member((char *)&i, 8)) {
                                        is_member_count++;
                                }
                        }
                        break;
                default:
                        /* not reached */
                        break;
        }

        set_bits = estimate_cardinality();

        /* print info */
        printf("%-8s: ins time: %2ld.%-6ld false pos: %6.2f%% (%10lu) fill factor: %6.2f%% (%10lu) err rate: %6.2f%% (%10lu)\n",
            type,
            (long int)tval_result.tv_sec,
            (long int)tval_result.tv_usec,
            (double)is_member_count / (double)insert_size * 100.0,
            is_member_count,
            (double)set_bits / (double)filter_size * 100.0,
            set_bits,
            (double)(insert_size * K - set_bits) / (double)(insert_size * K) * 100.0,
            insert_size * K - set_bits);
}

uint8_t
parse_arguments(int argc, const char *argv[])
{
        uint8_t use_hashes = 0;
        int i;

        if (argc < 2) {
                usage_quit(argv[0]);
        }

        for (i = 1; i < argc; i++) {
                if ((strcmp(argv[i], "-h") == 0)
                    || strcmp(argv[i], "--help") == 0) {
                        usage_quit(argv[0]);
                } else if (strcmp(argv[i], "fnv") == 0) {
                        use_hashes |= FNV;
                } else if (strcmp(argv[i], "jenkins") == 0) {
                        use_hashes |= JENKINS;
                } else if (strcmp(argv[i], "murmur64") == 0) {
                        use_hashes |= MURMUR64;
                } else if (strcmp(argv[i], "bernstein") == 0) {
                        use_hashes |= BERNSTEIN;
                } else if (strcmp(argv[i], "elf") == 0) {
                        use_hashes |= ELF;
                } else {
                        usage_quit(argv[0]);
                }
        }

        return use_hashes;
}

void
print_info(uint8_t hashes)
{
        printf("hashes: [");
        if (hashes & FNV) {
                printf(" fnv");
        }
        if (hashes & MURMUR64) {
                printf(" murmur64");
        }
        if (hashes & JENKINS) {
                printf(" jenkins");
        }
        if (hashes & ELF) {
                printf(" elf");
        }
        if (hashes & BERNSTEIN) {
                printf(" bernstein");
        }
        printf(" ] bloomsize: %lu insert_size %lu\n", filter_size,
            insert_size);
}

void
usage_quit(const char *program_name)
{
        printf("error! no hashes specified.\n"
            "usage: %s [fnv | bernstein | murmur64 | elf | jenkins] ...\n"
            "note: its possible to specify a combination of hashes like:\n"
            "%s murmur64 jenkins elf\n",
            program_name, program_name);
        exit(1);
}
