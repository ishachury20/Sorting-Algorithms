#include "set.h"

Set set_empty(void) {
    return 0;
}

Set set_universal(void) {
    return 0xffffffff;
}

Set set_insert(Set s, uint8_t x) {
    return s | (1 << x);
}

Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << x);
}

bool set_member(Set s, uint8_t x) {
    return s & (1 << x);
}

Set set_union(Set s, Set t) {
    uint32_t same = s | t;
    return same;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}
