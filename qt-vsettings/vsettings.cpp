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


#include "vsettings.h"

//#include "vdeb.h"
#include <QSettings>
#include <QWidget>

//=======================================================================================
//=======================================================================================
// 		HELPERS
//=======================================================================================
class VSettings::Helper
{
public:
    virtual ~Helper() {}

    virtual QVariant read(const QString &key, const QVariant &default_val) const = 0;
    virtual void write(const QString &key, const QVariant &val) = 0;

    class Root_Helper;
    class Child_Helper;

protected:
    virtual void push_group(const QString &g) = 0;
    virtual void pop_group() = 0;
};
//=======================================================================================
class VSettings::Helper::Root_Helper : public VSettings::Helper
{
    QSettings s;

public:
    //-----------------------------------------------------------------------------------
    Root_Helper(const QString &filename)
        : s( filename, QSettings::IniFormat )
    {
        if( s.status() != QSettings::NoError ) {
            throw std::runtime_error( "Error during opening file ");// << filename
                 //<< ", error code: " << s.status();
            //halt;
        }
    }
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    virtual QVariant read( const QString &key,
                           const QVariant &default_val ) const override final
    {
        return s.value(key, default_val);
    }
    //-----------------------------------------------------------------------------------
    virtual void write(const QString &key, const QVariant &val) override final
    {
        s.setValue(key, val);
        s.sync();
    }
    //-----------------------------------------------------------------------------------


private:
    //-----------------------------------------------------------------------------------
    virtual void push_group(const QString &g) override final
    {
        s.beginGroup(g);
    }
    //-----------------------------------------------------------------------------------
    virtual void pop_group() override final
    {
        s.endGroup();
    }
    //-----------------------------------------------------------------------------------
};
//=======================================================================================
class VSettings::Helper::Child_Helper : public VSettings::Helper
{
    HelperPtr root = 0;
    QString group;

public:
    //-----------------------------------------------------------------------------------
    Child_Helper( HelperPtr root_, const QString &group_ )
        : root ( root_  )
        , group( group_ )
    {}
    //-----------------------------------------------------------------------------------
    virtual void write(const QString &key, const QVariant &val) override final
    {
        root->push_group( group );
        root->write( key, val );
        root->pop_group();
    }
    //-----------------------------------------------------------------------------------
    virtual QVariant read( const QString &key,
                           const QVariant &default_val ) const override final
    {
        root->push_group( group );
        auto res = root->read( key, default_val );
        root->pop_group();
        return res;
    }
    //-----------------------------------------------------------------------------------

private:
    //-----------------------------------------------------------------------------------
    virtual void push_group(const QString &g) override final
    {
        root->push_group(group);
        root->push_group(g);
    }
    //-----------------------------------------------------------------------------------
    virtual void pop_group() override final
    {
        root->pop_group();
        root->pop_group();
    }
    //-----------------------------------------------------------------------------------
};
//=======================================================================================
// 		HELPERS
//=======================================================================================
//=======================================================================================



//=======================================================================================
//=======================================================================================
//		VSETTINGS
//=======================================================================================
VSettings::VSettings()
{}
//=======================================================================================
VSettings::VSettings( const QString &filename )
    : h( new Helper::Root_Helper(filename) )
{}
//=======================================================================================
VSettings::VSettings(HelperPtr root, const QString &group)
    : h( new Helper::Child_Helper( root, group) )
{}
//=======================================================================================
VSettings::~VSettings()
{}
//=======================================================================================
QVariant VSettings::read(const QString &key, const QVariant &default_val) const
{
    Q_ASSERT(h);
    return h->read(key, default_val);
}
//=======================================================================================
void VSettings::write(const QString &key, const QVariant &val)
{
    Q_ASSERT(h);
//    if (!h)
//        vdeb;
    h->write(key, val);
}
//=======================================================================================
VSettings VSettings::subgroup(const QString &group) const
{
    Q_ASSERT(h);
    return VSettings( h, group );
}
//=======================================================================================
VSettings::operator bool() const
{
    return h.use_count();
}
//=======================================================================================
//		VSETTINGS
//=======================================================================================
//=======================================================================================




//=======================================================================================
//=======================================================================================
//		VSETTINGS INTERFACE
//=======================================================================================
VSettings_Interface::VSettings_Interface()
{}
//=======================================================================================
VSettings_Interface::~VSettings_Interface()
{}
//=======================================================================================
void VSettings_Interface::set_settings(const VSettings &settings_)
{
    settings = settings_;
    if (settings) load_settings();
}
//=======================================================================================
void VSettings_Interface::load_settings()
{}
//=======================================================================================
VSettings VSettings_Interface::settings_subgroup(const QString &sg) const
{
    return settings ? settings.subgroup(sg) : VSettings();
}
//=======================================================================================
QVariant VSettings_Interface::setting_read( const QString &key,
                                            const QVariant &default_val ) const
{
    Q_ASSERT(settings);
    //if (!settings) { vdeb; }
    return settings ? settings.read(key, default_val) : QVariant();
}
//=======================================================================================
void VSettings_Interface::setting_write(const QString &key, const QVariant &val)
{
    if (settings)
        settings.write(key, val);
}
//=======================================================================================
//		VSETTINGS INTERFACE
//=======================================================================================
//=======================================================================================

