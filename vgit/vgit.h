#ifndef VGIT_H
#define VGIT_H

#include <string>


//=======================================================================================
class VGit
{
public:
    static std::string revcount();
    static std::string hash();
    static std::string date();
    static std::string author();
    static std::string branch();

    // Слон, к сожалению, из коробки не взлетел. Причина пока непонятна.
    //static std::string comment();

    // Метка времени компиляции.
    // К git отношения не имеет, но где-то надо хранить...
    static std::string compile_datetime();

    // принимает --vgit-branch, --vgit-hash, --vgit-revcount, --vgit-date, vgit-author,
    //           --vgit-full.
    // Возвращает, соответственно. По умолчанию и при ошибках использует --vgit-full
    static std::string as_message( const std::string &query = "--vgit-full" );

    // ищет параметры вида --vgit*, если найдет, печатает соответствующее сообщение
    // и выходит по exit(retcode);
    static void print_and_exit_if_need( int argc,
                                        const char * const * const argv,
                                        int retcode = 0 );
};
//=======================================================================================


#endif // VGIT_H
