#include "nfifo.h"

#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>
#include "c_errno.h"
//#include <fcntl.h>

#include "nfile.h"

using namespace std;



//=======================================================================================
NFifoWriter::NFifoWriter( const std::string &fname )
    : _fifo_name( fname )
{
    C_ErrNo err( mkfifo(fname.c_str(), 0666) );

    if (err) throw runtime_error(err.text());
}
//=======================================================================================
NFileInputStream NFifoWriter::get_stream()
{
    auto f = NFile::for_path( _fifo_name );
    f.create();
    f.input();
    throw std::exception(); // not implemented.
}
//=======================================================================================
//bool NFifoWriter::write(const std::string &str)
//{
//    if (_id <= 0) return false;

//    auto w = ::write( _id, str.c_str(), str.size() );

//    return w == int(str.size());
//}
//=======================================================================================
