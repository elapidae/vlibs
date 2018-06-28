#ifndef VLOGENTRY_H
#define VLOGENTRY_H

#include "vcat.h"
#include "vtimepoint.h"
#include "vbufferforwardreader.h"


//=======================================================================================
class VLogEntry
{
public:

    //-------------------------------------------------------------------------------

    enum class Type { Trace, Dbg, Runlog, Warning, Fatal };

    VLogEntry( Type,
               const std::string &file, int32_t line, const std::string &func,
               const std::string &msg );


    VTimePoint  timestamp() const;

    Type        type()      const;
    std::string str_type()  const;  // 3-х символьное обозначение типа.
    char        char_type() const;  // Односимвольный код типа.

    std::string filename()  const;  // только имя файла (путь отсечен).
    std::string filepath()  const;  // полный путь, обычно ведет к build-папке.

    int32_t     line()      const;

    std::string funcname()  const;

    std::string message()   const;

    bool        is_fatal()  const;  // принципиален только этот флаг.

    //-------------------------------------------------------------------------------

    static VLogEntry deserialize( VBufferForwardReader *reader );
    void serialize( VString *dst ) const;

    //-------------------------------------------------------------------------------

private:
    VTimePoint  _timestmap;

    Type        _type;
    std::string _file;
    int32_t     _line;
    std::string _func;
    std::string _msg;

    friend class VLogger;
    VLogEntry( Type, const std::string &file, int32_t line, const std::string &func);
    void _set_msg( const std::string msg ) { _msg = msg; }
};
//=======================================================================================





#endif // VLOGENTRY_H
