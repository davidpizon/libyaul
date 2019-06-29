#include <string.h>
#include <stdint.h>

#define BITOP(a,b,op) \
 ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))

size_t strspn(const char *s, const char *c)
{
        const char *a = s;
        size_t byteset[32/sizeof(size_t)] = { 0 };

        if (!c[0]) return 0;
        if (!c[1]) {
                for (; *s == *c; s++);
                return s-a;
        }

        for (; *c && BITOP(byteset, *(uint8_t *)c, |=); c++);
        for (; *s && BITOP(byteset, *(uint8_t *)s, &); s++);
        return s-a;
}
