#include "nstreams.h"

#include "impl/ncastinghelper.h"

//=======================================================================================
//      InputStream
//=======================================================================================
NInputStream::NInputStream( GInputStream *istream )
    : NObject( gcast_to_gobject(istream) )
    , _g_input_stream( istream )
{}
//=======================================================================================
ssize_t NInputStream::read( void *buffer, size_t count,
                                NCancellable *cancel,
                                NError *err )
{
    static_assert( sizeof(gssize) == sizeof(decltype(read(0,0))), "");
    static_assert( sizeof(gsize)  == sizeof(decltype(count)), "");

    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _NErrorProxy err_proxy( err );
    auto res = g_input_stream_read( _g_input_stream,
                                    buffer, count,
                                    gcancel, err_proxy );

    return res;
}
//=======================================================================================
NBytes NInputStream::read_bytes( size_t count, NCancellable *cancel, NError *err )
{
    static_assert( sizeof(gsize)  == sizeof(decltype(count)), "");

    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _NErrorProxy err_proxy( err );
    auto bytes_ptr = g_input_stream_read_bytes( _g_input_stream,
                                                count,
                                                gcancel,
                                                err_proxy );
    return { .RAW = bytes_ptr };
}
//=======================================================================================
bool NInputStream::is_pollable() const
{
    auto ptr = G_POLLABLE_INPUT_STREAM( _g_input_stream );
    return g_pollable_input_stream_can_poll( ptr );
    return (ptr);
}
//=======================================================================================
//      InputStream
//=======================================================================================


//=======================================================================================
//      OutputStream
//=======================================================================================
NOutputStream::NOutputStream( GOutputStream *s )
    : NObject( gcast_to_gobject(s) )
    , _g_output_stream( s )
{}
//=======================================================================================
ssize_t NOutputStream::write( const void *buffer, size_t count,
                              NCancellable *cancel, NError *err )
{
    static_assert( sizeof(gssize) == sizeof(decltype(write(0,0))), "");
    static_assert( sizeof(gsize)  == sizeof(decltype(count)), "");

    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _NErrorProxy err_proxy( err );

    auto res = g_output_stream_write( _g_output_stream,
                                      buffer, count,
                                      gcancel, err_proxy );
    return res;
}
//=======================================================================================
ssize_t NOutputStream::write( const std::string &msg, NCancellable *cancel, NError *err )
{
    return write( msg.data(), msg.size(), cancel, err );
}
//=======================================================================================
//      OutputStream
//=======================================================================================
