#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './podcastsettingsbase.ui'
**
** Created: Ter Fev 19 16:01:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "podcastsettingsbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <kurlrequester.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kurlrequester.h"
#include "klineedit.h"
#include "kpushbutton.h"

/*
 *  Constructs a PodcastSettingsDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PodcastSettingsDialogBase::PodcastSettingsDialogBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Form1" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, sizePolicy().hasHeightForWidth() ) );
    Form1Layout = new QGridLayout( this, 1, 1, 11, 6, "Form1Layout"); 

    layout32 = new QHBoxLayout( 0, 0, 6, "layout32"); 

    m_autoFetchCheck = new QCheckBox( this, "m_autoFetchCheck" );
    layout32->addWidget( m_autoFetchCheck );

    Form1Layout->addLayout( layout32, 4, 0 );

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    textLabel9 = new QLabel( this, "textLabel9" );
    textLabel9->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, textLabel9->sizePolicy().hasHeightForWidth() ) );
    layout6->addWidget( textLabel9 );

    m_urlLine = new QLineEdit( this, "m_urlLine" );
    m_urlLine->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, m_urlLine->sizePolicy().hasHeightForWidth() ) );
    layout6->addWidget( m_urlLine );

    Form1Layout->addLayout( layout6, 0, 0 );

    buttonGroup1 = new QButtonGroup( this, "buttonGroup1" );
    buttonGroup1->setLineWidth( 1 );
    buttonGroup1->setMargin( 6 );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    m_streamRadio = new QRadioButton( buttonGroup1, "m_streamRadio" );

    buttonGroup1Layout->addWidget( m_streamRadio, 1, 0 );

    m_downloadRadio = new QRadioButton( buttonGroup1, "m_downloadRadio" );

    buttonGroup1Layout->addWidget( m_downloadRadio, 2, 0 );

    Form1Layout->addWidget( buttonGroup1, 6, 0 );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout5->addWidget( textLabel1 );

    m_saveLocation = new KURLRequester( this, "m_saveLocation" );
    layout5->addWidget( m_saveLocation );

    Form1Layout->addLayout( layout5, 2, 0 );

    layout34 = new QHBoxLayout( 0, 0, 6, "layout34"); 

    m_purgeCheck = new QCheckBox( this, "m_purgeCheck" );
    layout34->addWidget( m_purgeCheck );
    spacer16 = new QSpacerItem( 38, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout34->addItem( spacer16 );

    textLabel8 = new QLabel( this, "textLabel8" );
    layout34->addWidget( textLabel8 );

    m_purgeCountSpinBox = new QSpinBox( this, "m_purgeCountSpinBox" );
    m_purgeCountSpinBox->setMinValue( 1 );
    layout34->addWidget( m_purgeCountSpinBox );

    Form1Layout->addLayout( layout34, 8, 0 );
    languageChange();
    resize( QSize(481, 238).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( m_purgeCheck, SIGNAL( toggled(bool) ), m_purgeCountSpinBox, SLOT( setEnabled(bool) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
PodcastSettingsDialogBase::~PodcastSettingsDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PodcastSettingsDialogBase::languageChange()
{
    setCaption( tr2i18n( "Podcast Configuration" ) );
    m_autoFetchCheck->setText( tr2i18n( "Enable &auto-fetching" ) );
    QToolTip::add( m_autoFetchCheck, tr2i18n( "When checked, amaroK will automatically scan the podcast for updates" ) );
    QWhatsThis::add( m_autoFetchCheck, tr2i18n( "When checked, amaroK will automatically scan the podcast for updates" ) );
    textLabel9->setText( tr2i18n( "URL:" ) );
    QToolTip::add( m_urlLine, tr2i18n( "Location of the podcast" ) );
    QWhatsThis::add( m_urlLine, tr2i18n( "Location of the podcast" ) );
    buttonGroup1->setTitle( tr2i18n( "Media Download" ) );
    m_streamRadio->setText( tr2i18n( "Stream or download on re&quest" ) );
    QToolTip::add( m_streamRadio, tr2i18n( "Media must be downloaded, otherwise the podcast will be played from the remote server." ) );
    QWhatsThis::add( m_streamRadio, tr2i18n( "Media must be downloaded, otherwise the podcast will be played from the remote server." ) );
    m_downloadRadio->setText( tr2i18n( "Download when a&vailable" ) );
    QToolTip::add( m_downloadRadio, tr2i18n( "Download media as soon as it becomes available" ) );
    QWhatsThis::add( m_downloadRadio, tr2i18n( "Download media as soon as it becomes available" ) );
    textLabel1->setText( tr2i18n( "Save location:" ) );
    m_purgeCheck->setText( tr2i18n( "Limit &number of items" ) );
    QToolTip::add( m_purgeCheck, tr2i18n( "If checked, amaroK will throw away old podcasts" ) );
    QWhatsThis::add( m_purgeCheck, tr2i18n( "If checked, amaroK will throw away old podcasts" ) );
    textLabel8->setText( tr2i18n( "Keep maximum of:" ) );
    m_purgeCountSpinBox->setSuffix( tr2i18n( " Items" ) );
    QToolTip::add( m_purgeCountSpinBox, tr2i18n( "The maximum number of podcast items to store" ) );
    QWhatsThis::add( m_purgeCountSpinBox, tr2i18n( "The maximum number of podcast items to store" ) );
}

#include "podcastsettingsbase.moc"
