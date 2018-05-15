#include "vgpioleg.h"

#include <unistd.h>
#include "vfile.h"
#include "vcat.h"


using namespace std;

//=======================================================================================
//          STATIC HELPER DEFINES AND FUNCTIONS
//=======================================================================================
static const string  gpio_path         = "/sys/class/gpio/";
static const auto    export_filename   = gpio_path + "export";
static const auto    unexport_filename = gpio_path + "unexport";
//=======================================================================================
//  Функция делает запись к-л значения в указанный файл и, в случае ошибки, бросает
//  исключение VGpioLeg::Exception.
static void write_to( const std::string &fname, const std::string &what )
{
    VFile f( fname, VFile::WriteOnly );

    if ( !f.open() )
    {
        throw VGpioLeg::Exception( vcat("Cannot open file '", fname, "'.") );
    }

    auto written = f.write_str( what );
    if ( written != int(what.size()) )
    {
        throw VGpioLeg::Exception( vcat("Cannot write '", what, "' ")
                                       ("to file '", fname, "'.") );
    }
}
//=======================================================================================
//          STATIC HELPER DEFINES AND FUNCTIONS
//=======================================================================================



//=======================================================================================
//          GPIO LEG CLASS
//=======================================================================================
VGpioLeg::Exception::Exception( const string &err )
    : runtime_error( err )
{}
//=======================================================================================
VGpioLeg::VGpioLeg( int leg )
    : _leg( leg )
{}
//=======================================================================================
VGpioLeg &VGpioLeg::unexport_leg()
{
    try
    {
        write_to( unexport_filename, vcat(_leg) );
    }
    catch( const Exception& )
    {}
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::export_leg()
{
    write_to( export_filename, vcat(_leg) );
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::set_direction( VGpioLeg::Direction dir )
{
    auto direction = dir == Direction::In ? "in" : "out";
    write_to( vcat(gpio_path)("gpio", _leg)("/direction"), direction );
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::direction_out()
{
    return set_direction( Direction::Out );
}
//=======================================================================================
VGpioLeg &VGpioLeg::direction_in()
{
    return set_direction( Direction::In );
}
//=======================================================================================
VGpioLeg &VGpioLeg::set_value( VGpioLeg::Value val )
{
    auto value = val == Value::Low ? "0" : "1";
    write_to( vcat(gpio_path)("gpio", _leg)("/value"), value );
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::hi()
{
    return set_value( Value::Hi );
}
//=======================================================================================
VGpioLeg &VGpioLeg::low()
{
    return set_value( Value::Low );
}
//=======================================================================================
VGpioLeg &VGpioLeg::usleep( int us )
{
    ::usleep( us );
    return *this;
}
//=======================================================================================
//          GPIO LEG CLASS
//=======================================================================================
