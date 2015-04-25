#include <stdint.h>

enum hashes {
        FNV       = 0x01,
        MURMUR64  = 0x02,
        JENKINS   = 0x04,
        ELF       = 0x08,
        BERNSTEIN = 0x10
};

uint64_t hash_fnv(const char *, const size_t);
uint64_t hash_murmur64(const char *, const size_t, unsigned int);
uint32_t hash_jenkins(const char *, const size_t);
uint32_t hash_elf(const char *, const size_t);
uint32_t hash_bernstein(const char *, const size_t);
