#ifndef NFILE_H
#define NFILE_H

#include <gio/gio.h>
#include "nstreams.h"
#include "nfileinfo.h"

//=======================================================================================
class NFileInputStream : public NInputStream
{
public:

    //GFileInputStream *RAW() { return p.get(); }

private:
    friend class NFile;
    NFileInputStream( GFileInputStream *s );
    //std::shared_ptr<GFileInputStream> p;
};
//=======================================================================================

//=======================================================================================
class NFileOutputStream : public NOutputStream
{
public:
protected:
private:
    friend class NFile;
    NFileOutputStream( GFileOutputStream *s );
    //GFileOutputStream *s
};
//=======================================================================================

//=======================================================================================
class NFile
{
public:
    bool is_valid() const { return bool(p); }

    // Ommited ctors:
    // g_file_new_tmp() to create a temporary file from a template.
    // g_file_parse_name() from a UTF-8 string gotten from g_file_get_parse_name().
    static NFile for_path ( const std::string &path );
    static NFile for_uri  ( const std::string &uri  );

    static NFile for_commandline_arg( const char * arg ); // abs path / rel path / uri...

    std::string get_parse_name() const;

    std::string get_basename() const;

    std::string get_path() const;

    NFile get_parent() const;

    NFileInputStream input( NCancellable *cancel = nullptr, NError *err = nullptr );

    NFileOutputStream create  ( GFileCreateFlags flags = G_FILE_CREATE_NONE,
                                NCancellable *cancel = nullptr,
                                NError *err = nullptr );
    NFileOutputStream replace ( GFileCreateFlags flags = G_FILE_CREATE_NONE,
                                NCancellable *cancel = nullptr,
                                NError *err = nullptr );
    NFileOutputStream append  ( GFileCreateFlags flags = G_FILE_CREATE_NONE,
                                NCancellable *cancel = nullptr,
                                NError *err = nullptr );

    NFileInfo query_info( NCancellable *cancel = nullptr, NError *err = nullptr ) const;

private:
    NFile( GFile *f ) : p( f, NFile::_unref ) {}
    std::shared_ptr<GFile> p;
    static void _unref( void *ptr ) { if (ptr) g_object_unref(ptr); }
};
//=======================================================================================




#endif // NFILE_H
