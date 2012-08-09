#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './dbsetup.ui'
**
** Created: Fri Mar 23 10:56:41 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "dbsetup.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidgetstack.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <knuminput.h>
#include <klineedit.h>
#include <kcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "knuminput.h"
#include "klineedit.h"
#include "kcombobox.h"
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

    configStack = new QWidgetStack( this, "configStack" );
    configStack->setFrameShadow( QWidgetStack::Plain );

    SQLLite = new QWidget( configStack, "SQLLite" );
    configStack->addWidget( SQLLite, 0 );

    MySQL = new QWidget( configStack, "MySQL" );
    MySQLLayout = new QHBoxLayout( MySQL, 0, 6, "MySQLLayout"); 

    mySqlFrame = new QFrame( MySQL, "mySqlFrame" );
    mySqlFrame->setFrameShape( QFrame::NoFrame );
    mySqlFrame->setFrameShadow( QFrame::Raised );
    mySqlFrame->setLineWidth( 0 );
    mySqlFrameLayout = new QGridLayout( mySqlFrame, 1, 1, 0, 6, "mySqlFrameLayout"); 

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

    kcfg_MySqlPassword2 = new KLineEdit( mysqlConfig, "kcfg_MySqlPassword2" );
    kcfg_MySqlPassword2->setEchoMode( KLineEdit::Password );
    layout4->addWidget( kcfg_MySqlPassword2 );

    mysqlConfigLayout->addMultiCellLayout( layout4, 3, 3, 0, 3 );

    mySqlFrameLayout->addWidget( mysqlConfig, 0, 0 );
    MySQLLayout->addWidget( mySqlFrame );
    configStack->addWidget( MySQL, 1 );

    PostgreSQL = new QWidget( configStack, "PostgreSQL" );
    PostgreSQLLayout = new QHBoxLayout( PostgreSQL, 0, 6, "PostgreSQLLayout"); 

    postgreSqlFrame = new QFrame( PostgreSQL, "postgreSqlFrame" );
    postgreSqlFrame->setFrameShape( QFrame::NoFrame );
    postgreSqlFrame->setFrameShadow( QFrame::Raised );
    postgreSqlFrameLayout = new QGridLayout( postgreSqlFrame, 1, 1, 0, 6, "postgreSqlFrameLayout"); 

    postgresqlConfig = new QGroupBox( postgreSqlFrame, "postgresqlConfig" );
    postgresqlConfig->setColumnLayout(0, Qt::Vertical );
    postgresqlConfig->layout()->setSpacing( 6 );
    postgresqlConfig->layout()->setMargin( 11 );
    postgresqlConfigLayout = new QGridLayout( postgresqlConfig->layout() );
    postgresqlConfigLayout->setAlignment( Qt::AlignTop );

    textLabel1_2 = new QLabel( postgresqlConfig, "textLabel1_2" );

    postgresqlConfigLayout->addWidget( textLabel1_2, 0, 0 );

    textLabel5_2 = new QLabel( postgresqlConfig, "textLabel5_2" );

    postgresqlConfigLayout->addWidget( textLabel5_2, 1, 0 );

    kcfg_PostgresqlPort = new KIntSpinBox( postgresqlConfig, "kcfg_PostgresqlPort" );
    kcfg_PostgresqlPort->setMaximumSize( QSize( 100, 32767 ) );
    kcfg_PostgresqlPort->setMaxValue( 65535 );

    postgresqlConfigLayout->addWidget( kcfg_PostgresqlPort, 0, 3 );

    textLabel2_2 = new QLabel( postgresqlConfig, "textLabel2_2" );

    postgresqlConfigLayout->addWidget( textLabel2_2, 0, 2 );

    kcfg_PostgresqlHost = new KLineEdit( postgresqlConfig, "kcfg_PostgresqlHost" );

    postgresqlConfigLayout->addWidget( kcfg_PostgresqlHost, 0, 1 );

    kcfg_PostgresqlDbName = new KLineEdit( postgresqlConfig, "kcfg_PostgresqlDbName" );

    postgresqlConfigLayout->addWidget( kcfg_PostgresqlDbName, 1, 1 );

    line1_2 = new QFrame( postgresqlConfig, "line1_2" );
    line1_2->setFrameShape( QFrame::HLine );
    line1_2->setFrameShadow( QFrame::Sunken );
    line1_2->setFrameShape( QFrame::HLine );

    postgresqlConfigLayout->addMultiCellWidget( line1_2, 2, 2, 0, 3 );

    layout4_2 = new QHBoxLayout( 0, 0, 6, "layout4_2"); 

    textLabel3_2 = new QLabel( postgresqlConfig, "textLabel3_2" );
    layout4_2->addWidget( textLabel3_2 );

    kcfg_PostgresqlUser = new KLineEdit( postgresqlConfig, "kcfg_PostgresqlUser" );
    layout4_2->addWidget( kcfg_PostgresqlUser );

    textLabel4_2 = new QLabel( postgresqlConfig, "textLabel4_2" );
    layout4_2->addWidget( textLabel4_2 );

    kcfg_PostgresqlPassword2 = new KLineEdit( postgresqlConfig, "kcfg_PostgresqlPassword2" );
    kcfg_PostgresqlPassword2->setEchoMode( KLineEdit::Password );
    layout4_2->addWidget( kcfg_PostgresqlPassword2 );

    postgresqlConfigLayout->addMultiCellLayout( layout4_2, 3, 3, 0, 3 );

    postgreSqlFrameLayout->addWidget( postgresqlConfig, 0, 0 );
    PostgreSQLLayout->addWidget( postgreSqlFrame );
    configStack->addWidget( PostgreSQL, 2 );

    DbSetupLayout->addMultiCellWidget( configStack, 1, 1, 0, 1 );

    textLabel1_2_2 = new QLabel( this, "textLabel1_2_2" );

    DbSetupLayout->addWidget( textLabel1_2_2, 0, 0 );

    databaseEngine = new KComboBox( FALSE, this, "databaseEngine" );
    databaseEngine->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, databaseEngine->sizePolicy().hasHeightForWidth() ) );

    DbSetupLayout->addWidget( databaseEngine, 0, 1 );
    languageChange();
    resize( QSize(385, 155).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( databaseEngine, SIGNAL( activated(int) ), configStack, SLOT( raiseWidget(int) ) );
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
    mysqlConfig->setTitle( tr2i18n( "MySQL Configuration" ) );
    textLabel1->setText( tr2i18n( "Hostname:" ) );
    textLabel5->setText( tr2i18n( "Database:" ) );
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
    QToolTip::add( kcfg_MySqlPassword2, tr2i18n( "Password with which to connect to." ) );
    QWhatsThis::add( kcfg_MySqlPassword2, tr2i18n( "Password with which to connect to." ) );
    postgresqlConfig->setTitle( tr2i18n( "PostgreSQL Configuration" ) );
    textLabel1_2->setText( tr2i18n( "Hostname:" ) );
    textLabel5_2->setText( tr2i18n( "Database:" ) );
    QToolTip::add( kcfg_PostgresqlPort, tr2i18n( "Which port postgresql should connect to." ) );
    QWhatsThis::add( kcfg_PostgresqlPort, tr2i18n( "Which port postgresql should connect to." ) );
    textLabel2_2->setText( tr2i18n( "Port:" ) );
    QToolTip::add( kcfg_PostgresqlHost, tr2i18n( "Hostname where database lives." ) );
    QWhatsThis::add( kcfg_PostgresqlHost, tr2i18n( "Hostname where database lives." ) );
    QToolTip::add( kcfg_PostgresqlDbName, tr2i18n( "Name of the database." ) );
    QWhatsThis::add( kcfg_PostgresqlDbName, tr2i18n( "Name of the database." ) );
    textLabel3_2->setText( tr2i18n( "Username:" ) );
    QToolTip::add( kcfg_PostgresqlUser, tr2i18n( "Username with which to connect to." ) );
    QWhatsThis::add( kcfg_PostgresqlUser, tr2i18n( "Username with which to connect to." ) );
    textLabel4_2->setText( tr2i18n( "Password:" ) );
    QToolTip::add( kcfg_PostgresqlPassword2, tr2i18n( "Password with which to connect to." ) );
    QWhatsThis::add( kcfg_PostgresqlPassword2, tr2i18n( "Password with which to connect to." ) );
    textLabel1_2_2->setText( tr2i18n( "Database:" ) );
    databaseEngine->clear();
    databaseEngine->insertItem( tr2i18n( "SQLite" ) );
}

#include "dbsetup.moc"
