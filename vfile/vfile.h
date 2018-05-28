#ifndef VFILE_H
#define VFILE_H

#include "vbytearray.h"
#include <string>

//=======================================================================================
class VFile final
{
public:

    enum OpenMode
    {
        ReadOnly,
        WriteOnly,      // truncate file to 0 size.
        ReadWrite
    };

    [[deprecated]]
    VFile( const std::string &fname = std::string(), OpenMode mode = ReadOnly );
    virtual ~VFile();

    int last_errno() const;

    void set_filename( const std::string &fname );
    void set_mode( OpenMode mode );

    bool is_open() const;

    bool open();
    bool open_with( const std::string &fname, OpenMode mode );
    bool open_with_filename( const std::string &fname );
    bool open_with_mode( OpenMode mode );

    void close();

    //  < 0 on error.
    ssize_t write( const VByteArray &data );
    ssize_t write_str( const std::string &data );

    template<typename Container>
    ssize_t write_any( const Container &data )
    { return write( VByteArray(data.cbegin(), data.cend()) ); }

    ssize_t read(char *buf, int maxlen );
    VByteArray read_all();

private:
    int _handle = 0;
    std::string _filename;
    OpenMode _mode = ReadOnly;

    int _last_error = 0;

    VFile(const VFile &) = delete;
    const VFile &operator =(const VFile &) = delete;
};
//=======================================================================================


#endif // VFILE_H
