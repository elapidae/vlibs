#ifndef VGSTBIN_H
#define VGSTBIN_H


//=======================================================================================
// https://gstreamer.freedesktop.org/data/doc/gstreamer/1.13/gstreamer/html/GstBin.html

//GObject
//╰── GInitiallyUnowned
//    ╰── GstObject
//        ╰── GstElement
//            ╰── GstBin
//                ╰── GstPipeline
//=======================================================================================


//=======================================================================================
#include "vgstelement.h"
//=======================================================================================


//=======================================================================================
typedef struct _GstBin GstBin;
//=======================================================================================


//=======================================================================================
class VGstBin : public VGstElement
{
public:
    explicit VGstBin( const std::string& name = {} );

    void add( VGstElement* elem );

    template< typename ... Elems >
    void add( VGstElement* elem1, Elems* ... elems );

protected:
    VGstBin( GstBin* raw );

private:
    GstBin* _raw_gst_bin;
};
//=======================================================================================


//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template< typename ... Elems >
void VGstBin::add( VGstElement* elem1, Elems* ... elems )
{
    add( elem1 );
    add( elems... );
}
//=======================================================================================


#endif // VGSTBIN_H
