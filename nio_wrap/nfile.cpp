#include "nfile.h"

#include "impl/ncastinghelper.h"
#include "impl/nconvertinghelper.h"

//=======================================================================================
//      FileInputStream
//=======================================================================================
NFileInputStream::NFileInputStream( GFileInputStream *s )
    : NInputStream( gcast_to_input_stream(s) )
{}
//=======================================================================================
//      FileInputStream
//=======================================================================================



//=======================================================================================
//      FileOutputStream
//=======================================================================================
NFileOutputStream::NFileOutputStream( GFileOutputStream *s )
    : NOutputStream( gcast_to_output_stream(s) )
{}
//=======================================================================================
//      FileOutputStream
//=======================================================================================







//=======================================================================================
//      File
//=======================================================================================
NFile NFile::for_path( const std::string &path )
{
    return g_file_new_for_path( path.c_str() );
}
//=======================================================================================
NFile NFile::for_uri( const std::string &uri )
{
    return g_file_new_for_uri( uri.c_str() );
}
//=======================================================================================
NFile NFile::for_commandline_arg( const char *arg )
{
    return g_file_new_for_commandline_arg( arg );
}
//=======================================================================================
std::string NFile::get_parse_name() const
{
    return n_convert_and_free( g_file_get_parse_name(p.get()) );
}
//=======================================================================================
std::string NFile::get_basename() const // not UTF-8
{
    return n_convert_and_free( g_file_get_basename(p.get()) );
}
//=======================================================================================
std::string NFile::get_path() const
{
    return n_convert_and_free( g_file_get_path(p.get()) );
}
//=======================================================================================
NFile NFile::get_parent() const
{
    return g_file_get_parent( p.get() );
}
//=======================================================================================
NFileOutputStream NFile::create( GFileCreateFlags flags,
                                 NCancellable *cancel,
                                 NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    return g_file_create( p.get(), flags, gcancel, err_proxy );
}
//=======================================================================================
NFileOutputStream NFile::append( GFileCreateFlags flags,
                                 NCancellable *cancel,
                                 NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    return g_file_append_to( p.get(), flags, gcancel, err_proxy );
}
//=======================================================================================
NFileOutputStream NFile::replace( GFileCreateFlags flags,
                                  NCancellable *cancel,
                                  NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    return g_file_replace( p.get(), nullptr, false, flags, gcancel, err_proxy );
}
//=======================================================================================
NFileInfo NFile::query_info( NCancellable *cancel, NError *err ) const
{
    // ???
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;

    _n_error_proxy err_proxy( err );
    auto res = g_file_query_info( p.get(),
                                  "*",
                                  G_FILE_QUERY_INFO_NONE,
                                  gcancel,
                                  err_proxy );
    return res;
}
//=======================================================================================
NFileInputStream NFile::input( NCancellable *cancel, NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;

    _n_error_proxy err_proxy( err );
    auto res = g_file_read( p.get(), gcancel, err_proxy );

    return res;
}
//=======================================================================================
//      File
//=======================================================================================


