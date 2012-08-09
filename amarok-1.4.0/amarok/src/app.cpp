/***************************************************************************
                      app.cpp  -  description
                         -------------------
begin                : Mit Okt 23 14:35:18 CEST 2002
copyright            : (C) 2002 by Mark Kretschmann
email                : markey@web.de
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "amarok.h"
#include "amarokconfig.h"
#include "amarokdcophandler.h"
#include "app.h"
#include "config.h"
#include "configdialog.h"
#include "contextbrowser.h"
#include "collectionbrowser.h"
#include "dbsetup.h"             //firstRunWizard()
#include "debug.h"
#include "devicemanager.h"
#include "effectwidget.h"
#include "enginebase.h"
#include "enginecontroller.h"
#include "equalizersetup.h"
#include "firstrunwizard.h"
#include "metabundle.h"
#include "osd.h"
#include "playerwindow.h"
#include "playlist.h"
#include "playlistwindow.h"
#include "pluginmanager.h"
#include "refreshimages.h"
#include "scriptmanager.h"
#include "scrobbler.h"
#include "statusbar.h"
#include "systray.h"
#include "threadweaver.h"
#include "tracktooltip.h"        //engineNewMetaData()

#include <iostream>

#include <kconfigdialogmanager.h>
#include <kcombobox.h>           //firstRunWizard()
#include <kcmdlineargs.h>        //initCliArgs()
#include <kcursor.h>             //amaroK::OverrideCursor
#include <kedittoolbar.h>        //slotConfigToolbars()
#include <kglobalaccel.h>        //initGlobalShortcuts()
#include <kglobalsettings.h>     //applyColorScheme()
#include <kiconloader.h>         //amarok Icon
#include <kkeydialog.h>          //slotConfigShortcuts()
#include <klocale.h>
#include <kmessagebox.h>         //applySettings(), genericEventHandler()
#include <krun.h>                //amaroK::invokeBrowser()
#include <kstandarddirs.h>
#include <kurldrag.h>            //genericEventHandler()
#include <kaboutdata.h>
#include <kio/job.h>

#include <qevent.h>              //genericEventHandler()
#include <qeventloop.h>          //applySettings()
#include <qfile.h>
#include <qobjectlist.h>         //applyColorScheme()
#include <qpalette.h>            //applyColorScheme()
#include <qpixmap.h>             //QPixmap::setDefaultOptimization()
#include <qpopupmenu.h>          //genericEventHandler
#include <qtimer.h>              //showHyperThreadingWarning()
#include <qtooltip.h>            //default tooltip for trayicon

// For the HyperThreading fix
#ifdef __linux__
    #ifdef SCHEDAFFINITY_SUPPORT
        #include <errno.h>
        #include <sched.h>
    #endif //SCHEDAFFINITY_SUPPORT
#endif //__linux__

int App::mainThreadId = 0;

LIBAMAROK_EXPORT KAboutData aboutData( "amarok",
    I18N_NOOP( "amaroK" ), APP_VERSION,
    I18N_NOOP( "The audio player for KDE" ), KAboutData::License_GPL,
    I18N_NOOP( "(C) 2002-2003, Mark Kretschmann\n(C) 2003-2006, The amaroK Development Squad" ),
    I18N_NOOP( "IRC:\nirc.freenode.net - #amarok, #amarok.de\n\nFeedback:\namarok-devel@lists.sourceforge.net\n\n(Build Date: " __DATE__ ")" ),
             ( "http://amarok.kde.org" ) );

App::App()
        : KApplication()
        , m_pPlayerWindow( 0 ) //will be created in applySettings()
{
    DEBUG_BLOCK

    const KCmdLineArgs* const args = KCmdLineArgs::parsedArgs();
    bool restoreSession = args->count() == 0 || args->isSet( "append" ) || args->isSet( "enqueue" )
                                || amaroK::config()->readBoolEntry( "AppendAsDefault", false );    

    QPixmap::setDefaultOptimization( QPixmap::MemoryOptim );

    //needs to be created before the wizard
    new amaroK::DcopPlayerHandler(); // Must be created first
    new amaroK::DcopPlaylistHandler();
    new amaroK::DcopPlaylistBrowserHandler();
    new amaroK::DcopContextBrowserHandler();
    new amaroK::DcopCollectionHandler();
    new amaroK::DcopMediaBrowserHandler();
    new amaroK::DcopScriptHandler();
    new amaroK::DcopDevicesHandler();

    // Remember old folder setup, so we can detect changes after the wizard was used
    const QStringList oldCollectionFolders = AmarokConfig::collectionFolders();

    if ( amaroK::config()->readBoolEntry( "First Run", true ) || args->isSet( "wizard" ) ) {
        std::cout << "STARTUP\n" << std::flush; //hide the splashscreen
        firstRunWizard();
        amaroK::config()->writeEntry( "First Run", false );
        amaroK::config()->sync();
    }

    fixHyperThreading();

    m_pDeviceManager = DeviceManager::instance();

    m_pGlobalAccel    = new KGlobalAccel( this );
    m_pPlaylistWindow = new PlaylistWindow();
    m_pTray           = new amaroK::TrayIcon( m_pPlaylistWindow );

    m_pPlaylistWindow->init(); //creates the playlist, browsers, etc.
    initGlobalShortcuts();

    //load previous playlist in separate thread
    if ( restoreSession && AmarokConfig::savePlaylist() )
        Playlist::instance()->restoreSession();

    if( args->isSet( "engine" ) ) {
        // we correct some common errors (case issues, missing -engine off the end)
        QString engine = args->getOption( "engine" ).lower();
        if( engine.startsWith( "gstreamer" ) ) engine = "gst-engine";
        if( !engine.endsWith( "engine" ) ) engine += "-engine";

        AmarokConfig::setSoundSystem( engine );
    }

    //create engine, show PlayerWindow, show TrayIcon etc.
    applySettings( true );

    // Start ScriptManager. Must be created _after_ PlaylistWindow.
    ScriptManager::instance();

    //notify loader application that we have started
    std::cout << "STARTUP\n" << std::flush;

    //after this point only analyzer and temporary pixmaps will be created
    QPixmap::setDefaultOptimization( QPixmap::BestOptim );

    //do after applySettings(), or the OSD will flicker and other wierdness!
    //do before restoreSession()!
    EngineController::instance()->attach( this );

    //set a default interface
    engineStateChanged( Engine::Empty );

    if ( AmarokConfig::resumePlayback() && restoreSession && !args->isSet( "stop" ) ) {
        //restore session as long as the user didn't specify media to play etc.
        //do this after applySettings() so OSD displays correctly
        EngineController::instance()->restoreSession();
    }

    // Refetch covers every 80 days to comply with Amazon license
    #ifdef AMAZON_SUPPORT
    new RefreshImages();
    #endif

    // Trigger collection scan if folder setup was changed by wizard
    if ( oldCollectionFolders != AmarokConfig::collectionFolders() )
        QTimer::singleShot( 0, CollectionDB::instance(), SLOT( startScan() ) );
    // If database version is updated, the collection needs to be rescanned.
    // Works also if the collection is empty for some other reason
    // (e.g. deleted collection.db)
    else if ( CollectionDB::instance()->isEmpty() )
    {
        QTimer::singleShot( 0, CollectionDB::instance(), SLOT( startScan() ) );
    }
    else if ( AmarokConfig::monitorChanges() )
        QTimer::singleShot( 0, CollectionDB::instance(), SLOT( scanModifiedDirs() ) );


    handleCliArgs();
}

App::~App()
{
    DEBUG_BLOCK

    // Hiding the OSD before exit prevents crash
    amaroK::OSD::instance()->hide();

    EngineBase* const engine = EngineController::engine();

    if ( AmarokConfig::resumePlayback() ) {
        if ( engine->state() != Engine::Empty ) {
            AmarokConfig::setResumeTrack( EngineController::instance()->playingURL().prettyURL() );
            AmarokConfig::setResumeTime( engine->position() );
        }
        else AmarokConfig::setResumeTrack( QString::null ); //otherwise it'll play previous resume next time!
    }

    EngineController::instance()->endSession(); //records final statistics
    EngineController::instance()->detach( this );

    // do even if trayicon is not shown, it is safe
    amaroK::config()->writeEntry( "HiddenOnExit", mainWindow()->isHidden() );

    CollectionDB::instance()->stopScan();
    ThreadWeaver::instance()->abortAllJobsNamed( "CreateMood" ); //these take forever

    delete m_pPlayerWindow;   //sets some XT keys
    delete m_pPlaylistWindow; //sets some XT keys

    ThreadWeaver::deleteInstance(); //waits for jobs to finish

    // this must be deleted before the connection to the Xserver is
    // severed, or we risk a crash when the QApplication is exited,
    // I asked Trolltech! *smug*
    delete amaroK::OSD::instance();

    AmarokConfig::setVersion( APP_VERSION );
    AmarokConfig::writeConfig();

    //need to unload the engine before the kapplication is destroyed
    PluginManager::unload( engine );
}


#include <dcopref.h>
#include <qstringlist.h>

namespace
{
    // grabbed from KsCD source, kompatctdisk.cpp
    QString urlToDevice(const QString& device)
    {
        KURL deviceUrl(device);
        if (deviceUrl.protocol() == "media" || deviceUrl.protocol() == "system")
        {
            DCOPRef mediamanager( "kded", "mediamanager" );
            DCOPReply reply = mediamanager.call( "properties(QString)", deviceUrl.fileName() );
            QStringList properties = reply;

            if (!reply.isValid() || properties.count() < 6)
            {
                debug() << "Invalid reply from mediamanager" << endl;
                return QString::null;
            }
            else
            {
                debug() << "Reply from mediamanager " << properties[5] << endl;
                return properties[5];
            }
        }

        return device;
    }

}


void App::handleCliArgs() //static
{
    static char cwd[PATH_MAX];
    KCmdLineArgs* const args = KCmdLineArgs::parsedArgs();

    if ( args->isSet( "cwd" ) )
    {
        strncpy(cwd, args->getOption( "cwd" ), sizeof(cwd) );
        cwd[sizeof(cwd)-1] = '\0';
        KCmdLineArgs::setCwd( cwd );
    }

    if ( args->count() > 0 )
    {
        KURL::List list;
        for( int i = 0; i < args->count(); i++ )
            list << args->url( i );

        int options;
        bool appendAsDefault = amaroK::config()->readBoolEntry( "AppendAsDefault", false );
        if( args->isSet( "queue" ) )
           options = Playlist::Queue;
        else if( args->isSet( "append" ) || args->isSet( "enqueue" ) || appendAsDefault ) {
           options = Playlist::Append;
           if( args->isSet( "play" ) )
              options |= Playlist::DirectPlay;
        }
        else
           options = Playlist::Replace | Playlist::DirectPlay;

        Playlist::instance()->insertMedia( list, options );
    }

    //we shouldn't let the user specify two of these since it is pointless!
    //so we prioritise, pause > stop > play > next > prev
    //thus pause is the least destructive, followed by stop as brakes are the most important bit of a car(!)
    //then the others seemed sensible. Feel free to modify this order, but please leave justification in the cvs log
    //I considered doing some sanity checks (eg only stop if paused or playing), but decided it wasn't worth it
    else if ( args->isSet( "pause" ) )
        EngineController::instance()->pause();
    else if ( args->isSet( "stop" ) )
        EngineController::instance()->stop();
    else if ( args->isSet( "play-pause" ) )
        EngineController::instance()->playPause();
    else if ( args->isSet( "play" ) ) //will restart if we are playing
        EngineController::instance()->play();
    else if ( args->isSet( "next" ) )
        EngineController::instance()->next();
    else if ( args->isSet( "previous" ) )
        EngineController::instance()->previous();
    else if (args->isSet("cdplay")) {
        QString device = args->getOption("cdplay");
        KURL::List urls;
        if (EngineController::engine()->getAudioCDContents(device, urls)) {
            Playlist::instance()->insertMedia(
                urls, Playlist::Replace|Playlist::DirectPlay);
        } else { // Default behaviour
            debug() <<
                "Sorry, the engine doesn't support direct play from AudioCD..."
                    << endl;
        }
    }

    if ( args->isSet( "toggle-playlist-window" ) )
        pApp->m_pPlaylistWindow->showHide();

    args->clear();    //free up memory
}


/////////////////////////////////////////////////////////////////////////////////////
// INIT
/////////////////////////////////////////////////////////////////////////////////////

void App::initCliArgs( int argc, char *argv[] ) //static
{
    static KCmdLineOptions options[] =
        {
            { "+[URL(s)]", I18N_NOOP( "Files/URLs to open" ), 0 },
            { "r", 0, 0 },
            { "previous", I18N_NOOP( "Skip backwards in playlist" ), 0 },
            { "p", 0, 0 },
            { "play", I18N_NOOP( "Start playing current playlist" ), 0 },
            { "t", 0, 0 },
            { "play-pause", I18N_NOOP( "Play if stopped, pause if playing" ), 0 },
            { "pause", I18N_NOOP( "Pause playback" ), 0 },
            { "s", 0, 0 },
            { "stop", I18N_NOOP( "Stop playback" ), 0 },
            { "f", 0, 0 },
            { "next", I18N_NOOP( "Skip forwards in playlist" ), 0 },
            { ":", I18N_NOOP("Additional options:"), 0 },
            { "a", 0, 0 },
            { "append", I18N_NOOP( "Append files/URLs to playlist" ), 0 },
            { "e", 0, 0 },
            { "enqueue", I18N_NOOP("See append, available for backwards compatability"), 0 },
            { "queue", I18N_NOOP("Queue URLs after the currently playing track"), 0 },
            { "m", 0, 0 },
            { "toggle-playlist-window", I18N_NOOP("Toggle the Playlist-window"), 0 },
            { "wizard", I18N_NOOP( "Run first-run wizard" ), 0 },
            { "engine <name>", I18N_NOOP( "Use the <name> engine" ), 0 },
            { "cwd <directory>", I18N_NOOP( "Base for relative filenames/URLs" ), 0 },
            { "cdplay <device>", I18N_NOOP("Play an AudioCD from <device>"), 0 },
            { 0, 0, 0 }
        };

    KCmdLineArgs::reset();
    KCmdLineArgs::init( argc, argv, &::aboutData ); //calls KApplication::addCmdLineOptions()
    KCmdLineArgs::addCmdLineOptions( options );   //add our own options
}


#include <kaction.h>
#include <kshortcutlist.h>
void App::initGlobalShortcuts()
{
    EngineController* const ec = EngineController::instance();

    m_pGlobalAccel->insert( "play", i18n( "Play" ), 0, KKey("WIN+x"), 0,
                            ec, SLOT( play() ), true, true );
    m_pGlobalAccel->insert( "pause", i18n( "Pause" ), 0, KKey("WIN+c"), 0,
                            ec, SLOT( pause() ), true, true );
    m_pGlobalAccel->insert( "play_pause", i18n( "Play/Pause" ), 0, 0, 0,
                            ec, SLOT( playPause() ), true, true );
    m_pGlobalAccel->insert( "stop", i18n( "Stop" ), 0, KKey("WIN+v"), 0,
                            ec, SLOT( stop() ), true, true );
    m_pGlobalAccel->insert( "stop_after_global", i18n( "Stop Playing After Current Track" ), 0, KKey("WIN+CTRL+v"), 0,
                            Playlist::instance()->qscrollview(), SLOT( toggleStopAfterCurrentTrack() ), true, true );
    m_pGlobalAccel->insert( "next", i18n( "Next Track" ), 0, KKey("WIN+b"), 0,
                            ec, SLOT( next() ), true, true );
    m_pGlobalAccel->insert( "prev", i18n( "Previous Track" ), 0, KKey("WIN+z"), 0,
                            ec, SLOT( previous() ), true, true );
    m_pGlobalAccel->insert( "volup", i18n( "Increase Volume" ), 0, KKey("WIN+KP_Add"), 0,
                            ec, SLOT( increaseVolume() ), true, true );
    m_pGlobalAccel->insert( "voldn", i18n( "Decrease Volume" ), 0, KKey("WIN+KP_Subtract"), 0,
                            ec, SLOT( decreaseVolume() ), true, true );
    m_pGlobalAccel->insert( "seekforward", i18n( "Seek Forward" ), 0, KKey("WIN+Shift+KP_Add"), 0,
                            ec, SLOT( seekForward() ), true, true );
    m_pGlobalAccel->insert( "seekbackward", i18n( "Seek Backward" ), 0, KKey("WIN+Shift+KP_Subtract"), 0,
                            ec, SLOT( seekBackward() ), true, true );
    m_pGlobalAccel->insert( "playlist_add", i18n( "Add Media..." ), 0, KKey("WIN+a"), 0,
                            m_pPlaylistWindow, SLOT( slotAddLocation() ), true, true );
    m_pGlobalAccel->insert( "show", i18n( "Toggle Playlist Window" ), 0, KKey("WIN+p"), 0,
                            m_pPlaylistWindow, SLOT( showHide() ), true, true );
    m_pGlobalAccel->insert( "osd", i18n( "Show OSD" ), 0, KKey("WIN+o"), 0,
                            amaroK::OSD::instance(), SLOT( forceToggleOSD() ), true, true );
    m_pGlobalAccel->insert( "mute", i18n( "Mute Volume" ), 0, KKey("WIN+m"), 0,
                            ec, SLOT( mute() ), true, true );

    m_pGlobalAccel->insert( "rating1", i18n( "Rate Current Track: 1" ), 0, KKey("WIN+1"), 0,
                            this, SLOT( setRating1() ), true, true );
    m_pGlobalAccel->insert( "rating2", i18n( "Rate Current Track: 2" ), 0, KKey("WIN+2"), 0,
                            this, SLOT( setRating2() ), true, true );
    m_pGlobalAccel->insert( "rating3", i18n( "Rate Current Track: 3" ), 0, KKey("WIN+3"), 0,
                            this, SLOT( setRating3() ), true, true );
    m_pGlobalAccel->insert( "rating4", i18n( "Rate Current Track: 4" ), 0, KKey("WIN+4"), 0,
                            this, SLOT( setRating4() ), true, true );
    m_pGlobalAccel->insert( "rating5", i18n( "Rate Current Track: 5" ), 0, KKey("WIN+5"), 0,
                            this, SLOT( setRating5() ), true, true );

    m_pGlobalAccel->setConfigGroup( "Shortcuts" );
    m_pGlobalAccel->readSettings( kapp->config() );
    m_pGlobalAccel->updateConnections();

    //TODO fix kde accel system so that kactions find appropriate global shortcuts
    //     and there is only one configure shortcuts dialog

    KActionCollection* const ac = amaroK::actionCollection();
    KAccelShortcutList list( m_pGlobalAccel );

    for( uint i = 0; i < list.count(); ++i )
    {
        KAction *action = ac->action( list.name( i ).latin1() );

        if( action )
        {
            //this is a hack really, also it means there may be two calls to the slot for the shortcut
            action->setShortcutConfigurable( false );
            action->setShortcut( list.shortcut( i ) );
        }
    }
}


void App::fixHyperThreading()
{
    /** Workaround for stability issues with HyperThreading CPU's, @see BUG 99199.
     * First we detect the presence of HyperThreading. If active, we bind amarokapp
     * to the first CPU only (hard affinity).
     *
     * @see http://www-128.ibm.com/developerworks/linux/library/l-affinity.html
     * @see http://www.linuxjournal.com/article/6799
     * (articles on processor affinity with the linux kernel)
     */

    DEBUG_BLOCK

    #ifdef __linux__
    QString line;
    uint cpuCount = 0;
    QFile cpuinfo( "/proc/cpuinfo" );
    if ( cpuinfo.open( IO_ReadOnly ) ) {
        while ( cpuinfo.readLine( line, 20000 ) != -1 ) {
            if ( line.startsWith( "flags" ) ) {
                const QString flagsLine = line.section( ":", 1 );
                const QStringList flags = QStringList::split( " ", flagsLine );
                if ( flags.contains( "ht" ) ) ++cpuCount;
            }
        }
    }
    // If multiple CPUs are listed with the HT flag, we got HyperThreading enabled
    if ( cpuCount > 1 ) {
        debug() << "CPU with active HyperThreading detected. Enabling WORKAROUND.\n";

        // If the library is new enough try and call sched_setaffinity.
        #ifdef SCHEDAFFINITY_SUPPORT
        cpu_set_t mask;
        CPU_ZERO( &mask ); // Initializes all the bits in the mask to zero
        CPU_SET( 0, &mask ); // Sets only the bit corresponding to cpu
        #ifdef SCHEDAFFINITY_3PARAMS
        if ( sched_setaffinity( 0, sizeof(mask), &mask ) == -1 )
        #else  //SCHEDAFFINITY_3PARAMS
        if ( sched_setaffinity( 0, &mask ) == -1 )
        #endif //SCHEDAFFINITY_3PARAMS
        {
            warning() << "sched_setaffinity() call failed with error code: " << errno << endl;
            QTimer::singleShot( 0, this, SLOT( showHyperThreadingWarning() ) );
            return;
        }
        #else //SCHEDAFFINITY_SUPPORT
             warning()<<"glibc failed checks for sched_setaffinity" << endl;
        QTimer::singleShot( 0, this, SLOT( showHyperThreadingWarning() ) );
        #endif //SCHEDAFFINITY_SUPPORT
    }
    else { debug() << "Fix not enabled" << endl; }
    #else //__linux__
    debug() << "SCHEDAFFINITY_SUPPORT disabled since this isn't Linux" << endl;
    #endif //__linux__
}


void App::showHyperThreadingWarning() // SLOT
{
    const QString text =
        i18n( "<p>You are using a processor with the <i>HyperThreading</i> "
              "feature enabled. Please note that amaroK may be unstable with this "
              "configuration.</p>"
              "<p>If you are experiencing problems, use the Linux kernel option 'NOHT', "
              "or disable <i>HyperThreading</i> in your BIOS setup.</p>"
              "<p>More information can be found in the README file. For further assistance "
              "join us at #amarok on irc.freenode.net.</p>" );

    KMessageBox::information( 0, text, i18n( "Warning" ), "showHyperThreadingWarning" );
}


/////////////////////////////////////////////////////////////////////////////////////
// METHODS
/////////////////////////////////////////////////////////////////////////////////////

#include <taglib/id3v1tag.h>
#include <taglib/tbytevector.h>
#include <qtextcodec.h>

//this class is only used in this module, so I figured I may as well define it
//here and save creating another header/source file combination

class ID3v1StringHandler : public TagLib::ID3v1::StringHandler
{
    QTextCodec *m_codec;

    virtual TagLib::String parse( const TagLib::ByteVector &data ) const
    {
        return QStringToTString( m_codec->toUnicode( data.data(), data.size() ) );
    }

    virtual TagLib::ByteVector render( const TagLib::String &ts ) const
    {
        const QCString qcs = m_codec->fromUnicode( TStringToQString(ts) );
        return TagLib::ByteVector( qcs, qcs.length() );
    }

public:
    ID3v1StringHandler( int codecIndex )
            : m_codec( QTextCodec::codecForIndex( codecIndex ) )
    {
        debug() << "codec: " << m_codec << endl;
        debug() << "codec-name: " << m_codec->name() << endl;
    }

    ID3v1StringHandler( QTextCodec *codec )
            : m_codec( codec )
    {
        debug() << "codec: " << m_codec << endl;
        debug() << "codec-name: " << m_codec->name() << endl;
    }
};

//SLOT
void App::applySettings( bool firstTime )
{
    ///Called when the configDialog is closed with OK or Apply

    DEBUG_BLOCK

    //determine and apply colors first
    applyColorScheme();

    TrackToolTip::instance()->removeFromWidget( m_pTray );

    if( AmarokConfig::showPlayerWindow() )
    {
        if( !m_pPlayerWindow )
        {
            //the player Window becomes the main Window
            //it is the focus for hideWithMainWindow behaviour etc.
            //it gets the majestic "amaroK" caption
            m_pPlaylistWindow->setCaption( kapp->makeStdCaption( i18n("Playlist") ) );

            m_pPlayerWindow = new PlayerWidget( m_pPlaylistWindow, "PlayerWindow", firstTime && AmarokConfig::playlistWindowEnabled() );

            //don't show PlayerWindow on firstTime, that is done below
            //we need to explicately set the PL button if it's the first time
            if( !firstTime ) m_pPlayerWindow->show();


            connect( m_pPlayerWindow, SIGNAL(playlistToggled( bool )), m_pPlaylistWindow, SLOT(showHide()) );

            //TODO get this to work!
            //may work if you set no parent for the systray?
            //KWin::setSystemTrayWindowFor( m_pTray->winId(), m_pPlayerWindow->winId() );

            delete m_pTray; m_pTray = new amaroK::TrayIcon( m_pPlayerWindow );

            //make tray icon behave properly after selecting to show or hide player window
            m_pTray->engineStateChanged(EngineController::instance()->engine()->state(), EngineController::instance()->engine()->state());
            m_pTray->engineNewMetaData(EngineController::instance()->bundle(), false);

            //make player window minimal if it was last time
            if( AmarokConfig::playerWindowMinimalView() ){
                m_pPlayerWindow->setMinimalView( true );
            }
        }
        else
            //this is called in the PlayerWindow ctor, hence the else
            m_pPlayerWindow->applySettings();

    } else if( m_pPlayerWindow ) {
        delete m_pTray; m_pTray = new amaroK::TrayIcon( m_pPlaylistWindow );
        m_pTray->engineStateChanged(EngineController::instance()->engine()->state(), EngineController::instance()->engine()->state());
        m_pTray->engineNewMetaData(EngineController::instance()->bundle(), false);
        delete m_pPlayerWindow; m_pPlayerWindow = 0;

        //Set the caption correctly.
        if ( !EngineController::instance()->bundle().prettyTitle().isEmpty() )
            m_pPlaylistWindow->setCaption( i18n("amaroK - %1").arg( EngineController::instance()->bundle().veryNiceTitle() ) );
        else
            m_pPlaylistWindow->setCaption( "amaroK" );


        //m_pPlaylistWindow->show(); //must be shown //we do below now

        //ensure that at least one Menu is plugged into an accessible UI element
        if( !AmarokConfig::showMenuBar() && !amaroK::actionCollection()->action( "amarok_menu" )->isPlugged() )
           playlistWindow()->createGUI();
    }

    playlistWindow()->applySettings();
    Scrobbler::instance()->applySettings();
    amaroK::OSD::instance()->applySettings();
    CollectionDB::instance()->applySettings();
    m_pTray->setShown( AmarokConfig::showTrayIcon() );
    TrackToolTip::instance()->addToWidget( m_pTray );


    //on startup we need to show the window, but only if it wasn't hidden on exit
    //and always if the trayicon isn't showing
    if( firstTime && !amaroK::config()->readBoolEntry( "HiddenOnExit", false ) || !AmarokConfig::showTrayIcon() )
    {
        mainWindow()->show();

        //takes longer but feels shorter. Crazy eh? :)
        kapp->eventLoop()->processEvents( QEventLoop::ExcludeUserInput );
    }


    { //<Engine>
        EngineBase *engine = EngineController::engine();

        if( firstTime || AmarokConfig::soundSystem() !=
                         PluginManager::getService( engine )->property( "X-KDE-amaroK-name" ).toString() )
        {
            //will unload engine for us first if necessary
            engine = EngineController::instance()->loadEngine();
        }

        engine->setXfadeLength( AmarokConfig::crossfade() ? AmarokConfig::crossfadeLength() : 0 );
        engine->setVolume( AmarokConfig::masterVolume() );

        engine->setEqualizerEnabled( AmarokConfig::equalizerEnabled() );
        if ( AmarokConfig::equalizerEnabled() )
            engine->setEqualizerParameters( AmarokConfig::equalizerPreamp(), AmarokConfig::equalizerGains() );

        amaroK::actionCollection()->action("play_audiocd")->setEnabled( EngineController::hasEngineProperty( "HasKIO" ) || EngineController::hasEngineProperty("HasCDDA"));
    } //</Engine>

    { //<Collection>
        CollectionView::instance()->renderView(true);
    } //</Collection>
    { //<Context>
        ContextBrowser::instance()->renderView();
    } //</Context>

    {   // delete unneeded cover images from cache
        const QString size = QString::number( AmarokConfig::coverPreviewSize() ) + '@';
        const QDir cacheDir = amaroK::saveLocation( "albumcovers/cache/" );
        const QStringList obsoleteCovers = cacheDir.entryList( "*" );
        foreach( obsoleteCovers )
            if ( !(*it).startsWith( size  ) && !(*it).startsWith( "50@" ) )
                QFile( cacheDir.filePath( *it ) ).remove();
    }

    //if ( !firstTime )
        // Bizarrely and ironically calling this causes crashes for
        // some people! FIXME
        //AmarokConfig::writeConfig();
}

void
App::applyColorScheme()
{
    QColorGroup group;
    using amaroK::ColorScheme::AltBase;
    int h, s, v;
    QWidget* const browserBar = static_cast<QWidget*>( playlistWindow()->child( "BrowserBar" ) );

    if( AmarokConfig::schemeKDE() )
    {
        AltBase = KGlobalSettings::alternateBackgroundColor();

        playlistWindow()->unsetPalette();
        browserBar->unsetPalette();

        PlayerWidget::determineAmarokColors();
    }

    else if( AmarokConfig::schemeAmarok() )
    {
        group = QApplication::palette().active();
        const QColor bg( amaroK::blue );
        AltBase.setRgb( 57, 64, 98 );

        group.setColor( QColorGroup::Text, Qt::white );
        group.setColor( QColorGroup::Link, 0xCCCCCC );
        group.setColor( QColorGroup::Base, bg );
        group.setColor( QColorGroup::Foreground, 0xd7d7ef );
        group.setColor( QColorGroup::Background, AltBase );

        group.setColor( QColorGroup::Button, AltBase );
        group.setColor( QColorGroup::ButtonText, 0xd7d7ef );

//         group.setColor( QColorGroup::Light,    Qt::cyan   /*lighter than Button color*/ );
//         group.setColor( QColorGroup::Midlight, Qt::blue   /*between Button and Light*/ );
//         group.setColor( QColorGroup::Dark,     Qt::green  /*darker than Button*/ );
//         group.setColor( QColorGroup::Mid,      Qt::red    /*between Button and Dark*/ );
//         group.setColor( QColorGroup::Shadow,   Qt::yellow /*a very dark color. By default, the shadow color is Qt::black*/ );

        group.setColor( QColorGroup::Highlight, Qt::white );
        group.setColor( QColorGroup::HighlightedText, bg );
        //group.setColor( QColorGroup::BrightText, QColor( 0xff, 0x40, 0x40 ) ); //GlowColor

        AltBase.getHsv( &h, &s, &v );
        group.setColor( QColorGroup::Midlight, QColor( h, s/3, (int)(v * 1.2), QColor::Hsv ) ); //column separator in playlist

        //TODO set all colours, even button colours, that way we can change the dark,
        //light, etc. colours and amaroK scheme will look much better

        using namespace amaroK::ColorScheme;
        Base       = amaroK::blue;
        Text       = Qt::white;
        Background = 0x002090;
        Foreground = 0x80A0FF;

        //all children() derive their palette from this
        playlistWindow()->setPalette( QPalette( group, group, group ) );
        browserBar->unsetPalette();
    }

    else if( AmarokConfig::schemeCustom() )
    {
        // we try to be smart: this code figures out contrasting colors for
        // selection and alternate background rows
        group = QApplication::palette().active();
        const QColor fg( AmarokConfig::playlistWindowFgColor() );
        const QColor bg( AmarokConfig::playlistWindowBgColor() );

        //TODO use the ensureContrast function you devised in BlockAnalyzer

        bg.hsv( &h, &s, &v );
        v += (v < 128) ? +50 : -50;
        v &= 255; //ensures 0 <= v < 256
        AltBase.setHsv( h, s, v );

        fg.hsv( &h, &s, &v );
        v += (v < 128) ? +150 : -150;
        v &= 255; //ensures 0 <= v < 256
        QColor highlight( h, s, v, QColor::Hsv );

        group.setColor( QColorGroup::Base, bg );
        group.setColor( QColorGroup::Background, bg.dark( 115 ) );
        group.setColor( QColorGroup::Text, fg );
        group.setColor( QColorGroup::Link, fg.light( 120 ) );
        group.setColor( QColorGroup::Highlight, highlight );
        group.setColor( QColorGroup::HighlightedText, Qt::white );
        group.setColor( QColorGroup::Dark, Qt::darkGray );

        PlayerWidget::determineAmarokColors();

        // we only colour the middle section since we only
        // allow the user to choose two colours
        browserBar->setPalette( QPalette( group, group, group ) );
        playlistWindow()->unsetPalette();
    }

    // set the KListView alternate colours
    QObjectList* const list = playlistWindow()->queryList( "KListView" );
    for( QObject *o = list->first(); o; o = list->next() )
        static_cast<KListView*>(o)->setAlternateBackground( AltBase );
    delete list; //heap allocated!
}


bool amaroK::genericEventHandler( QWidget *recipient, QEvent *e )
{
    //this is used as a generic event handler for widgets that want to handle
    //typical events in an amaroK fashion

    //to use it just pass the event eg:
    //
    // void Foo::barEvent( QBarEvent *e )
    // {
    //     amaroK::genericEventHandler( this, e );
    // }

    switch( e->type() )
    {
    case QEvent::DragEnter:
        #define e static_cast<QDropEvent*>(e)
        e->accept( KURLDrag::canDecode( e ) );
        break;

    case QEvent::Drop:
        if( KURLDrag::canDecode( e ) )
        {
            QPopupMenu popup;
            //FIXME this isn't a good way to determine if there is a currentTrack, need playlist() function
            const bool b = EngineController::engine()->loaded();

            popup.insertItem( i18n( "&Append to Playlist" ), Playlist::Append );
            popup.insertItem( i18n( "Append && &Play" ), Playlist::DirectPlay | Playlist::Append );
            if( b ) popup.insertItem( i18n( "&Queue Track" ), Playlist::Queue );
            popup.insertSeparator();
            popup.insertItem( i18n( "&Cancel" ), 0 );

            const int id = popup.exec( recipient->mapToGlobal( e->pos() ) );
            KURL::List list;
            KURLDrag::decode( e, list );

            if ( id > 0 )
                Playlist::instance()->insertMedia( list, id );
        }
        else return false;
        #undef e

        break;

    //this like every entry in the generic event handler is used by more than one widget
    //please don't remove!
    case QEvent::Wheel:
    {
        #define e static_cast<QWheelEvent*>(e)

        //this behaviour happens for the systray and the player window
        //to override one, override it in that class

        switch( e->state() )
        {
        case Qt::ControlButton:
        {
            const bool up = e->delta() > 0;

            //if this seems strange to you, please bring it up on #amarok
            //for discussion as we can't decide which way is best!
            if( up ) EngineController::instance()->previous();
            else     EngineController::instance()->next();
            break;
        }
        case Qt::ShiftButton:
        {
            EngineController::instance()->seekRelative( ( e->delta() / 120 ) * 10000 ); // 10 seconds
            break;
        }
        default:
            EngineController::instance()->increaseVolume( e->delta() / amaroK::VOLUME_SENSITIVITY );
        }

        e->accept();
        #undef e

        break;
    }

    case QEvent::Close:

        //KDE policy states we should hide to tray and not quit() when the
        //close window button is pushed for the main widget

        static_cast<QCloseEvent*>(e)->accept(); //if we don't do this the info box appears on quit()!

        if( AmarokConfig::showTrayIcon() && !e->spontaneous() && !kapp->sessionSaving() )
        {
            KMessageBox::information( recipient,
                i18n( "<qt>Closing the main-window will keep amaroK running in the System Tray. "
                      "Use <B>Quit</B> from the menu, or the amaroK tray-icon to exit the application.</qt>" ),
                i18n( "Docking in System Tray" ), "hideOnCloseInfo" );
        }
        else pApp->quit();

        break;

    default:
        return false;
    }

    return true;
}


void App::engineStateChanged( Engine::State state, Engine::State oldState )
{
    const MetaBundle &bundle = EngineController::instance()->bundle();
    switch( state )
    {
    case Engine::Empty:
        if ( AmarokConfig::showPlayerWindow() )
            m_pPlaylistWindow->setCaption( kapp->makeStdCaption( i18n("Playlist") ) );
        else m_pPlaylistWindow->setCaption( "amaroK" );
        TrackToolTip::instance()->clear();
        amaroK::OSD::instance()->setImage( KIconLoader().iconPath( "amarok", -KIcon::SizeHuge ) );
        break;

    case Engine::Playing:
        if ( oldState == Engine::Paused )
            amaroK::OSD::instance()->OSDWidget::show( i18n( "state, as in playing", "Play" ) );
        if ( !bundle.prettyTitle().isEmpty() )
            m_pPlaylistWindow->setCaption( i18n("amaroK - %1").arg( bundle.veryNiceTitle() ) );
        break;

    case Engine::Paused:
        amaroK::OSD::instance()->OSDWidget::show( i18n("Paused") );
        break;

    case Engine::Idle:
        if ( AmarokConfig::showPlayerWindow() )
            m_pPlaylistWindow->setCaption( kapp->makeStdCaption( i18n("Playlist") ) );
        else m_pPlaylistWindow->setCaption( "amaroK" );
        break;

    default:
        ;
    }
}

void App::engineNewMetaData( const MetaBundle &bundle, bool /*trackChanged*/ )
{
    amaroK::OSD::instance()->show( bundle );
    if ( !bundle.prettyTitle().isEmpty() )
        m_pPlaylistWindow->setCaption( i18n("amaroK - %1").arg( bundle.veryNiceTitle() ) );

    TrackToolTip::instance()->setTrack( bundle );
}

void App::engineTrackPositionChanged( long position, bool /*userSeek*/ )
{
    TrackToolTip::instance()->setPos( position );
}

void App::engineVolumeChanged( int newVolume )
{
    amaroK::OSD::instance()->OSDWidget::show( newVolume ? i18n("Volume: %1%").arg( newVolume ) : i18n("Mute") );
}

void App::slotConfigEqualizer() //SLOT
{
    EqualizerSetup::instance()->show();
    EqualizerSetup::instance()->raise();
}


void App::slotConfigAmarok( const QCString& page )
{
    DEBUG_THREAD_FUNC_INFO

    AmarokConfigDialog* dialog = static_cast<AmarokConfigDialog*>( KConfigDialog::exists( "settings" ) );

    if( !dialog )
    {
        //KConfigDialog didn't find an instance of this dialog, so lets create it :
        dialog = new AmarokConfigDialog( m_pPlaylistWindow, "settings", AmarokConfig::self() );

        connect( dialog, SIGNAL(settingsChanged()), SLOT(applySettings()) );
    }

    //FIXME it seems that if the dialog is on a different desktop it gets lost
    //      what do to? detect and move it?

    dialog->show();
    dialog->raise();
    dialog->setActiveWindow();

    //so that if the engine page is needed to be shown it works
    kapp->processEvents();

    if ( !page.isNull() ) dialog->showPage( page );
}

void App::slotConfigShortcuts()
{
    KKeyDialog::configure( amaroK::actionCollection(), m_pPlaylistWindow );
}

void App::slotConfigGlobalShortcuts()
{
    KKeyDialog::configure( m_pGlobalAccel, true, m_pPlaylistWindow, true );
}

void App::slotConfigToolBars()
{
    PlaylistWindow* const pw = playlistWindow();
    KEditToolbar dialog( pw->actionCollection(), pw->xmlFile(), true, pw );

    dialog.showButtonApply( false );

    if( dialog.exec() )
    {
        playlistWindow()->reloadXML();
        playlistWindow()->createGUI();
    }
}

void App::firstRunWizard()
{
    ///show firstRunWizard

    FirstRunWizard wizard;
    setTopWidget( &wizard );
    KConfigDialogManager* config = new KConfigDialogManager(&wizard, AmarokConfig::self(), "wizardconfig");
    config->updateWidgets();
   // connect(config, SIGNAL(settingsChanged()), SLOT(updateSettings()));
    wizard.setCaption( makeStdCaption( i18n( "First-Run Wizard" ) ) );

    if( wizard.exec() != QDialog::Rejected )
    {
        switch( wizard.interface() )
        {
        case FirstRunWizard::XMMS:
            amaroK::config()->writeEntry( "XMLFile", "amarokui_xmms.rc" );
            AmarokConfig::setShowPlayerWindow( true );
            //FIXME the statusbar is now quite essential and also without it
            // the popup messages break. Fix in 1.2.1
            break;

        case FirstRunWizard::Compact:
            amaroK::config()->writeEntry( "XMLFile", "amarokui.rc" );
            AmarokConfig::setShowPlayerWindow( false );
            break;
        }

        const QStringList oldCollectionFolders = AmarokConfig::collectionFolders();
        wizard.writeCollectionConfig();

        // If wizard is invoked at runtime, rescan collection if folder setup has changed
        if ( !amaroK::config()->readBoolEntry( "First Run", true ) &&
             oldCollectionFolders != AmarokConfig::collectionFolders() )
            CollectionDB::instance()->startScan();

        AmarokConfig::setDatabaseEngine(
            QString::number( amaroK::databaseTypeCode( wizard.dbSetup7->databaseEngine->currentText() ) ) );

        config->updateSettings();
    }
}

void App::setUseScores( bool use )
{
    AmarokConfig::setUseScores( use );
    emit useScores( use );
}

void App::setUseRatings( bool use )
{
    AmarokConfig::setUseRatings( use );
    emit useRatings( use );
}

KIO::Job *App::trashFiles( const KURL::List &files )
{
#if KDE_IS_VERSION( 3, 3, 91 )
    KIO::Job *job = KIO::trash( files, true /*show progress*/ );
    amaroK::StatusBar::instance()->newProgressOperation( job ).setDescription( i18n("Moving files to trash") );
    connect( job, SIGNAL( result( KIO::Job* ) ), this, SLOT( slotTrashResult( KIO::Job* ) ) );
    return job;
#else
    return 0;
#endif
}

void App::setRating( int n )
{
    n *= 2;

    if( EngineController::instance()->engine()->state() == Engine::Playing ||
        EngineController::instance()->engine()->state() == Engine::Paused  ||
        EngineController::instance()->engine()->state() == Engine::Idle    )
    {
        CollectionDB::instance()->setSongRating( EngineController::instance()->playingURL().path(), n );
        amaroK::OSD::instance()->OSDWidget::show( i18n("Rating: %1").arg( QString().fill( '*', n/2 ) ) );
    }
    else if( PlaylistWindow::self()->isReallyShown() && Playlist::instance()->qscrollview()->hasFocus() )
        Playlist::instance()->setSelectedRatings( n );
}

void App::slotTrashResult( KIO::Job *job )
{
    if( job->error() )
        job->showErrorDialog( PlaylistWindow::self() );
}

QWidget *App::mainWindow() const
{
    return AmarokConfig::showPlayerWindow() ? static_cast<QWidget*>( m_pPlayerWindow )
                                            : static_cast<QWidget*>( m_pPlaylistWindow );
}

void App::quit()
{
    emit prepareToQuit();
    KApplication::quit();
}

namespace amaroK
{
    /// @see amarok.h

    QWidget *mainWindow()
    {
        return pApp->playlistWindow();
    }

    KActionCollection *actionCollection()
    {
        return pApp->playlistWindow()->actionCollection();
    }

    KConfig *config( const QString &group )
    {
        //Slightly more useful config() that allows setting the group simultaneously

        kapp->config()->setGroup( group );
        return kapp->config();
    }

    bool invokeBrowser( const QString& url )
    {
        const QString cmd = "%1 \"%2\"";
        int pid = KRun::runCommand( cmd.arg( AmarokConfig::externalBrowser(), url ) );

        return pid > 0;
    }

    namespace ColorScheme
    {
        QColor Base;
        QColor Text;
        QColor Background;
        QColor Foreground;
        QColor AltBase;
    }

    OverrideCursor::OverrideCursor( Qt::CursorShape cursor )
    {
        QApplication::setOverrideCursor( cursor == Qt::WaitCursor ? KCursor::waitCursor() : KCursor::workingCursor() );
    }

    OverrideCursor::~OverrideCursor()
    {
        QApplication::restoreOverrideCursor();
    }

    QString saveLocation( const QString &directory )
    {
        return KGlobal::dirs()->saveLocation( "data", QString("amarok/") + directory, true );
    }

    QString cleanPath( const QString &path, bool onlyASCII )
    {
        QString result = path;
        // german umlauts
        result.replace( QChar(0x00e4), "ae" ).replace( QChar(0x00c4), "Ae" );
        result.replace( QChar(0x00f6), "oe" ).replace( QChar(0x00d6), "Oe" );
        result.replace( QChar(0x00dc), "ue" ).replace( QChar(0x00fc), "Ue" );
        result.replace( QChar(0x00df), "ss" );

        // some strange accents
        result.replace( QChar(0x00e7), "c" ).replace( QChar(0x00c7), "C" );
        result.replace( QChar(0x00fd), "y" ).replace( QChar(0x00dd), "Y" );
        result.replace( QChar(0x00f1), "n" ).replace( QChar(0x00d1), "N" );

        // accented vowels
        QChar a[] = { 'a', 0xe0,0xe1,0xe2,0xe3,0xe5, 0 };
        QChar A[] = { 'A', 0xc0,0xc1,0xc2,0xc3,0xc5, 0 };
        QChar E[] = { 'e', 0xe8,0xe9,0xea,0xeb, 0 };
        QChar e[] = { 'E', 0xc8,0xc9,0xca,0xcb, 0 };
        QChar i[] = { 'i', 0xec,0xed,0xee,0xef, 0 };
        QChar I[] = { 'I', 0xcc,0xcd,0xce,0xcf, 0 };
        QChar o[] = { 'o', 0xf2,0xf3,0xf4,0xf5,0xf8, 0 };
        QChar O[] = { 'O', 0xd2,0xd3,0xd4,0xd5,0xd8, 0 };
        QChar u[] = { 'u', 0xf9,0xfa,0xfb, 0 };
        QChar U[] = { 'U', 0xd9,0xda,0xdb, 0 };
        QChar nul[] = { 0 };
        QChar *replacements[] = { a, A, e, E, i, I, o, O, u, U, nul };

        for( uint i = 0; i < result.length(); i++ )
        {
            QChar c = result.ref( i );
            for( uint n = 0; replacements[n][0] != QChar(0); n++ )
            {
                for( uint k=0; replacements[n][k] != QChar(0); k++ )
                {
                    if( replacements[n][k] == c )
                    {
                        c = replacements[n][0];
                    }
                }
            }
            if( onlyASCII && ( c > QChar(0x7f) || c == QChar(0) ) )
            {
                c = '_';
            }
            result.ref( i ) = c;
        }
        return result;
    }

    QString vfatPath( const QString &path )
    {
        QString s = path;

        for( uint i = 0; i < s.length(); i++ )
        {
            QChar c = s.ref( i );
            if( c < QChar(0x20)
                    || c=='*' || c=='?' || c=='<' || c=='>'
                    || c=='|' || c=='"' || c==':' || c=='/'
                    || c=='\\' )
                c = '_';
            s.ref( i ) = c;
        }

        uint len = s.length();
        if( len == 3 || (len > 3 && s[3] == '.') )
        {
            QString l = s.left(3).lower();
            if( l=="aux" || l=="con" || l=="nul" || l=="prn" )
                s = "_" + s;
        }
        else if( len == 4 || (len > 4 && s[4] == '.') )
        {
            QString l = s.left(3).lower();
            QString d = s.mid(3,1);
            if( (l=="com" || l=="lpt") &&
                    (d=="0" || d=="1" || d=="2" || d=="3" || d=="4" ||
                     d=="5" || d=="6" || d=="7" || d=="8" || d=="9") )
                s = "_" + s;
        }

        while( s.startsWith( "." ) )
            s = s.mid(1);

        while( s.endsWith( "." ) )
            s = s.left( s.length()-1 );

        s = s.left(255);
        len = s.length();
        if( s[len-1] == ' ' )
            s[len-1] = '_';

        return s;
    }

    void setUseScores( bool use ) { App::instance()->setUseScores( use ); }
    void setUseRatings( bool use ) { App::instance()->setUseRatings( use ); }
    KIO::Job *trashFiles( const KURL::List &files ) { return App::instance()->trashFiles( files ); }
}

#include "app.moc"