#include <stdint.h>

void create_filter(uint64_t, uint8_t);
void insert_key(char *, size_t);
int is_member(char *, size_t);
uint64_t estimate_cardinality(void);
