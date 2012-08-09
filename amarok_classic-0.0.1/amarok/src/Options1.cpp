#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options1.ui'
**
** Created: Ter Fev 19 16:01:25 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
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
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

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

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QVBoxLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    kcfg_ShowSplashscreen = new QCheckBox( groupBox1, "kcfg_ShowSplashscreen" );
    groupBox1Layout->addWidget( kcfg_ShowSplashscreen );

    kcfg_ShowTrayIcon = new QCheckBox( groupBox1, "kcfg_ShowTrayIcon" );
    groupBox1Layout->addWidget( kcfg_ShowTrayIcon );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 
    spacer3_2 = new QSpacerItem( 16, 21, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout5->addItem( spacer3_2 );

    kcfg_AnimateTrayIcon = new QCheckBox( groupBox1, "kcfg_AnimateTrayIcon" );
    kcfg_AnimateTrayIcon->setEnabled( FALSE );
    layout5->addWidget( kcfg_AnimateTrayIcon );
    groupBox1Layout->addLayout( layout5 );

    kcfg_ShowPlayerWindow = new QCheckBox( groupBox1, "kcfg_ShowPlayerWindow" );
    groupBox1Layout->addWidget( kcfg_ShowPlayerWindow );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    textLabel1 = new QLabel( groupBox1, "textLabel1" );
    layout4->addWidget( textLabel1 );

    kcfg_CoverPreviewSize = new QSpinBox( groupBox1, "kcfg_CoverPreviewSize" );
    kcfg_CoverPreviewSize->setMaxValue( 150 );
    kcfg_CoverPreviewSize->setMinValue( 50 );
    kcfg_CoverPreviewSize->setValue( 100 );
    layout4->addWidget( kcfg_CoverPreviewSize );
    spacer7 = new QSpacerItem( 30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer7 );
    groupBox1Layout->addLayout( layout4 );
    GeneralLayout->addWidget( groupBox1 );

    groupBox2 = new QGroupBox( this, "groupBox2" );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( 6 );
    groupBox2->layout()->setMargin( 11 );
    groupBox2Layout = new QVBoxLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    kcfg_SavePlaylist = new QCheckBox( groupBox2, "kcfg_SavePlaylist" );
    groupBox2Layout->addWidget( kcfg_SavePlaylist );

    kcfg_RelativePlaylist = new QCheckBox( groupBox2, "kcfg_RelativePlaylist" );
    groupBox2Layout->addWidget( kcfg_RelativePlaylist );

    kcfg_PlaylistFollowActive = new QCheckBox( groupBox2, "kcfg_PlaylistFollowActive" );
    groupBox2Layout->addWidget( kcfg_PlaylistFollowActive );

    kcfg_AutoShowContextBrowser = new QCheckBox( groupBox2, "kcfg_AutoShowContextBrowser" );
    groupBox2Layout->addWidget( kcfg_AutoShowContextBrowser );

    kcfg_ShowStatusBar = new QCheckBox( groupBox2, "kcfg_ShowStatusBar" );
    groupBox2Layout->addWidget( kcfg_ShowStatusBar );

    kcfg_ShowStatByAlbums = new QCheckBox( groupBox2, "kcfg_ShowStatByAlbums" );
    groupBox2Layout->addWidget( kcfg_ShowStatByAlbums );
    GeneralLayout->addWidget( groupBox2 );

    groupBox5 = new QGroupBox( this, "groupBox5" );
    groupBox5->setColumnLayout(0, Qt::Vertical );
    groupBox5->layout()->setSpacing( 6 );
    groupBox5->layout()->setMargin( 11 );
    groupBox5Layout = new QVBoxLayout( groupBox5->layout() );
    groupBox5Layout->setAlignment( Qt::AlignTop );

    textLabel2 = new QLabel( groupBox5, "textLabel2" );
    groupBox5Layout->addWidget( textLabel2 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 
    spacer3 = new QSpacerItem( 16, 21, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout3->addItem( spacer3 );

    layout2 = new QVBoxLayout( 0, 0, 6, "layout2"); 

    kcfg_RecodeID3v1Tags = new QCheckBox( groupBox5, "kcfg_RecodeID3v1Tags" );
    layout2->addWidget( kcfg_RecodeID3v1Tags );

    kcfg_RecodeShoutcastMetadata = new QCheckBox( groupBox5, "kcfg_RecodeShoutcastMetadata" );
    layout2->addWidget( kcfg_RecodeShoutcastMetadata );
    layout3->addLayout( layout2 );
    groupBox5Layout->addLayout( layout3 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    textLabel1_3 = new QLabel( groupBox5, "textLabel1_3" );
    textLabel1_3->setAlignment( int( QLabel::AlignVCenter ) );
    layout7->addWidget( textLabel1_3 );

    kcfg_RecodeEncoding = new QComboBox( FALSE, groupBox5, "kcfg_RecodeEncoding" );
    kcfg_RecodeEncoding->setEnabled( TRUE );
    kcfg_RecodeEncoding->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)0, 0, 0, kcfg_RecodeEncoding->sizePolicy().hasHeightForWidth() ) );
    layout7->addWidget( kcfg_RecodeEncoding );
    groupBox5Layout->addLayout( layout7 );
    GeneralLayout->addWidget( groupBox5 );
    spacer5 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    GeneralLayout->addItem( spacer5 );
    languageChange();
    resize( QSize(365, 548).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kcfg_ShowTrayIcon, SIGNAL( toggled(bool) ), kcfg_AnimateTrayIcon, SLOT( setEnabled(bool) ) );

    // buddies
    textLabel1->setBuddy( kcfg_CoverPreviewSize );
    textLabel1_3->setBuddy( kcfg_RecodeEncoding );
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
    groupBox1->setTitle( tr2i18n( "General Options" ) );
    kcfg_ShowSplashscreen->setText( tr2i18n( "Show splash-screen on start&up" ) );
    QToolTip::add( kcfg_ShowSplashscreen, tr2i18n( "Check to enable the splashscreen during amaroK startup." ) );
    QWhatsThis::add( kcfg_ShowSplashscreen, tr2i18n( "Check to enable the splashscreen during amaroK startup." ) );
    kcfg_ShowTrayIcon->setText( tr2i18n( "Show tra&y icon" ) );
    QToolTip::add( kcfg_ShowTrayIcon, tr2i18n( "Check to enable the amaroK system tray icon." ) );
    QWhatsThis::add( kcfg_ShowTrayIcon, tr2i18n( "Check to enable the amaroK system tray icon." ) );
    kcfg_AnimateTrayIcon->setText( tr2i18n( "&Flash tray icon when playing" ) );
    QToolTip::add( kcfg_AnimateTrayIcon, tr2i18n( "Check to animate the amaroK system tray icon." ) );
    QWhatsThis::add( kcfg_AnimateTrayIcon, tr2i18n( "Check to animate the amaroK system tray icon." ) );
    kcfg_ShowPlayerWindow->setText( tr2i18n( "Show player window (like &XMMS)" ) );
    QToolTip::add( kcfg_ShowPlayerWindow, tr2i18n( "Check to enable an extra player window." ) );
    QWhatsThis::add( kcfg_ShowPlayerWindow, tr2i18n( "Check to enable an extra player window." ) );
    textLabel1->setText( tr2i18n( "Default size for &cover previews:" ) );
    QToolTip::add( textLabel1, tr2i18n( "Size of the cover image in the context viewer in pixels." ) );
    QWhatsThis::add( textLabel1, tr2i18n( "Size of the cover image in the context viewer in pixels." ) );
    kcfg_CoverPreviewSize->setSuffix( tr2i18n( "px" ) );
    QToolTip::add( kcfg_CoverPreviewSize, tr2i18n( "Size of the cover images in the context viewer in pixels." ) );
    QWhatsThis::add( kcfg_CoverPreviewSize, tr2i18n( "Size of the cover images in the context viewer in pixels." ) );
    groupBox2->setTitle( tr2i18n( "Playlist-Window Options" ) );
    kcfg_SavePlaylist->setText( tr2i18n( "&Remember current playlist on exit" ) );
    QToolTip::add( kcfg_SavePlaylist, tr2i18n( "If checked, amaroK saves the current playlist on quit and restores it when restarted.<br>" ) );
    QWhatsThis::add( kcfg_SavePlaylist, tr2i18n( "If checked, amaroK saves the current playlist\\non quit and restores it when restarted." ) );
    kcfg_RelativePlaylist->setText( tr2i18n( "&Manually saved playlists use relative path" ) );
    QToolTip::add( kcfg_RelativePlaylist, tr2i18n( "If checked, amaroK uses a relative path for the tracks of manually saved playlists" ) );
    QWhatsThis::add( kcfg_RelativePlaylist, tr2i18n( "If checked, amaroK uses a relative path for the tracks of manually saved playlists" ) );
    kcfg_PlaylistFollowActive->setText( tr2i18n( "&Keep the active song visible on track change" ) );
    QToolTip::add( kcfg_PlaylistFollowActive, tr2i18n( "If checked, the playlist scrolls on song change to make the currently playing item visible in the playlist. Measures are taken not to scroll if inappropriate.<br>" ) );
    QWhatsThis::add( kcfg_PlaylistFollowActive, tr2i18n( "If checked, the playlist scrolls on song change to make the currently playing item visible in the playlist. Measures are taken not to scroll if inappropriate." ) );
    kcfg_AutoShowContextBrowser->setText( tr2i18n( "Switch to Context Browser on track ch&ange" ) );
    QToolTip::add( kcfg_AutoShowContextBrowser, tr2i18n( "Switch to the context browser, when playing a track.<br>" ) );
    QWhatsThis::add( kcfg_AutoShowContextBrowser, tr2i18n( "Switch to the context browser, when playing a track." ) );
    kcfg_ShowStatusBar->setText( tr2i18n( "Show s&tatusbar" ) );
    QToolTip::add( kcfg_ShowStatusBar, tr2i18n( "Check to enable the statusbar on the playlist window.<br>" ) );
    QWhatsThis::add( kcfg_ShowStatusBar, tr2i18n( "Check to enable the statusbar on the playlist window." ) );
    kcfg_ShowStatByAlbums->setText( tr2i18n( "Show statistics by a&lbums" ) );
    QToolTip::add( kcfg_ShowStatByAlbums, tr2i18n( "Show statistics by albums in the context browser.<br>" ) );
    QWhatsThis::add( kcfg_ShowStatByAlbums, tr2i18n( "Show statistics by albums in the context browser." ) );
    groupBox5->setTitle( tr2i18n( "Encodings" ) );
    textLabel2->setText( tr2i18n( "Do not decode the following as latin1:" ) );
    kcfg_RecodeID3v1Tags->setText( tr2i18n( "ID&3v1 tags" ) );
    kcfg_RecodeID3v1Tags->setAccel( QKeySequence( tr2i18n( "Alt+3" ) ) );
    QToolTip::add( kcfg_RecodeID3v1Tags, QString::null );
    QWhatsThis::add( kcfg_RecodeID3v1Tags, tr2i18n( "Decode ID3v1 tags (used by some MP3 files) using the character set specified below." ) );
    kcfg_RecodeShoutcastMetadata->setText( tr2i18n( "&Shoutcast metadata" ) );
    QWhatsThis::add( kcfg_RecodeShoutcastMetadata, tr2i18n( "Decode the title and artist information of Shoutcast music streams using the character set specified below." ) );
    textLabel1_3->setText( tr2i18n( "Instead &decode using this character set:" ) );
    QToolTip::add( kcfg_RecodeEncoding, QString::null );
    QWhatsThis::add( kcfg_RecodeEncoding, tr2i18n( "If ID3v1 or Shoutcast metadata is checked, it will decode them using this character encoding." ) );
}

#include "Options1.moc"
