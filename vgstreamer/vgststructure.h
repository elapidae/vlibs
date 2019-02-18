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


#ifndef VGSTSTRUCTURE_H
#define VGSTSTRUCTURE_H


/* https://gstreamer.freedesktop.org/data/doc/gstreamer/1.12/gstreamer/
html/GstStructure.html */

//GBoxed
//╰── GstStructure
//=======================================================================================


//=======================================================================================
#include <memory>
#include <vector>
#include <string>
//=======================================================================================


//=======================================================================================
typedef struct _GstStructure GstStructure;
//=======================================================================================


//=======================================================================================
class VGstStructure
{
public:
    //bool has_field( const std::string& fieldname ) const;
    bool has_int_field( const std::string& fieldname ) const;
    bool has_string_field( const std::string& fieldname ) const;

    int get_int( const std::string& fieldname ) const;
    std::string get_string( const std::string& fieldname ) const;

    int get_width()  const;
    int get_height() const;
    std::string get_format() const;

    int fields_count() const;
    std::string field_name( uint idx ) const;
    std::vector<std::string> field_names() const;

    class Loaned;

private:
    friend class VGstCaps;
    static VGstStructure loan( GstStructure* s );

private:
    VGstStructure( GstStructure* gstruct, bool call_free );
    std::shared_ptr<GstStructure> _raw_gst_structure;
    GstStructure *ptr_gst_structure();
    const GstStructure *ptr_gst_structure() const;
};
//=======================================================================================
typedef struct _GstCaps GstCaps;
class VGstStructure::Loaned
{
public:
    VGstStructure& operator()();

private:
    friend class VGstCaps;
    Loaned( const std::weak_ptr<GstCaps>& w, const VGstStructure& s );

    class Pimpl;
    std::shared_ptr<Pimpl> p;
};



#endif // VGSTSTRUCTURE_H
