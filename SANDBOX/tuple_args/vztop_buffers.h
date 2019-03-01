#ifndef VZTOP_BUFFERS_H
#define VZTOP_BUFFERS_H

#include "vstring.h"
#include "vlog_pretty.h"
#include "vztop_signature.h"


//=======================================================================================
namespace vztop
{
    //===================================================================================
    class ReadBuffer
    {
    public:
        ReadBuffer( VString::ForwardView *view ) : _view(view) {}

        template <typename T>
        inline typename std::enable_if<Signature<T>::is_string(), std::string>::type
        read()
        {
            auto sz = read<uint32_t>();
            return _view->take_str( sz );
        }

        template <typename T>
        inline typename std::enable_if<std::is_arithmetic<T>::value, T>::type
        read()
        {
            return _view->take_LE<T>();
        }

    private:
        VString::ForwardView *_view;
    };


    class WriteBuffer
    {
    public:

        template<typename T>
        inline typename std::enable_if<std::is_arithmetic<T>::value, void>::type
        write( const T& val )
        {
            _buf.append_LE( val );
        }

        void write( const std::string& val )
        {
            uint32_t sz = static_cast<uint32_t>( val.size() );
            _buf.append_LE( sz );
            _buf.append( val );
        }

        const VString& buffer() const { return _buf; }

    private:
        VString _buf;
    };
    //===================================================================================
} // namespace vztop
//=======================================================================================


#endif // VZTOP_BUFFERS_H
