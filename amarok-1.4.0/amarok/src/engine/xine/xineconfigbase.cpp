#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './xineconfigbase.ui'
**
** Created: Sex Mar 23 10:36:18 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "xineconfigbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <knuminput.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a XineConfigBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
XineConfigBase::XineConfigBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "XineConfigBase" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    XineConfigBaseLayout = new QVBoxLayout( this, 0, 6, "XineConfigBaseLayout"); 

    layout11 = new QHBoxLayout( 0, 0, 6, "layout11"); 

    xineLogo = new QLabel( this, "xineLogo" );
    xineLogo->setPaletteForegroundColor( QColor( 0, 0, 0 ) );
    xineLogo->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    xineLogo->setFrameShape( QLabel::StyledPanel );
    xineLogo->setFrameShadow( QLabel::Raised );
    xineLogo->setMargin( 1 );
    xineLogo->setAlignment( int( QLabel::AlignCenter ) );
    layout11->addWidget( xineLogo );

    layout10 = new QVBoxLayout( 0, 0, 6, "layout10"); 

    layout10_2 = new QVBoxLayout( 0, 0, 6, "layout10_2"); 

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    textLabel2 = new QLabel( this, "textLabel2" );
    layout2->addWidget( textLabel2 );

    deviceComboBox = new KComboBox( FALSE, this, "deviceComboBox" );
    layout2->addWidget( deviceComboBox );
    layout10_2->addLayout( layout2 );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, textLabel3->sizePolicy().hasHeightForWidth() ) );
    textLabel3->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter ) );
    layout10_2->addWidget( textLabel3 );

    alsaGroupBox = new QGroupBox( this, "alsaGroupBox" );
    alsaGroupBox->setColumnLayout(0, Qt::Vertical );
    alsaGroupBox->layout()->setSpacing( 6 );
    alsaGroupBox->layout()->setMargin( 11 );
    alsaGroupBoxLayout = new QGridLayout( alsaGroupBox->layout() );
    alsaGroupBoxLayout->setAlignment( Qt::AlignTop );

    textLabel2_3 = new QLabel( alsaGroupBox, "textLabel2_3" );

    alsaGroupBoxLayout->addWidget( textLabel2_3, 0, 0 );

    textLabel3_3 = new QLabel( alsaGroupBox, "textLabel3_3" );

    alsaGroupBoxLayout->addWidget( textLabel3_3, 1, 0 );

    textLabel4_2 = new QLabel( alsaGroupBox, "textLabel4_2" );

    alsaGroupBoxLayout->addWidget( textLabel4_2, 0, 2 );

    chan5Label = new QLabel( alsaGroupBox, "chan5Label" );

    alsaGroupBoxLayout->addWidget( chan5Label, 1, 2 );

    monoLineEdit = new QLineEdit( alsaGroupBox, "monoLineEdit" );

    alsaGroupBoxLayout->addWidget( monoLineEdit, 0, 1 );

    stereoLineEdit = new QLineEdit( alsaGroupBox, "stereoLineEdit" );

    alsaGroupBoxLayout->addWidget( stereoLineEdit, 1, 1 );

    chan4LineEdit = new QLineEdit( alsaGroupBox, "chan4LineEdit" );

    alsaGroupBoxLayout->addWidget( chan4LineEdit, 0, 3 );

    chan5LineEdit = new QLineEdit( alsaGroupBox, "chan5LineEdit" );

    alsaGroupBoxLayout->addWidget( chan5LineEdit, 1, 3 );
    layout10_2->addWidget( alsaGroupBox );

    ossGroupBox = new QGroupBox( this, "ossGroupBox" );
    ossGroupBox->setColumnLayout(0, Qt::Vertical );
    ossGroupBox->layout()->setSpacing( 6 );
    ossGroupBox->layout()->setMargin( 11 );
    ossGroupBoxLayout = new QHBoxLayout( ossGroupBox->layout() );
    ossGroupBoxLayout->setAlignment( Qt::AlignTop );

    textLabel1 = new QLabel( ossGroupBox, "textLabel1" );
    ossGroupBoxLayout->addWidget( textLabel1 );

    ossDeviceComboBox = new QComboBox( FALSE, ossGroupBox, "ossDeviceComboBox" );
    ossGroupBoxLayout->addWidget( ossDeviceComboBox );
    layout10_2->addWidget( ossGroupBox );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    layout5->addWidget( textLabel1_2 );

    speakerComboBox = new QComboBox( FALSE, this, "speakerComboBox" );
    layout5->addWidget( speakerComboBox );
    layout10_2->addLayout( layout5 );

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QVBoxLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    textLabel2_2 = new QLabel( groupBox1, "textLabel2_2" );
    layout4->addWidget( textLabel2_2 );

    hostLineEdit = new QLineEdit( groupBox1, "hostLineEdit" );
    layout4->addWidget( hostLineEdit );

    portIntBox = new KIntSpinBox( groupBox1, "portIntBox" );
    portIntBox->setMaxValue( 65534 );
    portIntBox->setMinValue( 1 );
    portIntBox->setValue( 60000 );
    layout4->addWidget( portIntBox );
    groupBox1Layout->addLayout( layout4 );

    layout2_2 = new QHBoxLayout( 0, 0, 6, "layout2_2"); 

    textLabel3_2 = new QLabel( groupBox1, "textLabel3_2" );
    layout2_2->addWidget( textLabel3_2 );

    userLineEdit = new QLineEdit( groupBox1, "userLineEdit" );
    layout2_2->addWidget( userLineEdit );

    textLabel4 = new QLabel( groupBox1, "textLabel4" );
    layout2_2->addWidget( textLabel4 );

    passLineEdit = new QLineEdit( groupBox1, "passLineEdit" );
    passLineEdit->setEchoMode( QLineEdit::Password );
    layout2_2->addWidget( passLineEdit );
    groupBox1Layout->addLayout( layout2_2 );
    layout10_2->addWidget( groupBox1 );

    audiocdGroupBox = new QGroupBox( this, "audiocdGroupBox" );
    audiocdGroupBox->setColumnLayout(0, Qt::Vertical );
    audiocdGroupBox->layout()->setSpacing( 6 );
    audiocdGroupBox->layout()->setMargin( 11 );
    audiocdGroupBoxLayout = new QHBoxLayout( audiocdGroupBox->layout() );
    audiocdGroupBoxLayout->setAlignment( Qt::AlignTop );

    layout11_2 = new QVBoxLayout( 0, 0, 6, "layout11_2"); 

    textLabel2_3_2 = new QLabel( audiocdGroupBox, "textLabel2_3_2" );
    layout11_2->addWidget( textLabel2_3_2 );

    textLabel2_2_2 = new QLabel( audiocdGroupBox, "textLabel2_2_2" );
    layout11_2->addWidget( textLabel2_2_2 );

    textLabel2_3_2_2 = new QLabel( audiocdGroupBox, "textLabel2_3_2_2" );
    layout11_2->addWidget( textLabel2_3_2_2 );
    audiocdGroupBoxLayout->addLayout( layout11_2 );

    layout12 = new QVBoxLayout( 0, 0, 6, "layout12"); 

    audiocd_device = new QLineEdit( audiocdGroupBox, "audiocd_device" );
    layout12->addWidget( audiocd_device );

    layout10_3 = new QHBoxLayout( 0, 0, 6, "layout10_3"); 

    cddb_server = new QLineEdit( audiocdGroupBox, "cddb_server" );
    layout10_3->addWidget( cddb_server );

    cddb_port = new KIntSpinBox( audiocdGroupBox, "cddb_port" );
    cddb_port->setMaxValue( 65534 );
    cddb_port->setMinValue( 1 );
    cddb_port->setValue( 60000 );
    layout10_3->addWidget( cddb_port );
    layout12->addLayout( layout10_3 );

    cddb_cache_dir = new QLineEdit( audiocdGroupBox, "cddb_cache_dir" );
    layout12->addWidget( cddb_cache_dir );
    audiocdGroupBoxLayout->addLayout( layout12 );
    layout10_2->addWidget( audiocdGroupBox );
    layout10->addLayout( layout10_2 );
    spacer3 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout10->addItem( spacer3 );
    layout11->addLayout( layout10 );
    XineConfigBaseLayout->addLayout( layout11 );
    languageChange();
    resize( QSize(437, 458).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // buddies
    textLabel2->setBuddy( deviceComboBox );
    textLabel2_3->setBuddy( monoLineEdit );
    textLabel3_3->setBuddy( stereoLineEdit );
    textLabel4_2->setBuddy( chan4LineEdit );
    chan5Label->setBuddy( chan5LineEdit );
    textLabel1->setBuddy( ossDeviceComboBox );
    textLabel1_2->setBuddy( speakerComboBox );
    textLabel2_2->setBuddy( hostLineEdit );
    textLabel3_2->setBuddy( userLineEdit );
    textLabel4->setBuddy( passLineEdit );
    textLabel2_3_2->setBuddy( monoLineEdit );
    textLabel2_2_2->setBuddy( hostLineEdit );
    textLabel2_3_2_2->setBuddy( monoLineEdit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
XineConfigBase::~XineConfigBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void XineConfigBase::languageChange()
{
    setCaption( tr2i18n( "Xine Configure" ) );
    xineLogo->setText( QString::null );
    textLabel2->setText( tr2i18n( "&Output plugin:" ) );
    textLabel3->setText( tr2i18n( "Sound device may be modified after the output plugin has been changed to ALSA or OSS." ) );
    alsaGroupBox->setTitle( tr2i18n( "ALSA Device Configuration" ) );
    textLabel2_3->setText( tr2i18n( "&Mono:" ) );
    textLabel3_3->setText( tr2i18n( "&Stereo:" ) );
    textLabel4_2->setText( tr2i18n( "&4 Channels:" ) );
    chan5Label->setText( tr2i18n( "&6 Channels:" ) );
    ossGroupBox->setTitle( tr2i18n( "OSS Device Configuration" ) );
    textLabel1->setText( tr2i18n( "&Device:" ) );
    textLabel1_2->setText( tr2i18n( "Speaker &arrangement:" ) );
    groupBox1->setTitle( tr2i18n( "HTTP Proxy for Streaming" ) );
    textLabel2_2->setText( tr2i18n( "&Host:" ) );
    textLabel3_2->setText( tr2i18n( "&User:" ) );
    textLabel4->setText( tr2i18n( "&Password:" ) );
    audiocdGroupBox->setTitle( tr2i18n( "Audio CD Configuration" ) );
    textLabel2_3_2->setText( tr2i18n( "Default device:" ) );
    textLabel2_2_2->setText( tr2i18n( "CDDB Server:" ) );
    textLabel2_3_2_2->setText( tr2i18n( "CDDB Cache dir:" ) );
    audiocd_device->setText( QString::null );
    cddb_cache_dir->setText( QString::null );
}

#include "xineconfigbase.moc"
