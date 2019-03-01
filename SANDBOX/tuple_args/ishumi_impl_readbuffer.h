#ifndef ISHUMI_IMPL_READBUFFER_H
#define ISHUMI_IMPL_READBUFFER_H

#include "ishumi_impl_signature.h"
#include "vstring.h"


//=======================================================================================
namespace ishumi
{
    //===================================================================================
    namespace impl
    {
        //===============================================================================
        class ReadBuffer
        {
        public:
            ReadBuffer( const VString& buf );
            bool finished() const;

            template <typename T> typename std::enable_if< is_string<T>(),
            std::string>::type read();

            template <typename T> typename std::enable_if< is_arithmetic<T>(),
            T>::type read();

            uint32_t read_size();

        private:
            VString _buf;
            VString::ForwardView _view;
        };
        //===============================================================================

        //===== IMPLEMENTATION ==========================================================
        template <typename T> typename std::enable_if<is_string<T>(),
        std::string>::type ReadBuffer::read()
        {
            auto sz = read_size();
            return _view.take_str( sz );
        }
        //===============================================================================
        template <typename T> typename std::enable_if<is_arithmetic<T>(),
        T>::type ReadBuffer::read()
        {
            return _view.take_LE<T>();
        }
        //===== IMPLEMENTATION ==========================================================
    } // namespace impl
    //===================================================================================
} // namespace ishumi
//=======================================================================================


#endif // ISHUMI_IMPL_READBUFFER_H
