#ifndef ISHUMI_IMPL_WRITEBUFFER_H
#define ISHUMI_IMPL_WRITEBUFFER_H

#include "ishumi_impl_signature.h"
#include "vstring.h"


//=======================================================================================
namespace ishumi
{
    //===================================================================================
    namespace impl
    {
        //===============================================================================
        class WriteBuffer
        {
        public:
            explicit WriteBuffer( size_t reserve = 0 );

            template<typename T> typename std::enable_if< is_arithmetic<T>(),
            void>::type write( const T& val );

            void write( const std::string& val );

            void write_size( size_t sz );

            const VString& result() const { return _buf; }

        private:
            VString _buf;
        };
        //===============================================================================

        //===== IMPLEMENTATION ==========================================================
        template<typename T> typename std::enable_if< is_arithmetic<T>(),
        void>::type WriteBuffer::write( const T& val )
        {
            _buf.append_LE( val );
        }
        //===== IMPLEMENTATION ==========================================================
    } // namespace impl
    //===================================================================================
} // namespace ishumi
//=======================================================================================


#endif // ISHUMI_IMPL_WRITEBUFFER_H
