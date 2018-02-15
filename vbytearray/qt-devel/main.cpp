#include "mainwindow.h"
#include <QApplication>

#include "vbytearray.h"

#include "vlogger.h"
#include <complex>

#include "vbitarray.h"

using namespace std;

struct A
{
    int i;
};

int main(int argc, char *argv[])
{
    VBitArray ti( string(1, 0x1b) );


    for (int i = 0; i < 8; ++i)
    {
        ti = string(1, i); ti.pop_i(5);
        vdeb(vlog(ti.pop_i(3)));
    }
    vdeb(vlog("----------------------------"));
    for (int i = 0; i < 8; ++i)
    {
        ti = string(1, i); ti.pop_i(5);
        vdeb(vlog(ti.pop_i_dop(3)));
    }
    vdeb(vlog("----------------------------"));
    for (int i = 0; i < 8; ++i)
    {
        ti = string(1, i); ti.pop_i(5);
        vdeb(vlog(ti.pop_u(3)));
    }
    vdeb(vlog("----------------------------"));
    for (int i = 0; i < 8; ++i)
    {
        ti = string(1, i); ti.pop_i(5);
        vdeb(vlog(ti.pop_u_dop(3)));
    }
    return 0;

    //VBitArray ti( string(1, 0x1b) );
    vdeb(vlog(ti.pop_i(2)));
    vdeb(vlog(ti.pop_i(2)));
    vdeb(vlog(ti.pop_i(2)));
    vdeb(vlog(ti.pop_i(2)));
    return 0;


    VBitArray bd( string(1, 11));
    vdeb(vlog(bd.pop_i_dop(2)));
    vdeb(vlog(bd.pop_u_dop(6)));
    return 0;

    VByteArray arr("hello world   ddd     ddwww   456   ");

    vdeb(vlog(hex, arr.front_BE<int64_t>()));
    vdeb(vlog(hex, arr.front_LE<int64_t>()));

    auto reader = arr.get_forward_reader();

    vdeb(vlog(reader.pop_LE<int>()));
    vdeb(vlog(reader.pop_LE<char>()));
    vdeb(vlog(reader.pop_BE<uint16_t>()));
    vdeb(vlog(reader.pop_LE<long long>()));
    vdeb(vlog(reader.pop_str(3)));
    arr.chop_to_position( reader );
    vdeb(vlog(arr));

    VBitArray bits( arr );

//    vdeb(vlog(bits.pop(1)));
//    vdeb(vlog(bits.pop(2)));
//    vdeb(vlog(bits.pop(3)));
//    vdeb(vlog(bits.pop(4)));
//    vdeb(vlog(bits.pop(5)));
//    vdeb(vlog(bits.pop(6)));
//    vdeb(vlog(bits.pop(7)));
//    vdeb(vlog(bits.pop(8)));
//    vdeb(vlog(bits.pop(9)));
//    vdeb(vlog(bits.pop(12)));
//    vdeb(vlog(bits.pop(19)));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return 0;
    return a.exec();
}
