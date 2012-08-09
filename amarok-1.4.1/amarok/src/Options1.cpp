#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options1.ui'
**
** Created: Fri Mar 23 10:56:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "Options1.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <kcombobox.h>
#include <klineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kcombobox.h"
#include "klineedit.h"
#include "./Options1.ui.h"

/*
 *  Constructs a Options1 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Options1::Options1( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "General" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, sizePolicy().hasHeightForWidth() ) );
    GeneralLayout = new QVBoxLayout( this, 0, 6, "GeneralLayout"); 

    generalBox = new QGroupBox( this, "generalBox" );
    generalBox->setMargin( 0 );
    generalBox->setColumnLayout(0, Qt::Vertical );
    generalBox->layout()->setSpacing( 6 );
    generalBox->layout()->setMargin( 11 );
    generalBoxLayout = new QVBoxLayout( generalBox->layout() );
    generalBoxLayout->setAlignment( Qt::AlignTop );

    kcfg_ShowSplashscreen = new QCheckBox( generalBox, "kcfg_ShowSplashscreen" );
    generalBoxLayout->addWidget( kcfg_ShowSplashscreen );

    kcfg_ShowTrayIcon = new QCheckBox( generalBox, "kcfg_ShowTrayIcon" );
    generalBoxLayout->addWidget( kcfg_ShowTrayIcon );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 
    spacer3_2 = new QSpacerItem( 16, 21, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout5->addItem( spacer3_2 );

    kcfg_AnimateTrayIcon = new QCheckBox( generalBox, "kcfg_AnimateTrayIcon" );
    kcfg_AnimateTrayIcon->setEnabled( FALSE );
    layout5->addWidget( kcfg_AnimateTrayIcon );
    generalBoxLayout->addLayout( layout5 );

    kcfg_ShowPlayerWindow = new QCheckBox( generalBox, "kcfg_ShowPlayerWindow" );
    generalBoxLayout->addWidget( kcfg_ShowPlayerWindow );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    textLabel1 = new QLabel( generalBox, "textLabel1" );
    layout4->addWidget( textLabel1 );

    kcfg_CoverPreviewSize = new QSpinBox( generalBox, "kcfg_CoverPreviewSize" );
    kcfg_CoverPreviewSize->setMaxValue( 150 );
    kcfg_CoverPreviewSize->setMinValue( 50 );
    kcfg_CoverPreviewSize->setValue( 100 );
    layout4->addWidget( kcfg_CoverPreviewSize );
    spacer7 = new QSpacerItem( 30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer7 );
    generalBoxLayout->addLayout( layout4 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    textLabel1_2 = new QLabel( generalBox, "textLabel1_2" );
    textLabel1_2->setMinimumSize( QSize( 150, 0 ) );
    layout7->addWidget( textLabel1_2 );

    kComboBox_browser = new KComboBox( FALSE, generalBox, "kComboBox_browser" );
    kComboBox_browser->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_browser->sizePolicy().hasHeightForWidth() ) );
    kComboBox_browser->setMinimumSize( QSize( 150, 0 ) );
    layout7->addWidget( kComboBox_browser );
    spacer7_2 = new QSpacerItem( 50, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout7->addItem( spacer7_2 );
    generalBoxLayout->addLayout( layout7 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    checkBox_customBrowser = new QCheckBox( generalBox, "checkBox_customBrowser" );
    checkBox_customBrowser->setEnabled( TRUE );
    checkBox_customBrowser->setMinimumSize( QSize( 150, 0 ) );
    layout8->addWidget( checkBox_customBrowser );

    kLineEdit_customBrowser = new KLineEdit( generalBox, "kLineEdit_customBrowser" );
    kLineEdit_customBrowser->setEnabled( FALSE );
    kLineEdit_customBrowser->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kLineEdit_customBrowser->sizePolicy().hasHeightForWidth() ) );
    kLineEdit_customBrowser->setMinimumSize( QSize( 150, 0 ) );
    layout8->addWidget( kLineEdit_customBrowser );
    spacer7_2_3 = new QSpacerItem( 50, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout8->addItem( spacer7_2_3 );
    generalBoxLayout->addLayout( layout8 );
    GeneralLayout->addWidget( generalBox );

    componentsBox = new QGroupBox( this, "componentsBox" );
    componentsBox->setMargin( 0 );
    componentsBox->setColumnLayout(0, Qt::Vertical );
    componentsBox->layout()->setSpacing( 6 );
    componentsBox->layout()->setMargin( 11 );
    componentsBoxLayout = new QVBoxLayout( componentsBox->layout() );
    componentsBoxLayout->setAlignment( Qt::AlignTop );

    kcfg_UseScores = new QCheckBox( componentsBox, "kcfg_UseScores" );
    kcfg_UseScores->setChecked( FALSE );
    componentsBoxLayout->addWidget( kcfg_UseScores );

    kcfg_UseRatings = new QCheckBox( componentsBox, "kcfg_UseRatings" );
    componentsBoxLayout->addWidget( kcfg_UseRatings );
    GeneralLayout->addWidget( componentsBox );

    groupBox2 = new QGroupBox( this, "groupBox2" );
    groupBox2->setMargin( 0 );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( 6 );
    groupBox2->layout()->setMargin( 11 );
    groupBox2Layout = new QVBoxLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    kcfg_SavePlaylist = new QCheckBox( groupBox2, "kcfg_SavePlaylist" );
    groupBox2Layout->addWidget( kcfg_SavePlaylist );

    kcfg_RelativePlaylist = new QCheckBox( groupBox2, "kcfg_RelativePlaylist" );
    groupBox2Layout->addWidget( kcfg_RelativePlaylist );
    GeneralLayout->addWidget( groupBox2 );
    spacer5 = new QSpacerItem( 20, 152, QSizePolicy::Minimum, QSizePolicy::Expanding );
    GeneralLayout->addItem( spacer5 );
    languageChange();
    resize( QSize(417, 686).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kcfg_ShowTrayIcon, SIGNAL( toggled(bool) ), kcfg_AnimateTrayIcon, SLOT( setEnabled(bool) ) );
    connect( checkBox_customBrowser, SIGNAL( toggled(bool) ), kComboBox_browser, SLOT( setDisabled(bool) ) );
    connect( checkBox_customBrowser, SIGNAL( toggled(bool) ), kLineEdit_customBrowser, SLOT( setEnabled(bool) ) );

    // buddies
    textLabel1->setBuddy( kcfg_CoverPreviewSize );
    textLabel1_2->setBuddy( kComboBox_browser );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
Options1::~Options1()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Options1::languageChange()
{
    setCaption( tr2i18n( "General" ) );
    generalBox->setTitle( tr2i18n( "General Options" ) );
    kcfg_ShowSplashscreen->setText( tr2i18n( "Sho&w splash-screen on startup" ) );
    QToolTip::add( kcfg_ShowSplashscreen, tr2i18n( "Check to enable the splashscreen during Amarok startup." ) );
    QWhatsThis::add( kcfg_ShowSplashscreen, tr2i18n( "Check to enable the splashscreen during Amarok startup." ) );
    kcfg_ShowTrayIcon->setText( tr2i18n( "Show tray &icon" ) );
    QToolTip::add( kcfg_ShowTrayIcon, tr2i18n( "Check to enable the Amarok system tray icon." ) );
    QWhatsThis::add( kcfg_ShowTrayIcon, tr2i18n( "Check to enable the Amarok system tray icon." ) );
    kcfg_AnimateTrayIcon->setText( tr2i18n( "&Flash tray icon when playing" ) );
    QToolTip::add( kcfg_AnimateTrayIcon, tr2i18n( "Check to animate the Amarok system tray icon." ) );
    QWhatsThis::add( kcfg_AnimateTrayIcon, tr2i18n( "Check to animate the Amarok system tray icon." ) );
    kcfg_ShowPlayerWindow->setText( tr2i18n( "Show player window" ) );
    QToolTip::add( kcfg_ShowPlayerWindow, tr2i18n( "Check to enable an extra player window." ) );
    QWhatsThis::add( kcfg_ShowPlayerWindow, tr2i18n( "Check to enable an extra player window." ) );
    textLabel1->setText( tr2i18n( "Default si&ze for cover previews:" ) );
    QToolTip::add( textLabel1, tr2i18n( "Size of the cover image in the context viewer in pixels." ) );
    QWhatsThis::add( textLabel1, tr2i18n( "Size of the cover image in the context viewer in pixels." ) );
    kcfg_CoverPreviewSize->setSuffix( tr2i18n( "px" ) );
    QToolTip::add( kcfg_CoverPreviewSize, tr2i18n( "Size of the cover images in the context viewer in pixels." ) );
    QWhatsThis::add( kcfg_CoverPreviewSize, tr2i18n( "Size of the cover images in the context viewer in pixels." ) );
    textLabel1_2->setText( tr2i18n( "External web &browser:" ) );
    QToolTip::add( kComboBox_browser, tr2i18n( "Choose the external web browser to be used by Amarok." ) );
    checkBox_customBrowser->setText( tr2i18n( "Use &another browser:" ) );
    QToolTip::add( kLineEdit_customBrowser, tr2i18n( "Enter filename of external web browser." ) );
    componentsBox->setTitle( tr2i18n( "Components" ) );
    kcfg_UseScores->setText( tr2i18n( "Use &scores" ) );
    QToolTip::add( kcfg_UseScores, tr2i18n( "Scores for tracks are calculated automatically, based on your listening habits." ) );
    kcfg_UseRatings->setText( tr2i18n( "Use ratings" ) );
    QToolTip::add( kcfg_UseRatings, tr2i18n( "You can assign ratings to tracks manually, from 1 to 5 stars." ) );
    groupBox2->setTitle( tr2i18n( "Playlist-Window Options" ) );
    kcfg_SavePlaylist->setText( tr2i18n( "&Remember current playlist on exit" ) );
    QToolTip::add( kcfg_SavePlaylist, tr2i18n( "If checked, Amarok saves the current playlist on quit and restores it when restarted.<br>" ) );
    QWhatsThis::add( kcfg_SavePlaylist, tr2i18n( "If checked, Amarok saves the current playlist on quit and restores it when restarted." ) );
    kcfg_RelativePlaylist->setText( tr2i18n( "Manually sa&ved playlists use relative path" ) );
    QToolTip::add( kcfg_RelativePlaylist, tr2i18n( "If checked, Amarok uses a relative path for the tracks of manually saved playlists" ) );
    QWhatsThis::add( kcfg_RelativePlaylist, tr2i18n( "If checked, Amarok uses a relative path for the tracks of manually saved playlists" ) );
}

#include "Options1.moc"
