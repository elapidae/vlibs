#ifndef ISHUMI_SERIAL_TYPE_TRAITS_H
#define ISHUMI_SERIAL_TYPE_TRAITS_H

#include "ishumi_impl_signature.h"


namespace ishumi
{
    //===================================================================================
    namespace serial
    {
        //===============================================================================
        //  Все сериализуемые типы делятся на четыре группы:
        //  Simple -- std::ariphmetic или std::string
        // Используется для специализации структур записи и чтения.
        enum class Type_Spec { Simple, Vector, Serialized, Tuple, Undefined };
        template<typename T> static constexpr Type_Spec type_spec();
        //===============================================================================


        template<typename T, Type_Spec>
        struct MinSize;

        template<typename T>
        struct MinSize<T,Type_Spec::Simple>
        {
            static constexpr uint minsize()
            {
                //  Странный выбор размера для строки продиктован, что строки,
                //  скорее всего, будут небольшими, но не пустыми.
                return impl::is_string<T>() ? 4 : sizeof(T);
            }
        };

        template<typename T>
        struct MinSize<T,Type_Spec::Tuple>
        {
            static constexpr uint minsize()
            {
                //  Странный выбор размера для строки продиктован, что строки,
                //  скорее всего, будут небольшими, но не пустыми.
                return impl::is_string<T>() ? 4 : sizeof(T);
            }
        };


        template<typename T>
        struct Helper
        {
            static constexpr Type_Spec type_spec();
        };

    } // namespace serial
} // namespace ishumi

#endif // ISHUMI_SERIAL_TYPE_TRAITS_H
