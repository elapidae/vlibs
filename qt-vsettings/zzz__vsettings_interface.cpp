#include "vsettings_interface.h"

#include <QWidget>

//================================================================================================
VSettings_Interface::VSettings_Interface()
{}
//================================================================================================
VSettings_Interface::~VSettings_Interface()
{
    if (!settings) return;

    QWidget *as_widget = dynamic_cast<QWidget*>(this);
    if (as_widget)
        setting_write( "geometry", as_widget->saveGeometry() );
}
//================================================================================================
void VSettings_Interface::set_settings(const VSettings &settings_)
{
    settings = settings_;
    if (settings) load_settings();
}
//================================================================================================
void VSettings_Interface::load_settings()
{
    QWidget *as_widget = dynamic_cast<QWidget*>(this);
    if (as_widget)
        as_widget->restoreGeometry( setting_read("geometry").toByteArray() );
}
//================================================================================================
VSettings VSettings_Interface::settings_subgroup(const QString &sg) const
{
    return settings ? settings.subgroup(sg) : VSettings();
}
//================================================================================================
QVariant VSettings_Interface::setting_read(const QString &key, const QVariant &default_val) const
{
    return settings ? settings.read(key, default_val) : QVariant();
}
//================================================================================================
void VSettings_Interface::setting_write(const QString &key, const QVariant &val)
{
    if (settings)
        settings.write(key, val);
}
//================================================================================================
