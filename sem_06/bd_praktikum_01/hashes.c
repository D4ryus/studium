#include <stdlib.h>
#include <stdint.h>

#include "hashes.h"

uint64_t
hash_fnv(const char *key, const size_t len)
{
        const uint64_t magic_prime = 0x00000100000001b3;
        uint64_t       hash        = 0xcbf29ce484222325;
        size_t i;

        for (i = 0; i < len; i++) {
                hash = (hash ^ *(key + i)) * magic_prime;
        }

        return hash;
}

uint64_t
hash_murmur64(const char *key, const size_t len, unsigned int seed)
{
        const uint64_t m = 0xc6a4a7935bd1e995;
        const int      r = 47;
        uint64_t       h = seed ^ (uint64_t)len;

        const uint64_t *data = (const uint64_t *)key;
        const uint64_t *end  = data + (len/8);

        while (data != end) {
                uint64_t k = *data++;

                k *= m;
                k ^= k >> r;
                k *= m;

                h ^= k;
                h *= m;
        }

        const unsigned char *data2 = (const unsigned char *)data;

        switch (len & 7) {
                case 7: h ^= (uint64_t)data2[6] << 48;
                case 6: h ^= (uint64_t)data2[5] << 40;
                case 5: h ^= (uint64_t)data2[4] << 32;
                case 4: h ^= (uint64_t)data2[3] << 24;
                case 3: h ^= (uint64_t)data2[2] << 16;
                case 2: h ^= (uint64_t)data2[1] << 8;
                case 1: h ^= (uint64_t)data2[0];
                        h *= m;
                default: /* not reached */
                        break;
        };

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
}

uint32_t
hash_jenkins(const char *key, const size_t len)
{
        uint32_t hash;
        uint32_t i;

        for (hash = i = 0; i < len; i++) {
                hash += key[i];
                hash += (hash << 10);
                hash ^= (hash >> 6);
        }

        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return hash;
}

uint32_t
hash_elf(const char *key, const size_t len)
{
        uint32_t h;
        uint32_t g;
        size_t i;

        h = 0;

        for (i = 0; i < len; i++) {
                h = (h << 4) + key[i];
                g = h & 0xf0000000L;

                if (g != 0) {
                    h ^= g >> 24;
                }

                h &= ~g;
        }

        return h;
}

uint32_t
hash_bernstein(const char *key, const size_t len)
{
        uint32_t h = 0;
        size_t i;

        for (i = 0; i < len; i++) {
                h = 33 * h ^ key[i];
        }

        return h;
}
