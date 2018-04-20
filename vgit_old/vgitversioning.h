#ifndef VGITVERSIONING_H
#define VGITVERSIONING_H

#include <string>


class VGitVersioning
{
public:

    static std::string  hash();
    static std::string  branch();
    static int          revcount();

    // принимает --vgit-branch, --vgit-hash, --vgit-revcount, --vgit-full
    // возвращает, соответственно. По умолчанию и при ошибках использует --vgit-full
    static std::string as_message( const std::string &query = "--vgit-full" );

    // ищет параметры вида --vgit*, если найдет, печатает соответствующее сообщение
    // и выходит по exit(0);
    static void print_and_exit_if_need( int argc, char **argv );
};



#endif // VGITVERSIONING_H
