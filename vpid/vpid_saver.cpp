#include "vpid_saver.h"

#include <unistd.h>
#include "voutfile.h"
#include "vlog_pretty.h"
#include "vdir.h"

//=======================================================================================
VPid_Saver::VPid_Saver( const std::string &path, const std::string &fname )
    : _fname( path + "/" + fname )
{
    system( ("mkdir -p " + path).c_str() );

    if ( path.empty() || fname.empty() )
        vfatal.nospace() << "Путь или имя файла для сохранения PID процесса пусты.";

    VOutFile f(_fname);
    f.write( vcat(getpid()) );

    if ( !f.is_good() )
        vfatal.nospace() << "Ошибка сохранения PID процесса в файле '" << _fname << "'.";
}
//=======================================================================================
VPid_Saver::~VPid_Saver()
{
    std::remove( _fname.c_str() );
}
//=======================================================================================
__pid_t get_pid()
{
    return ::getpid();
}
//=======================================================================================
