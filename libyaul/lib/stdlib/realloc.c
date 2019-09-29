#include <sys/cdefs.h>

#if defined(MALLOC_IMPL_TLSF)
#include <mm/tlsf.h>
#elif defined(MALLOC_IMPL_SLOB)
#include <mm/slob.h>
#endif /* MALLOC_IMPL_TLSF || MALLOC_IMPL_SLOB */

#include <internal.h>

void * __weak
realloc(void *old, size_t new_len)
{
        void *ret;

#if defined(MALLOC_IMPL_TLSF)
        tlsf_t pool;
        pool = master_state()->tlsf_pools[TLSF_POOL_PRIVATE];

        ret = tlsf_realloc(pool, old, new_len);
#elif defined(MALLOC_IMPL_SLOB)
        ret = slob_realloc(old, new_len);
#endif /* MALLOC_IMPL_TLSF || MALLOC_IMPL_SLOB */

        return ret;
}
