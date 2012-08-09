/****************************************************************************
** amaroK::PluginConfig meta object code from reading C++ file 'pluginconfig.h'
**
** Created: Tue Feb 19 15:56:34 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "pluginconfig.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *amaroK::PluginConfig::className() const
{
    return "amaroK::PluginConfig";
}

QMetaObject *amaroK::PluginConfig::metaObj = 0;
static QMetaObjectCleanUp cleanUp_amaroK__PluginConfig( "amaroK::PluginConfig", &amaroK::PluginConfig::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString amaroK::PluginConfig::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "amaroK::PluginConfig", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString amaroK::PluginConfig::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "amaroK::PluginConfig", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* amaroK::PluginConfig::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"save", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "save()", &slot_0, QMetaData::Public }
    };
    static const QUMethod signal_0 = {"viewChanged", 0, 0 };
    static const QUMethod signal_1 = {"settingsSaved", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "viewChanged()", &signal_0, QMetaData::Private },
	{ "settingsSaved()", &signal_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"amaroK::PluginConfig", parentObject,
	slot_tbl, 1,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_amaroK__PluginConfig.setMetaObject( metaObj );
    return metaObj;
}

void* amaroK::PluginConfig::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "amaroK::PluginConfig" ) )
	return this;
    return QObject::qt_cast( clname );
}

// SIGNAL viewChanged
void amaroK::PluginConfig::viewChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

// SIGNAL settingsSaved
void amaroK::PluginConfig::settingsSaved()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

bool amaroK::PluginConfig::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: save(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool amaroK::PluginConfig::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: viewChanged(); break;
    case 1: settingsSaved(); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool amaroK::PluginConfig::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool amaroK::PluginConfig::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
