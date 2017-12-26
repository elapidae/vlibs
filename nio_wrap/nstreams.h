#ifndef NSTREAMS_H
#define NSTREAMS_H

#include "nobject.h"
#include "ncancellable.h"
#include "nerror.h"
#include "nbytes.h"

//=======================================================================================
class NInputStream : public NObject
{
public:

    ssize_t read( void *buffer, size_t count,
                      NCancellable *cancel = nullptr,
                      NError *err = nullptr );

    NBytes read_bytes( size_t count,
                       NCancellable *cancel = nullptr,
                       NError *err = nullptr );

    NBytes read_bytes_async( size_t count,
                             NCancellable *cancel = nullptr,
                             NError *err = nullptr );



    bool is_pollable() const;

protected:
    NInputStream( GInputStream *istream );

private:
    GInputStream *_g_input_stream;
};
//=======================================================================================
// https://developer.gnome.org/gio/stable/GOutputStream.html
class NOutputStream : public NObject
{
public:

    ssize_t write( const void *buffer, size_t count,
                   NCancellable *cancel = nullptr,
                   NError *err = nullptr );

    ssize_t write( const std::string &msg,
                   NCancellable *cancel = nullptr,
                   NError *err = nullptr );

protected:
    NOutputStream( GOutputStream *s );

private:
    GOutputStream *_g_output_stream;
};
//=======================================================================================



#endif // NSTREAMS_H
