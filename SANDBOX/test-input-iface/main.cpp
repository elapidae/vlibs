#include "mainwindow.h"
#include <QApplication>



#include <stdint.h>

#include <linux/input.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "vlog_qt.h"
#include "vposix_input_texts.h"

#include "vapplication.h"
#include "vpoll/vpoll.h"

#include "vgio_keyfile_schema.h"

#include <linux/input.h>

using namespace std::chrono;

class Config
{
public:
    double x, y, z;

    Config( const std::string& fname )
    {
        vgio::KeyFile_Schema shema;

        shema.set_current_group("Route");
        shema.append( "X", &x, 0 );
        shema.append( "Y", &y, 0 );
        shema.append( "Z", &z, 0 );

        auto kf = vgio::KeyFile::from_file( fname );
        shema.capture( kf );
    }

//    void write_default_to_file( const std::string& str )
//    {
//        vgio::KeyFile kf;
//        shema.fill( &kf );

//    }
};




#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)


class EvPoll : public VPoll::EventReceiver
{
    const int fd = -1;

public:
    EvPoll( int fd) : fd(fd)
    {
        VPoll::add_fd( fd, this );
    }
    ~EvPoll() override
    {
        VPoll::del_fd( fd );
    }

    void event_received( VPoll::EventFlags flags ) override
    {
        assert( flags.take_IN() );
        assert( flags.empty() );

        struct input_event ev[64];
        auto rd = read(fd, ev, sizeof(struct input_event) * 64);

        if (rd < (int) sizeof(struct input_event))
        {
            printf("yyy\n");
            perror("\nevtest: error reading");
            exit(1);
        }

        for ( auto i = 0; i < rd / sizeof(struct input_event); i++)
        {
            if (ev[i].type == EV_SYN) {
                printf("Event: time %ld.%06ld, -------------- %s ------------\n",
                    ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].code ? "Config Sync" : "Report Sync" );
            } else if (ev[i].type == EV_MSC && (ev[i].code == MSC_RAW || ev[i].code == MSC_SCAN)) {
                vdeb("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %02x\n",
                    ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,
                    events()[ev[i].type],
                    ev[i].code,
                    names()[ev[i].type][ev[i].code],
                    ev[i].value);
            } else {
                vdeb("Event: time ",
                        VTimePoint( seconds(ev[i].time.tv_sec) +
                                    microseconds(ev[i].time.tv_usec)),
                    ev[i].time.tv_sec, ev[i].time.tv_usec,
                     ev[i].type,
                    events()[ev[i].type],
                    ev[i].code,
                    names()[ev[i].type] [ev[i].code],
                    ev[i].value);
            }
        } // for all ev[i]

    } // event received
};

//EV_MAX + 1
void test(std::string evname)
{
    vdeb << "==========================================================================";
    vdeb << "About " << evname;
    int fd;
    if ((fd = open(evname.c_str(), O_RDONLY)) < 0) {
        perror("evtest");
        exit(1);
    }

    int version;
    if (ioctl(fd, EVIOCGVERSION, &version)) {
        perror("evtest: can't get version");
        exit(1);
    }

    printf("Input driver version is %d.%d.%d\n",
        version >> 16, (version >> 8) & 0xff, version & 0xff);


    unsigned short id[4];
    ioctl(fd, EVIOCGID, id);
    printf("Input device ID: bus 0x%x vendor 0x%x product 0x%x version 0x%x\n",
        id[ID_BUS], id[ID_VENDOR], id[ID_PRODUCT], id[ID_VERSION]);


    char name[256] = "Unknown";
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Input device name: \"%s\"\n", name);

    unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
    memset(bit, 0, sizeof(bit));
    ioctl(fd, EVIOCGBIT(0, EV_MAX), bit[0]);
    printf("Supported events:\n");

    for (auto i = 0u; i < EV_MAX; i++)
    {

        if (test_bit(i, bit[0]))
        {
            vdeb << "  Event type" << i << events()[i];

            if (!i) continue; // <<--- WTF ???????????
            ioctl(fd, EVIOCGBIT(i, KEY_MAX), bit[i]);
            for (auto j = 0u; j < KEY_MAX; j++)
            {
                if (test_bit(j, bit[i]))
                {
                    try {
                        vdeb << "Event code of" << i << j << names().at(i).at(j);
                    } catch (std::out_of_range) {
                        vdeb << "BAD EVENT CODE OF:" << i << j;
                    }

                    if (i == EV_ABS)
                    {
                        int abs[5];
                        ioctl(fd, EVIOCGABS(j), abs);
                        for (auto k = 0u; k < 5; k++)
                            if ((k < 3) || abs[k])
                                vdeb << "      " << absval()[k] << abs[k];
                    }
                }
            }
        }
    }

    printf("Testing ... (interrupt to exit)\n");

//    new EvPoll( fd );
//    while (1)
//    {
//    } // while(1);
}
//=======================================================================================



int main(int argc, char *argv[])
{
//    for (int i = 0; i <= 16; ++i)
//        test( vcat("/dev/input/event", i) );
//    return 0;

    VApplication app( argc, argv );

    Config conf("test.conf");
    vdeb << conf.x << conf.y << conf.z;

    std::string fname = "/dev/input/event5";
    if ( app.args().remain().size() > 0 )
        fname = app.args().remain().at(0);

    int fd;
    if ((fd = open(fname.c_str(), O_RDONLY)) < 0) {
        perror("evtest");
        exit(1);
    }

    EvPoll evpoll( fd );

    //test( "/dev/input/event4" );
    app.poll();
    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
