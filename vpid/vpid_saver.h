#ifndef VPID_SAVER_H
#define VPID_SAVER_H


#include <string>

//=======================================================================================
__pid_t get_pid();
//=======================================================================================


//=======================================================================================
class VPid_Saver final
{
public:
    VPid_Saver( const std::string &path, const std::string &fname );
    ~VPid_Saver();

private:
    const std::string _fname;
};
//=======================================================================================


#endif // VPID_SAVER_H
