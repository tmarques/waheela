#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './scriptmanagerbase.ui'
**
** Created: Sex Mar 23 10:42:50 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "scriptmanagerbase.h"

#include <qvariant.h>
#include <kdialog.h>
#include <qheader.h>
#include <klistview.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ScriptManagerBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ScriptManagerBase::ScriptManagerBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ScriptManagerBase" );
    ScriptManagerBaseLayout = new QGridLayout( this, 1, 1, 0, KDialog::spacingHint(), "ScriptManagerBaseLayout"); 

    listView = new KListView( this, "listView" );
    listView->addColumn( tr2i18n( "Scripts" ) );

    ScriptManagerBaseLayout->addMultiCellWidget( listView, 0, 8, 0, 0 );
    spacer2 = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding );
    ScriptManagerBaseLayout->addItem( spacer2, 8, 1 );

    installButton = new QPushButton( this, "installButton" );

    ScriptManagerBaseLayout->addWidget( installButton, 0, 1 );

    retrieveButton = new QPushButton( this, "retrieveButton" );

    ScriptManagerBaseLayout->addWidget( retrieveButton, 1, 1 );

    line2_2 = new QFrame( this, "line2_2" );
    line2_2->setFrameShape( QFrame::HLine );
    line2_2->setFrameShadow( QFrame::Sunken );
    line2_2->setFrameShape( QFrame::HLine );

    ScriptManagerBaseLayout->addWidget( line2_2, 2, 1 );

    aboutButton = new QPushButton( this, "aboutButton" );

    ScriptManagerBaseLayout->addWidget( aboutButton, 3, 1 );

    runButton = new QPushButton( this, "runButton" );

    ScriptManagerBaseLayout->addWidget( runButton, 4, 1 );

    stopButton = new QPushButton( this, "stopButton" );

    ScriptManagerBaseLayout->addWidget( stopButton, 5, 1 );

    configureButton = new QPushButton( this, "configureButton" );

    ScriptManagerBaseLayout->addWidget( configureButton, 6, 1 );

    uninstallButton = new QPushButton( this, "uninstallButton" );

    ScriptManagerBaseLayout->addWidget( uninstallButton, 7, 1 );
    languageChange();
    resize( QSize(367, 237).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScriptManagerBase::~ScriptManagerBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ScriptManagerBase::languageChange()
{
    setCaption( tr2i18n( "DirectoryListBase" ) );
    listView->header()->setLabel( 0, tr2i18n( "Scripts" ) );
    QToolTip::add( listView, tr2i18n( "These scripts are currently known to amaroK." ) );
    installButton->setText( tr2i18n( "&Install Script" ) );
    retrieveButton->setText( tr2i18n( "&Get More Scripts" ) );
    aboutButton->setText( tr2i18n( "&About" ) );
    runButton->setText( tr2i18n( "&Run" ) );
    stopButton->setText( tr2i18n( "&Stop" ) );
    configureButton->setText( tr2i18n( "&Configure" ) );
    uninstallButton->setText( tr2i18n( "&Uninstall" ) );
}

#include "scriptmanagerbase.moc"
