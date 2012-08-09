/****************************************************************************
** StdinReader meta object code from reading C++ file 'stdinreader.h'
**
** Created: Tue Feb 19 15:57:12 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "stdinreader.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StdinReader::className() const
{
    return "StdinReader";
}

QMetaObject *StdinReader::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StdinReader( "StdinReader", &StdinReader::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StdinReader::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StdinReader", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StdinReader::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StdinReader", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StdinReader::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"dataRecieved", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "dataRecieved()", &slot_0, QMetaData::Public }
    };
    static const QUMethod signal_0 = {"openWindow", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "openWindow()", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"StdinReader", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StdinReader.setMetaObject( metaObj );
    return metaObj;
}

void* StdinReader::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StdinReader" ) )
	return this;
    return QObject::qt_cast( clname );
}

// SIGNAL openWindow
void StdinReader::openWindow()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool StdinReader::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: dataRecieved(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool StdinReader::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: openWindow(); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool StdinReader::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool StdinReader::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
