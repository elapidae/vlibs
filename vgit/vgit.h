#ifndef VGIT_H
#define VGIT_H

#include <string>


class VGit
{
public:
    static std::string hash();
    static std::string branch();
    static std::string revcount();

    // Метка времени компиляции.
    // К git отношения не имеет, но где-то надо хранить...
    static std::string compile_datetime();

    // принимает --vgit-branch, --vgit-hash, --vgit-revcount, --vgit-full
    // возвращает, соответственно. По умолчанию и при ошибках использует --vgit-full
    static std::string as_message( const std::string &query = "--vgit-full" );

    // ищет параметры вида --vgit*, если найдет, печатает соответствующее сообщение
    // и выходит по exit(retcode);
    static void print_and_exit_if_need( int argc, char **argv, int retcode = 0 );
};



#endif // VGIT_H
