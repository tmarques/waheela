#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options2.ui'
**
** Created: Ter Fev 19 16:01:27 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "Options2.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <kfontrequester.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <kcolorbutton.h>
#include <kcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "./Options2.ui.h"

/*
 *  Constructs a Options2 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Options2::Options2( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Options2" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, sizePolicy().hasHeightForWidth() ) );
    Options2Layout = new QVBoxLayout( this, 0, 6, "Options2Layout"); 

    groupBox4 = new QGroupBox( this, "groupBox4" );
    groupBox4->setColumnLayout(0, Qt::Vertical );
    groupBox4->layout()->setSpacing( 0 );
    groupBox4->layout()->setMargin( 11 );
    groupBox4Layout = new QVBoxLayout( groupBox4->layout() );
    groupBox4Layout->setAlignment( Qt::AlignTop );

    kcfg_UseCustomFonts = new QCheckBox( groupBox4, "kcfg_UseCustomFonts" );
    kcfg_UseCustomFonts->setChecked( FALSE );
    groupBox4Layout->addWidget( kcfg_UseCustomFonts );

    fontGroupBox = new QGroupBox( groupBox4, "fontGroupBox" );
    fontGroupBox->setEnabled( FALSE );
    fontGroupBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, fontGroupBox->sizePolicy().hasHeightForWidth() ) );
    fontGroupBox->setFrameShape( QGroupBox::NoFrame );
    fontGroupBox->setLineWidth( 0 );
    fontGroupBox->setFlat( TRUE );
    fontGroupBox->setColumnLayout(0, Qt::Vertical );
    fontGroupBox->layout()->setSpacing( 6 );
    fontGroupBox->layout()->setMargin( 11 );
    fontGroupBoxLayout = new QVBoxLayout( fontGroupBox->layout() );
    fontGroupBoxLayout->setAlignment( Qt::AlignTop );

    textLabel1 = new QLabel( fontGroupBox, "textLabel1" );
    textLabel1->setMinimumSize( QSize( 0, 0 ) );
    textLabel1->setAlignment( int( QLabel::AlignTop | QLabel::AlignLeft ) );
    fontGroupBoxLayout->addWidget( textLabel1 );

    kcfg_PlayerWidgetFont = new KFontRequester( fontGroupBox, "kcfg_PlayerWidgetFont" );
    kcfg_PlayerWidgetFont->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, kcfg_PlayerWidgetFont->sizePolicy().hasHeightForWidth() ) );
    fontGroupBoxLayout->addWidget( kcfg_PlayerWidgetFont );

    textLabel3 = new QLabel( fontGroupBox, "textLabel3" );
    textLabel3->setMinimumSize( QSize( 0, 0 ) );
    fontGroupBoxLayout->addWidget( textLabel3 );

    kcfg_PlaylistWindowFont = new KFontRequester( fontGroupBox, "kcfg_PlaylistWindowFont" );
    kcfg_PlaylistWindowFont->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, kcfg_PlaylistWindowFont->sizePolicy().hasHeightForWidth() ) );
    fontGroupBoxLayout->addWidget( kcfg_PlaylistWindowFont );

    textLabel3_2 = new QLabel( fontGroupBox, "textLabel3_2" );
    textLabel3_2->setMinimumSize( QSize( 0, 0 ) );
    fontGroupBoxLayout->addWidget( textLabel3_2 );

    kcfg_ContextBrowserFont = new KFontRequester( fontGroupBox, "kcfg_ContextBrowserFont" );
    kcfg_ContextBrowserFont->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, kcfg_ContextBrowserFont->sizePolicy().hasHeightForWidth() ) );
    fontGroupBoxLayout->addWidget( kcfg_ContextBrowserFont );
    groupBox4Layout->addWidget( fontGroupBox );
    Options2Layout->addWidget( groupBox4 );

    groupBox3 = new QGroupBox( this, "groupBox3" );
    groupBox3->setColumnLayout(0, Qt::Vertical );
    groupBox3->layout()->setSpacing( 6 );
    groupBox3->layout()->setMargin( 11 );
    groupBox3Layout = new QGridLayout( groupBox3->layout() );
    groupBox3Layout->setAlignment( Qt::AlignTop );

    radioGroup = new QButtonGroup( groupBox3, "radioGroup" );
    radioGroup->setFrameShape( QButtonGroup::NoFrame );
    radioGroup->setColumnLayout(0, Qt::Vertical );
    radioGroup->layout()->setSpacing( 6 );
    radioGroup->layout()->setMargin( 0 );
    radioGroupLayout = new QGridLayout( radioGroup->layout() );
    radioGroupLayout->setAlignment( Qt::AlignTop );

    layout2 = new QVBoxLayout( 0, 0, 0, "layout2"); 

    kcfg_SchemeCustom = new QRadioButton( radioGroup, "kcfg_SchemeCustom" );
    kcfg_SchemeCustom->setChecked( TRUE );
    layout2->addWidget( kcfg_SchemeCustom );

    customSchemeBox = new QGroupBox( radioGroup, "customSchemeBox" );
    customSchemeBox->setEnabled( TRUE );
    customSchemeBox->setFocusPolicy( QGroupBox::NoFocus );
    customSchemeBox->setFrameShape( QGroupBox::NoFrame );
    customSchemeBox->setFlat( FALSE );
    customSchemeBox->setChecked( FALSE );
    customSchemeBox->setColumnLayout(0, Qt::Vertical );
    customSchemeBox->layout()->setSpacing( 6 );
    customSchemeBox->layout()->setMargin( 11 );
    customSchemeBoxLayout = new QGridLayout( customSchemeBox->layout() );
    customSchemeBoxLayout->setAlignment( Qt::AlignTop );

    fgLabel = new QLabel( customSchemeBox, "fgLabel" );
    fgLabel->setEnabled( TRUE );
    fgLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)5, 0, 0, fgLabel->sizePolicy().hasHeightForWidth() ) );
    fgLabel->setMinimumSize( QSize( 0, 0 ) );
    fgLabel->setTextFormat( QLabel::AutoText );

    customSchemeBoxLayout->addWidget( fgLabel, 0, 0 );

    kcfg_PlaylistWindowFgColor = new KColorButton( customSchemeBox, "kcfg_PlaylistWindowFgColor" );
    kcfg_PlaylistWindowFgColor->setEnabled( TRUE );
    kcfg_PlaylistWindowFgColor->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 2, 0, kcfg_PlaylistWindowFgColor->sizePolicy().hasHeightForWidth() ) );
    kcfg_PlaylistWindowFgColor->setColor( QColor( 255, 255, 255 ) );

    customSchemeBoxLayout->addWidget( kcfg_PlaylistWindowFgColor, 0, 1 );

    bgColor = new QLabel( customSchemeBox, "bgColor" );
    bgColor->setEnabled( TRUE );
    bgColor->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)5, 0, 0, bgColor->sizePolicy().hasHeightForWidth() ) );
    bgColor->setTextFormat( QLabel::AutoText );

    customSchemeBoxLayout->addWidget( bgColor, 1, 0 );

    kcfg_PlaylistWindowBgColor = new KColorButton( customSchemeBox, "kcfg_PlaylistWindowBgColor" );
    kcfg_PlaylistWindowBgColor->setEnabled( TRUE );
    kcfg_PlaylistWindowBgColor->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 2, 0, kcfg_PlaylistWindowBgColor->sizePolicy().hasHeightForWidth() ) );
    kcfg_PlaylistWindowBgColor->setMinimumSize( QSize( 0, 0 ) );
    kcfg_PlaylistWindowBgColor->setMaximumSize( QSize( 192, 32767 ) );
    kcfg_PlaylistWindowBgColor->setColor( QColor( 32, 32, 80 ) );

    customSchemeBoxLayout->addWidget( kcfg_PlaylistWindowBgColor, 1, 1 );
    layout2->addWidget( customSchemeBox );

    radioGroupLayout->addLayout( layout2, 2, 0 );

    kcfg_SchemeKDE = new QRadioButton( radioGroup, "kcfg_SchemeKDE" );
    radioGroup->insert( kcfg_SchemeKDE, 0 );

    radioGroupLayout->addWidget( kcfg_SchemeKDE, 0, 0 );

    kcfg_SchemeAmarok = new QRadioButton( radioGroup, "kcfg_SchemeAmarok" );
    radioGroup->insert( kcfg_SchemeAmarok, 1 );

    radioGroupLayout->addWidget( kcfg_SchemeAmarok, 1, 0 );

    groupBox3Layout->addWidget( radioGroup, 0, 0 );
    Options2Layout->addWidget( groupBox3 );

    contextGroupBox = new QGroupBox( this, "contextGroupBox" );
    contextGroupBox->setColumnLayout(0, Qt::Vertical );
    contextGroupBox->layout()->setSpacing( 6 );
    contextGroupBox->layout()->setMargin( 11 );
    contextGroupBoxLayout = new QVBoxLayout( contextGroupBox->layout() );
    contextGroupBoxLayout->setAlignment( Qt::AlignTop );

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    textLabel1_2 = new QLabel( contextGroupBox, "textLabel1_2" );
    textLabel1_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, textLabel1_2->sizePolicy().hasHeightForWidth() ) );
    layout6->addWidget( textLabel1_2 );

    styleComboBox = new KComboBox( FALSE, contextGroupBox, "styleComboBox" );
    layout6->addWidget( styleComboBox );
    contextGroupBoxLayout->addLayout( layout6 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    installPushButton = new QPushButton( contextGroupBox, "installPushButton" );
    layout7->addWidget( installPushButton );

    retrievePushButton = new QPushButton( contextGroupBox, "retrievePushButton" );
    layout7->addWidget( retrievePushButton );
    contextGroupBoxLayout->addLayout( layout7 );
    Options2Layout->addWidget( contextGroupBox );
    spacer1 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Options2Layout->addItem( spacer1 );
    languageChange();
    resize( QSize(369, 514).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kcfg_UseCustomFonts, SIGNAL( toggled(bool) ), fontGroupBox, SLOT( setEnabled(bool) ) );
    connect( kcfg_SchemeCustom, SIGNAL( toggled(bool) ), customSchemeBox, SLOT( setEnabled(bool) ) );
    connect( installPushButton, SIGNAL( clicked() ), this, SLOT( installPushButton_clicked() ) );
    connect( retrievePushButton, SIGNAL( clicked() ), this, SLOT( retrievePushButton_clicked() ) );

    // buddies
    fgLabel->setBuddy( kcfg_PlaylistWindowFgColor );
    bgColor->setBuddy( kcfg_PlaylistWindowBgColor );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
Options2::~Options2()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Options2::languageChange()
{
    groupBox4->setTitle( tr2i18n( "Fonts" ) );
    kcfg_UseCustomFonts->setText( tr2i18n( "&Use custom fonts" ) );
    QToolTip::add( kcfg_UseCustomFonts, tr2i18n( "Check to enable custom fonts." ) );
    QWhatsThis::add( kcfg_UseCustomFonts, tr2i18n( "Check to enable custom fonts." ) );
    fontGroupBox->setTitle( QString::null );
    textLabel1->setText( tr2i18n( "Player-window font:" ) );
    QToolTip::add( textLabel1, tr2i18n( "The font to use in the player window." ) );
    QWhatsThis::add( textLabel1, tr2i18n( "The font to use in the player window." ) );
    kcfg_PlayerWidgetFont->setSampleText( QString::null );
    QToolTip::add( kcfg_PlayerWidgetFont, tr2i18n( "The font to use in the player window." ) );
    QWhatsThis::add( kcfg_PlayerWidgetFont, tr2i18n( "The font to use in the player window." ) );
    textLabel3->setText( tr2i18n( "Playlist-window font:" ) );
    QToolTip::add( textLabel3, tr2i18n( "The font to use in the playlist window." ) );
    QWhatsThis::add( textLabel3, tr2i18n( "The font to use in the playlist window." ) );
    kcfg_PlaylistWindowFont->setSampleText( QString::null );
    QToolTip::add( kcfg_PlaylistWindowFont, tr2i18n( "The font to use in the playlist window." ) );
    QWhatsThis::add( kcfg_PlaylistWindowFont, tr2i18n( "The font to use in the playlist window." ) );
    textLabel3_2->setText( tr2i18n( "Context-browser font:" ) );
    QToolTip::add( textLabel3_2, tr2i18n( "The font to use in the context browser." ) );
    QWhatsThis::add( textLabel3_2, tr2i18n( "The font to use in the context browser." ) );
    kcfg_ContextBrowserFont->setSampleText( QString::null );
    QToolTip::add( kcfg_ContextBrowserFont, tr2i18n( "The font to use in the context browser." ) );
    QWhatsThis::add( kcfg_ContextBrowserFont, tr2i18n( "The font to use in the context browser." ) );
    groupBox3->setTitle( tr2i18n( "Color Scheme" ) );
    radioGroup->setTitle( QString::null );
    kcfg_SchemeCustom->setText( tr2i18n( "&Custom color scheme" ) );
    QToolTip::add( kcfg_SchemeCustom, tr2i18n( "If selected, amaroK uses the user-defined colors in the playlist." ) );
    QWhatsThis::add( kcfg_SchemeCustom, tr2i18n( "If selected, amaroK uses the user-defined colors in the playlist." ) );
    customSchemeBox->setTitle( QString::null );
    fgLabel->setText( tr2i18n( "Fo&reground:" ) );
    QWhatsThis::add( fgLabel, tr2i18n( "Selects the color to use as foreground color in the playlist." ) );
    kcfg_PlaylistWindowFgColor->setText( QString::null );
    QToolTip::add( kcfg_PlaylistWindowFgColor, tr2i18n( "Click to select the foreground text color in the playlist window." ) );
    QWhatsThis::add( kcfg_PlaylistWindowFgColor, tr2i18n( "Selects the color to use as foreground (text) color in the playlist." ) );
    bgColor->setText( tr2i18n( "&Background:" ) );
    QWhatsThis::add( bgColor, tr2i18n( "Selects the color to use as background color in the playlist." ) );
    kcfg_PlaylistWindowBgColor->setText( QString::null );
    QToolTip::add( kcfg_PlaylistWindowBgColor, tr2i18n( "Click to select the background color in the playlist window." ) );
    QWhatsThis::add( kcfg_PlaylistWindowBgColor, tr2i18n( "Selects the color to use as background color in the playlist." ) );
    kcfg_SchemeKDE->setText( tr2i18n( "The current &KDE color-scheme" ) );
    QToolTip::add( kcfg_SchemeKDE, tr2i18n( "If selected, amaroK uses the KDE standard colors in the playlist." ) );
    QWhatsThis::add( kcfg_SchemeKDE, tr2i18n( "If selected, amaroK uses the KDE standard colors in the playlist." ) );
    kcfg_SchemeAmarok->setText( tr2i18n( "The classic &amaroK, \"funky-monkey\", theme" ) );
    QToolTip::add( kcfg_SchemeAmarok, tr2i18n( "If selected, amaroK uses the amaroK standard colors in the playlist." ) );
    QWhatsThis::add( kcfg_SchemeAmarok, tr2i18n( "If selected, amaroK uses the amaroK standard colors in the playlist." ) );
    contextGroupBox->setTitle( tr2i18n( "Context Browser Style" ) );
    textLabel1_2->setText( tr2i18n( "Select a style:" ) );
    QToolTip::add( textLabel1_2, QString::null );
    QToolTip::add( styleComboBox, tr2i18n( "Select the style of the Context Browser." ) );
    QWhatsThis::add( styleComboBox, tr2i18n( "Select the style of the Context Browser." ) );
    installPushButton->setText( tr2i18n( "Install New Style..." ) );
    QToolTip::add( installPushButton, tr2i18n( "Click to install a new Context Browser style.<br>Tip: More styles can be found on <a href='http://kde-look.org'>http://kde-look.org</a>" ) );
    QWhatsThis::add( installPushButton, tr2i18n( "Select and install a new Context Browser style." ) );
    retrievePushButton->setText( tr2i18n( "Download Styles..." ) );
    QToolTip::add( retrievePushButton, tr2i18n( "Click to download new Context Browser styles." ) );
    QWhatsThis::add( retrievePushButton, tr2i18n( "Select and download new Context Browser styles." ) );
}

#include "Options2.moc"
