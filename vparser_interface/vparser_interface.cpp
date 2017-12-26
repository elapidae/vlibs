#include "vparser_interface.h"

#include <stdexcept>
//#include "vlogger.h"

using namespace std;


//=======================================================================================
VParser_Interface::~VParser_Interface()
{}
//=======================================================================================


//=======================================================================================
void VParser_Interface::Rotator::append( VParser_Interface *parser )
{
    _parsers.push_back( parser );
}
//=======================================================================================
void VParser_Interface::Rotator::parse( const VByteArray &data )
{
    _buffer.append( data );

    while ( !_buffer.empty() )
    {
        if ( !_parse_one() )
            break;
    }
}
//=======================================================================================
bool VParser_Interface::Rotator::_parse_one()
{
    //vdeb(vlog("here"));
    assert(false);
    // флаг, что хоть один парсер мог бы распарсить.
//    bool can_be_any = false;

//    for ( VParser_Interface *parser: _parsers )
//    {
//        bool enough_len = parser->is_mine() <= _buffer.size();
//        bool maybe_this_parser = enough_len && parser->maybe_mine( _buffer );

//        can_be_any = can_be_any | !enough_len;  // wait about min_len.

//        if ( maybe_this_parser )
//        {
//            return parser->cut( &_buffer );
//        }
//    } // for each parser

//    if (can_be_any)
//        return false;

//    //vwarning( vlog("About to kill durty byte:", hex, int(_buffer.front())) );
//    undefined_symbol( _buffer.front() );
//    _buffer.pop_front();
//    return true;    // any operation was happened.
}
//=======================================================================================


