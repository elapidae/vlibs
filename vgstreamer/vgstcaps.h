#ifndef VGSTCAPS_H
#define VGSTCAPS_H

#include <memory>
#include "vgststructure.h"


typedef struct _GstCaps     GstCaps;
typedef struct _GstSample   GstSample;


class VGstCaps
{
public:
    static GstCaps* new_simple( const std::string& media_name );

    static VGstCaps application_x_rtp();
    static VGstCaps video_x_raw();
    VGstCaps( const std::string& media_name );

    void set_simple( const std::string& field_name, int val );
    void set_simple( const std::string& field_name, const std::string& val );

    void set_encoding_name( const std::string& ename ); // H264
    void set_payload( int payload );    // 96, 127 -- dont know what is it...

    void set_format( const std::string& fmt ); // RGB
    void set_format_RGB();

    //  Структуры отсюда нельзя копировать или аккумулировать.
    //  Только посмотреть одну за раз.
    uint struct_count() const;
    const VGstStructure::Loaned struct_at( uint idx ) const;

    std::string to_string() const;

//    class Loaned;

private:
    friend class VGstSample;
    VGstCaps( GstCaps* caps );

    friend class VGObject;
    GstCaps* ptr_gst_caps();
    const GstCaps* ptr_gst_caps() const;

    std::shared_ptr<GstCaps> _raw_gst_caps;
};

//class VGstCaps::Loaned
//{
//public:

//private:
//    Loaned( std::weak_ptr<GstSample> owner_sample, const VGstCaps& caps );
//};


#endif // VGSTCAPS_H
