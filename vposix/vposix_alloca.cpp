#include "vposix_alloca.h"

#include "vlog_pretty.h"
#include <malloc.h>
#include "vposix_core.h"
#include <stdexcept>

using namespace vposix;

//=======================================================================================
void *Alloca::do_allocate( size_t sz )
{
    if ( do_trace() ) vtrace("V::alloca(", sz, ")" );

    auto res = alloca( sz );
    if ( !res ) throw std::bad_alloc();

    return res;
}
//=======================================================================================
