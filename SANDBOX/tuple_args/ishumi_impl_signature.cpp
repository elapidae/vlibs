#include "ishumi_impl_signature.h"

#include <set>
#include <mutex>
#include <stdexcept>
#include "vcat.h"

//=======================================================================================
void ishumi::impl::add_check_signature( ishumi::impl::signature_type sig_of_name )
{
    static std::set<ishumi::impl::signature_type> snames;
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock( mutex );

    auto res = snames.emplace( sig_of_name );

    if ( !res.second )
        throw std::logic_error( vcat().hex()("Signature '", sig_of_name,
                                "' already registered, collision detected.") );
}
//=======================================================================================
