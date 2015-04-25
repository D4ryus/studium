#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "bloom.h"
#include "hashes.h"

uint64_t bloom_size    = 0;
uint8_t  *bloom_filter = NULL;
uint8_t  HASHES = 0;

void
create_filter(uint64_t bit_size, uint8_t use_hashes)
{
        /* if is still set, delete data */
        if (bloom_filter != NULL) {
                free(bloom_filter);
                bloom_filter = NULL;
        }

        HASHES = use_hashes;
        bloom_size = bit_size;
        bloom_filter = malloc(bloom_size >> 3);
        memset(bloom_filter, '\0', bloom_size >> 3);
}

void
insert_key(char *key, size_t length)
{
        uint64_t hash;

        if (HASHES & FNV) {
                hash = hash_fnv(key, length);
                bloom_filter[(hash % bloom_size) >> 3] |= 1 << (hash & 0x7);
        }
        if (HASHES & MURMUR64) {
                hash = hash_murmur64(key, length, 0);
                bloom_filter[(hash % bloom_size) >> 3] |= 1 << (hash & 0x7);
        }
        if (HASHES & JENKINS) {
                hash = hash_jenkins(key, length);
                bloom_filter[(hash % bloom_size) >> 3] |= 1 << (hash & 0x7);
        }
        if (HASHES & ELF) {
                hash = hash_elf(key, length);
                bloom_filter[(hash % bloom_size) >> 3] |= 1 << (hash & 0x7);
        }
        if (HASHES & BERNSTEIN) {
                hash = hash_bernstein(key, length);
                bloom_filter[(hash % bloom_size) >> 3] |= 1 << (hash & 0x7);
        }
}

int
is_member(char *key, size_t length)
{
        uint64_t hash;

        if (HASHES & FNV) {
                hash = hash_fnv(key, length);
                if ((bloom_filter[(hash % bloom_size) >> 3] & 1 << (hash & 0x7)) == 0) {
                        return 0;
                }
        }
        if (HASHES & MURMUR64) {
                hash = hash_murmur64(key, length, 0);
                if ((bloom_filter[(hash % bloom_size) >> 3] & 1 << (hash & 0x7)) == 0) {
                        return 0;
                }
        }
        if (HASHES & JENKINS) {
                hash = hash_jenkins(key, length);
                if ((bloom_filter[(hash % bloom_size) >> 3] & 1 << (hash & 0x7)) == 0) {
                        return 0;
                }
        }
        if (HASHES & ELF) {
                hash = hash_elf(key, length);
                if ((bloom_filter[(hash % bloom_size) >> 3] & 1 << (hash & 0x7)) == 0) {
                        return 0;
                }
        }
        if (HASHES & BERNSTEIN) {
                hash = hash_bernstein(key, length);
                if ((bloom_filter[(hash % bloom_size) >> 3] & 1 << (hash & 0x7)) == 0) {
                        return 0;
                }
        }

        return 1;
}

uint64_t
estimate_cardinality()
{
        uint64_t i;
        uint64_t set_bits;

        set_bits = 0;
        for (i = 0; i < bloom_size >> 3; i++) {
                if (bloom_filter[i] & 0x01) set_bits++;
                if (bloom_filter[i] & 0x02) set_bits++;
                if (bloom_filter[i] & 0x04) set_bits++;
                if (bloom_filter[i] & 0x08) set_bits++;
                if (bloom_filter[i] & 0x10) set_bits++;
                if (bloom_filter[i] & 0x20) set_bits++;
                if (bloom_filter[i] & 0x40) set_bits++;
                if (bloom_filter[i] & 0x80) set_bits++;
        }

        return set_bits;
}
