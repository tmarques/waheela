/***************************************************************************
                        Playlist.h  -  description
                            -------------------
    begin                : Don Dez 5 2002
    copyright            : (C) 2002 by Mark Kretschmann
                           (C) 2005 Ian Monroe
                           (C) 2005 by Gábor Lehel
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#ifndef AMAROK_PLAYLIST_H
#define AMAROK_PLAYLIST_H

#include "amarok_export.h"
#include "amarokconfig.h"
#include "amarokdcophandler.h"
#include "engineobserver.h"  //baseclass
#include "dynamicmode.h"
#include "playlistwindow.h"  //friend
#include "playlistitem.h"
#include "metabundle.h"
#include "tooltip.h"         //baseclass
#include "tracktooltip.h"

#include <klistview.h>       //baseclass
#include <kurl.h>            //KURL::List
#include <qdir.h>            //stack allocated
#include <qpoint.h>          //stack allocated
#include <qptrlist.h>        //stack allocated
#include <qstringlist.h>     //stack allocated
#include <vector>            //stack allocated

class KAction;
class KActionCollection;
class MyAtomicString;
class PlaylistItem;
class PlaylistEntry;
class PlaylistLoader;
class PlaylistAlbum;
class QBoxLayout;
class QLabel;
class QTimer;

class Medium;
class ReadMood;
namespace amaroK { class TrackSlider; }

/**
 * @authors Mark Kretschmann && Max Howell
 *
 * Playlist inherits KListView privately and thus is no longer a ListView
 * Instead it is a part of PlaylistWindow and they interact in harmony. The change
 * was necessary as it is too dangerous to allow public access to PlaylistItems
 * due to the multi-threading environment.
 *
 * Unfortunately, since QObject is now inaccessible you have to connect slots
 * via one of PlaylistWindow's friend members or in Playlist
 *
 * If you want to add new playlist type functionality you should implement it
 * inside this class or inside PlaylistWindow.
 *
 */


class Playlist : private KListView, public EngineObserver, public amaroK::ToolTipClient
{
        Q_OBJECT

    public:
        ~Playlist();

        LIBAMAROK_EXPORT static Playlist *instance() { return s_instance; }
        static QString defaultPlaylistPath();
        static const int NO_SORT = 200;

        static const int Append     = 1;     /// inserts media after the last item in the playlist
        static const int Queue      = 2;     /// inserts media after the currentTrack
        static const int Clear      = 4;     /// clears the playlist first
        static const int Replace    = Clear;
        static const int DirectPlay = 8;     /// start playback of the first item in the list
        static const int Unique     = 16;    /// don't insert anything already in the playlist

        // it's really just the *ListView parts we want to hide...
        QScrollView *qscrollview() const
        {
            return reinterpret_cast<QScrollView*>( const_cast<Playlist*>( this ) );
        }

        /** Add media to the playlist
         *  @param options you can OR these together, see the enum
         *  @param sql     Sql program to execute */
        LIBAMAROK_EXPORT void insertMedia( KURL::List, int options = Append );
        void insertMediaSql( const QString& sql, int options = Append );

        /// Dynamic mode functions
        void addSpecialTracks( uint songCount, const int type = DynamicMode::RANDOM );
        void addSpecialCustomTracks( uint songCount );
        void adjustDynamicUpcoming( bool saveUndo = false, const int type = DynamicMode::RANDOM );
        void adjustDynamicPrevious( uint songCount, bool saveUndo = false );
        void advanceDynamicTrack( PlaylistItem *item = 0 );
        void alterHistoryItems( bool enable = false, bool entire = false );

        void burnPlaylist      ( int projectType = -1 );
        void burnSelectedTracks( int projectType = -1 );
        int  currentTrackIndex( bool onlyCountVisible = true );
        bool isEmpty()       const  { return childCount() == 0; }
        bool isTrackBefore() const;
        bool isTrackAfter()  const;
        void restoreSession();          // called during initialisation
        bool saveM3U( const QString&, bool relative = AmarokConfig::relativePlaylist() ) const;
        void saveXML( const QString& );
        bool saveXSPF( const QString& );
        int  totalTrackCount() const;
        BundleList nextTracks() const;
        uint repeatAlbumTrackCount() const;    //returns number of tracks from same album
        //as current track that are in playlist (may require Play Albums in Order on). 
        //If the information is not available, returns 0.

        //const so you don't change it behind Playlist's back, use modifyDynamicMode() for that
        const DynamicMode *dynamicMode() const;

        //modify the returned DynamicMode, then finishedModifying() it when done
        DynamicMode *modifyDynamicMode();

        //call this every time you modifyDynamicMode(), otherwise you'll get memory leaks and/or crashes
        void finishedModifying( DynamicMode *mode );

        int  stopAfterMode() const;

        void addCustomMenuItem ( const QString &submenu, const QString &itemTitle );
        void customMenuClicked ( int id );
        bool removeCustomMenuItem( const QString &submenu, const QString &itemTitle );

        void setFont( const QFont &f ) { KListView::setFont( f ); } //made public for convenience
        void unsetFont()               { KListView::unsetFont(); }

        PlaylistItem *firstChild() const { return static_cast<PlaylistItem*>( KListView::firstChild() ); }
        PlaylistItem *lastItem()   const { return static_cast<PlaylistItem*>( KListView::lastItem() ); }
        PlaylistItem *currentItem() const { return static_cast<PlaylistItem*>( KListView::currentItem() ); }

        int  numVisibleColumns() const;
        QValueList<int> visibleColumns() const;
        int  mapToLogicalColumn( int physical ) const; // Converts physical PlaylistItem column position to logical
        QString columnText( int c ) const { return KListView::columnText( c ); };
        void setColumns( QValueList<int> order, QValueList<int> visible );

        /** Call this to prevent items being removed from the playlist, it is mostly for internal use only
         *  Dont forget to unlock() !! */
        void lock();
        void unlock();

        //reimplemented to save columns by name instead of index, to be more resilient to reorderings and such
        void saveLayout(KConfig *config, const QString &group) const;
        void restoreLayout(KConfig *config, const QString &group);

        //ATF-related functions
        bool checkFileStatus( PlaylistItem * item );

        enum RequestType { Prev = -1, Current = 0, Next = 1 };
        enum StopAfterMode { DoNotStop, StopAfterCurrent, StopAfterQueue, StopAfterOther };

        class QDragObject *dragObject();
        friend class amaroK::TrackSlider;
        friend class PlaylistItem::ReadMood;
        friend class PlaylistItem;
        friend class UrlLoader;
        friend class QueueManager;
        friend class QueueLabel;
        friend class PlaylistWindow;
        friend class ColumnList;
        friend void amaroK::DcopPlaylistHandler::removeCurrentTrack(); //calls removeItem() and currentTrack()
        friend void amaroK::DcopPlaylistHandler::removeByIndex( int ); //calls removeItem()
        friend void PlaylistWindow::init(); //setting up connections etc.
        friend TrackToolTip::TrackToolTip();
        friend bool PlaylistWindow::eventFilter( QObject*, QEvent* ); //for convenience we handle some playlist events here

    public:
        QPair<QString, QRect> toolTipText( QWidget*, const QPoint &pos ) const;

    signals:
        void aboutToClear();
        void itemCountChanged( int newCount, int newLength, int visCount, int visLength, int selCount, int selLength );
        void queueChanged( const PLItemList &queued, const PLItemList &dequeued );
        void columnsChanged();
        void dynamicModeChanged( const DynamicMode *newMode );

    public slots:
        void activateByIndex(int);
        void addCustomColumn();
        void appendMedia( const KURL &url );
        void appendMedia( const QString &path );
        void clear();
        void copyToClipboard( const QListViewItem* = 0 ) const;
        void deleteSelectedFiles();
        void trashSelectedFiles();
        void ensureItemCentered( QListViewItem* item );
        void playCurrentTrack();
        void playNextTrack( const bool forceNext = true );
        void playPrevTrack();
        void queueSelected();
        void setSelectedRatings( int rating );
        void redo();
        void removeDuplicates();
        void removeSelectedItems();
        void setDynamicMode( DynamicMode *mode );
        void loadDynamicMode( DynamicMode *mode ); //saveUndoState() + setDynamicMode()
        void disableDynamicMode() { setDynamicMode( 0 ); }
        void editActiveDynamicMode();
        void repopulate();
        void safeClear();
        void scoreChanged( const QString &path, int score );
        void ratingChanged( const QString &path, int rating );
        void fileMoved( const QString &srcPath, const QString &dstPath );
        void selectAll() { QListView::selectAll( true ); }
        void setFilter( const QString &filter );
        void setFilterSlot( const QString &filter );                       //uses a delay where applicable
        void setStopAfterCurrent( bool on );
        void toggleStopAfterCurrentItem();
        void toggleStopAfterCurrentTrack();
        void setStopAfterMode( int mode );
        void showCurrentTrack() { ensureItemCentered( m_currentTrack ); }
        void showQueueManager();
        void shuffle();
        void undo();
        void updateMetaData( const MetaBundle& );
        void fileHasMood( const QString path );
        void refreshMoods();
        void applySettings();
        void adjustColumn( int n );

    protected:
        virtual void fontChange( const QFont &old );

    protected slots:
        void contentsMouseMoveEvent( QMouseEvent *e = 0 );
        void leaveEvent( QEvent *e );
        void contentsMousePressEvent( QMouseEvent *e );
        void contentsWheelEvent( QWheelEvent *e );

    private slots:
        void mediumChange( const Medium *medium, QString name );
        void slotCountChanged();
        void activate( QListViewItem* );
        void columnOrderChanged();
        void columnResizeEvent( int, int, int );
        void doubleClicked( QListViewItem* );

        void generateInfo(); //generates info for Random Albums

        void queue( QListViewItem*, bool multi = false );
           /* the only difference multi makes is whether it emits queueChanged(). (if multi, then no)
              if you're queue()ing many items, consider passing true and emitting queueChanged() yourself. */

        void saveUndoState();
        void setDelayedFilter();                                           //after the delay is over
        void showContextMenu( QListViewItem*, const QPoint&, int );
        void slotEraseMarker();
        void slotGlowTimer();
        void reallyEnsureItemCentered();
        void slotMouseButtonPressed( int, QListViewItem*, const QPoint&, int );
        void slotSingleClick();
        void slotContentsMoving();
        void slotRepeatTrackToggled( int mode );
        void slotQueueChanged( const PLItemList &in, const PLItemList &out);
        void slotUseScores( bool use );
        void slotUseRatings( bool use );
        void updateNextPrev();
        void writeTag( QListViewItem*, const QString&, int );

    private:
        Playlist( QWidget* );
        Playlist( const Playlist& ); //not defined

        LIBAMAROK_EXPORT static Playlist *s_instance;

        void countChanged();

        PlaylistItem *currentTrack() const { return m_currentTrack; }
        PlaylistItem *restoreCurrentTrack();

        void insertMediaInternal( const KURL::List&, PlaylistItem*, bool directPlay = false );
        bool isAdvancedQuery( const QString &query );
        void refreshNextTracks( int = -1 );
        void removeItem( PlaylistItem*, bool = false );
        bool saveState( QStringList& );
        void setCurrentTrack( PlaylistItem* );
        void setCurrentTrackPixmap( int state = -1 );
        void showTagDialog( QPtrList<QListViewItem> items );
        void sortQueuedItems();
        void switchState( QStringList&, QStringList& );
        void saveSelectedAsPlaylist();
        void initStarPixmaps();

        //engine observer functions
        void engineNewMetaData( const MetaBundle&, bool );
        void engineStateChanged( Engine::State, Engine::State = Engine::Empty );

        /// KListView Overloaded functions
        void contentsDropEvent     ( QDropEvent* );
        void contentsDragEnterEvent( QDragEnterEvent* );
        void contentsDragMoveEvent ( QDragMoveEvent* );
        void contentsDragLeaveEvent( QDragLeaveEvent* );

        #ifdef PURIST //KListView imposes hand cursor so override it
        void contentsMouseMoveEvent( QMouseEvent *e ) { QListView::contentsMouseMoveEvent( e ); }
        #endif

        void customEvent( QCustomEvent* );
        bool eventFilter( QObject*, QEvent* );
        void paletteChange( const QPalette& );
        void rename( QListViewItem*, int );
        void setColumnWidth( int, int );
        void setSorting( int, bool = true );

        void viewportPaintEvent( QPaintEvent* );
        void viewportResizeEvent( QResizeEvent* );

        void appendToPreviousTracks( PlaylistItem *item );
        void appendToPreviousAlbums( PlaylistAlbum *album );
        void removeFromPreviousTracks( PlaylistItem *item = 0 );
        void removeFromPreviousAlbums( PlaylistAlbum *album = 0 );

        typedef QMap<MyAtomicString, PlaylistAlbum*> AlbumMap;
        typedef QMap<MyAtomicString, AlbumMap> ArtistAlbumMap;
        ArtistAlbumMap m_albums;
        uint m_startupTime_t; //QDateTime::currentDateTime().toTime_t as of startup
        uint m_oldestTime_t; //the createdate of the oldest song in the collection


        /// ATTRIBUTES

        PlaylistItem  *m_currentTrack;          //the track that is playing
        QListViewItem *m_marker;                //track that has the drag/drop marker under it
        PlaylistItem  *m_hoveredRating;         //if the mouse is hovering over the rating of an item

        //NOTE these container types were carefully chosen
        QPtrList<PlaylistAlbum> m_prevAlbums; //the previously played albums in Entire Albums mode
        PLItemList m_prevTracks;    //the previous history
        PLItemList m_nextTracks;    //the tracks to be played after the current track

        QString m_filter;
        QString m_prevfilter;
        QTimer *m_filtertimer;

        PLItemList m_itemsToChangeTagsFor;

        bool          m_smartResizing;

        int           m_firstColumn;
        int           m_totalCount;
        int           m_totalLength;
        int           m_selCount;
        int           m_selLength;
        int           m_visCount;
        int           m_visLength;
        Q_INT64       m_total; //for Favor Tracks
        bool          m_itemCountDirty;

        KAction      *m_undoButton;
        KAction      *m_redoButton;
        KAction      *m_clearButton;

        QDir          m_undoDir;
        QStringList   m_undoList;
        QStringList   m_redoList;
        uint          m_undoCounter;

        DynamicMode  *m_dynamicMode;
        KURL::List    m_queueList;
        PlaylistItem *m_stopAfterTrack;
        bool          m_showHelp;
        bool          m_stateSwitched;
        bool          m_dynamicDirt;          //So we dont call advanceDynamicTrack() on activate()
        bool          m_queueDirt;          //When queuing disabled items, we need to place the marker on the newly inserted item
        bool          m_undoDirt;           //Make sure we dont repopulate the playlist when dynamic mode and undo()

        QListViewItem *m_itemToReallyCenter;
        QListViewItem *m_renameItem;
        int            m_renameColumn;
        QTimer        *m_clicktimer;
        QListViewItem *m_itemToRename;
        QPoint         m_clickPos;
        int            m_columnToRename;

        QMap<QString, QStringList> m_customSubmenuItem;
        QMap<int, QString>         m_customIdItem;

        bool isLocked() const { return m_lockStack > 0; }

        /// stack counter for PLaylist::lock() and unlock()
        int m_lockStack;

        QString m_editOldTag; //text before inline editing ( the new tag is written only if it's changed )

        std::vector<double> m_columnFraction;

        bool m_atfEnabled;
};

class MyAtomicString: public AtomicString
{
public:
    MyAtomicString() { }
    MyAtomicString(const QString &string): AtomicString( string ) { }
    MyAtomicString(const AtomicString &other): AtomicString( other ) { }
    bool operator<(const AtomicString &other) const { return ptr() < other.ptr(); }
};

class PlaylistAlbum
{
public:
    PLItemList tracks;
    int refcount;
    Q_INT64 total; //for Favor Tracks
    PlaylistAlbum(): refcount( 0 ), total( 0 ) { }
};

#endif //AMAROK_PLAYLIST_H
