#ifndef NFIFO_H
#define NFIFO_H

#include <string>

#include "nstreams.h"
#include "nfile.h"

class NFifoWriter
{
public:
    NFifoWriter( const std::string &fname );

    NFileInputStream get_stream();
    //bool write( const std::string &str );

private:
    int _id;
    std::string _fifo_name;
};


class NFifoReader
{
public:
    explicit NFifoReader();
    //explicit NFifoReader( const  );
};



#endif // NFIFO_H
