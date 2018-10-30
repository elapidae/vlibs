#ifndef VGSTMAPINFO_H
#define VGSTMAPINFO_H


// https://developer.gnome.org/gstreamer/1.0/gstreamer-GstMemory.html#GstMapInfo


#include <memory>


struct _will_GstMapInfo;
typedef struct _GstBuffer GstBuffer;


class VGstMapInfo final
{
public:
    ssize_t ssize() const;
    size_t  size()  const;
    const u_char* raw_data() const;

    bool flag_read()  const;
    bool flag_write() const;

private:
    friend class VGstBuffer;
    static VGstMapInfo do_map_read( const std::shared_ptr<GstBuffer>& sbuf );

    explicit VGstMapInfo( const std::weak_ptr<GstBuffer>& wbuf );
    std::shared_ptr<_will_GstMapInfo> _raw_map_info;
};


#endif // VGSTMAPINFO_H
