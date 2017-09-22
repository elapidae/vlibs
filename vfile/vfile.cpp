#include "vfile.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <vector>

template<typename Test>
class TestType;


static const size_t TheBufferLen = 4096;



//=======================================================================================
VFile::VFile(const std::string &fname, VFile::OpenMode mode)
    : _filename( fname )
    , _mode( mode )
{}
//=======================================================================================
VFile::~VFile()
{
    close();
}
//=======================================================================================
int VFile::last_errno() const
{
    return _last_error;
}
//=======================================================================================
void VFile::set_filename( const std::string &fname )
{
    _filename = fname;
}
//=======================================================================================
void VFile::set_mode( VFile::OpenMode mode )
{
    _mode = mode;
}
//=======================================================================================
bool VFile::is_open() const
{
    return _handle > 0;
}
//=======================================================================================
// http://www.opennet.ru/man.shtml?category=2&topic=open
//
//O_CREAT
//    (если файл не существует, то он будет создан. Владелец (идентификатор пользователя) файла устанавливается в значение эффективного идентификатора пользователя процесса. Группа (идентификатор группы) устанавливается либо в значение эффективного идентификатора группы процесса, либо в значение идентификатора группы родительского каталога (зависит от типа файловой системы, параметров подсоединения (mount) и режима родительского каталога, см. например, параметры подсоединения bsdgroups и sysvgroups файловой системы ext2, как описано в руководстве mount(8)).);
//
//O_NOCTTY
//    (если pathname указывает на терминальное устройство --- см. tty(4) ---,
//то оно не станет терминалом управления процесса, даже если процесс такового не имеет);
//
//O_TRUNC
//    (если файл уже существует, он является обычным файлом и режим позволяет записывать в этот файл (т.е. установлено O_RDWR или O_WRONLY), то его длина будет урезана до нуля. Если файл является каналом FIFO или терминальным устройством, то этот флаг игнорируется. Иначе действие флага O_TRUNC не определено.
//
//O_LARGEFILE
//    (На 32-битных системах, поддерживающих файловые системы (Large), этот флаг позволяет открывать файлы, длина которых больше 31-ого бита.
bool VFile::open()
{
    if (is_open()) close();

    auto flags = _mode == ReadOnly
                    ? O_RDONLY
                    : _mode == WriteOnly
                        ? O_WRONLY
                        : O_RDWR;

    flags |= O_NOCTTY;
    flags |= O_CREAT;
    flags |= O_LARGEFILE;

    if (_mode == WriteOnly)
    {
        flags |= O_TRUNC;
    }

    auto mode = 0644;   // восьмерично, если не понятно -- ткните автора, чтобы доделал.

    _handle = ::open( _filename.c_str(), flags, mode );
    _last_error = _handle <= 0 ? errno : 0;

    return _handle > 0;
}
//=======================================================================================
bool VFile::open_with( const std::string &fname, VFile::OpenMode mode )
{
    _filename = fname;
    _mode = mode;
    return open();
}
//=======================================================================================
bool VFile::open_with_filename( const std::string &fname )
{
    _filename = fname;
    return open();
}
//=======================================================================================
bool VFile::open_with_mode( VFile::OpenMode mode )
{
    _mode = mode;
    return open();
}
//=======================================================================================
//bool VFile::create()
//{
//    assert( _mode != ReadOnly );

//    if (is_open()) close();

//    auto flags = _mode == WriteOnly
//                        ? O_WRONLY
//                        : O_RDWR;

//    flags |= O_NOCTTY;
//    flags |= O_LARGEFILE;
//    flags |= O_CREAT;
//    flags |= O_TRUNC;

//    auto mode = 0644;   // восьмерично, если не понятно -- ткните автора, чтобы доделал.

//    _handle = ::open( _filename.c_str(), flags, mode );
//    _last_error = _handle <= 0 ? errno : 0;

//    return _handle > 0;
//}
//=======================================================================================
void VFile::close()
{
    if (_handle > 0)
        ::close( _handle );

    _handle = 0;
    _last_error = 0;
}
//=======================================================================================
ssize_t VFile::write( const VByteArray &data )
{
    auto has_write = ::write( _handle, data.data(), data.size() );

    if ( has_write != int(data.size()) )
        _last_error = errno;

    return has_write;
}
//=======================================================================================
ssize_t VFile::write_str( const std::string &data )
{
    return write( VByteArray(data) );
}
//=======================================================================================
ssize_t VFile::read( char *buf, int maxlen )
{
    auto has_read = ::read( _handle, buf, maxlen );

    if (has_read < 0)
        _last_error = errno;

    return has_read;
}
//=======================================================================================
VByteArray VFile::read_all()
{
    VByteArray buffer( TheBufferLen );
    VByteArray res;

    while (1)
    {
        auto has_read = read( buffer.data(), buffer.size() );
        if ( has_read < 0)
            break;

        res.append( buffer.begin(), buffer.begin() + has_read );

        if ( has_read < int(TheBufferLen) )
            break;
    }
    return res;
}
//=======================================================================================
