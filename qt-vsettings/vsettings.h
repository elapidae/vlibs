#ifndef VSETTINGS_H
#define VSETTINGS_H

/**
        VSettings -- Модуль для адекватного сохранения настроек внутри всяких там виджетов.
    Предназначен для того, чтобы настройки виджетов не пересекались, каждый объект в
    динамической иерархии может свободно сохранять свои настройки, не заботясь об
    уникальности полей. Также, создавая объекты, которые тоже хотят что-нибудь похранить,
    может передавать им subgroup(name) а они уже будут работать с полями только внутри
    своей группы.

        Использует безопасные указатели. Можно использовать при удалении
    родителей.

		VSettings_Interface -- Подмешиваемый класс, позволяющий сохраняться удобнее.
	Перегружайте метод load_settings() для загрузки своих параметров. 
	Сохраняйте параметры в деструкторе.
		Вызов методов четния и записи безопасно, ничего проверйть не надо.
**/

#include <QString>
#include <QVariant>

#include <memory> // for std::shred_ptr

//================================================================================================
class VSettings
{
public:
    VSettings();
    explicit VSettings( const QString &filename );
    virtual ~VSettings();

    QVariant read( const QString &key, const QVariant &default_val = QVariant() ) const;
    void write( const QString &key, const QVariant &val );

    VSettings subgroup( const QString &group ) const;

    explicit operator bool() const;

private:
    class Helper;
    typedef std::shared_ptr<Helper> HelperPtr;
    HelperPtr h;

    VSettings( HelperPtr root, const QString &group );
};
//================================================================================================


//================================================================================================
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
//================================================================================================

#endif // VSETTINGS_H
