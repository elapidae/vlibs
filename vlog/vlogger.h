#ifndef VLOGGER_H
#define VLOGGER_H

#include "vlogentry.h"


//=======================================================================================
class VLogError;
namespace vlog
{
    //===================================================================================
    class VLogger final : public _vcat_iface<VLogger>
    {
    public:

        //-------------------------------------------------------------------------------
        using Executer = std::function<void(const VLogEntry &entry)>;

        // Предназначен для создания из макросов.
        VLogger( VLogEntry::Type,
                 const std::string &file, int32_t line, const std::string &func );

        //-------------------------------------------------------------------------------
        // Здесь регистрируются обработчики, исполнители вхождений логов.
        static void add_executer( Executer e );
        static void clear_executers();
        static void execute( const VLogEntry &entry );
        static void exit_on_fatal( bool on );

        static void _log_to_cout( const VLogEntry &entry );
        static void _log_to_cerr( const VLogEntry &entry );
        static void _do_exit_on_fatal( const VLogEntry &entry );

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

        friend class _vcat_iface<VLogger>;
        template<typename T> void do_cat( const T& val ) { _cat.cat(val); }

        friend class ::VLogError;
        VLogEntry _get_cur_entry() const;
    };
    //===================================================================================
} // vlog namespace
//=======================================================================================







#endif // VLOGGER_H
