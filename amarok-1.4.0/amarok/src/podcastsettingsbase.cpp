#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './podcastsettingsbase.ui'
**
** Created: Sex Mar 23 10:42:48 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "podcastsettingsbase.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <kurlrequester.h>
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
    Form1Layout = new QGridLayout( this, 1, 1, 0, 6, "Form1Layout"); 

    buttonGroup1 = new QButtonGroup( this, "buttonGroup1" );
    buttonGroup1->setLineWidth( 1 );
    buttonGroup1->setMargin( 6 );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QVBoxLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    m_streamRadio = new QRadioButton( buttonGroup1, "m_streamRadio" );
    buttonGroup1Layout->addWidget( m_streamRadio );

    m_downloadRadio = new QRadioButton( buttonGroup1, "m_downloadRadio" );
    buttonGroup1Layout->addWidget( m_downloadRadio );

    m_addToMediaDeviceCheck = new QCheckBox( buttonGroup1, "m_addToMediaDeviceCheck" );
    buttonGroup1Layout->addWidget( m_addToMediaDeviceCheck );

    Form1Layout->addMultiCellWidget( buttonGroup1, 3, 3, 0, 5 );

    m_purgeCheck = new QCheckBox( this, "m_purgeCheck" );

    Form1Layout->addMultiCellWidget( m_purgeCheck, 4, 4, 0, 2 );
    spacer16 = new QSpacerItem( 111, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Form1Layout->addItem( spacer16, 4, 3 );

    m_purgeCountLabel = new QLabel( this, "m_purgeCountLabel" );

    Form1Layout->addWidget( m_purgeCountLabel, 4, 4 );

    m_purgeCountSpinBox = new QSpinBox( this, "m_purgeCountSpinBox" );
    m_purgeCountSpinBox->setMinValue( 1 );

    Form1Layout->addWidget( m_purgeCountSpinBox, 4, 5 );

    m_autoFetchCheck = new QCheckBox( this, "m_autoFetchCheck" );

    Form1Layout->addMultiCellWidget( m_autoFetchCheck, 2, 2, 0, 5 );

    textLabel1 = new QLabel( this, "textLabel1" );

    Form1Layout->addMultiCellWidget( textLabel1, 1, 1, 0, 1 );

    m_saveLocation = new KURLRequester( this, "m_saveLocation" );

    Form1Layout->addMultiCellWidget( m_saveLocation, 1, 1, 2, 5 );
    spacer17 = new QSpacerItem( 20, 5, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding );
    Form1Layout->addItem( spacer17, 5, 3 );
    languageChange();
    resize( QSize(499, 213).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( m_purgeCheck, SIGNAL( toggled(bool) ), m_purgeCountSpinBox, SLOT( setEnabled(bool) ) );
    connect( m_purgeCheck, SIGNAL( toggled(bool) ), m_purgeCountLabel, SLOT( setEnabled(bool) ) );
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
    buttonGroup1->setTitle( tr2i18n( "Media Download" ) );
    m_streamRadio->setText( tr2i18n( "Stream or download on re&quest" ) );
    QToolTip::add( m_streamRadio, tr2i18n( "Media must be explicitly downloaded, otherwise the podcast will be played from the remote server." ) );
    QWhatsThis::add( m_streamRadio, tr2i18n( "Media must be explicitly downloaded, otherwise the podcast will be played from the remote server." ) );
    m_downloadRadio->setText( tr2i18n( "Download when a&vailable" ) );
    QToolTip::add( m_downloadRadio, tr2i18n( "Download media as soon as it becomes available" ) );
    QWhatsThis::add( m_downloadRadio, tr2i18n( "Download media as soon as it becomes available" ) );
    m_addToMediaDeviceCheck->setText( tr2i18n( "Add to media device &transfer queue" ) );
    QToolTip::add( m_addToMediaDeviceCheck, tr2i18n( "When checked, amaroK will automatically add newly downloaded podcast shows to the media device transfer queue" ) );
    QWhatsThis::add( m_addToMediaDeviceCheck, tr2i18n( "When checked, amaroK will automatically add newly downloaded podcast shows to the media device transfer queue" ) );
    m_purgeCheck->setText( tr2i18n( "Limit &number of episodes" ) );
    QToolTip::add( m_purgeCheck, tr2i18n( "If checked, amaroK will throw away old podcast episodes" ) );
    QWhatsThis::add( m_purgeCheck, tr2i18n( "If checked, amaroK will throw away old podcast episodes" ) );
    m_purgeCountLabel->setText( tr2i18n( "Keep maximum of:" ) );
    m_purgeCountSpinBox->setSuffix( tr2i18n( " Items" ) );
    QToolTip::add( m_purgeCountSpinBox, tr2i18n( "The maximum number of podcast items to store" ) );
    QWhatsThis::add( m_purgeCountSpinBox, tr2i18n( "The maximum number of podcast items to store" ) );
    m_autoFetchCheck->setText( tr2i18n( "Automatically scan for updates" ) );
    QToolTip::add( m_autoFetchCheck, tr2i18n( "When checked, amaroK will automatically scan the podcast for updates" ) );
    QWhatsThis::add( m_autoFetchCheck, tr2i18n( "When checked, amaroK will automatically scan the podcast for updates" ) );
    textLabel1->setText( tr2i18n( "Save location:" ) );
}

#include "podcastsettingsbase.moc"
