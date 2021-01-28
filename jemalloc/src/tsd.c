#define	JEMALLOC_TSD_C_
#include "jemalloc/internal/jemalloc_internal.h"

/******************************************************************************/
/* Data. */

static unsigned ncleanups;
static malloc_tsd_cleanup_t cleanups[MALLOC_TSD_CLEANUPS_MAX];

/******************************************************************************/

void *
malloc_tsd_malloc(size_t size)
{

	/* Avoid choose_arena() in order to dodge bootstrapping issues. */
	return (arena_malloc(arenas[0], size, false, false));
}

void
malloc_tsd_dalloc(void *wrapper)
{
	idalloct(wrapper, false);
}

void
malloc_tsd_no_cleanup(void *arg)
{
	not_reached();
}

void
malloc_tsd_cleanup_register(bool (*f)(void))
{
	assert(ncleanups < MALLOC_TSD_CLEANUPS_MAX);
	cleanups[ncleanups] = f;
	ncleanups++;
}

void
malloc_tsd_boot(void)
{
	ncleanups = 0;
}
