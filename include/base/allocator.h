//
// Created by brian on 4/20/18.
//

#pragma once

#include <cassert>

#if defined(_WIN32)
#include <malloc.h>
#else

#include <cstdlib>

#endif

namespace x {

inline void *aligned_alloc(size_t size, size_t align) {
    if (align < sizeof(void *))
        align = sizeof(void *);

    void *r;

#if defined(_WIN32)
    r = _aligned_malloc(size, align);
    assert(r && "_aligned_malloc failed");
#else
    int res = posix_memalign(&r, align, size);
    assert(res == 0 && "posix memalign failed");
    (void) res;
#endif
    return r;
}

inline void aligned_free(void *p) {
#if defined(_WIN32)
    _aligned_free(p);
#else
    free(p);
#endif
}

}
