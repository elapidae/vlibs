#ifndef C_ERRNO_H
#define C_ERRNO_H

#include <string>


//=======================================================================================
//      Сделано для помощи в работе с кодами возврата через errno.
//  Просто обертка под древний механизм, позволяющий извлекать и сохранять номер
//  и текст ошибки.
//=======================================================================================


class C_ErrNo
{
public:
    explicit C_ErrNo( int res_from_c_style_funcs );

    operator bool() const;

    bool has()      const;
    int  err_code() const;

    const std::string &text() const;

private:
    int _err = 0;
    std::string _msg;
};


#endif // C_ERRNO_H
