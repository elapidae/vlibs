#ifndef VSETTINGS_INTERFACE_H
#define VSETTINGS_INTERFACE_H

#include "vsettings.h"

class VSettings_Interface
{
public:
    VSettings_Interface();
    virtual ~VSettings_Interface();

public:
    void set_settings(const VSettings &settings);

protected:
    virtual void load_settings();
    VSettings settings_subgroup(const QString &sg) const;

    QVariant setting_read( const QString &key, const QVariant &default_val = QVariant() ) const;
    void setting_write( const QString &key, const QVariant &val );

private:
    VSettings settings;
};

#endif // VSETTINGS_INTERFACE_H
