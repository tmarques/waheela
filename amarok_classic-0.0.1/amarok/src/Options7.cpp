#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options7.ui'
**
** Created: Ter Fev 19 16:01:35 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "Options7.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "dbsetup.h"

/*
 *  Constructs a Options7 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Options7::Options7( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "MySql" );
    MySqlLayout = new QVBoxLayout( this, 0, 6, "MySqlLayout"); 

    collectionFoldersBox = new QGroupBox( this, "collectionFoldersBox" );
    MySqlLayout->addWidget( collectionFoldersBox );

    databaseBox = new QGroupBox( this, "databaseBox" );
    databaseBox->setColumnLayout(0, Qt::Vertical );
    databaseBox->layout()->setSpacing( 6 );
    databaseBox->layout()->setMargin( 11 );
    databaseBoxLayout = new QVBoxLayout( databaseBox->layout() );
    databaseBoxLayout->setAlignment( Qt::AlignTop );

    dbSetupFrame = new DbSetup( databaseBox, "dbSetupFrame" );
    databaseBoxLayout->addWidget( dbSetupFrame );
    MySqlLayout->addWidget( databaseBox );
    languageChange();
    resize( QSize(404, 215).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
Options7::~Options7()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Options7::languageChange()
{
    setCaption( tr2i18n( "MySql" ) );
    collectionFoldersBox->setTitle( tr2i18n( "Collection Folders" ) );
    databaseBox->setTitle( tr2i18n( "Collection Database" ) );
}

#include "Options7.moc"
