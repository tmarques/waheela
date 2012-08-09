#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options5.ui'
**
** Created: Sex Mar 23 10:42:30 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "Options5.h"

#include <qvariant.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <kfontrequester.h>
#include <qlabel.h>
#include <kcolorbutton.h>
#include <ktextedit.h>
#include <knuminput.h>
#include <kcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "ktextedit.h"
#include "./Options5.ui.h"

/*
 *  Constructs a Options5 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Options5::Options5( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Options5" );
    Options5Layout = new QVBoxLayout( this, 0, 6, "Options5Layout"); 

    kcfg_OsdEnabled = new QCheckBox( this, "kcfg_OsdEnabled" );
    kcfg_OsdEnabled->setChecked( TRUE );
    Options5Layout->addWidget( kcfg_OsdEnabled );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 
    spacer2 = new QSpacerItem( 16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout2->addItem( spacer2 );

    mainBox = new QGroupBox( this, "mainBox" );
    mainBox->setFrameShape( QGroupBox::NoFrame );
    mainBox->setColumnLayout(0, Qt::Vertical );
    mainBox->layout()->setSpacing( 6 );
    mainBox->layout()->setMargin( 0 );
    mainBoxLayout = new QVBoxLayout( mainBox->layout() );
    mainBoxLayout->setAlignment( Qt::AlignTop );

    fontBox = new QGroupBox( mainBox, "fontBox" );
    fontBox->setFrameShape( QGroupBox::GroupBoxPanel );
    fontBox->setFrameShadow( QGroupBox::Sunken );
    fontBox->setLineWidth( 1 );
    fontBox->setFlat( FALSE );
    fontBox->setColumnLayout(0, Qt::Vertical );
    fontBox->layout()->setSpacing( 6 );
    fontBox->layout()->setMargin( 11 );
    fontBoxLayout = new QVBoxLayout( fontBox->layout() );
    fontBoxLayout->setAlignment( Qt::AlignTop );

    kcfg_OsdFont = new KFontRequester( fontBox, "kcfg_OsdFont" );
    QFont kcfg_OsdFont_font(  kcfg_OsdFont->font() );
    kcfg_OsdFont->setFont( kcfg_OsdFont_font ); 
    fontBoxLayout->addWidget( kcfg_OsdFont );

    kcfg_OsdDrawShadow = new QCheckBox( fontBox, "kcfg_OsdDrawShadow" );
    fontBoxLayout->addWidget( kcfg_OsdDrawShadow );
    mainBoxLayout->addWidget( fontBox );

    groupBox9 = new QGroupBox( mainBox, "groupBox9" );
    groupBox9->setColumnLayout(0, Qt::Vertical );
    groupBox9->layout()->setSpacing( 6 );
    groupBox9->layout()->setMargin( 11 );
    groupBox9Layout = new QVBoxLayout( groupBox9->layout() );
    groupBox9Layout->setAlignment( Qt::AlignTop );

    layout3 = new QVBoxLayout( 0, 0, 2, "layout3"); 

    kcfg_OsdUseCustomColors = new QCheckBox( groupBox9, "kcfg_OsdUseCustomColors" );
    layout3->addWidget( kcfg_OsdUseCustomColors );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 
    spacer1 = new QSpacerItem( 16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    colorsBox = new QGroupBox( groupBox9, "colorsBox" );
    colorsBox->setEnabled( FALSE );
    colorsBox->setFrameShape( QGroupBox::NoFrame );
    colorsBox->setFlat( FALSE );
    colorsBox->setColumnLayout(0, Qt::Vertical );
    colorsBox->layout()->setSpacing( 6 );
    colorsBox->layout()->setMargin( 0 );
    colorsBoxLayout = new QGridLayout( colorsBox->layout() );
    colorsBoxLayout->setAlignment( Qt::AlignTop );

    textLabel2_2 = new QLabel( colorsBox, "textLabel2_2" );
    textLabel2_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 1, 0, textLabel2_2->sizePolicy().hasHeightForWidth() ) );
    textLabel2_2->setFrameShape( QLabel::NoFrame );

    colorsBoxLayout->addWidget( textLabel2_2, 1, 0 );

    kcfg_OsdTextColor = new KColorButton( colorsBox, "kcfg_OsdTextColor" );
    kcfg_OsdTextColor->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 2, 0, kcfg_OsdTextColor->sizePolicy().hasHeightForWidth() ) );
    kcfg_OsdTextColor->setColor( QColor( 255, 0, 0 ) );

    colorsBoxLayout->addWidget( kcfg_OsdTextColor, 0, 1 );

    kcfg_OsdBackgroundColor = new KColorButton( colorsBox, "kcfg_OsdBackgroundColor" );
    kcfg_OsdBackgroundColor->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 2, 0, kcfg_OsdBackgroundColor->sizePolicy().hasHeightForWidth() ) );
    kcfg_OsdBackgroundColor->setColor( QColor( 255, 0, 0 ) );

    colorsBoxLayout->addWidget( kcfg_OsdBackgroundColor, 1, 1 );

    textLabel2 = new QLabel( colorsBox, "textLabel2" );
    textLabel2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 1, 0, textLabel2->sizePolicy().hasHeightForWidth() ) );

    colorsBoxLayout->addWidget( textLabel2, 0, 0 );
    layout1->addWidget( colorsBox );
    layout3->addLayout( layout1 );
    groupBox9Layout->addLayout( layout3 );

    kcfg_OsdUseFakeTranslucency = new QCheckBox( groupBox9, "kcfg_OsdUseFakeTranslucency" );
    groupBox9Layout->addWidget( kcfg_OsdUseFakeTranslucency );
    mainBoxLayout->addWidget( groupBox9 );

    osdText = new QGroupBox( mainBox, "osdText" );
    osdText->setFrameShape( QGroupBox::GroupBoxPanel );
    osdText->setFlat( FALSE );
    osdText->setColumnLayout(0, Qt::Vertical );
    osdText->layout()->setSpacing( 6 );
    osdText->layout()->setMargin( 11 );
    osdTextLayout = new QVBoxLayout( osdText->layout() );
    osdTextLayout->setAlignment( Qt::AlignTop );

    kcfg_OsdUsePlaylistColumns = new QCheckBox( osdText, "kcfg_OsdUsePlaylistColumns" );
    osdTextLayout->addWidget( kcfg_OsdUsePlaylistColumns );

    kcfg_OsdText = new KTextEdit( osdText, "kcfg_OsdText" );
    kcfg_OsdText->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, kcfg_OsdText->sizePolicy().hasHeightForWidth() ) );
    kcfg_OsdText->setLineWidth( 2 );
    kcfg_OsdText->setTextFormat( KTextEdit::PlainText );
    kcfg_OsdText->setTabChangesFocus( TRUE );
    osdTextLayout->addWidget( kcfg_OsdText );
    mainBoxLayout->addWidget( osdText );

    groupBox22 = new QGroupBox( mainBox, "groupBox22" );
    groupBox22->setColumnLayout(0, Qt::Vertical );
    groupBox22->layout()->setSpacing( 6 );
    groupBox22->layout()->setMargin( 11 );
    groupBox22Layout = new QGridLayout( groupBox22->layout() );
    groupBox22Layout->setAlignment( Qt::AlignTop );

    textLabel1 = new QLabel( groupBox22, "textLabel1" );

    groupBox22Layout->addWidget( textLabel1, 0, 0 );

    kcfg_OsdDuration = new KIntSpinBox( groupBox22, "kcfg_OsdDuration" );
    kcfg_OsdDuration->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 2, 0, kcfg_OsdDuration->sizePolicy().hasHeightForWidth() ) );
    kcfg_OsdDuration->setButtonSymbols( KIntSpinBox::UpDownArrows );
    kcfg_OsdDuration->setMaxValue( 600000 );
    kcfg_OsdDuration->setMinValue( 0 );
    kcfg_OsdDuration->setLineStep( 1000 );
    kcfg_OsdDuration->setValue( 5000 );

    groupBox22Layout->addWidget( kcfg_OsdDuration, 0, 1 );

    kcfg_OsdScreen = new KComboBox( FALSE, groupBox22, "kcfg_OsdScreen" );
    kcfg_OsdScreen->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 2, 0, kcfg_OsdScreen->sizePolicy().hasHeightForWidth() ) );

    groupBox22Layout->addWidget( kcfg_OsdScreen, 0, 3 );

    textLabel2_3 = new QLabel( groupBox22, "textLabel2_3" );

    groupBox22Layout->addWidget( textLabel2_3, 0, 2 );
    mainBoxLayout->addWidget( groupBox22 );
    layout2->addWidget( mainBox );
    Options5Layout->addLayout( layout2 );
    languageChange();
    resize( QSize(481, 472).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kcfg_OsdUseCustomColors, SIGNAL( toggled(bool) ), colorsBox, SLOT( setEnabled(bool) ) );
    connect( kcfg_OsdEnabled, SIGNAL( toggled(bool) ), mainBox, SLOT( setEnabled(bool) ) );
    connect( kcfg_OsdUseCustomColors, SIGNAL( toggled(bool) ), this, SLOT( useCustomColorsToggled(bool) ) );
    connect( kcfg_OsdUsePlaylistColumns, SIGNAL( toggled(bool) ), kcfg_OsdText, SLOT( setDisabled(bool) ) );

    // buddies
    textLabel1->setBuddy( kcfg_OsdDuration );
    textLabel2_3->setBuddy( kcfg_OsdScreen );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
Options5::~Options5()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Options5::languageChange()
{
    kcfg_OsdEnabled->setText( tr2i18n( "&Use On-Screen-Display" ) );
    QToolTip::add( kcfg_OsdEnabled, tr2i18n( "Check to enable the On-Screen-Display. <br>The OSD briefly displays track data when a new track is played." ) );
    QWhatsThis::add( kcfg_OsdEnabled, tr2i18n( "Check to enable the On-Screen-Display. The OSD briefly displays track data when a new track is played." ) );
    mainBox->setTitle( QString::null );
    fontBox->setTitle( tr2i18n( "&Font" ) );
    kcfg_OsdFont->setSampleText( QString::null );
    QToolTip::add( kcfg_OsdFont, tr2i18n( "The font to use for the On-Screen Display." ) );
    QWhatsThis::add( kcfg_OsdFont, tr2i18n( "The font to use for the On-Screen Display." ) );
    kcfg_OsdDrawShadow->setText( tr2i18n( "Draw &shadow" ) );
    groupBox9->setTitle( tr2i18n( "C&olors" ) );
    kcfg_OsdUseCustomColors->setText( tr2i18n( "Use &custom colors" ) );
    QToolTip::add( kcfg_OsdUseCustomColors, tr2i18n( "Check to enable custom colors for the On-Screen-Display." ) );
    QWhatsThis::add( kcfg_OsdUseCustomColors, tr2i18n( "Check to enable custom colors for the On-Screen-Display." ) );
    colorsBox->setTitle( QString::null );
    textLabel2_2->setText( tr2i18n( "Background color:" ) );
    QWhatsThis::add( textLabel2_2, tr2i18n( "The color of the OSD background." ) );
    kcfg_OsdTextColor->setText( QString::null );
    QToolTip::add( kcfg_OsdTextColor, tr2i18n( "Click to select the color of the OSD text." ) );
    QWhatsThis::add( kcfg_OsdTextColor, tr2i18n( "The color of the OSD text." ) );
    kcfg_OsdBackgroundColor->setText( QString::null );
    QToolTip::add( kcfg_OsdBackgroundColor, tr2i18n( "Click to select the background color of the OSD." ) );
    QWhatsThis::add( kcfg_OsdBackgroundColor, tr2i18n( "The color of the OSD background." ) );
    textLabel2->setText( tr2i18n( "Text color:" ) );
    QWhatsThis::add( textLabel2, tr2i18n( "The color of the OSD text." ) );
    kcfg_OsdUseFakeTranslucency->setText( tr2i18n( "Make the &background translucent" ) );
    osdText->setTitle( tr2i18n( "Display &Text" ) );
    kcfg_OsdUsePlaylistColumns->setText( tr2i18n( "Display the same information as the columns in the playlist" ) );
    groupBox22->setTitle( QString::null );
    textLabel1->setText( tr2i18n( "&Duration:" ) );
    kcfg_OsdDuration->setSuffix( tr2i18n( " ms" ) );
    kcfg_OsdDuration->setSpecialValueText( tr2i18n( "Forever" ) );
    QToolTip::add( kcfg_OsdDuration, tr2i18n( "The time in milliseconds to show the OSD. The value must be between 500 ms and 10000 ms." ) );
    QWhatsThis::add( kcfg_OsdDuration, tr2i18n( "The time in milliseconds to show the OSD. The value must be between 500 ms and 10000 ms." ) );
    QToolTip::add( kcfg_OsdScreen, tr2i18n( "The screen that should display the OSD." ) );
    QWhatsThis::add( kcfg_OsdScreen, tr2i18n( "The screen that should display the OSD." ) );
    textLabel2_3->setText( tr2i18n( "Sc&reen:" ) );
}

#include "Options5.moc"
