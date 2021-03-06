/***************************************************************************
  begin                : Fre Nov 15 2002
  copyright            : (C) Mark Kretschmann <markey@web.de>
                       : (C) Max Howell <max.howell@methylblue.com>
                       : (C) G??bor Lehel <illissius@gmail.com>
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "config.h"           //HAVE_XMMS definition

#include "actionclasses.h"    //see toolbar construction
#include "amarok.h"
#include "amarokconfig.h"
#include "browserbar.h"
#include "clicklineedit.h"    //m_lineEdit
#include "collectionbrowser.h"
#include "contextbrowser.h"
#include "debug.h"
#include "devicemanager.h"
#include "enginecontroller.h" //for actions in ctor
#include "filebrowser.h"
#include "k3bexporter.h"
#include "mediabrowser.h"
#include "dynamicmode.h"
#include "playlist.h"
#include "playlistbrowser.h"
#include "playlistwindow.h"
#include "scriptmanager.h"
#include "statistics.h"
#include "statusbar.h"
#include "threadweaver.h"

#include <qevent.h>           //eventFilter()
#include <qfont.h>
#include <qheader.h>
#include <qlayout.h>
#include <qlabel.h>           //search filter label

#include <qpainter.h>         //dynamic title
#include <qpen.h>

#include <qsizepolicy.h>      //qspaceritem in dynamic bar
#include <qtimer.h>           //search filter timer
#include <qtooltip.h>         //QToolTip::add()
#include <qvbox.h>            //contains the playlist

#include <kaction.h>          //m_actionCollection
#include <kapplication.h>     //kapp
#include <kfiledialog.h>      //savePlaylist(), openPlaylist()
#include <kglobal.h>
#include <khtml_part.h>       //Welcome Tab
#include <kiconloader.h>      //ClearFilter button
#include <klocale.h>
#include <kmenubar.h>
#include <kmessagebox.h>       //savePlaylist()
#include <kpopupmenu.h>
#include <kpushbutton.h>
#include <kstandarddirs.h>    //Welcome Tab, locate welcome.html
#include <ktoolbar.h>
#include <ktoolbarbutton.h>   //createGUI()
#include <kxmlguibuilder.h>   //XMLGUI
#include <kxmlguifactory.h>   //XMLGUI

#include <fixx11h.h>



//////////////////////////////////////////////////////////////////////////////////////////
/// CLASS amaroK::ToolBar
//////////////////////////////////////////////////////////////////////////////////////////

namespace amaroK
{
    class ToolBar : public KToolBar
    {
    public:
        ToolBar( QWidget *parent, const char *name )
            : KToolBar( parent, name )
        {}

    protected:
        virtual void
        mousePressEvent( QMouseEvent *e ) {
            if( e->button() == RightButton ) amaroK::Menu::instance()->popup( e->globalPos() );
        }

        virtual void
        wheelEvent( QWheelEvent *e ) {
            EngineController::instance()->increaseVolume( e->delta() / amaroK::VOLUME_SENSITIVITY );
        }
    };
}

PlaylistWindow *PlaylistWindow::s_instance = 0;

PlaylistWindow::PlaylistWindow()
        : QWidget( 0, "PlaylistWindow", Qt::WGroupLeader )
        , KXMLGUIClient()
        , m_lastBrowser( 0 )
{
    s_instance = this;

    // Sets caption and icon correctly (needed e.g. for GNOME)
    kapp->setTopWidget( this );

    KActionCollection* const ac = actionCollection();
    const EngineController* const ec = EngineController::instance();

    ac->setAutoConnectShortcuts( false );
    ac->setWidget( this );

    new K3bExporter();

    KStdAction::configureToolbars( kapp, SLOT( slotConfigToolBars() ), ac );
    KStdAction::keyBindings( kapp, SLOT( slotConfigShortcuts() ), ac );
    KStdAction::keyBindings( kapp, SLOT( slotConfigGlobalShortcuts() ), ac, "options_configure_globals" );
    KStdAction::preferences( kapp, SLOT( slotConfigAmarok() ), ac );
    KStdAction::quit( kapp, SLOT( quit() ), ac );
    KStdAction::open( this, SLOT(slotAddLocation()), ac, "playlist_add" )->setText( i18n("&Add Media...") );
    KStdAction::save( this, SLOT(savePlaylist()), ac, "playlist_save" )->setText( i18n("&Save Playlist As...") );
    KStdAction::showMenubar( this, SLOT(slotToggleMenu()), ac );

    new KAction( i18n("Play Media..."), "fileopen", 0, this, SLOT(slotPlayMedia()), ac, "playlist_playmedia" );
    new KAction( i18n("Play Audio CD"), "cdaudio_unmount", 0, this, SLOT(playAudioCD()), ac, "play_audiocd" );
    new KAction( i18n("Script Manager"), "pencil", 0, this, SLOT(showScriptSelector()), ac, "script_manager" );
    new KAction( i18n("Queue Manager"), "goto", 0, this, SLOT(showQueueManager()), ac, "queue_manager" );
    new KAction( i18n("Statistics"), amaroK::icon( "info" ), 0, this, SLOT(showStatistics()), ac, "statistics" );

    ac->action( "options_configure_globals" )->setText( i18n( "Configure &Global Shortcuts..." ) );

    new KAction( i18n( "Previous Track" ), amaroK::icon( "back" ), 0, ec, SLOT( previous() ), ac, "prev" );
    new KAction( i18n( "Play" ), amaroK::icon( "play" ), 0, ec, SLOT( play() ), ac, "play" );
    new KAction( i18n( "Pause" ), amaroK::icon( "pause" ), 0, ec, SLOT( pause() ), ac, "pause" );
    new KAction( i18n( "Next Track" ), amaroK::icon( "next" ), 0, ec, SLOT( next() ), ac, "next" );

    {
        KAction *gah = new KAction( i18n( "Toggle Focus" ), "reload", CTRL+Key_Tab,
            this, SLOT( slotToggleFocus() ), ac, "toggle_focus" );
        KPopupMenu asdf;
        gah->plug( &asdf );
        gah->unplug( &asdf );
    }

    new amaroK::MenuAction( ac );
    new amaroK::StopAction( ac );
    new amaroK::PlayPauseAction( ac );
    new amaroK::AnalyzerAction( ac );
    new amaroK::RepeatAction( ac );
    new amaroK::RandomAction( ac );
    new amaroK::FavorAction( ac );
    new amaroK::VolumeAction( ac );

    if( K3bExporter::isAvailable() )
        new amaroK::BurnMenuAction( ac );

    if( AmarokConfig::playlistWindowSize().isValid() ) {
        // if first ever run, use sizeHint(), and let
        // KWin place us otherwise use the stored values
        resize( AmarokConfig::playlistWindowSize() );
        move( AmarokConfig::playlistWindowPos() );
    }
}

PlaylistWindow::~PlaylistWindow()
{
    amaroK::config( "PlaylistWindow" )->writeEntry( "showMenuBar", m_menubar->isShown() );

    AmarokConfig::setPlaylistWindowPos( pos() );  //TODO de XT?
    AmarokConfig::setPlaylistWindowSize( size() ); //TODO de XT?
}


///////// public interface

/**
 * This function will intialize the playlist window.
 */
void PlaylistWindow::init()
{
    DEBUG_BLOCK

    //this function is necessary because amaroK::actionCollection() returns our actionCollection
    //via the App::m_pPlaylistWindow pointer since App::m_pPlaylistWindow is not defined until
    //the above ctor returns it causes a crash unless we do the initialisation in 2 stages.

    m_browsers = new BrowserBar( this );

    //<Dynamic Mode Status Bar />
    DynamicBar *dynamicBar = new DynamicBar( m_browsers->container());

    { //<Search LineEdit>
        KToolBar *bar = new KToolBar( m_browsers->container(), "NotMainToolBar" );
        bar->setIconSize( 22, false ); //looks more sensible
        bar->setFlat( true ); //removes the ugly frame
        bar->setMovingEnabled( false ); //removes the ugly frame

        QWidget *button = new KToolBarButton( "locationbar_erase", 1, bar );
        QLabel *filter_label = new QLabel( i18n("S&earch:") + " ", bar );
        m_lineEdit = new ClickLineEdit( i18n( "Enter search terms here" ), bar );

        filter_label->setBuddy( m_lineEdit );

        bar->setStretchableWidget( m_lineEdit );
        m_lineEdit->setFrame( QFrame::Sunken );
        m_lineEdit->installEventFilter( this ); //we intercept keyEvents

        connect( button, SIGNAL(clicked()), m_lineEdit, SLOT(clear()) );

        QToolTip::add( button, i18n( "Clear filter" ) );
        QString filtertip = i18n( "Enter space-separated terms to filter the playlist.\n\n"
                                  "Advanced, Google-esque syntax is also available;\n"
                                  "see the handbook (The Playlist section of chapter 4) for details." );

        QToolTip::add( filter_label, filtertip );
        QToolTip::add( m_lineEdit, filtertip );
    } //</Search LineEdit>



    QFrame *playlist = new Playlist( m_browsers->container() );
    dynamicBar->init();
    m_toolbar = new amaroK::ToolBar( m_browsers->container(), "mainToolBar" );
    m_toolbar->setShown( AmarokConfig::showToolbar() );
    QWidget *statusbar = new amaroK::StatusBar( this );

    KAction* repeatAction = amaroK::actionCollection()->action( "repeat" );
    connect( repeatAction, SIGNAL( activated( int ) ), playlist, SLOT( slotRepeatTrackToggled( int ) ) );

    connect( m_lineEdit, SIGNAL(textChanged( const QString& )), playlist, SLOT(setFilterSlot( const QString& )) );

    m_menubar = new KMenuBar( this );
    m_menubar->setShown( AmarokConfig::showMenuBar() );

    //BEGIN Actions menu
    KPopupMenu *actionsMenu = new KPopupMenu( m_menubar );
    actionCollection()->action("playlist_playmedia")->plug( actionsMenu );
    actionCollection()->action("play_audiocd")->plug( actionsMenu );
    actionsMenu->insertSeparator();
    actionCollection()->action("prev")->plug( actionsMenu );
    actionCollection()->action("play_pause")->plug( actionsMenu );
    actionCollection()->action("stop")->plug( actionsMenu );
    actionCollection()->action("next")->plug( actionsMenu );
    actionsMenu->insertSeparator();
    actionCollection()->action(KStdAction::name(KStdAction::Quit))->plug( actionsMenu );

    connect( actionsMenu, SIGNAL( aboutToShow() ), SLOT( actionsMenuAboutToShow() ) );
    //END Actions menu

    //BEGIN Playlist menu
    KPopupMenu *playlistMenu = new KPopupMenu( m_menubar );
    actionCollection()->action("playlist_add")->plug( playlistMenu );
    actionCollection()->action("playlist_save")->plug( playlistMenu );
    playlistMenu->insertSeparator();
    actionCollection()->action("playlist_undo")->plug( playlistMenu );
    actionCollection()->action("playlist_redo")->plug( playlistMenu );
    playlistMenu->insertSeparator();
    actionCollection()->action("playlist_clear")->plug( playlistMenu );
    actionCollection()->action("playlist_shuffle")->plug( playlistMenu );
    actionCollection()->action("playlist_show")->plug( playlistMenu );
    //this one has no real context with regard to the menu
    //actionCollection()->action("playlist_copy")->plug( playlistMenu );
    playlistMenu->insertSeparator();
    actionCollection()->action("queue_selected")->plug( playlistMenu );
    actionCollection()->action("playlist_remove_duplicates")->plug( playlistMenu );
    actionCollection()->action("playlist_select_all")->plug( playlistMenu );
    //END Playlist menu

    //BEGIN Mode menu
    KPopupMenu *modeMenu = new KPopupMenu( m_menubar );
    actionCollection()->action("repeat")->plug( modeMenu );
    KSelectAction *random = static_cast<KSelectAction*>( actionCollection()->action("random_mode") );
    random->plug( modeMenu );
    random->popupMenu()->insertSeparator();
    actionCollection()->action("favor_tracks")->plug( random->popupMenu() );
    //END Mode menu

    //BEGIN Tools menu
    m_toolsMenu = new KPopupMenu( m_menubar );
    m_toolsMenu->insertItem( SmallIconSet( "covermanager" ), i18n("&Cover Manager"), amaroK::Menu::ID_SHOW_COVER_MANAGER );
    actionCollection()->action("queue_manager")->plug( m_toolsMenu );
    m_toolsMenu->insertItem( SmallIconSet( "visualizations"), i18n("&Visualizations"), amaroK::Menu::ID_SHOW_VIS_SELECTOR );
    m_toolsMenu->insertItem( SmallIconSet( "equalizer"), i18n("&Equalizer"), kapp, SLOT( slotConfigEqualizer() ), 0, amaroK::Menu::ID_CONFIGURE_EQUALIZER );
    actionCollection()->action("script_manager")->plug( m_toolsMenu );
    actionCollection()->action("statistics")->plug( m_toolsMenu );
    m_toolsMenu->insertSeparator();
    m_toolsMenu->insertItem( SmallIconSet( "wizard"), i18n("&First-Run Wizard"), amaroK::Menu::ID_SHOW_WIZARD );
    m_toolsMenu->insertItem( SmallIconSet( amaroK::icon( "rescan" ) ), i18n("&Rescan Collection"), amaroK::Menu::ID_RESCAN_COLLECTION );

    #if defined HAVE_XMMS || defined HAVE_LIBVISUAL
    m_toolsMenu->setItemEnabled( amaroK::Menu::ID_SHOW_VIS_SELECTOR, true );
    #else
    m_toolsMenu->setItemEnabled( amaroK::Menu::ID_SHOW_VIS_SELECTOR, false );
    #endif

    connect( m_toolsMenu, SIGNAL( aboutToShow() ), SLOT( toolsMenuAboutToShow() ) );
    connect( m_toolsMenu, SIGNAL( activated(int) ), SLOT( slotMenuActivated(int) ) );
    //END Tools menu

    //BEGIN Settings menu
    m_settingsMenu = new KPopupMenu( m_menubar );
    //TODO use KStdAction or KMainWindow
    static_cast<KToggleAction *>(actionCollection()->action(KStdAction::name(KStdAction::ShowMenubar)))->setChecked( AmarokConfig::showMenuBar() );
    actionCollection()->action(KStdAction::name(KStdAction::ShowMenubar))->plug( m_settingsMenu );
    m_settingsMenu->insertItem( AmarokConfig::showToolbar() ? i18n( "Hide Toolbar" ) : i18n("Show Toolbar"), ID_SHOW_TOOLBAR );
    m_settingsMenu->insertItem( AmarokConfig::showPlayerWindow() ? i18n("Hide Player &Window") : i18n("Show Player &Window"), ID_SHOW_PLAYERWINDOW );
    m_settingsMenu->insertSeparator();
    actionCollection()->action("options_configure_globals")->plug( m_settingsMenu );
    actionCollection()->action(KStdAction::name(KStdAction::KeyBindings))->plug( m_settingsMenu );
    actionCollection()->action(KStdAction::name(KStdAction::ConfigureToolbars))->plug( m_settingsMenu );
    actionCollection()->action(KStdAction::name(KStdAction::Preferences))->plug( m_settingsMenu );

    connect( m_settingsMenu, SIGNAL( activated(int) ), SLOT( slotMenuActivated(int) ) );
    //END Settings menu

    m_menubar->insertItem( i18n( "&Actions" ), actionsMenu );
    m_menubar->insertItem( i18n( "&Playlist" ), playlistMenu );
    m_menubar->insertItem( i18n( "&Mode" ), modeMenu );
    m_menubar->insertItem( i18n( "&Tools" ), m_toolsMenu );
    m_menubar->insertItem( i18n( "&Settings" ), m_settingsMenu );
    m_menubar->insertItem( i18n( "&Help" ), amaroK::Menu::helpMenu() );


    QBoxLayout *layV = new QVBoxLayout( this );
    layV->addWidget( m_menubar );
    layV->addWidget( m_browsers, 1 );
    layV->addWidget( m_toolbar );
    layV->addSpacing( 2 );
    layV->addWidget( statusbar );

    //The volume slider later becomes our FocusProxy, so all wheelEvents get redirected to it
    m_toolbar->setFocusPolicy( QWidget::WheelFocus );
    m_toolbar->setFlat( true );
    m_toolbar->setMovingEnabled( false );
    playlist->setMargin( 2 );
    playlist->installEventFilter( this ); //we intercept keyEvents


    //<XMLGUI>
    {
        QString xmlFile = amaroK::config()->readEntry( "XMLFile", "amarokui.rc" );

        if ( xmlFile == "amarokui_first.rc" )
            // this bug can bite you if you are a pre 1.2 user, we
            // deleted amarokui_first.rc, but we must still support it
            xmlFile = "amarokui.rc";

        setXMLFile( xmlFile );
        createGUI(); //NOTE we implement this
    }
    //</XMLGUI>


    //<Browsers>
    {
        Debug::Block block( "Creating browsers. Please report long start times!" );

        #define addBrowserMacro( Type, name, text, icon ) { \
            Debug::Block block( name ); \
            m_browsers->addBrowser( new Type( name ), text, icon ); }

        #define addInstBrowserMacro( Type, name, text, icon ) { \
            Debug::Block block( name ); \
            m_browsers->addBrowser( Type::instance(), text, icon ); }

        addBrowserMacro( ContextBrowser, "ContextBrowser", i18n( "Context" ), amaroK::icon( "info" ) )
        addBrowserMacro( CollectionBrowser, "CollectionBrowser", i18n( "Collection" ), amaroK::icon( "collection" ) )
        addInstBrowserMacro( PlaylistBrowser, "PlaylistBrowser", i18n( "Playlists" ), amaroK::icon( "playlist" ) )

        //DEBUG: Comment out the addBrowserMacro line and uncomment the m_browsers line (passing in a vfat device name) to see the "virtual root" functionality

        addBrowserMacro( FileBrowser, "FileBrowser", i18n( "Files" ), "folder" )
        //m_browsers->addBrowser( new FileBrowser( "FileBrowser", DeviceManager::instance()->getDevice( "hda5" ) ), i18n( "Files" ), "folder" );

        new MediaBrowser( "MediaBrowser" );
        if( MediaBrowser::isAvailable() )
            addInstBrowserMacro( MediaBrowser, "MediaBrowser", i18n( "Media Device" ), amaroK::icon( "device" ) )
        #undef addBrowserMacro
        #undef addInstBrowserMacro
    }
    //</Browsers>

    connect( Playlist::instance()->qscrollview(), SIGNAL( dynamicModeChanged( const DynamicMode* ) ),
             PlaylistBrowser::instance(), SLOT( loadDynamicItems() ) );


    qApp->installEventFilter( this ); // keyboards shortcuts for the browsers

    connect( playlist, SIGNAL( itemCountChanged(     int, int, int, int, int, int ) ),
             statusbar,  SLOT( slotItemCountChanged( int, int, int, int, int, int ) ) );
    connect( playlist, SIGNAL( queueChanged( const PLItemList &, const PLItemList & ) ),
             statusbar,  SLOT( updateQueueLabel() ) );
    connect( playlist, SIGNAL( aboutToClear() ), m_lineEdit, SLOT( clear() ) );
    amaroK::MessageQueue::instance()->sendMessages();
}

void PlaylistWindow::addBrowser( const QString &name, QWidget *browser, const QString &text, const QString &icon )
{
    if( !m_browsers->browser( name ) )
        m_browsers->addBrowser( browser, text, icon );
}


/**
 * Reload the amarokui.rc xml file.
 * mainly just used by amarok::Menu
 */
void PlaylistWindow::recreateGUI()
{
    setXMLFile( amaroK::config()->readEntry( "XMLFile", "amarokui.rc" ) );
    reloadXML();
    createGUI();
}


/**
 * Create the amarok gui from the xml file.
 */
void PlaylistWindow::createGUI()
{
    setUpdatesEnabled( false );

    m_toolbar->clear();

    //KActions don't unplug themselves when the widget that is plugged is deleted!
    //we need to unplug to detect if the menu is plugged in App::applySettings()
    //TODO report to bugs.kde.org
    //we unplug after clear as otherwise it crashes! dunno why..
     KActionPtrList actions = actionCollection()->actions();
     for( KActionPtrList::Iterator it = actions.begin(), end = actions.end(); it != end; ++it )
     {
         (*it)->unplug( m_toolbar );
     }

    KXMLGUIBuilder builder( this );
    KXMLGUIFactory factory( &builder, this );

    //build Toolbar, plug actions
    factory.addClient( this );

    //TEXT ON RIGHT HACK
    //KToolBarButtons have independent settings for their appearance.
    //KToolBarButton::modeChange() causes that button to set its mode to that of its parent KToolBar
    //KToolBar::setIconText() calls modeChange() for children, unless 2nd param is false

    QStringList list;
    list << "toolbutton_playlist_add"
//         << "toolbutton_playlist_clear"
//         << "toolbutton_playlist_shuffle"
//         << "toolbutton_playlist_show"
         << "toolbutton_burn_menu"
         << "toolbutton_amarok_menu";

    m_toolbar->setIconText( KToolBar::IconTextRight, false ); //we want some buttons to have text on right

    const QStringList::ConstIterator end  = list.constEnd();
    const QStringList::ConstIterator last = list.fromLast();
    for( QStringList::ConstIterator it = list.constBegin(); it != end; ++it )
    {
        KToolBarButton* const button = static_cast<KToolBarButton*>( m_toolbar->child( (*it).latin1() ) );

        if ( it == last ) {
            //if the user has no PlayerWindow, he MUST have the menu action plugged
            //NOTE this is not saved to the local XMLFile, which is what the user will want
            if ( !AmarokConfig::showPlayerWindow() && !AmarokConfig::showMenuBar() && !button )
                actionCollection()->action( "amarok_menu" )->plug( m_toolbar );
        }

        if ( button ) {
            button->modeChange();
            button->setFocusPolicy( QWidget::NoFocus );
        }
    }

    if ( AmarokConfig::showMenuBar() ) {
        if ( actionCollection()->action( "amarok_menu" )->isPlugged() )
            actionCollection()->action( "amarok_menu" )->unplugAll();
    }

    m_toolbar->setIconText( KToolBar::IconOnly, false ); //default appearance
    conserveMemory();
    setUpdatesEnabled( true );
}


/**
 * Apply the loaded settings on the playlist window.
 * this function loads the custom fonts (if chosen) and than calls PlayList::instance()->applySettings();
 */
void PlaylistWindow::applySettings()
{
    switch( AmarokConfig::useCustomFonts() )
    {
    case true:
        Playlist::instance()->setFont( AmarokConfig::playlistWindowFont() );
        ContextBrowser::instance()->setFont( AmarokConfig::contextBrowserFont() );
        break;
    case false:
        Playlist::instance()->unsetFont();
        ContextBrowser::instance()->unsetFont();
        break;
    }
    Playlist::instance()->applySettings();
}


/**
 * @param o The object
 * @param e The event
 *
 * Here we filter some events for the Playlist Search LineEdit and the Playlist. @n
 * this makes life easier since we have more useful functions available from this class
 */
bool PlaylistWindow::eventFilter( QObject *o, QEvent *e )
{


    Playlist* const pl = Playlist::instance();
    typedef QListViewItemIterator It;

    switch( e->type() )
    {
    case 6/*QEvent::KeyPress*/:

        //there are a few keypresses that we intercept

        #define e static_cast<QKeyEvent*>(e)

        if( e->key() == Key_F2 )
        {
            // currentItem is ALWAYS visible.
            QListViewItem *item = pl->currentItem();

            // intercept F2 for inline tag renaming
            // NOTE: tab will move to the next tag
            // NOTE: if item is still null don't select first item in playlist, user wouldn't want that. It's silly.
            // TODO: berkus has solved the "inability to cancel" issue with KListView, but it's not in kdelibs yet..

            // item may still be null, but this is safe
            // NOTE: column 0 cannot be edited currently, hence we pick column 1
            pl->rename( item, 1 ); //TODO what if this column is hidden?

            return true;
        }

        if( e->state() & ControlButton )
        {
            int n = -1;
            switch( e->key() )
            {
                case Key_0: n = 0; break;
                case Key_1: n = 1; break;
                case Key_2: n = 2; break;
                case Key_3: n = 3; break;
                case Key_4: n = 4; break;
                case Key_5: n = 5; break;
            }
            if( n == 0 )
            {
                m_browsers->closeCurrentBrowser();
                return true;
            }
            else if( n > 0 && n <= m_browsers->visibleCount() )
            {
                m_browsers->showHideVisibleBrowser( n - 1 );
                return true;
            }
        }

        if( o == m_lineEdit ) //the search lineedit
        {
            QListViewItem *item;
            switch( e->key() )
            {
            case Key_Up:
            case Key_Down:
            case Key_PageDown:
            case Key_PageUp:
                pl->setFocus();
                QApplication::sendEvent( pl, e );
                return true;

            case Key_Return:
            case Key_Enter:
                item = *It( pl, It::Visible );
                m_lineEdit->clear();
                pl->m_filtertimer->stop(); //HACK HACK HACK
                if( e->state() & ControlButton )
                {
                    PLItemList in, out;
                    if( e->state() & ShiftButton )
                        for( It it( pl, It::Visible ); PlaylistItem *x = static_cast<PlaylistItem*>( *it ); ++it )
                        {
                            pl->queue( x, true );
                            ( pl->m_nextTracks.contains( x ) ? in : out ).append( x );
                        }
                    else
                    {
                        It it( pl, It::Visible );
                        pl->activate( *it );
                        ++it;
                        for( int i = 0; PlaylistItem *x = static_cast<PlaylistItem*>( *it ); ++i, ++it )
                        {
                            in.append( x );
                            pl->m_nextTracks.insert( i, x );
                        }
                    }
                    if( !in.isEmpty() || !out.isEmpty() )
                        emit pl->queueChanged( in, out );
                    pl->setFilter( "" );
                    pl->ensureItemCentered( ( e->state() & ShiftButton ) ? item : pl->currentTrack() );
                }
                else
                {
                    pl->setFilter( "" );
                    if( ( e->state() & ShiftButton ) && item )
                    {
                        pl->queue( item );
                        pl->ensureItemCentered( item );
                    }
                    else
                    {
                        pl->activate( item );
                        pl->showCurrentTrack();
                    }
                }
                return true;

            case Key_Escape:
                m_lineEdit->clear();
                return true;

            default:
                return false;
            }
        }

        //following are for Playlist::instance() only
        //we don't handle these in the playlist because often we manipulate the lineEdit too

        if( o == pl )
        {
            if( pl->currentItem() && ( e->key() == Key_Up && pl->currentItem()->itemAbove() == 0 ) )
            {
                QListViewItem *lastitem = *It( pl, It::Visible );
                while( lastitem && lastitem->itemBelow() )
                    lastitem = lastitem->itemBelow();
                pl->currentItem()->setSelected( false );
                pl->setCurrentItem( lastitem );
                lastitem->setSelected( true );
                pl->ensureItemVisible( lastitem );
                return true;
            }
            if( pl->currentItem() && ( e->key() == Key_Down && pl->currentItem()->itemBelow() == 0 ) )
            {
                pl->currentItem()->setSelected( false );
                pl->setCurrentItem( *It( pl, It::Visible ) );
                (*It( pl, It::Visible ))->setSelected( true );
                pl->ensureItemVisible( *It( pl, It::Visible ) );
                return true;
            }
            if( e->key() == Key_Delete )
            {
                pl->removeSelectedItems();
                return true;
            }
            if( ( e->key() >= Key_0 && e->key() <= Key_Z ) || e->key() == Key_Backspace || e->key() == Key_Escape )
            {
                m_lineEdit->setFocus();
                QApplication::sendEvent( m_lineEdit, e );
                return true;
            }
        }
        #undef e
        break;

    default:
        break;
    }

    return QWidget::eventFilter( o, e );
}


void PlaylistWindow::closeEvent( QCloseEvent *e )
{
    amaroK::genericEventHandler( this, e );
}


void PlaylistWindow::showEvent( QShowEvent* )
{
    static bool firstTime = true;
    if( firstTime )
        Playlist::instance()->setFocus();
    firstTime = false;
}

#include <qdesktopwidget.h>
QSize PlaylistWindow::sizeHint() const
{
    return QApplication::desktop()->screenGeometry( (QWidget*)this ).size() / 1.5;
}


void PlaylistWindow::savePlaylist() const //SLOT
{
    Playlist *pl = Playlist::instance();

    PlaylistItem *item = pl->firstChild();
    if( item && !item->isVisible() )
        item = static_cast<PlaylistItem*>( item->itemBelow() );

    QString title = i18n( "Untitled" );

    if( item )
    {
        QString artist = item->artist();
        QString album  = item->album();

        bool useArtist = true, useAlbum = true;

        item = static_cast<PlaylistItem*>( item->itemBelow() );

        for( ; item; item = static_cast<PlaylistItem*>( item->itemBelow() ) )
        {
            if( artist != item->artist() )
                useArtist = false;
            if( album  != item->album() )
                useAlbum = false;

            if( !useArtist && !useAlbum )
                break;
        }

        if( useArtist && useAlbum )
            title = i18n("%1 - %2").arg( artist, album );
        else if( useArtist )
            title = artist;
        else if( useAlbum )
            title = album;
    }

    QString path = PlaylistDialog::getSaveFileName( title );

    if( !path.isEmpty() && Playlist::instance()->saveM3U( path ) )
        PlaylistWindow::self()->showBrowser( "PlaylistBrowser" );
}


void PlaylistWindow::slotPlayMedia() //SLOT
{
    // Request location and immediately start playback
    slotAddLocation( true );
}


void PlaylistWindow::slotAddLocation( bool directPlay ) //SLOT
{
    // open a file selector to add media to the playlist
    KURL::List files;
    //files = KFileDialog::getOpenURLs( QString::null, "*.*|" + i18n("All Files"), this, i18n("Add Media") );
    KFileDialog dlg(QString::null, "*.*|", this, "openMediaDialog", true);
    dlg.setCaption(directPlay ? i18n("Play Media (Files or URLs)") : i18n("Add Media (Files or URLs)"));
    dlg.setMode( KFile::Files | KFile::Directory );
    dlg.exec();
    files = dlg.selectedURLs();
    if( files.isEmpty() ) return;
    const int options = directPlay ? Playlist::Append | Playlist::DirectPlay : Playlist::Append;

    const KURL::List::ConstIterator end  = files.constEnd();

    for(  KURL::List::ConstIterator it = files.constBegin(); it != end; ++it )
        if( it == files.constBegin() )
            Playlist::instance()->insertMedia( *it, options );
        else
            Playlist::instance()->insertMedia( *it, Playlist::Append );
}


void PlaylistWindow::playAudioCD() //SLOT
{
    KURL::List urls;
    if (EngineController::engine()->getAudioCDContents(QString::null, urls)) {
        if (!urls.isEmpty()) {
            Playlist::instance()->insertMedia(urls, Playlist::Replace);
        }
    } else { // Default behaviour
        m_browsers->showBrowser( "FileBrowser" );
        FileBrowser *fb = static_cast<FileBrowser *>( m_browsers->browser("FileBrowser") );
        fb->setUrl( KURL("audiocd:/Wav/") );
    }
}

void PlaylistWindow::showScriptSelector() //SLOT
{
    ScriptManager::instance()->show();
    ScriptManager::instance()->raise();
}

void PlaylistWindow::showQueueManager() //SLOT
{
    Playlist::instance()->showQueueManager();
}

void PlaylistWindow::showStatistics() //SLOT
{
    if( Statistics::instance() ) {
        Statistics::instance()->raise();
        return;
    }
    Statistics dialog;
    dialog.exec();
}

void PlaylistWindow::slotToggleFocus() //SLOT
{
    if( m_browsers->currentBrowser() && ( Playlist::instance()->hasFocus() || m_lineEdit->hasFocus() ) )
        m_browsers->currentBrowser()->setFocus();
    else
        Playlist::instance()->setFocus();
}

void PlaylistWindow::slotToggleMenu() //SLOT
{
    if( static_cast<KToggleAction *>(actionCollection()->action(KStdAction::name(KStdAction::ShowMenubar)))->isChecked() ) {
        AmarokConfig::setShowMenuBar( true );
        m_menubar->setShown( true );

        if( amaroK::actionCollection()->action( "amarok_menu" )->isPlugged() )
            amaroK::actionCollection()->action( "amarok_menu" )->unplugAll();
    }
    else
    {
        AmarokConfig::setShowMenuBar( false );
        m_menubar->setShown( false );
        recreateGUI();
    }
}

void PlaylistWindow::slotMenuActivated( int index ) //SLOT
{
    switch( index )
    {
    default:
        //saves duplicating the code and header requirements
        amaroK::Menu::instance()->slotActivated( index );
        break;
    case ID_SHOW_TOOLBAR:
        m_toolbar->setShown( !m_toolbar->isShown() );
        AmarokConfig::setShowToolbar( !AmarokConfig::showToolbar() );
        actionCollection()->action(KStdAction::name(KStdAction::ShowMenubar))->setEnabled( m_toolbar->isShown() );
        m_settingsMenu->changeItem( index, m_toolbar->isShown() ? i18n("Hide Toolbar") : i18n("Show Toolbar") );
        break;
    case ID_SHOW_PLAYERWINDOW:
        AmarokConfig::setShowPlayerWindow( !AmarokConfig::showPlayerWindow() );
        m_settingsMenu->changeItem( index, AmarokConfig::showPlayerWindow() ? i18n("Hide Player &Window") : i18n("Show Player &Window") );
        QTimer::singleShot( 0, kapp, SLOT( applySettings() ) );
        break;
    case amaroK::Menu::ID_RESCAN_COLLECTION:
        CollectionDB::instance()->startScan();
        break;
    }
}

void PlaylistWindow::actionsMenuAboutToShow() //SLOT
{
}

void PlaylistWindow::toolsMenuAboutToShow() //SLOT
{
    m_toolsMenu->setItemEnabled( amaroK::Menu::ID_CONFIGURE_EQUALIZER, EngineController::hasEngineProperty( "HasEqualizer" ) );
    m_toolsMenu->setItemEnabled( amaroK::Menu::ID_RESCAN_COLLECTION, !ThreadWeaver::instance()->isJobPending( "CollectionScanner" ) );
}


#include <kwin.h>
/**
 * Show/hide playlist global shortcut and PlayerWindow PlaylistButton connect to this slot
 * RULES:
 * 1. hidden & iconified -> deiconify & show @n
 * 2. hidden & deiconified -> show @n
 * 3. shown & iconified -> deiconify @n
 * 4. shown & deiconified -> hide @n
 * 5. don't hide if there is no tray icon or playerWindow. todo (I can't be arsed) @n
 *
 * @note isMinimized() can only be true if the window isShown()
 * this has taken me hours to get right, change at your peril!
 * there are more contingencies than you can believe
 */
void PlaylistWindow::showHide() //SLOT
{

    const KWin::WindowInfo info = KWin::windowInfo( winId() );
    const uint desktop = KWin::currentDesktop();
    const bool isOnThisDesktop = info.isOnDesktop( desktop );
    const bool isShaded = false;

    if( isShaded )
    {
        KWin::clearState( winId(), NET::Shaded );
        setShown( true );
    }

    if( !isOnThisDesktop )
    {
        KWin::setOnDesktop( winId(), desktop );
        setShown( true );
    }
    else if( !info.isMinimized() && !isShaded ) setShown( !isShown() );

    if( isShown() ) KWin::deIconifyWindow( winId() );
}

bool PlaylistWindow::isReallyShown() const
{
    const KWin::WindowInfo info = KWin::windowInfo( winId() );
    return isShown() && !info.isMinimized() && info.isOnDesktop( KWin::currentDesktop() );
}

//////////////////////////////////////////////////////////////////////////////////////////
/// DynamicBar
//////////////////////////////////////////////////////////////////////////////////////////
DynamicBar::DynamicBar(QWidget* parent)
    : QHBox( parent, "DynamicModeStatusBar" )
{
    m_titleWidget = new DynamicTitle(this);

    setSpacing( KDialog::spacingHint() );
    QWidget *spacer = new QWidget( this );
    setStretchFactor( spacer, 10 );
}

// necessary because it has to be constructed before Playlist::instance(), but also connect to it
void DynamicBar::init()
{
    connect(Playlist::instance()->qscrollview(), SIGNAL(dynamicModeChanged(const DynamicMode*)),
                                                   SLOT(slotNewDynamicMode(const DynamicMode*)));

    KPushButton* editDynamicButton = new KPushButton( i18n("Edit"), this, "DynamicModeEdit" );
    connect( editDynamicButton, SIGNAL(clicked()), Playlist::instance()->qscrollview(), SLOT(editActiveDynamicMode()) );

    KPushButton* repopButton = new KPushButton( i18n("Repopulate"), this, "DynamicModeRepopulate" );
    connect( repopButton, SIGNAL(clicked()), Playlist::instance()->qscrollview(), SLOT(repopulate()) );

    KPushButton* disableButton = new KPushButton( i18n("Turn Off"), this, "DynamicModeDisable" );
    connect( disableButton, SIGNAL(clicked()), Playlist::instance()->qscrollview(), SLOT(disableDynamicMode()) );

    slotNewDynamicMode( Playlist::instance()->dynamicMode() );
}

void DynamicBar::slotNewDynamicMode(const DynamicMode* mode)
{
    setShown(mode);
    if (mode)
        changeTitle(mode->title());
}

void DynamicBar::changeTitle(const QString& title)
{
   m_titleWidget->setTitle(title);
}

//////////////////////////////////////////////////////////////////////////////////////////
/// DynamicTitle
//////////////////////////////////////////////////////////////////////////////////////////
DynamicTitle::DynamicTitle(QWidget* w)
    : QWidget(w, "dynamic title")
{
    m_font.setBold( true );
    setTitle("");
}

void DynamicTitle::setTitle(const QString& newTitle)
{
    m_title = newTitle;
    QFontMetrics fm(m_font);
    setMinimumWidth( s_curveWidth*3 + fm.width(m_title) + s_imageSize );
    setMinimumHeight( fm.height() );
}

void DynamicTitle::paintEvent(QPaintEvent* /*e*/)
{
    QPainter p;
    p.begin( this, false );
    QPen pen( colorGroup().highlightedText(), 0, Qt::NoPen );
    p.setPen( pen );
    p.setBrush( colorGroup().highlight() );
    p.setFont(m_font);

    QFontMetrics fm(m_font);
    int textHeight = fm.height();
    if (textHeight < s_imageSize)
        textHeight = s_imageSize;
    int textWidth = fm.width(m_title);
    int yStart = (height() - textHeight) / 2;
    if(yStart < 0)
        yStart = 0;

    p.drawEllipse( 0, yStart, s_curveWidth * 2, textHeight);
    p.drawEllipse( s_curveWidth + textWidth + s_imageSize, yStart, s_curveWidth*2, textHeight);
    p.fillRect( s_curveWidth, yStart, textWidth + s_imageSize + s_curveWidth, textHeight
                    , QBrush( colorGroup().highlight()) );
    p.drawPixmap( s_curveWidth, yStart + ((textHeight - s_imageSize) /2), SmallIcon("dynamic") );
    //not sure why first arg of Rect shouldn't add @curveWidth
    p.drawText( QRect(s_imageSize, yStart, s_curveWidth + textWidth +s_imageSize, textHeight), Qt::AlignCenter, m_title);
}

#include "playlistwindow.moc"
