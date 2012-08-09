#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './scriptmanagerbase.ui'
**
** Created: Ter Fev 19 16:01:48 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "scriptmanagerbase.h"

#include <qvariant.h>
#include <kdialog.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <klistview.h>
#include <qframe.h>
#include <qcheckbox.h>
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
    ScriptManagerBaseLayout = new QVBoxLayout( this, 0, KDialog::spacingHint(), "ScriptManagerBaseLayout"); 

    layout6 = new QHBoxLayout( 0, 0, KDialog::spacingHint(), "layout6"); 

    listView = new KListView( this, "listView" );
    listView->addColumn( tr2i18n( "Scripts" ) );
    layout6->addWidget( listView );

    layout5 = new QVBoxLayout( 0, 0, KDialog::spacingHint(), "layout5"); 

    layout3 = new QVBoxLayout( 0, 0, KDialog::spacingHint(), "layout3"); 

    installButton = new QPushButton( this, "installButton" );
    layout3->addWidget( installButton );

    retrieveButton = new QPushButton( this, "retrieveButton" );
    layout3->addWidget( retrieveButton );

    line2_2 = new QFrame( this, "line2_2" );
    line2_2->setFrameShape( QFrame::HLine );
    line2_2->setFrameShadow( QFrame::Sunken );
    line2_2->setFrameShape( QFrame::HLine );
    layout3->addWidget( line2_2 );

    aboutButton = new QPushButton( this, "aboutButton" );
    layout3->addWidget( aboutButton );

    runButton = new QPushButton( this, "runButton" );
    layout3->addWidget( runButton );

    stopButton = new QPushButton( this, "stopButton" );
    layout3->addWidget( stopButton );

    configureButton = new QPushButton( this, "configureButton" );
    layout3->addWidget( configureButton );

    uninstallButton = new QPushButton( this, "uninstallButton" );
    layout3->addWidget( uninstallButton );
    layout5->addLayout( layout3 );
    spacer2 = new QSpacerItem( 20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout5->addItem( spacer2 );
    layout6->addLayout( layout5 );
    ScriptManagerBaseLayout->addLayout( layout6 );

    line2 = new QFrame( this, "line2" );
    line2->setFrameShape( QFrame::HLine );
    line2->setFrameShadow( QFrame::Sunken );
    line2->setFrameShape( QFrame::HLine );
    ScriptManagerBaseLayout->addWidget( line2 );

    checkBox_autoRun = new QCheckBox( this, "checkBox_autoRun" );
    ScriptManagerBaseLayout->addWidget( checkBox_autoRun );
    languageChange();
    resize( QSize(371, 292).expandedTo(minimumSizeHint()) );
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
    checkBox_autoRun->setText( tr2i18n( "R&estart running scripts on application startup" ) );
    QToolTip::add( checkBox_autoRun, tr2i18n( "If enabled, amaroK will automatically restart scripts that were running when you exited the application." ) );
}

#include "scriptmanagerbase.moc"
