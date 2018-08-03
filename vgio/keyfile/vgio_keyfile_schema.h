#ifndef NKEYFILE_SCHEMA_H
#define NKEYFILE_SCHEMA_H

#include "vgio_keyfile.h"

//=======================================================================================
/*
 *  2018-05-10
 *  UPD 2018-08-02 -- в порядке обновления vlib, перенос в простанство vgio.
 *
 *  KeyFile_Schema -- предназначен для захвата и записи полей из/в KeyFile.
*/
//=======================================================================================



//=======================================================================================
namespace vgio
{
    //===================================================================================
    //      KeyFile_Schema
    //===================================================================================
    class KeyFile_Schema
    {
    public:
        //-------------------------------------------------------------------------------
        //  Объявления, необходимые для интерфейса, сам интерфейс см. ниже.
        //  Общие определения для сокращения записи аргументов.
        using str           = std::string;
        using cstr          = const std::string&;

        using bool_list     = std::vector<bool>;
        using int_list      = std::vector<int>;
        using double_list   = std::vector<double>;
        using string_list   = std::vector<std::string>;

        using cbool_list    = const bool_list&;
        using cint_list     = const int_list&;
        using cdouble_list  = const double_list&;
        using cstr_list     = const string_list&;
        //-------------------------------------------------------------------------------
        // Валидатор, стандартное использование при вызове:
        //      append( ..., comment, {from, to} );
        template<class T> struct validator
        {
            validator  ();
            validator  ( T lo, T hi );
            bool is_ok ( T val ) const;

            T lo, hi;
            bool activated = false;
        };

        //-------------------------------------------------------------------------------
        //  User interface begins here
        //-------------------------------------------------------------------------------
        //  Перед началом использования следует указать первую группу.
        void set_current_group( const std::string &group );

        //-------------------------------------------------------------------------------
        void append( cstr key, bool* dst, bool defval, cstr comment = str() );

        void append( cstr key, int* dst, int defval, cstr comment = str(),
                     validator<int> validat = validator<int>() );

        void append( cstr key, double* dst, double defval, cstr comment = str(),
                     validator<double> validator = validator<double>() );

        void append( cstr key, str* dst, cstr defval, cstr comment = str() );

        //-------------------------------------------------------------------------------
        void append( cstr key, bool_list *dst, cbool_list defval,
                     cstr comment = str() );

        void append( cstr key, int_list *dst, cint_list defval,
                     cstr comment = str() );

        void append( cstr key, double_list *dst, cdouble_list defval,
                     cstr comment = str() );

        void append( cstr key, string_list *dst, cstr_list defval,
                     cstr comment = str() );

        //-------------------------------------------------------------------------------
        /// Устанавливает все заранее перечисленные поля в значения из keyfile.
        /// В случае ошибок, бросит исключение Exception.
        void capture( const KeyFile &kf ) const;

        /// seed -- Затравка для KeyFile. Обычно, в затравке передаю пару строк в начало.
        /// Будьте бдительны и не передавайте ничего, если не знаете что делаете.
        KeyFile build( cstr seed = str() ) const;
        void fill( KeyFile *kf ) const;

        //-------------------------------------------------------------------------------
        //      IMPLEMENTATION
        //-------------------------------------------------------------------------------
        //  Бросается, когда к-л переменная оказалась вне указанного диапазона.
        class ValidateException : public std::runtime_error
        { public: ValidateException( cstr msg ); };
        //-------------------------------------------------------------------------------
        KeyFile_Schema() = default;

        class _value;
        using _value_ptr = std::shared_ptr<_value>;

    private:
        KeyFile_Schema(const KeyFile_Schema &) = delete;
        KeyFile_Schema& operator = (const KeyFile_Schema &) = delete;

        //-------------------------------------------------------------------------------
        std::vector<_value_ptr> _values;
        std::string _cur_group;

        void _check_unique( cstr key, void *dst_ptr ) const;
    };
    //===================================================================================
    //      KeyFile_Schema
    //===================================================================================


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template<class T>
    KeyFile_Schema::validator<T>::validator()
    {}
    //===================================================================================
    template<class T>
    KeyFile_Schema::validator<T>::validator( T lo_, T hi_ )
        : lo( lo_ )
        , hi( hi_ )
        , activated( true )
    {}
    //===================================================================================
    template<class T>
    bool KeyFile_Schema::validator<T>::is_ok( T val ) const
    {
        if ( !activated ) return true;
        return lo <= val && val <= hi;
    }
    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
} // namespace vgio
//=======================================================================================




#endif // NKEYFILE_SCHEMA_H
