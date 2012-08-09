#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './dbsetup.ui'
**
** Created: Ter Fev 19 16:01:38 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "dbsetup.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <klineedit.h>
#include <knuminput.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kcombobox.h"
#include "klineedit.h"
#include "knuminput.h"
#include "amarokconfig.h"
#include "config.h"
#include "debug.h"
#include "./dbsetup.ui.h"

/*
 *  Constructs a DbSetup as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
DbSetup::DbSetup( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "DbSetup" );
    DbSetupLayout = new QGridLayout( this, 1, 1, 0, 6, "DbSetupLayout"); 

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    layout2->addWidget( textLabel1_2 );

    databaseEngine = new KComboBox( FALSE, this, "databaseEngine" );
    databaseEngine->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, databaseEngine->sizePolicy().hasHeightForWidth() ) );
    layout2->addWidget( databaseEngine );

    DbSetupLayout->addLayout( layout2, 0, 0 );

    postgreSqlFrame = new QFrame( this, "postgreSqlFrame" );
    postgreSqlFrame->setFrameShape( QFrame::NoFrame );
    postgreSqlFrame->setFrameShadow( QFrame::Raised );
    postgreSqlFrameLayout = new QGridLayout( postgreSqlFrame, 1, 1, 11, 6, "postgreSqlFrameLayout"); 

    postgresqlConfig = new QGroupBox( postgreSqlFrame, "postgresqlConfig" );
    postgresqlConfig->setColumnLayout(0, Qt::Vertical );
    postgresqlConfig->layout()->setSpacing( 6 );
    postgresqlConfig->layout()->setMargin( 11 );
    postgresqlConfigLayout = new QHBoxLayout( postgresqlConfig->layout() );
    postgresqlConfigLayout->setAlignment( Qt::AlignTop );

    textLabel1_3 = new QLabel( postgresqlConfig, "textLabel1_3" );
    postgresqlConfigLayout->addWidget( textLabel1_3 );

    kcfg_PostgresqlConninfo = new KLineEdit( postgresqlConfig, "kcfg_PostgresqlConninfo" );
    postgresqlConfigLayout->addWidget( kcfg_PostgresqlConninfo );

    postgreSqlFrameLayout->addWidget( postgresqlConfig, 0, 0 );

    DbSetupLayout->addWidget( postgreSqlFrame, 2, 0 );

    mySqlFrame = new QFrame( this, "mySqlFrame" );
    mySqlFrame->setFrameShape( QFrame::NoFrame );
    mySqlFrame->setFrameShadow( QFrame::Raised );
    mySqlFrame->setLineWidth( 0 );
    mySqlFrameLayout = new QGridLayout( mySqlFrame, 1, 1, 11, 6, "mySqlFrameLayout"); 

    mysqlConfig = new QGroupBox( mySqlFrame, "mysqlConfig" );
    mysqlConfig->setColumnLayout(0, Qt::Vertical );
    mysqlConfig->layout()->setSpacing( 6 );
    mysqlConfig->layout()->setMargin( 11 );
    mysqlConfigLayout = new QGridLayout( mysqlConfig->layout() );
    mysqlConfigLayout->setAlignment( Qt::AlignTop );

    textLabel1 = new QLabel( mysqlConfig, "textLabel1" );

    mysqlConfigLayout->addWidget( textLabel1, 0, 0 );

    textLabel5 = new QLabel( mysqlConfig, "textLabel5" );

    mysqlConfigLayout->addWidget( textLabel5, 1, 0 );

    kcfg_MySqlPort = new KIntSpinBox( mysqlConfig, "kcfg_MySqlPort" );
    kcfg_MySqlPort->setMaximumSize( QSize( 100, 32767 ) );
    kcfg_MySqlPort->setMaxValue( 65535 );

    mysqlConfigLayout->addWidget( kcfg_MySqlPort, 0, 3 );

    textLabel2 = new QLabel( mysqlConfig, "textLabel2" );

    mysqlConfigLayout->addWidget( textLabel2, 0, 2 );

    kcfg_MySqlHost = new KLineEdit( mysqlConfig, "kcfg_MySqlHost" );

    mysqlConfigLayout->addWidget( kcfg_MySqlHost, 0, 1 );

    kcfg_MySqlDbName = new KLineEdit( mysqlConfig, "kcfg_MySqlDbName" );

    mysqlConfigLayout->addWidget( kcfg_MySqlDbName, 1, 1 );

    line1 = new QFrame( mysqlConfig, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );

    mysqlConfigLayout->addMultiCellWidget( line1, 2, 2, 0, 3 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    textLabel3 = new QLabel( mysqlConfig, "textLabel3" );
    layout4->addWidget( textLabel3 );

    kcfg_MySqlUser = new KLineEdit( mysqlConfig, "kcfg_MySqlUser" );
    layout4->addWidget( kcfg_MySqlUser );

    textLabel4 = new QLabel( mysqlConfig, "textLabel4" );
    layout4->addWidget( textLabel4 );

    kcfg_MySqlPassword = new KLineEdit( mysqlConfig, "kcfg_MySqlPassword" );
    kcfg_MySqlPassword->setEchoMode( KLineEdit::Password );
    layout4->addWidget( kcfg_MySqlPassword );

    mysqlConfigLayout->addMultiCellLayout( layout4, 3, 3, 0, 3 );

    mySqlFrameLayout->addWidget( mysqlConfig, 0, 0 );

    DbSetupLayout->addWidget( mySqlFrame, 1, 0 );
    languageChange();
    resize( QSize(352, 293).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
DbSetup::~DbSetup()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void DbSetup::languageChange()
{
    setCaption( tr2i18n( "Database Setup" ) );
    textLabel1_2->setText( tr2i18n( "Database:" ) );
    databaseEngine->clear();
    databaseEngine->insertItem( tr2i18n( "SQLite" ) );
    postgresqlConfig->setTitle( tr2i18n( "Postgresql Configuration" ) );
    textLabel1_3->setText( tr2i18n( "Conninfo:" ) );
    QToolTip::add( kcfg_PostgresqlConninfo, tr2i18n( "Parameters to connect to the database." ) );
    QWhatsThis::add( kcfg_PostgresqlConninfo, tr2i18n( "Parameters to connect to the database." ) );
    mysqlConfig->setTitle( tr2i18n( "MySQL Configuration" ) );
    textLabel1->setText( tr2i18n( "Hostname:" ) );
    textLabel5->setText( tr2i18n( "Name:" ) );
    QToolTip::add( kcfg_MySqlPort, tr2i18n( "Which port mysql should connect to." ) );
    QWhatsThis::add( kcfg_MySqlPort, tr2i18n( "Which port mysql should connect to." ) );
    textLabel2->setText( tr2i18n( "Port:" ) );
    QToolTip::add( kcfg_MySqlHost, tr2i18n( "Hostname where database lives." ) );
    QWhatsThis::add( kcfg_MySqlHost, tr2i18n( "Hostname where database lives." ) );
    QToolTip::add( kcfg_MySqlDbName, tr2i18n( "Name of the database." ) );
    QWhatsThis::add( kcfg_MySqlDbName, tr2i18n( "Name of the database." ) );
    textLabel3->setText( tr2i18n( "Username:" ) );
    QToolTip::add( kcfg_MySqlUser, tr2i18n( "Username with which to connect to." ) );
    QWhatsThis::add( kcfg_MySqlUser, tr2i18n( "Username with which to connect to." ) );
    textLabel4->setText( tr2i18n( "Password:" ) );
    QToolTip::add( kcfg_MySqlPassword, tr2i18n( "Password with which to connect to." ) );
    QWhatsThis::add( kcfg_MySqlPassword, tr2i18n( "Password with which to connect to." ) );
}

#include "dbsetup.moc"
