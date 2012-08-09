/***************************************************************************
 * copyright            : (c) 2004 Pierpaolo Di Panfilo                    *
 *                        (c) 2004 Mark Kretschmann <markey@web.de>        *
 *                        (c) 2005-2006 Seb Ruiz <me@sebruiz.net>          *
 *                        (c) 2005 Gábor Lehel <illissius@gmail.com>       *
 *                        (c) 2005 Christian Muehlhaeuser <chris@chris.de> *
 * See COPYING file for licensing information                              *
 ***************************************************************************/

#define DEBUG_PREFIX "PlaylistBrowser"

#include "amarok.h"            //actionCollection()
#include "browserToolBar.h"
#include "collectiondb.h"      //smart playlists
#include "debug.h"
#include "htmlview.h"
#include "k3bexporter.h"
#include "mediabrowser.h"
#include "dynamicmode.h"
#include "playlist.h"
#include "playlistbrowser.h"
#include "playlistbrowseritem.h"
#include "playlistselection.h"
#include "podcastbundle.h"
#include "podcastsettings.h"
#include "scancontroller.h"
#include "smartplaylisteditor.h"
#include "tagdialog.h"         //showContextMenu()
#include "threadweaver.h"
#include "statusbar.h"
#include "contextbrowser.h"
#include "xspfplaylist.h"

#include <qevent.h>            //customEvent()
#include <qheader.h>           //mousePressed()
#include <qlabel.h>
#include <qpainter.h>          //paintCell()
#include <qpixmap.h>           //paintCell()
#include <qtextstream.h>       //loadPlaylists(), saveM3U(), savePLS()

#include <kaction.h>
#include <kactionclasses.h>
#include <kactioncollection.h>
#include <kapplication.h>
#include <kfiledialog.h>       //openPlaylist()
#include <kio/job.h>           //deleteSelectedPlaylists()
#include <kiconloader.h>       //smallIcon
#include <kinputdialog.h>
#include <klineedit.h>         //rename()
#include <klocale.h>
#include <kmessagebox.h>       //renamePlaylist(), deleteSelectedPlaylist()
#include <kmultipledrag.h>     //dragObject()
#include <kpopupmenu.h>
#include <kpushbutton.h>
#include <kstandarddirs.h>     //KGlobal::dirs()
#include <kurldrag.h>          //dragObject()

#include <cstdio>              //rename() in renamePlaylist()


inline QString
fileExtension( const QString &fileName )
{
    return amaroK::extension( fileName );
}


PlaylistBrowser *PlaylistBrowser::s_instance = 0;


PlaylistBrowser::PlaylistBrowser( const char *name )
        : QVBox( 0, name )
        , m_polished( false )
        , m_smartCategory( 0 )
        , m_playlistImports( 0 )
        , m_coolStreams( 0 )
        , m_smartDefaults( 0 )
        , m_ac( new KActionCollection( this ) )
        , m_podcastTimer( new QTimer( this ) )
{
    s_instance = this;

    QVBox *browserBox = new QVBox( this );
    browserBox->setSpacing( 3 );

    //<Toolbar>
    addMenuButton  = new KActionMenu( i18n("Add"), amaroK::icon( "add_playlist" ), m_ac );
    addMenuButton->setDelayed( false );

    KPopupMenu *addMenu  = addMenuButton->popupMenu();
    addMenu->insertItem( i18n("Playlist..."), PLAYLIST );
    addMenu->insertItem( i18n("Smart Playlist..."), SMARTPLAYLIST );
    addMenu->insertItem( i18n("Dynamic Playlist..."), ADDDYNAMIC);
    addMenu->insertItem( i18n("Radio Stream..."), STREAM );
    addMenu->insertItem( i18n("Podcast..."), PODCAST );
    connect( addMenu, SIGNAL( activated(int) ), SLOT( slotAddMenu(int) ) );

    KAction *saveButton = new KAction( i18n("Save"), amaroK::icon( "save" ), 0, this, SLOT( slotSave() ), m_ac );

    renameButton   = new KAction( i18n("Rename"), "editclear", 0, this, SLOT( renameSelectedItem() ), m_ac );
    removeButton   = new KAction( i18n("Delete"), amaroK::icon( "remove" ), 0, this, SLOT( removeSelectedItems() ), m_ac );

    m_toolbar = new Browser::ToolBar( browserBox );
    m_toolbar->setIconText( KToolBar::IconTextRight, false ); //we want the open button to have text on right
    addMenuButton->plug( m_toolbar );
    saveButton->plug( m_toolbar );

    m_toolbar->setIconText( KToolBar::IconOnly, false );      //default appearance
    m_toolbar->insertLineSeparator();
    renameButton->plug( m_toolbar);
    removeButton->plug( m_toolbar );

    renameButton->setEnabled( false );
    removeButton->setEnabled( false );
    //</Toolbar>

    m_splitter = new QSplitter( Qt::Vertical, browserBox );
    m_splitter->setChildrenCollapsible( false ); // hiding the InfoPane entirely can only be confusing

    m_listview = new PlaylistBrowserView( m_splitter );

    KConfig *config = amaroK::config( "PlaylistBrowser" );

    int sort = config->readNumEntry( "Sorting", Qt::Ascending );
    m_listview->setSorting( 0, sort == Qt::Ascending ? true : false );

    m_podcastTimerInterval = config->readNumEntry( "Podcast Interval", 14400000 );
    connect( m_podcastTimer, SIGNAL(timeout()), this, SLOT(scanPodcasts()) );

    // signals and slots connections
    connect( m_listview, SIGNAL( rightButtonPressed( QListViewItem *, const QPoint &, int ) ),
             this,         SLOT( showContextMenu( QListViewItem *, const QPoint &, int ) ) );
    connect( m_listview, SIGNAL( doubleClicked( QListViewItem *) ),
             this,         SLOT( slotDoubleClicked( QListViewItem * ) ) );
    connect( m_listview, SIGNAL( itemRenamed( QListViewItem*, const QString&, int ) ),
             this,         SLOT( renamePlaylist( QListViewItem*, const QString&, int ) ) );
    connect( m_listview, SIGNAL( currentChanged( QListViewItem * ) ),
             this,         SLOT( currentItemChanged( QListViewItem * ) ) );
    connect( CollectionDB::instance(), SIGNAL( scanDone( bool ) ), SLOT( collectionScanDone() ) );

    setMinimumWidth( m_toolbar->sizeHint().width() );

    m_infoPane = new InfoPane( m_splitter );

    m_podcastCategory = loadPodcasts();

    setSpacing( 4 );
    setFocusProxy( m_listview );
}


void
PlaylistBrowser::polish()
{
    // we make startup faster by doing the slow bits for this
    // only when we are shown on screen

    DEBUG_FUNC_INFO

    amaroK::OverrideCursor cursor;

//     blockSignals( true );
//     BrowserBar::instance()->restoreWidth();
//     blockSignals( false );

    QVBox::polish();

    /// Podcasting is always initialised in the ctor because of autoscanning

    m_polished = true;

    m_playlistCategory = loadPlaylists();

    if( !CollectionDB::instance()->isEmpty() )
    {
        m_smartCategory = loadSmartPlaylists();
        loadDefaultSmartPlaylists();
    }

    KConfig *config = amaroK::config( "PlaylistBrowser" );

    m_dynamicCategory = loadDynamics();
    m_randomDynamic   = new DynamicEntry( m_dynamicCategory, 0, i18n("Random Mix") );
    m_randomDynamic->setCycleTracks( config->readBoolEntry( "Dynamic Random Remove Played", true ) );
    m_randomDynamic->setMarkHistory( config->readBoolEntry( "Dynamic Random Mark History", true ) );
    m_randomDynamic->setUpcomingCount( config->readNumEntry( "Dynamic Random Upcoming Count", 15 ) );
    m_randomDynamic->setPreviousCount( config->readNumEntry( "Dynamic Random Previous Count", 5 ) );

    m_suggestedDynamic = new DynamicEntry( m_dynamicCategory, m_randomDynamic, i18n("Suggested Songs" ) );
    m_suggestedDynamic->setAppendType( DynamicMode::SUGGESTION );
    m_suggestedDynamic->setCycleTracks( config->readBoolEntry( "Dynamic Suggest Remove Played", true ) );
    m_suggestedDynamic->setMarkHistory( config->readBoolEntry( "Dynamic Suggest Mark History", true ) );
    m_suggestedDynamic->setUpcomingCount( config->readNumEntry( "Dynamic Suggest Upcoming Count", 15 ) );
    m_suggestedDynamic->setPreviousCount( config->readNumEntry( "Dynamic Suggest Previous Count", 5 ) );

    m_streamsCategory  = loadStreams();
    loadCoolStreams();

    if( amaroK::dynamicMode() )
    {
        QStringList playlists = amaroK::dynamicMode()->items();

        for( uint i=0; i < playlists.count(); i++ )
        {
            QListViewItem *item = m_listview->findItem( playlists[i], 0, Qt::ExactMatch );
            if( item )
            {
                m_dynamicEntries.append( item );
                if( item->rtti() == PlaylistEntry::RTTI )
                     static_cast<PlaylistEntry*>( item )->setDynamic( true );
                if( item->rtti() == SmartPlaylist::RTTI )
                     static_cast<SmartPlaylist*>( item )->setDynamic( true );
            }
        }
    }

    // ListView item state restoration:
    // First we check if the number of items in the listview is the same as it was on last
    // application exit. If true, we iterate over all items and restore their open/closed state.
    // Note: We ignore podcast items, because they are added dynamically added to the ListView.
    QValueList<int> stateList = config->readIntListEntry( "Item State" );
    QListViewItemIterator it( m_listview );
    uint count = 0;
    while ( it.current() ) {
        if( !isPodcastEpisode( it.current() ) )
            ++count;
        ++it;
    }

    if ( count == stateList.count() ) {
        uint index = 0;
        it = QListViewItemIterator( m_listview );
        while ( it.current() ) {
            if( !isPodcastEpisode( it.current() ) ) {
                it.current()->setOpen( stateList[index] );
                ++index;
            }
            ++it;
        }
    }

    // Set height of InfoPane
    m_infoPane->setStoredHeight( config->readNumEntry( "InfoPane Height", 200 ) );
}


PlaylistBrowser::~PlaylistBrowser()
{
    DEBUG_BLOCK

    if( m_polished )
    {
        // <markey> Not sure if these calls are still needed, now that we're saving
        //          the state after each change.
        savePlaylists();
        saveStreams();
        saveSmartPlaylists();
        saveDynamics();
        savePodcastFolderStates( m_podcastCategory );

        QStringList list;
        for( uint i=0; i < m_dynamicEntries.count(); i++ )
        {
            QListViewItem *item = m_dynamicEntries.at( i );
            list.append( item->text(0) );
        }

        KConfig *config = amaroK::config( "PlaylistBrowser" );
        config->writeEntry( "Sorting", m_listview->sortOrder() );
        config->writeEntry( "Podcast Interval", m_podcastTimerInterval );
        config->writeEntry( "Podcast Folder Open", m_podcastCategory->isOpen() );
        config->writeEntry( "InfoPane Height", m_infoPane->getHeight() );
    }
}


void
PlaylistBrowser::setInfo( const QString &title, const QString &info )
{
    m_infoPane->setInfo( title, info );
}

void
PlaylistBrowser::resizeEvent( QResizeEvent * )
{
    if( static_cast<QWidget*>( m_infoPane->child( "container" ) )->isShown() )
        m_infoPane->setMaximumHeight( ( int )( m_splitter->height() / 1.5 ) );
}


/**
 *************************************************************************
 *  STREAMS
 *************************************************************************
 **/

QString PlaylistBrowser::streamBrowserCache() const
{
    return amaroK::saveLocation() + "streambrowser_save.xml";
}


PlaylistCategory* PlaylistBrowser::loadStreams()
{
    QFile file( streamBrowserCache() );

    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );

    QDomDocument d;
    QDomElement e;

    QListViewItem *after = m_dynamicCategory;

    if( !file.open( IO_ReadOnly ) || !d.setContent( stream.read() ) )
    { /*Couldn't open the file or it had invalid content, so let's create an empty element*/
        return new PlaylistCategory(m_listview, after , i18n("Radio Streams") );
    }
    else {
        e = d.namedItem( "category" ).toElement();
        if ( e.attribute("formatversion") =="1.1" ) {
            PlaylistCategory* p = new PlaylistCategory( m_listview, after, e );
            p->setText(0, i18n("Radio Streams") );
            return p;
        }
        else { // Old unversioned format
            PlaylistCategory* p = new PlaylistCategory( m_listview, after, i18n("Radio Streams") );
            QListViewItem *last = 0;
            QDomNode n = d.namedItem( "streambrowser" ).namedItem("stream");
            for( ; !n.isNull();  n = n.nextSibling() ) {
                last = new StreamEntry( p, last, n.toElement() );
            }
            return p;
        }
    }
}

void PlaylistBrowser::loadCoolStreams()
{
    QFile file( locate( "data","amarok/data/Cool-Streams.xml" ) );
    if( !file.open( IO_ReadOnly ) )
        return;

    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );

    QDomDocument d;

    if( !d.setContent( stream.read() ) )
    {
        error() << "Bad Cool Streams XML file" << endl;
        return;
    }

    m_coolStreams = new PlaylistCategory( m_streamsCategory, 0, i18n("Cool-Streams") );
    m_coolStreams->setOpen( m_coolStreamsOpen );
    KListViewItem *last = 0;

    QDomNode n = d.namedItem( "coolstreams" ).firstChild();

    for( ; !n.isNull(); n = n.nextSibling() )
    {
        QDomElement e = n.toElement();
        QString name = e.attribute( "name" );
        e = n.namedItem( "url" ).toElement();
        KURL url  = KURL::KURL( e.text() );
        last = new StreamEntry( m_coolStreams, last, url, name );
    }
}


void PlaylistBrowser::addStream( QListViewItem *parent )
{
    StreamEditor dialog( this, i18n( "Radio Stream" ), QString::null );
    dialog.setCaption( i18n( "Add Radio Stream" ) );

    if( !parent ) parent = static_cast<QListViewItem*>(m_streamsCategory);

    if( dialog.exec() == QDialog::Accepted )
    {
        new StreamEntry( parent, 0, dialog.url(), dialog.name() );
        parent->sortChildItems( 0, true );
        parent->setOpen( true );

        saveStreams();
    }
}


void PlaylistBrowser::editStreamURL( StreamEntry *item, const bool readonly )
{
    StreamEditor dialog( this, item->title(), item->url().prettyURL(), readonly );
    dialog.setCaption( readonly ? i18n( "Radio Stream" ) : i18n( "Edit Radio Stream" ) );

    if( dialog.exec() == QDialog::Accepted )
    {
        item->setTitle( dialog.name() );
        item->setURL( dialog.url() );
        item->setText(0, dialog.name() );
    }
}


void PlaylistBrowser::saveStreams()
{
    QFile file( streamBrowserCache() );

    QDomDocument doc;
    QDomElement streamB = m_streamsCategory->xml();
    streamB.setAttribute( "product", "Amarok" );
    streamB.setAttribute( "version", APP_VERSION );
    streamB.setAttribute( "formatversion", "1.1" );
    QDomNode streamsNode = doc.importNode( streamB, true );
    doc.appendChild( streamsNode );

    QString temp( doc.toString() );

    // Only open the file after all data is ready. If it crashes, data is not lost!
    if ( !file.open( IO_WriteOnly ) ) return;

    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );
    stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    stream << temp;
}

/**
 *************************************************************************
 *  SMART-PLAYLISTS
 *************************************************************************
 **/

QString PlaylistBrowser::smartplaylistBrowserCache() const
{
    return amaroK::saveLocation() + "smartplaylistbrowser_save.xml";
}

void PlaylistBrowser::addSmartPlaylist( QListViewItem *parent ) //SLOT
{
    if( CollectionDB::instance()->isEmpty() || !m_smartCategory )
        return;

    if( !parent ) parent = static_cast<QListViewItem*>(m_smartCategory);

    SmartPlaylistEditor dialog( i18n("Untitled"), this );
    if( dialog.exec() == QDialog::Accepted ) {
        new SmartPlaylist( parent, 0, dialog.result() );
        parent->sortChildItems( 0, true );
        parent->setOpen( true );

        saveSmartPlaylists();
    }
}

PlaylistCategory* PlaylistBrowser::loadSmartPlaylists()
{

    QFile file( smartplaylistBrowserCache() );
    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );
    QListViewItem *after = m_playlistCategory;

    QDomDocument d;
    QDomElement e;

    if( !file.open( IO_ReadOnly ) || !d.setContent( stream.read() ) )
    { /*Couldn't open the file or it had invalid content, so let's create an empty element*/
        return new PlaylistCategory(m_listview, after, i18n("Smart Playlists") );
    }
    else {
        e = d.namedItem( "category" ).toElement();
        float version = e.attribute("formatversion").toFloat();
        if ( version == 1.7 )
        {
            PlaylistCategory* p = new PlaylistCategory(m_listview, after, e );
            p->setText( 0, i18n("Smart Playlists") );
            return p;
        }
        else if ( version >= 1.1  )
        {
            PlaylistCategory* p = new PlaylistCategory(m_listview, after, e );
            p->setText( 0, i18n("Smart Playlists") );
            debug() << "loading old format smart playlists, converted to new format" << endl;
            updateSmartPlaylists( p );
            saveSmartPlaylists( p );
            return p;
        }
        else { // Old unversioned format
            PlaylistCategory* p = new PlaylistCategory(m_listview, after , i18n("Smart Playlists") );
            QListViewItem *last = 0;
            QDomNode n = d.namedItem( "smartplaylists" ).namedItem("smartplaylist");
            for( ; !n.isNull();  n = n.nextSibling() ) {
                last = new SmartPlaylist( p, last, n.toElement() );
            }
            return p;
        }
    }
}

void PlaylistBrowser::updateSmartPlaylists( QListViewItem *p )
{
    if( !p )
        return;

    for( QListViewItem *it =  p->firstChild();
            it;
            it = it->nextSibling() )
    {
        SmartPlaylist *spl = dynamic_cast<SmartPlaylist *>( it );
        if( spl )
        {
            QDomElement xml = spl->xml();
            QDomElement query = xml.namedItem( "sqlquery" ).toElement();
            QRegExp limitSearch( "LIMIT.*(\\d+)\\s*,\\s*(\\d+)" );
            QRegExp selectFromSearch( "SELECT[^'\"]*FROM" );
            for(QDomNode child = query.firstChild();
                    !child.isNull();
                    child = child.nextSibling() )
            {
                if( child.isText() )
                {
                    //HACK this should be refactored to just regenerate the SQL from the <criteria>'s
                    QDomText text = child.toText();
                    QString sql = text.data();
                    if ( selectFromSearch.search( sql ) != -1 )
                        sql.replace( selectFromSearch, "SELECT " + QueryBuilder::dragSQLFields() + " FROM" );
                    if ( limitSearch.search( sql ) != -1 )
                        sql.replace( limitSearch,
                          QString( "LIMIT %1 OFFSET %2").arg( limitSearch.capturedTexts()[2].toInt() ).arg( limitSearch.capturedTexts()[1].toInt() ) );

                    text.setData( sql );
                    break;
                }
            }
            spl->setXml( xml );
        }
        else
            updateSmartPlaylists( it );
    }
}

void PlaylistBrowser::loadDefaultSmartPlaylists()
{
    const QStringList genres  = CollectionDB::instance()->query( "SELECT DISTINCT name FROM genre;" );
    const QStringList artists = CollectionDB::instance()->artistList();
    SmartPlaylist *item;
    QueryBuilder qb;
    QListViewItem *last = 0;

    m_smartDefaults = new PlaylistCategory( m_smartCategory, 0, i18n("Collection") );
    m_smartDefaults->setOpen( m_smartDefaultsOpen );

    /********** All Collection **************/
    qb.initSQLDrag();
    qb.sortBy( QueryBuilder::tabArtist, QueryBuilder::valName );
    qb.sortBy( QueryBuilder::tabAlbum, QueryBuilder::valName );
    qb.sortBy( QueryBuilder::tabSong, QueryBuilder::valTrack );

    item = new SmartPlaylist( m_smartDefaults, 0, i18n( "All Collection" ), qb.query() );
    item->setPixmap( 0, SmallIcon( amaroK::icon( "collection" ) ) );

    /********** Favorite Tracks **************/
    qb.initSQLDrag();
    qb.sortBy( QueryBuilder::tabStats, QueryBuilder::valPercentage, true );
    qb.setLimit( 0, 15 );

    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Favorite Tracks" ), qb.query() );
    last = 0;
    foreach( artists ) {
        qb.initSQLDrag();
        qb.addMatch( QueryBuilder::tabArtist, *it );
        qb.sortBy( QueryBuilder::tabStats, QueryBuilder::valPercentage, true );
        qb.setLimit( 0, 15 );

        last = new SmartPlaylist( item, last, i18n( "By %1" ).arg( *it ), qb.query() );
    }

    /********** Most Played **************/
    qb.initSQLDrag();
    qb.sortBy( QueryBuilder::tabStats, QueryBuilder::valPlayCounter, true );
    qb.setLimit( 0, 15 );

    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Most Played" ), qb.query() );
    last = 0;
    foreach( artists ) {
        qb.initSQLDrag();
        qb.addMatch( QueryBuilder::tabArtist, *it );
        qb.sortBy( QueryBuilder::tabStats, QueryBuilder::valPlayCounter, true );
        qb.setLimit( 0, 15 );

        last = new SmartPlaylist( item, last, i18n( "By %1" ).arg( *it ), qb.query() );
    }

    /********** Newest Tracks **************/
    qb.initSQLDrag();
    qb.sortBy( QueryBuilder::tabSong, QueryBuilder::valCreateDate, true );
    qb.setLimit( 0, 15 );

    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Newest Tracks" ), qb.query() );
    last = 0;
    foreach( artists ) {
        qb.initSQLDrag();
        qb.addMatch( QueryBuilder::tabArtist, *it );
        qb.sortBy( QueryBuilder::tabSong, QueryBuilder::valCreateDate, true );
        qb.setLimit( 0, 15 );

        last = new SmartPlaylist( item, last, i18n( "By %1" ).arg( *it ), qb.query() );
    }

    /********** Last Played **************/
    qb.initSQLDrag();
    qb.sortBy( QueryBuilder::tabStats, QueryBuilder::valAccessDate, true );
    qb.setLimit( 0, 15 );

    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Last Played" ), qb.query() );

    /********** Never Played **************/
    qb.initSQLDrag();
    qb.exclusiveFilter( QueryBuilder::tabSong, QueryBuilder::tabStats, QueryBuilder::valURL );
    qb.sortBy( QueryBuilder::tabArtist, QueryBuilder::valName );
    qb.sortBy( QueryBuilder::tabAlbum, QueryBuilder::valName );
    qb.sortBy( QueryBuilder::tabSong, QueryBuilder::valTrack );

    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Never Played" ), qb.query() );

    /********** Ever Played **************/
    qb.initSQLDrag();
    qb.excludeFilter( QueryBuilder::tabStats, QueryBuilder::valPlayCounter, "1", QueryBuilder::modeLess );
    qb.sortBy( QueryBuilder::tabArtist, QueryBuilder::valName );
    qb.sortBy( QueryBuilder::tabAlbum, QueryBuilder::valName );
    qb.sortBy( QueryBuilder::tabSong, QueryBuilder::valTrack );
    qb.sortBy( QueryBuilder::tabStats, QueryBuilder::valScore );

    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Ever Played" ), qb.query() );

    /********** Genres **************/
    item = new SmartPlaylist( m_smartDefaults, item, i18n( "Genres" ), QString() );
    last = 0;
    foreach( genres ) {
        qb.initSQLDrag();
        qb.addMatch( QueryBuilder::tabGenre, *it );
        qb.sortBy( QueryBuilder::tabArtist, QueryBuilder::valName );
        qb.sortBy( QueryBuilder::tabAlbum, QueryBuilder::valName );
        qb.sortBy( QueryBuilder::tabSong, QueryBuilder::valTrack );

        last = new SmartPlaylist( item, last, i18n( "%1" ).arg( *it ), qb.query() );
    }

    /********** 50 Random Tracks **************/
    qb.initSQLDrag();
    qb.setOptions( QueryBuilder::optRandomize );
    qb.setLimit( 0, 50 );
    item = new SmartPlaylist( m_smartDefaults, item, i18n( "50 Random Tracks" ), qb.query() );
}

void PlaylistBrowser::editSmartPlaylist( SmartPlaylist* item )
{
    SmartPlaylistEditor dialog( this, item->xml() );
    if( dialog.exec() == QDialog::Accepted ) {
        item->setXml( dialog.result() );
        item->setText(0, dialog.name());
    }
}

void PlaylistBrowser::saveSmartPlaylists( PlaylistCategory *smartCategory )
{
    QFile file( smartplaylistBrowserCache() );

    if( !smartCategory )
        smartCategory = m_smartCategory;

    // If the user hadn't set a collection, we didn't create the Smart Playlist Item
    if( !smartCategory ) return;

    QDomDocument doc;
    QDomElement smartB = smartCategory->xml();
    smartB.setAttribute( "product", "Amarok" );
    smartB.setAttribute( "version", APP_VERSION );
    smartB.setAttribute( "formatversion", "1.7" );
    QDomNode smartplaylistsNode = doc.importNode( smartB, true );
    doc.appendChild( smartplaylistsNode );

    QString temp( doc.toString() );

    // Only open the file after all data is ready. If it crashes, data is not lost!
    if ( !file.open( IO_WriteOnly ) ) return;

    QTextStream smart( &file );
    smart.setEncoding( QTextStream::UnicodeUTF8 );
    smart << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    smart << temp;
}

/**
 *************************************************************************
 *  PARTIES
 *************************************************************************
 **/

QString PlaylistBrowser::dynamicBrowserCache() const
{
    return amaroK::saveLocation() + "dynamicbrowser_save.xml";
}

PlaylistCategory* PlaylistBrowser::loadDynamics()
{
    QFile file( dynamicBrowserCache() );

    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );

    QDomDocument d;
    QDomElement e;

    PlaylistCategory *after = m_smartCategory;
    if( CollectionDB::instance()->isEmpty() || !m_smartCategory ) // incase of no collection
        after = m_playlistCategory;

    if( !file.open( IO_ReadOnly ) || !d.setContent( stream.read() ) )
    { /*Couldn't open the file or it had invalid content, so let's create some defaults*/
        PlaylistCategory *p = new PlaylistCategory( m_listview, after, i18n("Dynamic Playlists") );
        return p;
    }
    else {
        e = d.namedItem( "category" ).toElement();
        if ( e.attribute("formatversion") =="1.1" ) {
            PlaylistCategory* p = new PlaylistCategory( m_listview, after , e );
            p->setText( 0, i18n("Dynamic Playlists") );
            return p;
        }
        else { // Old unversioned format
            PlaylistCategory* p = new PlaylistCategory( m_listview, after, i18n("Dynamic Playlists") );
            QListViewItem *last = 0;
            QDomNode n = d.namedItem( "dynamicbrowser" ).namedItem("dynamic");
            for( ; !n.isNull();  n = n.nextSibling() ) {
                last = new DynamicEntry( p, last, n.toElement() );
            }
            return p;
        }
    }
}

void PlaylistBrowser::saveDynamics()
{
    // save alterations to the default dynamics
    KConfig *config = amaroK::config( "PlaylistBrowser" );
    config->writeEntry( "Dynamic Random Mark History",   m_randomDynamic->markHistory() );
    config->writeEntry( "Dynamic Random Remove Played",  m_randomDynamic->cycleTracks() );
    config->writeEntry( "Dynamic Random Upcoming Count", m_randomDynamic->upcomingCount() );
    config->writeEntry( "Dynamic Random Previous Count", m_randomDynamic->previousCount() );

    config->writeEntry( "Dynamic Suggest Mark History",   m_suggestedDynamic->markHistory() );
    config->writeEntry( "Dynamic Suggest Remove Played",  m_suggestedDynamic->cycleTracks() );
    config->writeEntry( "Dynamic Suggest Upcoming Count", m_suggestedDynamic->upcomingCount() );
    config->writeEntry( "Dynamic Suggest Previous Count", m_suggestedDynamic->previousCount() );

    QFile file( dynamicBrowserCache() );
    QTextStream stream( &file );

    QDomDocument doc;
    QDomElement dynamicB = m_dynamicCategory->xml();
    dynamicB.setAttribute( "product", "Amarok" );
    dynamicB.setAttribute( "version", APP_VERSION );
    dynamicB.setAttribute( "formatversion", "1.1" );
    QDomNode dynamicsNode = doc.importNode( dynamicB, true );
    doc.appendChild( dynamicsNode );

    QString temp( doc.toString() );

    // Only open the file after all data is ready. If it crashes, data is not lost!
    if ( !file.open( IO_WriteOnly ) ) return;

    stream.setEncoding( QTextStream::UnicodeUTF8 );
    stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    stream << temp;
}

void PlaylistBrowser::loadDynamicItems()
{
    // Make sure all items are unmarked
    for( uint i=0; i < m_dynamicEntries.count(); i++ )
    {
        QListViewItem *it = m_dynamicEntries.at( i );

        if( it )
        {
            if( isPlaylist( it ) )
            {
                PlaylistEntry *item = static_cast<PlaylistEntry*>(it);
                item->setDynamic( false );
            }
            else if( isSmartPlaylist( it ) )
            {
                SmartPlaylist *item = static_cast<SmartPlaylist*>(it);
                item->setDynamic( false );
            }
        }
    }
    m_dynamicEntries.clear();  // Dont use remove(), since we do i++, which would cause skip overs!!!

    // Mark appropriate items as used
    if( amaroK::dynamicMode() && amaroK::dynamicMode()->appendType()== DynamicMode::CUSTOM )
    {
        QStringList playlists = amaroK::dynamicMode()->items();
        for( uint i=0; i < playlists.count(); i++ )
        {
            QListViewItem *it = findItem( playlists[i], 0 );

            if( it )
            {
                m_dynamicEntries.append( it );
                if( isPlaylist( it ) )
                {
                    PlaylistEntry *item = static_cast<PlaylistEntry*>(it);
                    item->setDynamic( true );
                }
                else if( isSmartPlaylist( it ) )
                {
                    SmartPlaylist *item = static_cast<SmartPlaylist*>(it);
                    item->setDynamic( true );
                }
            }
        }
    }
}

/**
 *************************************************************************
 *  PODCASTS
 *************************************************************************
 **/

QString PlaylistBrowser::podcastBrowserCache() const
{
    //returns the playlists stats cache file
    return amaroK::saveLocation() + "podcastbrowser_save.xml";
}

PlaylistCategory* PlaylistBrowser::loadPodcasts()
{
    DEBUG_BLOCK

    QFile file( podcastBrowserCache() );
    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );

    QDomDocument d;
    QDomElement e;

    QListViewItem *after = 0;

    if( !file.open( IO_ReadOnly ) || !d.setContent( stream.read() ) )
    { /*Couldn't open the file or it had invalid content, so let's create an empty element*/
        PlaylistCategory *p = new PlaylistCategory( m_listview, after, i18n("Podcasts") );
        p->setId( 0 );
        loadPodcastsFromDatabase( p );
        return p;
    }
    else {
        e = d.namedItem( "category" ).toElement();

        if ( e.attribute("formatversion") == "1.1" ) {
            debug() << "Podcasts are being moved to the database..." << endl;
            m_podcastItemsToScan.clear();

            PlaylistCategory *p = new PlaylistCategory( m_listview, after, e );
            p->setId( 0 );
            //delete the file, it is deprecated
            KIO::del( KURL::fromPathOrURL( podcastBrowserCache() ) );

            if( !m_podcastItemsToScan.isEmpty() )
                m_podcastTimer->start( m_podcastTimerInterval );

            return p;
        }
    }
    PlaylistCategory *p = new PlaylistCategory( m_listview, after, i18n("Podcasts") );
    p->setId( 0 );
    return p;
}

void PlaylistBrowser::loadPodcastsFromDatabase( PlaylistCategory *p )
{
    if( !p )   p = m_podcastCategory;
    m_podcastItemsToScan.clear();

    while( p->firstChild() )
        delete p->firstChild();

    QMap<int,PlaylistCategory*> folderMap = loadPodcastFolders( p );

    QValueList<PodcastChannelBundle> channels;
    QValueList<PodcastEpisodeBundle> episodes;

    channels = CollectionDB::instance()->getPodcastChannels();

    PodcastChannel *channel = 0;

    foreachType( QValueList<PodcastChannelBundle>, channels )
    {
        PlaylistCategory *parent = p;
        const int parentId = (*it).parentId();
        if( parentId > 0 && folderMap.find( parentId ) != folderMap.end() )
            parent = folderMap[parentId];

        channel  = new PodcastChannel( parent, channel, *it );
        bool hasNew = false;
        episodes = CollectionDB::instance()->getPodcastEpisodes( (*it).url() );

        PodcastEpisodeBundle bundle;
         // podcasts are retured chronologically, insert them in reverse
        while( !episodes.isEmpty() )
        {
            bundle = episodes.first();
            new PodcastEpisode( channel, 0, bundle );

            if( bundle.isNew() )
                hasNew = true;

            episodes.pop_front();
        }
        channel->setNew( hasNew );

        if( channel->autoscan() )
            m_podcastItemsToScan.append( channel );
    }

    if( !m_podcastItemsToScan.isEmpty() )
        m_podcastTimer->start( m_podcastTimerInterval );
}

QMap<int,PlaylistCategory*>
PlaylistBrowser::loadPodcastFolders( PlaylistCategory *p )
{
    QString sql = "SELECT * FROM podcastfolders ORDER BY parent ASC;";
    QStringList values = CollectionDB::instance()->query( sql );

    // store the folder and IDs so finding a parent is fast
    QMap<int,PlaylistCategory*> folderMap;
    PlaylistCategory *folder = 0;
    foreach( values )
    {
        const int     id       =     (*it).toInt();
        const QString t        =    *++it;
        const int     parentId =   (*++it).toInt();
        const bool    isOpen   = ( (*++it) == CollectionDB::instance()->boolT() ? true : false );

        PlaylistCategory *parent = p;
        if( parentId > 0 && folderMap.find( parentId ) != folderMap.end() )
            parent = folderMap[parentId];

        folder = new PlaylistCategory( parent, folder, t, id );
        folder->setOpen( isOpen );

        folderMap[id] = folder;
    }
    // check if the base folder exists
    KConfig *config = amaroK::config( "PlaylistBrowser" );
    p->setOpen( config->readBoolEntry( "Podcast Folder Open", true ) );

    return folderMap;
}

void PlaylistBrowser::savePodcastFolderStates( PlaylistCategory *folder )
{
    if( !folder ) return;

    PlaylistCategory *child = static_cast<PlaylistCategory*>(folder->firstChild());
    while( child )
    {
        if( isCategory( child ) )
            savePodcastFolderStates( child );
        else
            break;

        child = static_cast<PlaylistCategory*>(child->nextSibling());
    }
    if( folder != m_podcastCategory )
    {
        if( folder->id() < 0 ) // probably due to a 1.3->1.4 migration
        {                      // we add the folder to the db, set the id and then update all the children
            int parentId = static_cast<PlaylistCategory*>(folder->parent())->id();
            int newId = CollectionDB::instance()->addPodcastFolder( folder->text(0), parentId, folder->isOpen() );
            folder->setId( newId );
            PodcastChannel *chan = static_cast<PodcastChannel*>(folder->firstChild());
            while( chan )
            {
                if( isPodcastChannel( chan ) )
                    // will update the database so child has correct parentId.
                    chan->setParent( folder );
                chan = static_cast<PodcastChannel*>(chan->nextSibling());
            }
        }
        else
        {
            CollectionDB::instance()->updatePodcastFolder( folder->id(), folder->text(0),
                              static_cast<PlaylistCategory*>(folder->parent())->id(), folder->isOpen() );
        }
    }
}

void PlaylistBrowser::scanPodcasts()
{
    //don't want to restart timer unnecessarily.  addPodcast will start it if it is necessary
    if( m_podcastItemsToScan.isEmpty() ) return;

    for( uint i=0; i < m_podcastItemsToScan.count(); i++ )
    {
        QListViewItem  *item = m_podcastItemsToScan.at( i );
        PodcastChannel *pc   = static_cast<PodcastChannel*>(item);
        pc->rescan();
    }
    //restart timer
    m_podcastTimer->start( m_podcastTimerInterval );
}

void PlaylistBrowser::refreshPodcasts( QListViewItem *parent )
{
    for( QListViewItem *child = parent->firstChild();
            child;
            child = child->nextSibling() )
    {
        if( isPodcastChannel( child ) )
            static_cast<PodcastChannel*>( child )->rescan();
        else if( isCategory( child ) )
            refreshPodcasts( child );
    }
}

void PlaylistBrowser::addPodcast( QListViewItem *parent )
{
    bool ok;
    const QString name = KInputDialog::getText(i18n("Add Podcast"), i18n("Enter Podcast URL:"), QString::null, &ok, this);

    if( ok && !name.isEmpty() )
    {
        addPodcast( KURL::fromPathOrURL( name ), parent );
    }
}

void PlaylistBrowser::configurePodcasts( QListViewItem *parent )
{
    QPtrList<PodcastChannel> podcastChannelList;
    for( QListViewItem *child = parent->firstChild();
         child;
         child = child->nextSibling() )
    {
        if( isPodcastChannel( child ) )
        {
            podcastChannelList.append( static_cast<PodcastChannel*>( child ) );
        }
    }
    if( !podcastChannelList.isEmpty() )
        configurePodcasts( podcastChannelList, i18n( "Podcasts contained in %1", "All in %1").arg( parent->text( 0 ) ) );
}

void PlaylistBrowser::configureSelectedPodcasts()
{
    QPtrList<PodcastChannel> selected;
    QListViewItemIterator it( m_listview, QListViewItemIterator::Selected);
    for( ; it.current(); ++it )
    {
        if( isPodcastChannel( (*it) ) )
            selected.append( static_cast<PodcastChannel*>(*it) );
    }
    if (selected.isEmpty() )
        return; //shouldn't happen

    if( selected.count() == 1 )
        selected.getFirst()->configure();
    else
        configurePodcasts( selected, i18n("1 Podcast", "%n Podcasts", selected.count() ) );

    if( m_podcastItemsToScan.isEmpty() )
        m_podcastTimer->stop();

    else if( m_podcastItemsToScan.count() == 1 )
        m_podcastTimer->start( m_podcastTimerInterval );
                    // else timer is already running
}

void PlaylistBrowser::configurePodcasts( QPtrList<PodcastChannel> &podcastChannelList,
                                         const QString &caption )
{

    if( podcastChannelList.isEmpty() )
    {
        debug() << "BUG: podcastChannelList is empty" << endl;
        return;
    }
    QPtrList<PodcastSettings> podcastSettingsList;
    foreachType( QPtrList<PodcastChannel>, podcastChannelList)
    {
        podcastSettingsList.append( (*it)->getSettings() );
    }
    PodcastSettingsDialog *dialog = new PodcastSettingsDialog( podcastSettingsList, caption );
    if( dialog->configure() )
    {
        PodcastChannel *channel = podcastChannelList.first();
        foreachType( QPtrList<PodcastSettings>, podcastSettingsList )
        {
            if ( (*it)->title() ==  channel->title() )
            {
                channel->setSettings( *it );
            }
            else
                debug() << " BUG in playlistbrowser.cpp:configurePodcasts( )" << endl;

            channel = podcastChannelList.next();
        }
    }
}

PodcastChannel *
PlaylistBrowser::findPodcastChannel( const KURL &feed, QListViewItem *parent ) const
{
    if( !parent ) parent = static_cast<QListViewItem*>(m_podcastCategory);

    for( QListViewItem *it = parent->firstChild();
            it;
            it = it->nextSibling() )
    {
        if( isPodcastChannel( it ) )
        {
            PodcastChannel *channel = static_cast<PodcastChannel *>( it );
            if( channel->url().prettyURL() == feed.prettyURL() )
            {
                return channel;
            }
        }
        else if( isCategory( it ) )
        {
            PodcastChannel *channel = findPodcastChannel( feed, it );
            if( channel )
                return channel;
        }
    }

    return 0;
}

PodcastEpisode *
PlaylistBrowser::findPodcastEpisode( const KURL &episode, const KURL &feed ) const
{
    PodcastChannel *channel = findPodcastChannel( feed );
    QListViewItem *child = channel->firstChild();
    while( child )
    {
        #define child static_cast<PodcastEpisode*>(child)
        if( child->url() == episode )
            return child;
        #undef  child
        child = child->nextSibling();
    }

    return 0;
}

void PlaylistBrowser::addPodcast( const KURL& url, QListViewItem *parent )
{
    if( !parent ) parent = static_cast<QListViewItem*>(m_podcastCategory);

    PodcastChannel *channel = findPodcastChannel( url );
    if( channel )
    {
        amaroK::StatusBar::instance()->longMessage(
                i18n( "Already subscribed to feed %1 as %2" )
                .arg( url.prettyURL(), channel->title() ),
                KDE::StatusBar::Sorry );
        return;
    }

    PodcastChannel *pc = new PodcastChannel( parent, 0, url );

    if( m_podcastItemsToScan.isEmpty() )
    {
        m_podcastItemsToScan.append( pc );
        m_podcastTimer->start( m_podcastTimerInterval );
    }
    else
    {
        m_podcastItemsToScan.append( pc );
    }

    parent->sortChildItems( 0, true );
    parent->setOpen( true );
}

void PlaylistBrowser::changePodcastInterval()
{
    double time = static_cast<double>(m_podcastTimerInterval / ( 60 * 60 * 1000 ));
    bool ok;
    double interval = KInputDialog::getDouble( i18n("Download Interval"),
                                            i18n("Scan interval (hours):"), time,
                                            0.5, 100.0, .5, 1, // min, max, step, base
                                            &ok, this);
    int milliseconds = static_cast<int>(interval*60.0*60.0*1000.0);
    if( ok )
    {
        if( milliseconds != m_podcastTimerInterval )
        {
            m_podcastTimerInterval = milliseconds;
            m_podcastTimer->changeInterval( m_podcastTimerInterval );
        }
    }
}

bool PlaylistBrowser::deleteSelectedPodcastItems( const bool removeItem, const bool silent )
{
    KURL::List urls;
    QListViewItemIterator it( m_podcastCategory, QListViewItemIterator::Selected );
    QPtrList<PodcastEpisode> erasedItems;

    for( ; it.current(); ++it )
    {
        if( isPodcastEpisode( *it ) )
        {
            #define item static_cast<PodcastEpisode*>(*it)
            if( item->isOnDisk() ) {
                urls.append( item->localUrl() );
                erasedItems.append( item );
            }
            #undef  item
        }
    }

    if( urls.isEmpty() ) return false;
    int button;
    if( !silent )
        button = KMessageBox::warningContinueCancel( this,
                    i18n( "<p>You have selected 1 podcast episode to be <b>irreversibly</b> deleted. ",
                          "<p>You have selected %n podcast episodes to be <b>irreversibly</b> deleted. ",
                           urls.count() ), QString::null, KStdGuiItem::del() );
    if( silent || button != KMessageBox::Continue )
        return false;

    KIO::del( urls );

    PodcastEpisode *item;
    for ( item = erasedItems.first(); item; item = erasedItems.next() )
    {
        if( removeItem )
        {
            CollectionDB::instance()->removePodcastEpisode( item->dBId() );
            delete item;
        }
        else
            item->isOnDisk();
    }
    return true;
}

/// @param items is a list of pointers to _both_ channels and episodes. delete them from
/// the database AND the listview as required.
bool PlaylistBrowser::deletePodcasts( QPtrList<PlaylistBrowserEntry> items )
{
    if( items.isEmpty() ) return false;

    KURL::List urls;
    foreachType( QPtrList<PlaylistBrowserEntry>, items )
    {
        if( isPodcastEpisode( *it ) )
        {
        #define item static_cast<PodcastEpisode*>(*it)
            if( item->isOnDisk() )
                urls.append( item->localUrl() );
            // remove from the database
            CollectionDB::instance()->removePodcastEpisode( item->dBId() );
        #undef item
        }
        else if( isPodcastChannel( *it ) )
        {
            for( QListViewItem *ch = (*it)->firstChild(); ch; ch = ch->nextSibling() )
            {
                #define ch static_cast<PodcastEpisode*>(ch)
                if( ch->isOnDisk() )
                {
                    //delete downloaded media
                    urls.append( ch->localUrl() );
                }
                #undef  ch
                /// we don't need to delete from the database, because removing the channel from the database
                /// automatically removes the children as well.
            }
            CollectionDB::instance()->removePodcastChannel( static_cast<PodcastChannel*>(*it)->url() );
        }
    }
    // TODO We need to check which files have been deleted successfully
    if ( urls.count() )
        KIO::del( urls );
    return true;
}

void PlaylistBrowser::downloadSelectedPodcasts()
{
    QListViewItemIterator it( m_listview, QListViewItemIterator::Selected );

    for( ; it.current(); ++it )
    {
        if( isPodcastEpisode( *it ) )
        {
            #define item static_cast<PodcastEpisode*>(*it)
            if( !item->isOnDisk() )
                m_podcastDownloadQueue.append( item );
            #undef  item
        }
    }
    downloadPodcastQueue();
}

void PlaylistBrowser::downloadPodcastQueue() //SLOT
{
    if( m_podcastDownloadQueue.isEmpty() ) return;

    PodcastEpisode *first = m_podcastDownloadQueue.first();
    first->downloadMedia();
    m_podcastDownloadQueue.removeFirst();

    connect( first, SIGNAL( downloadFinished() ), this, SLOT( downloadPodcastQueue() ) );
    connect( first, SIGNAL( downloadAborted() ),  this, SLOT( abortPodcastQueue()  ) );
}

void PlaylistBrowser::abortPodcastQueue() //SLOT
{
    m_podcastDownloadQueue.clear();
}

void PlaylistBrowser::registerPodcastSettings( const QString &title, const PodcastSettings *settings )
{
    m_podcastSettings.insert( title, settings );
}

/**
 *************************************************************************
 *  PLAYLISTS
 *************************************************************************
 **/

QString PlaylistBrowser::playlistBrowserCache() const
{
    //returns the playlists stats cache file
    return amaroK::saveLocation() + "playlistbrowser_save.xml";
}

PlaylistCategory* PlaylistBrowser::loadPlaylists()
{
    QFile file( playlistBrowserCache() );

    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );

    QDomDocument d;
    QDomElement e;

    if( !file.open( IO_ReadOnly ) || !d.setContent( stream.read() ) )
    { /*Couldn't open the file or it had invalid content, so let's create an empty element*/
        return new PlaylistCategory(m_listview, 0 , i18n("Playlists") );
    }
    else {
        e = d.namedItem( "category" ).toElement();
        if ( e.attribute("formatversion") =="1.1" )
        {
            PlaylistCategory* p = new PlaylistCategory( m_listview, 0 , e );
            p->setText( 0, i18n("Playlists") );
            return p;
        }
        else { // Old unversioned format
            PlaylistCategory* p = new PlaylistCategory( m_listview, 0 , i18n("Playlists") );
            QListViewItem *last = 0;
            QDomNode n = d.namedItem( "playlistbrowser" ).namedItem("playlist");

            for ( ; !n.isNull();  n = n.nextSibling() )
                last = new PlaylistEntry( p, last, n.toElement() );

            return p;
        }
    }
}

QListViewItem *
PlaylistBrowser::findItemInTree( const QString &searchstring, int c ) const
{
    QStringList list = QStringList::split( "/", searchstring, true );

    // select the 1st level
    QStringList::Iterator it = list.begin();
    QListViewItem *pli = findItem (*it, c);
    if ( !pli ) return pli;

    for ( ++it ; it != list.end(); ++it )
    {

        QListViewItemIterator it2( pli );
        for( ++it2 ; it2.current(); ++it2 )
        {
            if ( *it == (*it2)->text(0) )
            {
                pli = *it2;
                break;
            }
            // test, to not go over into the next category
            if ( isCategory( *it2 ) && (pli->nextSibling() == *it2) )
                return 0;
        }
        if ( ! it2.current() )
            return 0;

    }
    return pli;
}

DynamicMode *PlaylistBrowser::findDynamicModeByTitle( const QString &title )
{
    if( !m_polished )
       polish();

    for ( QListViewItem *item = m_dynamicCategory->firstChild(); item; item = item->nextSibling() )
    {
        DynamicEntry *entry = dynamic_cast<DynamicEntry *>( item );
        if ( entry && entry->title() == title )
            return entry;
    }

    return 0;
}

PlaylistEntry *
PlaylistBrowser::findPlaylistEntry( const QString &url, QListViewItem *parent ) const
{
    if( !parent ) parent = static_cast<QListViewItem*>(m_playlistCategory);

    for( QListViewItem *it = parent->firstChild();
            it;
            it = it->nextSibling() )
    {
        if( isPlaylist( it ) )
        {
            PlaylistEntry *pl = static_cast<PlaylistEntry*>( it );
            debug() << pl->url().path() << " == " << url << endl;
            if( pl->url().path() == url )
            {
                debug() << "ok!" << endl;
                return pl;
            }
        }
        else if( isCategory( it ) )
        {
            PlaylistEntry *pl = findPlaylistEntry( url, it );
            if( pl )
                return pl;
        }
    }

    return 0;
}

int PlaylistBrowser::loadPlaylist( const QString &playlist, bool /*force*/ )
{
    // roland
    DEBUG_BLOCK

    QListViewItem *pli = findItemInTree( playlist, 0 );
    if ( ! pli ) return -1;

    slotDoubleClicked( pli );
    return 0;
    // roland
}

void PlaylistBrowser::addPlaylist( const QString &path, QListViewItem *parent, bool force, bool imported )
{
    // this function adds a playlist to the playlist browser

    if( !m_polished )
       polish();

    QFile file( path );
    if( !file.exists() ) return;

    PlaylistEntry *playlist = findPlaylistEntry( path );

    if( playlist && force )
        playlist->load(); //reload the playlist

    if( imported ) {
        if ( !m_playlistImports ) m_playlistImports = new PlaylistCategory( m_playlistCategory, 0, i18n("Imported") );
        parent = static_cast<QListViewItem*>( m_playlistImports );
    }
    else if( !parent ) parent = static_cast<QListViewItem*>(m_playlistCategory);

    if( !playlist ) {
        if( !m_playlistCategory || !m_playlistCategory->childCount() ) {  //first child
            removeButton->setEnabled( true );
            renameButton->setEnabled( true );
        }

        KURL auxKURL;
        auxKURL.setPath(path);
        m_lastPlaylist = playlist = new PlaylistEntry( parent, 0, auxKURL );
    }

    parent->setOpen( true );
    parent->sortChildItems( 0, true );
    m_listview->clearSelection();
    playlist->setSelected( true );
}

bool PlaylistBrowser::savePlaylist( const QString &path, const QValueList<KURL> &in_urls,
                                    const QValueList<QString> &titles, const QValueList<int> &lengths,
                                    bool relative )
{
    if( path.isEmpty() )
        return false;

    QFile file( path );

    if( !file.open( IO_WriteOnly ) )
    {
        KMessageBox::sorry( PlaylistWindow::self(), i18n( "Cannot write playlist (%1).").arg(path) );
        return false;
    }

    QTextStream stream( &file );
    stream << "#EXTM3U\n";

    KURL::List urls;
    for( int i = 0, n = in_urls.count(); i < n; ++i )
    {
        const KURL &url = in_urls[i];
        if( url.isLocalFile() && QFileInfo( url.path() ).isDir() )
            urls += recurse( url );
        else
            urls += url;
    }

    for( int i = 0, n = urls.count(); i < n; ++i )
    {
        const KURL &url = urls[i];

        if( !titles.isEmpty() && !lengths.isEmpty() )
        {
            stream << "#EXTINF:";
            stream << QString::number( lengths[i] );
            stream << ',';
            stream << titles[i];
            stream << '\n';
        }
        if (url.protocol() == "file" ) {
            if ( relative ) {
                const QFileInfo fi(file);
                stream << KURL::relativePath(fi.dirPath(), url.path());
            } else
                stream << url.path();
        } else {
            stream << url.url();
        }
        stream << "\n";
    }

    file.close(); // Flushes the file, before we read it
    PlaylistBrowser::instance()->addPlaylist( path, 0, true );

    return true;
}

void PlaylistBrowser::openPlaylist( QListViewItem *parent ) //SLOT
{
    // open a file selector to add playlists to the playlist browser
    QStringList files;
    files = KFileDialog::getOpenFileNames( QString::null, "*.m3u *.pls *.xspf|" + i18n("Playlist Files"), this, i18n("Import Playlists") );

    const QStringList::ConstIterator end  = files.constEnd();
    for( QStringList::ConstIterator it = files.constBegin(); it != end; ++it )
        addPlaylist( *it, parent );

    savePlaylists();
}

void PlaylistBrowser::savePlaylists()
{
    QFile file( playlistBrowserCache() );

    QDomDocument doc;
    QDomElement playlistsB = m_playlistCategory->xml();
    playlistsB.setAttribute( "product", "Amarok" );
    playlistsB.setAttribute( "version", APP_VERSION );
    playlistsB.setAttribute( "formatversion", "1.1" );
    QDomNode playlistsNode = doc.importNode( playlistsB, true );
    doc.appendChild( playlistsNode );

    QString temp( doc.toString() );

    // Only open the file after all data is ready. If it crashes, data is not lost!
    if ( !file.open( IO_WriteOnly ) ) return;

    QTextStream stream( &file );
    stream.setEncoding( QTextStream::UnicodeUTF8 );
    stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    stream << temp;
}

bool PlaylistBrowser::deletePlaylists( QPtrList<PlaylistEntry> items )
{
    KURL::List urls;
    foreachType( QPtrList<PlaylistEntry>, items )
    {
        urls.append( (*it)->url() );
    }
    if( !urls.isEmpty() )
        return deletePlaylists( urls );

    return false;
}

bool PlaylistBrowser::deletePlaylists( KURL::List items )
{
    if ( items.isEmpty() ) return false;

    // TODO We need to check which files have been deleted successfully
    // Avoid deleting dirs. See bug #122480
    for ( KURL::List::iterator it = items.begin(), end = items.end(); it != end; ++it ) {
        if ( QFileInfo( (*it).path() ).isDir() ) {
            it = items.remove( it );
            continue;
        }
    }
    KIO::del( items );
    return true;
}

void PlaylistBrowser::savePlaylist( PlaylistEntry *item )
{
    bool append = false;

    if( item->trackList().count() == 0 ) //the playlist hasn't been loaded so we append the dropped tracks
        append = true;

    //save the modified playlist in m3u or pls format
    const QString ext = fileExtension( item->url().path() );
    if( ext.lower() == "m3u" )
        saveM3U( item, append );
    else if ( ext.lower() == "xspf" )
        saveXSPF( item, append );
    else
        savePLS( item, append );
}

/**
 *************************************************************************
 *  General Methods
 *************************************************************************
 **/

PlaylistBrowserEntry *
PlaylistBrowser::findItem( QString &t, int c ) const
{
    return static_cast<PlaylistBrowserEntry *>( m_listview->findItem( t, c, Qt::ExactMatch ) );
}

bool PlaylistBrowser::createPlaylist( QListViewItem *parent, bool current, QString title )
{
    if( title.isEmpty() ) title = i18n("Untitled");

    const QString path = PlaylistDialog::getSaveFileName( title );
    if( path.isEmpty() )
        return false;

    if( !parent )
        parent = static_cast<QListViewItem *>( m_playlistCategory );

    if( current )
    {
        if ( !Playlist::instance()->saveM3U( path ) ) {
            return false;
        }
    }
    else
    {
        //Remove any items in Listview that have the same path as this one
        //  Should only happen when overwriting a playlist
        QListViewItem *item = parent->firstChild();
        while( item )
        {
            if( static_cast<PlaylistEntry*>( item )->url() == path )
            {
                QListViewItem *todelete = item;
                item = item->nextSibling();
                delete todelete;
            }
            else
                item = item->nextSibling();
        }

        //Remove existing playlist if it exists
        if ( QFileInfo( path ).exists() )
            QFileInfo( path ).dir().remove( path );

        m_lastPlaylist = new PlaylistEntry( parent, 0, path );
        parent->sortChildItems( 0, true );
    }

    savePlaylists();

    return true;
}

void PlaylistBrowser::slotDoubleClicked( QListViewItem *item ) //SLOT
{
    if( !item ) return;

    if( isPlaylist( item ) ) {
        // open the playlist
        #define item static_cast<PlaylistEntry *>(item)
        //don't replace, it generally makes people think Amarok behaves like JuK
        //and we don't so they then get really confused about things
        Playlist::instance()->insertMedia( item->url(), Playlist::Replace );
        #undef  item
    }
    else if( isPodcastChannel( item ) )
    {
        #define item static_cast<PodcastChannel *>(item)
        KURL::List list;
        QListViewItem *child = item->firstChild();
        while( child )
        {
            #define child static_cast<PodcastEpisode *>(child)

            child->isOnDisk() ?
                list.append( child->localUrl() ):
                list.append( child->url()      );

            #undef child
            child = child->nextSibling();
        }

        Playlist::instance()->insertMedia( list, Playlist::Replace );
        item->setNew( false );

        #undef item
    }
    else if( isPodcastEpisode( item ) )
    {
        #define item static_cast<PodcastEpisode *>(item)
        KURL::List list;

        item->isOnDisk() ?
            list.append( item->localUrl() ):
            list.append( item->url()      );

        Playlist::instance()->insertMedia( list, Playlist::DirectPlay );
        item->setNew( false );
        item->setListened();

        #undef item
    }
    else if( isStream( item ) )
    {
        Playlist::instance()->insertMedia( static_cast<StreamEntry *>(item)->url(), Playlist::Replace );
    }
    else if( isSmartPlaylist( item ) )
    {
        #define item static_cast<SmartPlaylist *>(item)
        if( !item->query().isEmpty() )
            Playlist::instance()->insertMediaSql( item->query(), Playlist::Clear );
        #undef  item
    }
    else if( isCategory( item ) )
    {
        item->setOpen( !item->isOpen() );
    }
    else if( isPlaylistTrackItem( item ) )
    {
        KURL::List list( static_cast<PlaylistTrackItem *>(item)->url() );
        Playlist::instance()->insertMedia( list, Playlist::DirectPlay );
    }
    else if( isDynamic( item ) )
        Playlist::instance()->loadDynamicMode( static_cast<DynamicEntry *>(item) );
    else
        warning() << "No functionality for item double click implemented" << endl;
}

void PlaylistBrowser::collectionScanDone()
{
    if( !m_polished || CollectionDB::instance()->isEmpty() )
    {
        return;
    }
    else if( !m_smartCategory )
    {
        m_smartCategory = loadSmartPlaylists();
        loadDefaultSmartPlaylists();
        m_smartCategory->setOpen( true );
    }
}

void PlaylistBrowser::addToDynamic()
{
    QListViewItemIterator it( m_listview, QListViewItemIterator::Selected );

    for( ; it.current(); ++it )
    {
        if( m_dynamicEntries.find( *it ) < 0 ) // check that it is not there
        {
            m_dynamicEntries.append( *it );
            if( isPlaylist( *it ) )
            {
                PlaylistEntry *item = static_cast<PlaylistEntry*>(*it);
                item->setDynamic( true );
            }
            else if( isSmartPlaylist( *it ) )
            {
                SmartPlaylist *item = static_cast<SmartPlaylist*>(*it);
                item->setDynamic( true );
            }
        }
    }

    DynamicMode *m = Playlist::instance()->modifyDynamicMode();
    m->setDynamicItems(m_dynamicEntries);
    Playlist::instance()->finishedModifying( m );
}

void PlaylistBrowser::subFromDynamic()
{
    QListViewItemIterator it( m_listview, QListViewItemIterator::Selected );

    for( ; it.current(); ++it )
    {
        if( m_dynamicEntries.find( *it ) >= 0 ) // check if it is already present
        {
            m_dynamicEntries.remove( *it );
            if( isPlaylist( *it ) )
            {
                PlaylistEntry *item = static_cast<PlaylistEntry*>(*it);
                item->setDynamic( false );
            }
            else if( isSmartPlaylist( *it ) )
            {
                SmartPlaylist *item = static_cast<SmartPlaylist*>(*it);
                item->setDynamic( false );
            }
        }
    }

    DynamicMode *m = Playlist::instance()->modifyDynamicMode();
    m->setDynamicItems( m_dynamicEntries );
    Playlist::instance()->finishedModifying( m );
}

void PlaylistBrowser::removeSelectedItems() //SLOT
{
    // this function remove selected playlists and tracks

    int playlistCount = 0;
    int trackCount    = 0;
    int streamCount   = 0;
    int smartyCount   = 0;
    int dynamicCount  = 0;
    int podcastCount  = 0;
    int folderCount   = 0;

    QPtrList<PlaylistEntry>        playlistsToDelete;
    QPtrList<PlaylistBrowserEntry> podcastsToDelete; // use base class, since we insert channels AND episodes

    QPtrList<PlaylistCategory>     playlistFoldersToDelete;
    QPtrList<PlaylistCategory>     podcastFoldersToDelete;

    //remove currentItem, no matter if selected or not
    m_listview->setSelected( m_listview->currentItem(), true );

    QPtrList<QListViewItem> selected;
    QListViewItemIterator it( m_listview, QListViewItemIterator::Selected );
    for( ; it.current(); ++it )
    {
        if( (*it) == m_coolStreams   || (*it) == m_smartDefaults ||
            (*it) == m_randomDynamic || (*it) == m_suggestedDynamic )
            continue;

        if( isCategory( *it ) && !static_cast<PlaylistCategory*>(*it)->isFolder() ) //its a base category
            continue;

        // if the playlist containing this item is already selected the current item will be skipped
        // it will be deleted from the parent
        QListViewItem *parent = it.current()->parent();

        if( parent && parent->isSelected() ) //parent will remove children
            continue;

        while( parent->parent() && parent != m_coolStreams && parent != m_smartDefaults )
            parent = parent->parent();

        if( parent == m_coolStreams || parent == m_smartDefaults )
            continue;

        switch( (*it)->rtti() )
        {
            case PlaylistEntry::RTTI:
                playlistsToDelete.append( static_cast<PlaylistEntry*>(*it) );
                playlistCount++;
                continue; // don't add the folder to selected, else it will be deleted twice

            case PlaylistTrackItem::RTTI:
                trackCount++;
                break;

            case StreamEntry::RTTI:
                streamCount++;
                break;

            case DynamicEntry::RTTI:
                dynamicCount++;
                break;

            case SmartPlaylist::RTTI:
                smartyCount++;
                break;

            case PodcastChannel::RTTI:
            case PodcastEpisode::RTTI:
                podcastsToDelete.append( static_cast<PlaylistBrowserEntry*>(*it) );
                podcastCount++;
                continue; // don't add the folder to selected, else it will be deleted twice

            case PlaylistCategory::RTTI:
                folderCount++;
                if( parent == m_playlistCategory )
                {
                    for( QListViewItem *ch = (*it)->firstChild(); ch; ch = ch->nextSibling() )
                    {
                        if( isCategory( ch ) )
                        {
                            folderCount++;
                            playlistFoldersToDelete.append( static_cast<PlaylistCategory*>(ch) );
                        }
                        else
                        {
                            playlistCount++;
                            playlistsToDelete.append( static_cast<PlaylistEntry*>(ch) );
                        }
                    }
                    playlistFoldersToDelete.append( static_cast<PlaylistCategory*>(*it) );
                    continue; // don't add the folder to selected, else it will be deleted twice
                }
                else if( parent == m_podcastCategory )
                {
                    for( QListViewItem *ch = (*it)->firstChild(); ch; ch = ch->nextSibling() )
                    {
                        if( isCategory( ch ) )
                        {
                            folderCount++;
                            podcastFoldersToDelete.append( static_cast<PlaylistCategory*>(ch) );
                        }
                        else
                        {
                            podcastCount++;
                            podcastsToDelete.append( static_cast<PlaylistBrowserEntry*>(ch) );
                        }
                    }
                    podcastFoldersToDelete.append( static_cast<PlaylistCategory*>(*it) );
                    continue; // don't add the folder to selected, else it will be deleted twice
                }

            default:
                break;
        }

        selected.append( it.current() );
    }

    int totalCount = playlistCount + smartyCount + dynamicCount + streamCount + podcastCount + folderCount;

    if( selected.isEmpty() && !totalCount ) return;

    QString message = i18n( "<p>You have selected:<ul>" );

    if( playlistCount ) message += "<li>" + i18n( "1 playlist", "%n playlists", playlistCount )
                                            .arg( playlistCount ) + "</li>";

    if( smartyCount   ) message += "<li>" + i18n( "1 smart playlist", "%n smart playlists", smartyCount )
                                            .arg( smartyCount ) + "</li>";

    if( dynamicCount  ) message += "<li>" + i18n( "1 dynamic playlist", "%n dynamic playlists", dynamicCount )
                                            .arg( dynamicCount ) + "</li>";

    if( streamCount   ) message += "<li>" + i18n( "1 stream", "%n streams", streamCount )
                                            .arg( streamCount ) + "</li>";

    if( podcastCount  ) message += "<li>" + i18n( "1 podcast", "%n podcasts", podcastCount )
                                            .arg( podcastCount ) + "</li>";

    if( folderCount   ) message += "<li>" + i18n( "1 folder", "%n folders", folderCount )
                                            .arg( folderCount ) + "</li>";

    message += "</ul><br>to be <b>irreversibly</b> deleted.</p>";

    if( totalCount > 0 )
    {
        int button = KMessageBox::warningContinueCancel( this, message, QString::null, KStdGuiItem::del() );
        if( button != KMessageBox::Continue )
            return;
    }

    foreachType( QPtrList<QListViewItem>, selected )
    {
        if ( isPlaylistTrackItem( *it ) )
        {
            static_cast<PlaylistEntry*>( (*it)->parent() )->removeTrack( (*it) );
            continue;
        }
        delete (*it);
    }

    if( streamCount )        saveStreams();
    if( smartyCount ) saveSmartPlaylists();
    if( dynamicCount )      saveDynamics();

    // used for deleting playlists first, then folders.
    if( playlistCount )
    {
        if( deletePlaylists( playlistsToDelete ) )
        {
            foreachType( QPtrList<PlaylistEntry>, playlistsToDelete )
            {
                m_dynamicEntries.remove(*it);
                delete (*it);
            }
        }
    }

    if( podcastCount )
    {
        if( deletePodcasts( podcastsToDelete ) )
            foreachType( QPtrList<PlaylistBrowserEntry>, podcastsToDelete )
                delete (*it);
    }

    foreachType( QPtrList<PlaylistCategory>, playlistFoldersToDelete )
        delete (*it);

    foreachType( QPtrList<PlaylistCategory>, podcastFoldersToDelete )
        removePodcastFolder( *it );

    if( playlistCount || trackCount )
        savePlaylists();
}

// remove podcast folders. we need to do this recursively to ensure all children are removed from the db
void PlaylistBrowser::removePodcastFolder( PlaylistCategory *item )
{
    if( !item ) return;
    if( !item->childCount() )
    {
        CollectionDB::instance()->removePodcastFolder( item->id() );
        delete item;
        return;
    }

    QListViewItem *child = item->firstChild();
    while( child )
    {
        QListViewItem *nextChild = 0;
        if( isPodcastChannel( child ) )
        {
        #define child static_cast<PodcastChannel*>(child)
            nextChild = child->nextSibling();
            CollectionDB::instance()->removePodcastChannel( child->url() );
            m_podcastItemsToScan.remove( child );
        #undef  child
        }
        else if( isCategory( child ) )
        {
            nextChild = child->nextSibling();
            removePodcastFolder( static_cast<PlaylistCategory*>(child) );
        }

        child = nextChild;
    }
    CollectionDB::instance()->removePodcastFolder( item->id() );
    delete item;
}

void PlaylistBrowser::renameSelectedItem() //SLOT
{
    QListViewItem *item = m_listview->currentItem();
    if( !item ) return;

    if( item == m_randomDynamic || item == m_suggestedDynamic )
        return;

    if( isCategory( item ) && static_cast<PlaylistCategory*>(item)->isFolder() )
    {
        if( item == m_coolStreams || item == m_smartDefaults )
            return;

        item->setRenameEnabled( 0, true );
        m_listview->rename( item, 0 );
    }

    else if( isPlaylist( item ) || isStream( item ) || isSmartPlaylist( item ) || isDynamic( item ) )
    {
        QListViewItem *parent = item->parent();

        while( parent )
        {
            if( parent == m_coolStreams || parent == m_smartDefaults )
                return;

            if( !parent->parent() )
                break;

            parent = parent->parent();
        }

        item->setRenameEnabled( 0, true );
        m_listview->rename( item, 0 );
    }
}


void PlaylistBrowser::renamePlaylist( QListViewItem* item, const QString& newName, int ) //SLOT
{
    if( isPlaylist( item ) )
    {
        #define item static_cast<PlaylistEntry*>(item)

        QString oldPath = item->url().path();
        QString newPath = fileDirPath( oldPath ) + newName + "." + fileExtension( oldPath );

        if ( std::rename( QFile::encodeName( oldPath ), QFile::encodeName( newPath ) ) == -1 )
            KMessageBox::error( this, i18n("Error renaming the file.") );
        else
            item->setUrl( newPath );

        #undef item
    }
    else if( isSmartPlaylist( item ) )
    {
        QDomElement xml = static_cast<SmartPlaylist*>(item)->xml();
        xml.setAttribute( "name", newName );
    }

    item->setRenameEnabled( 0, false );
}


void PlaylistBrowser::saveM3U( PlaylistEntry *item, bool append )
{
    QFile file( item->url().path() );

    if( append ? file.open( IO_WriteOnly | IO_Append ) : file.open( IO_WriteOnly ) )
    {
        QTextStream stream( &file );
        if( !append )
            stream << "#EXTM3U\n";
        QPtrList<TrackItemInfo> trackList = append ? item->droppedTracks() : item->trackList();
        for( TrackItemInfo *info = trackList.first(); info; info = trackList.next() )
        {
            stream << "#EXTINF:";
            stream << info->length();
            stream << ',';
            stream << info->title();
            stream << '\n';
            stream << (info->url().protocol() == "file" ? info->url().path() : info->url().url());
            stream << "\n";
        }

        file.close();
    }
}

void PlaylistBrowser::saveXSPF( PlaylistEntry *item, bool append )
{
    XSPFPlaylist* playlist = new XSPFPlaylist();

    playlist->setCreator( "Amarok" );
    playlist->setTitle( item->text(0) );

    XSPFtrackList list;

    QPtrList<TrackItemInfo> trackList = append ? item->droppedTracks() : item->trackList();
    for( TrackItemInfo *info = trackList.first(); info; info = trackList.next() )
    {
        XSPFtrack track;
        MetaBundle b( info->url() );
        track.creator  = b.artist();
        track.title    = b.title();
        track.location = b.url().url();
        list.append( track );
    }

    playlist->setTrackList( list, append );

    QFile file( item->url().path() );
    file.open( IO_WriteOnly );

    QTextStream stream ( &file );

    playlist->save( stream, 2 );

    file.close();
}


void PlaylistBrowser::savePLS( PlaylistEntry *item, bool append )
{
    QFile file( item->url().path() );

    if( append ? file.open( IO_WriteOnly | IO_Append ) : file.open( IO_WriteOnly ) )
    {
        QTextStream stream( &file );
        QPtrList<TrackItemInfo> trackList = append ? item->droppedTracks() : item->trackList();
        stream << "NumberOfEntries=" << trackList.count() << endl;
        int c=1;
        for( TrackItemInfo *info = trackList.first(); info; info = trackList.next(), ++c )
        {
            stream << "File" << c << "=";
            stream << (info->url().protocol() == "file" ? info->url().path() : info->url().url());
            stream << "\nTitle" << c << "=";
            stream << info->title();
            stream << "\nLength" << c << "=";
            stream << info->length();
            stream << "\n";
        }

        stream << "Version=2\n";
        file.close();
    }
}

#include <kdirlister.h>
#include <qeventloop.h>
#include "playlistloader.h"
//this function (C) Copyright 2003-4 Max Howell, (C) Copyright 2004 Mark Kretschmann
KURL::List PlaylistBrowser::recurse( const KURL &url )
{
    typedef QMap<QString, KURL> FileMap;

    KDirLister lister( false );
    lister.setAutoUpdate( false );
    lister.setAutoErrorHandlingEnabled( false, 0 );
    lister.openURL( url );

    while( !lister.isFinished() )
        kapp->eventLoop()->processEvents( QEventLoop::ExcludeUserInput );

    KFileItemList items = lister.items(); //returns QPtrList, so we MUST only do it once!
    KURL::List urls;
    FileMap files;
    for( KFileItem *item = items.first(); item; item = items.next() ) {
        if( item->isFile() ) { files[item->name()] = item->url(); continue; }
        if( item->isDir() ) urls += recurse( item->url() );
    }

    foreachType( FileMap, files )
        // users often have playlist files that reflect directories
        // higher up, or stuff in this directory. Don't add them as
        // it produces double entries
        if( !PlaylistFile::isPlaylistFile( (*it).fileName() ) )
            urls += *it;

    return urls;
}


void PlaylistBrowser::currentItemChanged( QListViewItem *item )    //SLOT
{
    // rename remove and delete buttons are disabled if there are no playlists
    // rename and delete buttons are disabled for track items

    bool enable_remove = false;
    bool enable_rename = false;

    if( !item )
        goto enable_buttons;

    else if( isPlaylist( item ) )
    {
        enable_remove = true;
        enable_rename = true;
    }
    else if( isStream( item ) )
    {
        enable_remove = ( item->parent() != m_coolStreams );
        enable_rename = ( item->parent() != m_coolStreams );
    }
    else if( isSmartPlaylist( item ) )
    {
        QListViewItem *parent = item->parent();

        while( parent != m_smartCategory && parent != m_smartDefaults )
            parent = parent->parent();

        enable_remove = ( parent != m_smartDefaults );
        enable_rename = ( parent != m_smartDefaults );
    }
    else if( isDynamic( item ) )
    {
        enable_remove = ( item != m_randomDynamic && item != m_suggestedDynamic );
        enable_rename = ( item != m_randomDynamic && item != m_suggestedDynamic );
    }
    else if( isCategory( item ) )
    {
        if( static_cast<PlaylistCategory*>(item)->isFolder() )
        {
            if( item != m_coolStreams && item != m_smartDefaults ) {
                enable_remove = true;
                enable_rename = true;
            }
        }
    }
    else
        enable_remove = true;

    enable_buttons:

    removeButton->setEnabled( enable_remove );
    renameButton->setEnabled( enable_rename );

    static_cast<PlaylistBrowserEntry*>(item)->updateInfo();
}


void PlaylistBrowser::customEvent( QCustomEvent *e )
{
    // If a playlist is found in collection folders it will be automatically added to the playlist browser
    // The ScanController sends a PlaylistFoundEvent when a playlist is found.

    ScanController::PlaylistFoundEvent* p = static_cast<ScanController::PlaylistFoundEvent*>( e );
    addPlaylist( p->path(), 0, false, true );
}


void PlaylistBrowser::slotAddMenu( int id ) //SLOT
{
    switch( id )
    {
        case PLAYLIST:
            openPlaylist();
            break;

        case STREAM:
            addStream();
            break;

        case SMARTPLAYLIST:
            addSmartPlaylist();
            break;

        case PODCAST:
            addPodcast();
            break;
        case ADDDYNAMIC:
            ConfigDynamic::dynamicDialog(this);
            break;
        default:
            break;
    }
}


void PlaylistBrowser::slotSave() // SLOT
{
    createPlaylist();
}

/**
 ************************
 *  Context Menu Entries
 ************************
 **/

void PlaylistBrowser::showContextMenu( QListViewItem *item, const QPoint &p, int )  //SLOT
{
    if( !item ) return;

    KPopupMenu menu( this );

    if( isPlaylist( item ) ) {
        #define item static_cast<PlaylistEntry*>(item)
        enum Id { LOAD, ADD, DYNADD, DYNSUB, RENAME, DELETE, MEDIA_DEVICE };

        menu.insertItem( SmallIconSet( amaroK::icon( "files" ) ), i18n( "&Load" ), LOAD );
        menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "&Append to Playlist" ), ADD );

        if( amaroK::dynamicMode() && amaroK::dynamicMode()->appendType()== DynamicMode::CUSTOM )
        {
            if( static_cast<PlaylistEntry*>(item)->isDynamic() )
                menu.insertItem( SmallIconSet( amaroK::icon( "remove_from_playlist" ) ), i18n( "Remove From %1" ).arg(amaroK::dynamicMode()->title()), DYNSUB );
            else
                menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "Add to the %1 Entries" ).arg(amaroK::dynamicMode()->title()), DYNADD );
        }

        if( MediaBrowser::isAvailable() )
        {
            menu.insertSeparator();
            menu.insertItem( SmallIconSet( amaroK::icon( "device" ) ),
                    i18n( "&Transfer to Media Device" ), MEDIA_DEVICE );
        }

        menu.insertSeparator();
        menu.insertItem( SmallIconSet( amaroK::icon("edit") ), i18n( "&Rename" ), RENAME );
        menu.insertItem( SmallIconSet( amaroK::icon("remove_from_playlist") ), i18n( "&Delete" ), DELETE );
        menu.setAccel( Key_Space, LOAD );
        menu.setAccel( Key_F2, RENAME );
        menu.setAccel( SHIFT+Key_Delete, DELETE );

        switch( menu.exec( p ) )
        {
            case LOAD:
                slotDoubleClicked( item );
                break;
            case ADD:
                Playlist::instance()->insertMedia( item->url() );
                break;
            case DYNADD:
                addToDynamic();
                break;
            case DYNSUB:
                subFromDynamic();
                break;
            case RENAME:
                renameSelectedItem();
                break;
            case DELETE:
                removeSelectedItems();
                break;
            case MEDIA_DEVICE:
                MediaBrowser::queue()->addURLs( item->tracksURL(), item->text(0) );
                break;
        }
        #undef item
    }
    else if( isSmartPlaylist( item ) )
    {
        enum Actions { LOAD, ADD, DYNADD, DYNSUB, EDIT, REMOVE, MEDIA_DEVICE, MEDIA_DEVICE_PLAYLIST };

        menu.insertItem( SmallIconSet( amaroK::icon( "files" ) ), i18n( "&Load" ), LOAD );
        menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "&Append to Playlist" ), ADD );
        if( MediaBrowser::isAvailable() )
        {
            menu.insertSeparator();
            menu.insertItem( SmallIconSet( amaroK::icon( "device" ) ),
                    i18n( "&Transfer to Media Device" ), MEDIA_DEVICE_PLAYLIST );
            menu.insertItem( SmallIconSet( amaroK::icon( "device" ) ),
                    i18n( "&Transfer Contents to Media Device" ), MEDIA_DEVICE );
        }

        if( amaroK::dynamicMode() && amaroK::dynamicMode()->appendType()== DynamicMode::CUSTOM )
        {
            if( static_cast<SmartPlaylist*>(item)->isDynamic() )
                menu.insertItem( SmallIconSet( amaroK::icon( "remove_from_playlist" ) ), i18n( "Remove From %1" ).arg(amaroK::dynamicMode()->title()), DYNSUB );
            else
                menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "Add to the %1 Entries" ).arg(amaroK::dynamicMode()->title()), DYNADD );
        }

        // Forbid removal of Collection
        if( item->parent()->text(0) != i18n("Collection") )
        {
            menu.insertSeparator();
            if ( static_cast<SmartPlaylist *>(item)->isEditable() )
                menu.insertItem( SmallIconSet( amaroK::icon("edit") ), i18n( "E&dit..." ), EDIT );
            menu.insertItem( SmallIconSet( amaroK::icon("remove_from_playlist") ), i18n( "&Delete" ), REMOVE );
        }

        QString playlist;
        switch( menu.exec( p ) )
        {
            case LOAD:
                slotDoubleClicked( item );
                break;
            case ADD:
                Playlist::instance()->insertMediaSql( static_cast<SmartPlaylist *>(item)->query(), Playlist::Append );
                break;
            case DYNADD:
                addToDynamic();
                break;
            case DYNSUB:
                subFromDynamic();
                break;
            case EDIT:
                editSmartPlaylist( static_cast<SmartPlaylist *>(item) );
                break;
            case REMOVE:
                removeSelectedItems();
                break;
            case MEDIA_DEVICE_PLAYLIST:
                playlist = item->text(0);
                /* fall through */
            case MEDIA_DEVICE:
                {
                    KURL::List urls;
                    const QStringList values = CollectionDB::instance()->query( static_cast<SmartPlaylist *>(item)->query() );
                    int i=0;
                    for( for_iterators( QStringList, values ); it != end; ++it ) {
                        if(i%QueryBuilder::dragFieldCount == QueryBuilder::dragFieldCount-2)
                        {
                            urls << KURL::fromPathOrURL( *it );
                        }
                        i++;
                    }
                    MediaBrowser::queue()->addURLs( urls, playlist );
                }
                break;
        }
    }
    else if( isStream( item ) )
    {
        enum Actions { LOAD, ADD, EDIT, REMOVE, INFO };

        menu.insertItem( SmallIconSet( amaroK::icon( "files" ) ), i18n( "&Load" ), LOAD );
        menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "&Append to Playlist" ), ADD );
        menu.insertSeparator();
        // Forbid removal of Cool-Streams
        if( item->parent() != m_coolStreams )
        {
            menu.insertItem( SmallIconSet( amaroK::icon("edit") ), i18n( "E&dit" ), EDIT );
            menu.insertItem( SmallIconSet( amaroK::icon("remove_from_playlist") ), i18n( "&Delete" ), REMOVE );
        }
        else
            menu.insertItem( SmallIconSet( amaroK::icon( "info" ) ), i18n( "Show &Information" ), INFO );

        #define item static_cast<StreamEntry *>(item)
        switch( menu.exec( p ) )
        {
            case LOAD:
                slotDoubleClicked( item );
                break;
            case ADD:
                Playlist::instance()->insertMedia( item->url() );
                break;
            case EDIT:
                editStreamURL( item );
                break;
            case INFO:
                editStreamURL( item, true );
                break;
            case REMOVE:
                removeSelectedItems();
                break;
        }
        #undef  item
    }
    else if( isDynamic( item ) ) {
        #define item static_cast<DynamicEntry*>(item)
        enum Actions { LOAD, RENAME, REMOVE, EDIT };
        menu.insertItem( SmallIconSet( amaroK::icon( "files" ) ), i18n( "&Load" ), LOAD );
        menu.insertSeparator();
        menu.insertItem( SmallIconSet( amaroK::icon("edit") ), i18n( "E&dit" ), EDIT );
        menu.insertItem( SmallIconSet( amaroK::icon("remove_from_playlist") ), i18n( "&Delete" ), REMOVE );

        if( item == m_randomDynamic || item == m_suggestedDynamic )
            menu.setItemEnabled( REMOVE, false );

        switch( menu.exec( p ) )
        {
            case LOAD:
                slotDoubleClicked( item );
                break;
            case EDIT:
                item->edit();
                break;
            case REMOVE:
                removeSelectedItems();
                break;
        }
        #undef item
    }
    else if( isPodcastChannel( item ) ) {
        #define item static_cast<PodcastChannel*>(item)
        enum Actions { LOAD, ADD, DELETE, RESCAN, CONFIG};
        menu.insertItem( SmallIconSet( amaroK::icon( "files" ) ), i18n( "&Load" ), LOAD );
        menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "&Append to Playlist" ), ADD );
        menu.insertItem( SmallIconSet( amaroK::icon( "remove_from_playlist" ) ), i18n( "&Delete" ), DELETE );
        menu.insertSeparator();
        menu.insertItem( SmallIconSet( amaroK::icon( "refresh" ) ), i18n( "&Check for Updates" ), RESCAN );
        menu.insertItem( SmallIconSet( amaroK::icon( "configure" ) ), i18n( "&Configure..." ), CONFIG );


        switch( menu.exec( p ) )
        {
            case LOAD:
                slotDoubleClicked( item );
                break;

            case ADD:
            {
                KURL::List list;
                QListViewItem *child = item->firstChild();
                while( child )
                {
                    list.append( static_cast<PodcastEpisode*>( child )->url() );
                    child = child->nextSibling();
                }
                Playlist::instance()->insertMedia( list );
                break;
            }

            case RESCAN:
                item->rescan();
                break;

            case DELETE:
                removeSelectedItems();
                break;

            case CONFIG:
            {
                configureSelectedPodcasts();
                break;
            }
        }
        #undef item
    }
    else if( isPodcastEpisode( item ) ) {
        #define item static_cast<PodcastEpisode*>(item)
        enum Actions { LOAD, QUEUE, GET, DELETE, MEDIA_DEVICE };
        menu.insertItem( SmallIconSet( amaroK::icon( "play" ) ), i18n( "&Play" ), LOAD );
        menu.insertItem( SmallIconSet( amaroK::icon( "fastforward" ) ), i18n( "&Queue" ), QUEUE );

        if( MediaBrowser::isAvailable() )
        {
            menu.insertSeparator();
            menu.insertItem( SmallIconSet( amaroK::icon( "device" ) ),
                             i18n( "&Transfer to Media Device" ), MEDIA_DEVICE );
            menu.setItemEnabled( MEDIA_DEVICE, item->isOnDisk() );
        }

        menu.insertSeparator();
        menu.insertItem( SmallIconSet( amaroK::icon( "download" ) ), i18n( "&Download Media" ), GET );
        menu.insertItem( SmallIconSet( amaroK::icon("remove_from_playlist") ),
                         i18n( "De&lete Downloaded Podcast" ), DELETE );

        menu.setItemEnabled( GET, !item->isOnDisk() );
        menu.setItemEnabled( DELETE, item->isOnDisk() );

        switch( menu.exec( p ) )
        {
            case LOAD:
                slotDoubleClicked( item );
                break;

            case QUEUE:
                if( item->isOnDisk() )
                    Playlist::instance()->insertMedia( item->localUrl(), Playlist::Queue );
                else
                    Playlist::instance()->insertMedia( item->url(), Playlist::Queue );
                break;

            case GET:
                downloadSelectedPodcasts();
                break;

            case DELETE:
                deleteSelectedPodcastItems();
                break;

            case MEDIA_DEVICE:
                // tags on podcasts are sometimes bad, thus use other meta information if available
                if( item->isSelected() )
                {
                    for(QListViewItemIterator it(m_listview, QListViewItemIterator::Selected);
                            *it;
                            ++it)
                    {
                        if(isPodcastEpisode( *it ) )
                        {
                            PodcastEpisode *podcast = static_cast<PodcastEpisode*>(*it);
                            if(podcast->isOnDisk())
                            {
                                podcast->addToMediaDevice();
                            }
                        }
                    }
                }
                else
                {
                    static_cast<PodcastEpisode*>(item)->addToMediaDevice();
                }
                MediaBrowser::queue()->URLsAdded();
                break;
        }
        #undef item
    }
    else if( isCategory( item ) ) {
        #define item static_cast<PlaylistCategory*>(item)
        enum Actions { RENAME, REMOVE, CREATE, PLAYLIST, SMART, STREAM, DYNAMIC, PODCAST, REFRESH, CONFIG, INTERVAL };

        QListViewItem *parentCat = item;

        while( parentCat->parent() )
            parentCat = parentCat->parent();
        bool isPodcastFolder = false;
        if( item == m_coolStreams || item == m_smartDefaults ) return;

        if( item->isFolder() ) {
            menu.insertItem( SmallIconSet( amaroK::icon("edit") ), i18n( "&Rename" ), RENAME );
            menu.insertItem( SmallIconSet( amaroK::icon("remove_from_playlist") ), i18n( "&Delete" ), REMOVE );
            menu.insertSeparator();
        }

        if( parentCat == static_cast<QListViewItem*>(m_playlistCategory) )
            menu.insertItem( SmallIconSet(amaroK::icon( "add_playlist" )), i18n("Import Playlist..."), PLAYLIST );

        else if( parentCat == static_cast<QListViewItem*>(m_smartCategory) )
            menu.insertItem( SmallIconSet(amaroK::icon( "add_playlist" )), i18n("New Smart Playlist..."), SMART );

        else if( parentCat == static_cast<QListViewItem*>(m_dynamicCategory) )
            menu.insertItem( SmallIconSet(amaroK::icon( "add_playlist" )), i18n("New Dynamic Playlist..."), DYNAMIC );

        else if( parentCat == static_cast<QListViewItem*>(m_streamsCategory) )
            menu.insertItem( SmallIconSet(amaroK::icon( "add_playlist" )), i18n("Add Radio Stream..."), STREAM );

        else if( parentCat == static_cast<QListViewItem*>(m_podcastCategory) )
        {
            isPodcastFolder = true;
            menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n("Add Podcast..."), PODCAST );
            menu.insertItem( SmallIconSet( amaroK::icon( "refresh" ) ), i18n("Refresh All Podcasts"), REFRESH );
            menu.insertSeparator();
            menu.insertItem( SmallIconSet( amaroK::icon( "configure" ) ), i18n( "&Configure Children..." ), CONFIG );
            if( parentCat == item )
                menu.insertItem( SmallIconSet( amaroK::icon( "configure" ) ), i18n("Scan Interval..."), INTERVAL );
        }

        menu.insertSeparator();
        menu.insertItem( SmallIconSet( amaroK::icon( "files" ) ), i18n("Create Sub-Folder"), CREATE );

        QListViewItem *tracker = 0;
        PlaylistCategory *newFolder = 0;
        int c;
        QString name;

        switch( menu.exec( p ) ) {
            case RENAME:
                renameSelectedItem();
                break;

            case REMOVE:
                removeSelectedItems();
                break;

            case PLAYLIST:
                openPlaylist( item );
                break;

            case SMART:
                addSmartPlaylist( item );
                break;

            case STREAM:
                addStream( item );
                break;

            case DYNAMIC:
                ConfigDynamic::dynamicDialog(this);
                break;

            case PODCAST:
                addPodcast( item );
                break;

            case REFRESH:
                refreshPodcasts(item);
                break;

             case CONFIG:
                 configurePodcasts( item );
                 break;

            case CREATE:
                tracker = item->firstChild();

                for( c = 0 ; isCategory( tracker ); tracker = tracker->nextSibling() )
                {
                    if( tracker->text(0).startsWith( i18n("Folder") ) )
                        c++;
                    if( !isCategory( tracker->nextSibling() ) )
                        break;
                }
                name = i18n("Folder");
                if( c ) name = i18n("Folder %1").arg(c);
                if( tracker == item->firstChild() && !isCategory( tracker ) ) tracker = 0;

                newFolder = new PlaylistCategory( item, tracker, name, true );
                newFolder->startRename( 0 );
                if( isPodcastFolder )
                {
                    c = CollectionDB::instance()->addPodcastFolder( newFolder->text(0), item->id(), false );
                    newFolder->setId( c );
                }

                break;

            case INTERVAL:
                changePodcastInterval();
                break;
        }
        #undef item
    }
    else if( isPlaylistTrackItem( item ) )
    {
    //******** track menu ***********
        #define item static_cast<PlaylistTrackItem*>(item)

        enum Actions { MAKE, APPEND, QUEUE, BURN, REMOVE, INFO };

        menu.insertItem( SmallIconSet( amaroK::icon( "add_playlist" ) ), i18n( "&Append to Playlist" ), APPEND );
        menu.insertItem( SmallIconSet( amaroK::icon( "fastforward" ) ), i18n( "&Queue Track" ), QUEUE );
        menu.insertItem( SmallIconSet( amaroK::icon( "playlist" ) ), i18n( "&Make Playlist" ), MAKE );


        menu.insertSeparator();

        menu.insertItem( SmallIconSet( amaroK::icon( "burn" ) ), i18n("Burn to CD"), BURN );
        menu.setItemEnabled( BURN, K3bExporter::isAvailable() && item->url().isLocalFile() );

        menu.insertSeparator();

        menu.insertItem( SmallIconSet( amaroK::icon( "remove_from_playlist" ) ), i18n( "&Remove" ), REMOVE );
        menu.insertItem( SmallIconSet( amaroK::icon( "info" ) ), i18n( "Edit Track &Information..." ), INFO );

        switch( menu.exec( p ) ) {
            case MAKE:
                Playlist::instance()->clear(); //FALL THROUGH
            case APPEND:
                Playlist::instance()->insertMedia( item->url() );
                break;
            case QUEUE:
                Playlist::instance()->insertMedia( item->url(), Playlist::Queue );
                break;
            case BURN:
                 K3bExporter::instance()->exportTracks( item->url() );
                 break;
            case REMOVE:
                removeSelectedItems();
                break;
            case INFO:
                if( !item->url().isLocalFile() )
                    KMessageBox::sorry( this, i18n( "Track information is not available for remote media." ) );
                else if( QFile::exists( item->url().path() ) ) {
                    TagDialog* dialog = new TagDialog( item->url() );
                    dialog->show();
                }
                else KMessageBox::sorry( this, i18n( "This file does not exist: %1" ).arg( item->url().path() ) );
        }
        #undef item
    }
}

/////////////////////////////////////////////////////////////////////////////
//    CLASS PlaylistBrowserView
////////////////////////////////////////////////////////////////////////////

PlaylistBrowserView::PlaylistBrowserView( QWidget *parent, const char *name )
    : KListView( parent, name )
    , m_marker( 0 )
{
    addColumn( i18n("Playlists") );

    setSelectionMode( QListView::Extended );
    setResizeMode( QListView::AllColumns );
    setShowSortIndicator( true );
    setRootIsDecorated( true );

    setDropVisualizer( true );    //the visualizer (a line marker) is drawn when dragging over tracks
    setDropHighlighter( true );   //and the highligther (a focus rect) is drawn when dragging over playlists
    setDropVisualizerWidth( 3 );
    setAcceptDrops( true );

    setTreeStepSize( 20 );

    connect( this, SIGNAL( mouseButtonPressed ( int, QListViewItem *, const QPoint &, int ) ),
             this,   SLOT( mousePressed( int, QListViewItem *, const QPoint &, int ) ) );

    //TODO moving tracks
    //connect( this, SIGNAL( moved(QListViewItem *, QListViewItem *, QListViewItem * )),
    //        this, SLOT( itemMoved(QListViewItem *, QListViewItem *, QListViewItem * )));
}

PlaylistBrowserView::~PlaylistBrowserView() { }

void PlaylistBrowserView::contentsDragEnterEvent( QDragEnterEvent *e )
{
    e->accept( e->source() == viewport() || KURLDrag::canDecode( e ) );
}

void PlaylistBrowserView::contentsDragMoveEvent( QDragMoveEvent* e )
{
    //Get the closest item _before_ the cursor
    const QPoint p = contentsToViewport( e->pos() );
    QListViewItem *item = itemAt( p );
    if( !item ) {
        eraseMarker();
        return;
    }

    //only for track items (for playlist items we draw the highlighter)
    if( isPlaylistTrackItem( item ) )
        item = item->itemAbove();

    if( item != m_marker )
    {
        eraseMarker();
        m_marker = item;
        viewportPaintEvent( 0 );
    }
}

void PlaylistBrowserView::contentsDragLeaveEvent( QDragLeaveEvent* )
{
     eraseMarker();
}


void PlaylistBrowserView::contentsDropEvent( QDropEvent *e )
{
    QListViewItem *parent = 0;
    QListViewItem *after;

    const QPoint p = contentsToViewport( e->pos() );
    QListViewItem *item = itemAt( p );
    if( !item ) {
        eraseMarker();
        return;
    }

    if( !isPlaylist( item ) )
        findDrop( e->pos(), parent, after );

    eraseMarker();

    if( e->source() == this )
    {
        moveSelectedItems( item ); // D&D sucks, do it ourselves
    }
    else {
        KURL::List decodedList;
        QValueList<MetaBundle> bundles;
        if( KURLDrag::decode( e, decodedList ) )
        {
            KURL::List::ConstIterator it = decodedList.begin();
            MetaBundle first( *it );
            const QString album  = first.album();
            const QString artist = first.artist();

            int suggestion = !album.stripWhiteSpace().isEmpty() ? 1 : !artist.stripWhiteSpace().isEmpty() ? 2 : 3;

            for ( ; it != decodedList.end(); ++it )
            {
                if( isCategory(item) )
                { // check if it is podcast category
                    QListViewItem *cat = item;
                    while( isCategory(cat) && cat!=PlaylistBrowser::instance()->podcastCategory() )
                        cat = cat->parent();

                    if( cat == PlaylistBrowser::instance()->podcastCategory() )
                        PlaylistBrowser::instance()->addPodcast(*it, item);
                    continue;
                }

                QString filename = (*it).fileName();

                if( filename.endsWith("m3u") || filename.endsWith("pls") )
                    PlaylistBrowser::instance()->addPlaylist( (*it).path() );
                else if( ContextBrowser::hasContextProtocol( *it ) )
                {
                    KURL::List urls = ContextBrowser::expandURL( *it );
                    for( KURL::List::iterator i = urls.begin();
                            i != urls.end();
                            i++ )
                    {
                        MetaBundle mb(*i);
                        bundles.append( mb );
                    }
                }
                else //TODO: check canDecode ?
                {
                    MetaBundle mb(*it);
                    bundles.append( mb );
                    if( suggestion == 1 && mb.album()->lower().stripWhiteSpace() != album.lower().stripWhiteSpace() )
                        suggestion = 2;
                    if( suggestion == 2 && mb.artist()->lower().stripWhiteSpace() != artist.lower().stripWhiteSpace() )
                        suggestion = 3;
                }
            }

            if( bundles.isEmpty() ) return;

            if( parent && isPlaylist( parent ) ) {
                //insert the dropped tracks
                PlaylistEntry *playlist = static_cast<PlaylistEntry *>( parent );
                playlist->insertTracks( after, bundles );
            }
            else //dropped on a playlist item
            {
                QListViewItem *parent = item;
                bool isPlaylistFolder = false;

                while( parent )
                {
                    if( parent == PlaylistBrowser::instance()->m_playlistCategory )
                    {
                        isPlaylistFolder = true;
                        break;
                    }
                    parent = parent->parent();
                }

                if( isPlaylist( item ) ) {
                    PlaylistEntry *playlist = static_cast<PlaylistEntry *>( item );
                    //append the dropped tracks
                    playlist->insertTracks( 0, bundles );
                }
                else if( isCategory( item ) && isPlaylistFolder )
                {
                    PlaylistBrowser *pb = PlaylistBrowser::instance();
                    QString title = suggestion == 1 ? album
                                                  : suggestion == 2 ? artist
                                                  : QString::null;
                    if ( pb->createPlaylist( item, false, title ) )
                        pb->m_lastPlaylist->insertTracks( 0, bundles );
                }
            }
        }
        else
            e->ignore();
    }

}

void PlaylistBrowserView::eraseMarker() //SLOT
{
    if( m_marker )
    {
        QRect spot;
        if( isPlaylist( m_marker ) )
            spot = drawItemHighlighter( 0, m_marker );
        else
            spot = drawDropVisualizer( 0, 0, m_marker );

        m_marker = 0;
        viewport()->repaint( spot, false );
    }
}

void PlaylistBrowserView::viewportPaintEvent( QPaintEvent *e )
{
    if( e ) KListView::viewportPaintEvent( e ); //we call with 0 in contentsDropEvent()

    if( m_marker )
    {
        QPainter painter( viewport() );
        if( isPlaylist( m_marker ) )    //when dragging on a playlist we draw a focus rect
            drawItemHighlighter( &painter, m_marker );
        else //when dragging on a track we draw a line marker
            painter.fillRect( drawDropVisualizer( 0, 0, m_marker ),
                                   QBrush( colorGroup().highlight(), QBrush::Dense4Pattern ) );
    }
}

void PlaylistBrowserView::mousePressed( int button, QListViewItem *item, const QPoint &pnt, int )    //SLOT
{
    // this function expande/collapse the playlist if the +/- symbol has been pressed
    // and show the save menu if the save icon has been pressed

    if( !item || button != LeftButton ) return;

    if( isPlaylist( item ) )
    {
        QPoint p = mapFromGlobal( pnt );
        p.setY( p.y() - header()->height() );

        QRect itemrect = itemRect( item );

        QRect expandRect = QRect( 4, itemrect.y() + (item->height()/2) - 5, 15, 15 );
        if( expandRect.contains( p ) ) {    //expand symbol clicked
            setOpen( item, !item->isOpen() );
            return;
        }
    }
}

void PlaylistBrowserView::moveSelectedItems( QListViewItem *newParent )
{
    if( !newParent || isDynamic( newParent ) || isPodcastChannel( newParent ) ||
         isSmartPlaylist( newParent ) || isPodcastEpisode( newParent ) )
        return;

    if( newParent == PlaylistBrowser::instance()->m_coolStreams ||
        newParent == PlaylistBrowser::instance()->m_smartDefaults )
        return;

    QPtrList<QListViewItem> selected;
    QListViewItemIterator it( this, QListViewItemIterator::Selected );
    for( ; it.current(); ++it )
    {
        if( !(*it)->parent() ) //must be a base category we are draggin'
            continue;

        selected.append( *it );
    }

    QListViewItem *after=0;
    for( QListViewItem *item = selected.first(); item; item = selected.next() )
    {
        QListViewItem *itemParent = item->parent();
        if( isPlaylistTrackItem( item ) )
        {
            if( isPlaylistTrackItem( newParent ) )
            {
                if( !after && newParent != newParent->parent()->firstChild() )
                    after = newParent->itemAbove();

                newParent = static_cast<PlaylistEntry*>(newParent->parent());
            }
            else if( !isPlaylist( newParent ) )
                continue;


            #define newParent static_cast<PlaylistEntry*>(newParent)
            newParent->insertTracks( after, KURL::List( static_cast<PlaylistTrackItem*>(item)->url() ));
            #undef  newParent
            #define itemParent static_cast<PlaylistEntry*>(itemParent)
            itemParent->removeTrack( static_cast<PlaylistTrackItem*>(item) );
            #undef  itemParent
            continue;
        }
        else if( !isCategory( newParent ) )
            continue;

        QListViewItem *base = newParent;
        while( base->parent() )
            base = base->parent();

        if( base == PlaylistBrowser::instance()->m_playlistCategory && isPlaylist( item )   ||
            base == PlaylistBrowser::instance()->m_streamsCategory && isStream( item )      ||
            base == PlaylistBrowser::instance()->m_smartCategory && isSmartPlaylist( item ) ||
            base == PlaylistBrowser::instance()->m_dynamicCategory && isDynamic( item )      )
        {
            itemParent->takeItem( item );
            newParent->insertItem( item );
            newParent->sortChildItems( 0, true );
        }
        else if( base == PlaylistBrowser::instance()->m_podcastCategory && isPodcastChannel( item ) )
        {
        #define item static_cast<PodcastChannel*>(item)
            item->setParent( static_cast<PlaylistCategory*>(newParent) );
        #undef  item
        }
    }
}

void PlaylistBrowserView::rename( QListViewItem *item, int c )
{
    KListView::rename( item, c );

    QRect rect( itemRect( item ) );
    int fieldX = rect.x() + treeStepSize() + 2;
    int fieldW = rect.width() - treeStepSize() - 2;

    KLineEdit *renameEdit = renameLineEdit();
    renameEdit->setGeometry( fieldX, rect.y(), fieldW, rect.height() );
    renameEdit->show();
}

void PlaylistBrowserView::keyPressEvent( QKeyEvent *e )
{
    switch( e->key() ) {
         case Key_Space:    //load
            PlaylistBrowser::instance()->slotDoubleClicked( currentItem() );
            break;

        case SHIFT+Key_Delete:    //delete
        case Key_Delete:          //remove
            PlaylistBrowser::instance()->removeSelectedItems();
            break;

        case Key_F2:    //rename
            PlaylistBrowser::instance()->renameSelectedItem();
            break;

        default:
            KListView::keyPressEvent( e );
            break;
    }
}


void PlaylistBrowserView::startDrag()
{
    DEBUG_BLOCK

    KURL::List urls;
    KURL::List itemList; // this is for CollectionDB::createDragPixmap()

    KMultipleDrag *drag = new KMultipleDrag( this );

    QListViewItemIterator it( this, QListViewItemIterator::Selected );
    QString pixText = QString::null;
    uint count = 0;

    for( ; it.current(); ++it )
    {
        if( isPlaylist( *it ) )
        {
            urls     += static_cast<PlaylistEntry*>(*it)->url();
            itemList += static_cast<PlaylistEntry*>(*it)->url();
            pixText = (*it)->text(0);
        }
        else if( isStream( *it ) )
        {
            urls     += static_cast<StreamEntry*>(*it)->url();
            itemList += KURL::fromPathOrURL( "stream://" );
            pixText = (*it)->text(0);
        }

        else if( isPodcastEpisode( *it ) )
        {
            #define item static_cast<PodcastEpisode *>(*it)
            if( item->isOnDisk() )
            {
                urls     += item->localUrl();
                itemList += item->url();
            }
            else
            {
                urls     += item->url();
                itemList += item->url();
            }

            pixText = (*it)->text(0);
            #undef item
        }
        else if( isPodcastChannel( *it ) )
        {
            #define item static_cast<PodcastChannel *>(*it)
            QListViewItem *child = item->firstChild();
            while( child )
            {
                PodcastEpisode *pe = static_cast<PodcastEpisode*>( child );
                if( pe->isOnDisk() )
                    urls += pe->localUrl();
                else
                    urls += pe->url();
                child = child->nextSibling();
            }
            itemList += KURL::fromPathOrURL( item->url().url() );
            pixText = (*it)->text(0);
            #undef item
        }

        else if( isSmartPlaylist( *it ) )
        {
            SmartPlaylist *item = static_cast<SmartPlaylist*>( *it );

            if( !item->query().isEmpty() )
            {
                QTextDrag *textdrag = new QTextDrag( item->query(), 0 );
                textdrag->setSubtype( "amarok-sql" );
                drag->addDragObject( textdrag );
            }
            itemList += KURL::fromPathOrURL( QString("smartplaylist://%1").arg( item->text(0) ) );
            pixText = (*it)->text(0);
        }

        else if( isDynamic( *it ) )
        {
            DynamicEntry *item = static_cast<DynamicEntry*>( *it );

            // Serialize pointer to string
            const QString str = QString::number( reinterpret_cast<Q_ULLONG>( item ) );

            QTextDrag *textdrag = new QTextDrag( str, 0 );
            textdrag->setSubtype( "dynamic" );
            drag->addDragObject( textdrag );
            itemList += KURL::fromPathOrURL( QString("dynamic://%1").arg( item->text(0) ) );
            pixText = (*it)->text(0);
        }

        else if( isPlaylistTrackItem( *it ) )
        {
            urls     += static_cast<PlaylistTrackItem*>(*it)->url();
            itemList += static_cast<PlaylistTrackItem*>(*it)->url();
        }
        count++;
    }
    if( count > 1 ) pixText = QString::null;

    drag->addDragObject( new KURLDrag( urls, viewport() ) );
    drag->setPixmap( CollectionDB::createDragPixmap( itemList, pixText ),
                     QPoint( CollectionDB::DRAGPIXMAP_OFFSET_X, CollectionDB::DRAGPIXMAP_OFFSET_Y ) );
    drag->dragCopy();
}

/////////////////////////////////////////////////////////////////////////////
//    CLASS PlaylistDialog
////////////////////////////////////////////////////////////////////////////

QString PlaylistDialog::getSaveFileName( const QString &suggestion ) //static
{
    PlaylistDialog dialog;
    if( !suggestion.isEmpty() )
    {
        QString path = KGlobal::dirs()->saveLocation( "data", "amarok/playlists/", true ) + "%1" + ".m3u";
        if( QFileInfo( path.arg( suggestion ) ).exists() )
        {
            int n = 2;
            while( QFileInfo( path.arg( i18n( "%1 (%2)" ).arg( suggestion, QString::number( n ) ) ) ).exists() )
                n++;
            dialog.edit->setText( i18n( "%1 (%2)" ).arg( suggestion, QString::number( n ) ) );
        }
        else
          dialog.edit->setText( suggestion );
    }
    if( dialog.exec() == Accepted )
        return dialog.result;
    return QString::null;
}

PlaylistDialog::PlaylistDialog()
    : KDialogBase( PlaylistWindow::self(), "saveplaylist", true /*modal*/,
                   i18n( "Save Playlist" ), Ok | Cancel | User1, Ok, false /*seperator*/,
                   KGuiItem( i18n( "Save to location..." ), SmallIconSet( amaroK::icon( "files" ) ) ) )
    , customChosen( false )
{
    QVBox *vbox = makeVBoxMainWidget();
    QLabel *label = new QLabel( i18n( "&Enter a name for the playlist:" ), vbox );
    edit = new KLineEdit( vbox );
    edit->setFocus();
    label->setBuddy( edit );
    enableButtonOK( false );
    connect( edit, SIGNAL( textChanged( const QString & ) ),
             this, SLOT( slotTextChanged( const QString& ) ) );
    connect( this, SIGNAL( user1Clicked() ), SLOT( slotCustomPath() ) );
}

void PlaylistDialog::slotOk()
{
    // TODO Remove this hack for 1.2. It's needed because playlists was a file once.
    QString folder = KGlobal::dirs()->saveLocation( "data", "amarok/playlists", false );
    QFileInfo info( folder );
    if ( !info.isDir() ) QFile::remove( folder );

    if( !customChosen && !edit->text().isEmpty() )
        result = KGlobal::dirs()->saveLocation( "data", "amarok/playlists/", true ) + edit->text() + ".m3u";

    if( !QFileInfo( result ).exists() ||
        KMessageBox::warningContinueCancel(
            PlaylistWindow::self(),
            i18n( "A playlist named \"%1\" already exists. Do you want to overwrite it?" ).arg( edit->text() ),
            i18n( "Overwrite Playlist?" ), i18n( "Overwrite" ) ) == KMessageBox::Continue )
    {
        KDialogBase::slotOk();
    }
}

void PlaylistDialog::slotTextChanged( const QString &s )
{
    enableButtonOK( !s.isEmpty() );
}

void PlaylistDialog::slotCustomPath()
{
   result = KFileDialog::getSaveFileName( ":saveplaylists", "*.m3u" );
   if( !result.isNull() )
   {
      edit->setText( result );
      edit->setReadOnly( true );
      enableButtonOK( true );
      customChosen = true;
   }
}


InfoPane::InfoPane( QWidget *parent )
        : QVBox( parent ),
          m_enable( false ),
          m_storedHeight( 100 )
{
    QFrame *container = new QVBox( this, "container" );
    container->hide();

    {
        QFrame *box = new QHBox( container );
        box->setMargin( 3 );
        box->setBackgroundMode( Qt::PaletteBase );

        m_infoBrowser = new HTMLView( box, "extended_info" );

        container->setFrameStyle( QFrame::StyledPanel );
        container->setMargin( 3 );
        container->setBackgroundMode( Qt::PaletteBase );
    }

    m_pushButton = new KPushButton( KGuiItem( i18n("&Show Extended Info"), "info" ), this );
    m_pushButton->setToggleButton( true );
    m_pushButton->setEnabled( m_enable );
    connect( m_pushButton, SIGNAL(toggled( bool )), SLOT(toggle( bool )) );

    //Set the height to fixed. The button shouldn't be resized.
    setFixedHeight( m_pushButton->sizeHint().height() );
}

const int
InfoPane::getHeight()
{
    if( static_cast<QWidget*>( child( "container" ) )->isShown() )
    {
        //If the InfoPane is shown, return true height.
        return static_cast<QSplitter*>( parentWidget() )->sizes().last();
    }

    return m_storedHeight;
}

void
InfoPane::setStoredHeight( const int newHeight ) {
    m_storedHeight = newHeight;
}

void
InfoPane::toggle( bool toggled )
{
    QSplitter *splitter = static_cast<QSplitter*>( parentWidget() );

    if ( !toggled )
    {
        //Save the height for later
        setStoredHeight( splitter->sizes().last() );

        //Set the height to fixed. The button shouldn't be resized.
        setFixedHeight( m_pushButton->sizeHint().height() );

        //Now the info pane is not shown, we can disable the button if necessary
        m_pushButton->setEnabled( m_enable );
    }
    else {
        setMaximumHeight( ( int )( parentWidget()->height() / 1.5 ) );

        //Restore the height of the InfoPane (change the splitter properties)
        //Done everytime since the pane forgets its height if you try to resize it while the info is hidden.
        QValueList<int> sizes = splitter->sizes();
        const int sizeOffset = getHeight() - sizes.last();
        sizes.first() -= sizeOffset;
        sizes.last() += sizeOffset;
        splitter->setSizes( sizes );

        setMinimumHeight( 150 );
    }

    static_cast<QWidget*>( child( "container" ) )->setShown( toggled );
}

void
InfoPane::setInfo( const QString &title, const QString &info )
{
    //If the info pane is not shown, we can enable or disable the button depending on
    //whether there is content to show. Otherwise, just remember what we wanted to do
    //so we can do it later, when the user does hide the pane.
    m_enable = !( info.isEmpty() && title.isEmpty() );
    if ( !static_cast<QWidget*>(child("container"))->isShown() )
        m_pushButton->setEnabled( m_enable );

    m_infoBrowser->set(
        m_enable ?
        QString( "<div id='extended_box' class='box'>"
                  "<div id='extended_box-header-title' class='box-header'>"
                  "<span id='extended_box-header-title' class='box-header-title'>"
                  " %1 "
                  "</span>"
                  "</div>"
                  "<table id='extended_box-table' class='box-body' width='100%' cellpadding='0' cellspacing='0'>"
                  "<tr>"
                  "<td id='extended_box-information-td'>"
                  "  %2 "
                  "</td>"
                  "</tr>"
                  "</table>"
                  "</div>" ).arg( title, info ) :
        QString::null );
}

#include "playlistbrowser.moc"
