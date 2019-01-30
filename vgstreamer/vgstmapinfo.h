/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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
