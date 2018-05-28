#ifndef VLOGGER_H
#define VLOGGER_H

#include "vlogentry.h"


//=======================================================================================
class VLogger final : public _vcat_iface<VLogger>
{
public:

    //-------------------------------------------------------------------------------
    using Executer = std::function<void(const VLogEntry &entry)>;

    // Предназначен для создания из макросов.
    VLogger( VLogEntry::Type,
             const std::string &file, int32_t line, const std::string &func );

    enum class _is_proxy { is_proxy };
    VLogger( VLogEntry::Type,
             const std::string &file, int32_t line, const std::string &func,
             _is_proxy );

    VLogEntry cur_entry() const;
    operator VLogEntry()  const;

    //-------------------------------------------------------------------------------
    // Здесь регистрируются обработчики, исполнители вхождений логов.
    // NB! throw_on_fatal(on) было удалено, от него больше вреда, чем пользы.
    // Вместо подобных "трюков" следует "честно" бросать исключения.
    // В vlog_pretty.h определен класс VLogError : public std::exception,
    // которым можно пользоваться, например, так: throw VLogError( vfatal << "msg" );
    static void add_executer( Executer e );
    static void clear_executers();
    static void execute( const VLogEntry &entry );


    static void _log_to_cout( const VLogEntry &entry );
    static void _log_to_cerr( const VLogEntry &entry );

    //-------------------------------------------------------------------------------

    ~VLogger();

    VLogger( VLogger && )               = default;
    VLogger& operator = ( VLogger && )  = default;

    VLogger( const VLogger & )              = delete;
    VLogger& operator = ( const VLogger & ) = delete;

    //-------------------------------------------------------------------------------
private:
    VLogEntry _entry;
    vcat      _cat;
    bool      _i_am_proxy = false;

    friend class _vcat_iface<VLogger>;
    template<typename T> void do_cat( const T& val ) { _cat.cat(val); }
};
//=======================================================================================







#endif // VLOGGER_H
