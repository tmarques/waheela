/***************************************************************************
 * copyright            : (c) 2004 Pierpaolo Di Panfilo                    *
 *                        (c) 2004 Mark Kretschmann <markey@web.de>        *
 *                        (c) 2005-2006 Seb Ruiz <me@sebruiz.net>          *
 *                        (c) 2005 Gábor Lehel <illissius@gmail.com>       *
 * See COPYING file for licensing information                              *
 ***************************************************************************/

#ifndef PLAYLISTBROWSER_H
#define PLAYLISTBROWSER_H

#include "amarokconfig.h"
#include "playlistbrowseritem.h"
#include "podcastsettings.h"

#include <kaction.h>
#include <klistview.h>
#include <kurl.h>
#include <qdom.h>
#include <qptrlist.h>
#include <qvbox.h>

class KTextBrowser;
class KToolBar;

class QCustomEvent;
class QColorGroup;
class QDragObject;
class QPainter;
class QPixmap;
class QPoint;
class QSplitter;
class QTimer;

class HTMLView;
class InfoPane;
class PlaylistBrowserView;
class PlaylistTrackItem;


class PlaylistBrowser : public QVBox
{
        Q_OBJECT
    friend class DynamicMode;
    friend class PlaylistBrowserView;
    friend class PlaylistBrowserEntry;
    friend class PlaylistCategory;
    friend class PlaylistEntry;
    friend class PodcastChannel;  //for changing podcast timer list

    public:
        enum ViewMode { DETAILEDVIEW, LISTVIEW };
        enum AddMode  { PLAYLIST, STREAM, SMARTPLAYLIST, PODCAST, ADDDYNAMIC };

        ~PlaylistBrowser();

        void setInfo( const QString &info );

        void addStream( QListViewItem *parent = 0 );
        void addSmartPlaylist( QListViewItem *parent = 0 );
        void addDynamic( QListViewItem *parent = 0 );
        void addPlaylist( const QString &path, QListViewItem *parent = 0, bool force=false );
        int  loadPlaylist( const QString &playlist, bool force=false );
        void addPodcast( QListViewItem *parent = 0 );
        void addPodcast( const KURL &url, QListViewItem *parent = 0 );
        void loadPodcastsFromDatabase( PlaylistCategory *p = 0 );
        void registerPodcastSettings( const QString &title, const PodcastSettings *settings );

        static bool savePlaylist( const QString &path, const QValueList<KURL> &urls,
                                  const QValueList<QString> &titles = QValueList<QString>(),
                                  const QValueList<int> &lengths = QValueList<int>(),
                                  bool relative = AmarokConfig::relativePlaylist() );

        QString dynamicBrowserCache() const;
        QString playlistBrowserCache() const;
        QString podcastBrowserCache() const;
        QString streamBrowserCache() const;
        QString smartplaylistBrowserCache() const;

        PlaylistBrowserEntry *findItem( QString &t, int c ) const;
        QListViewItem *findItemInTree( const QString &searchstring, int c ) const;
        PodcastEpisode *findPodcastEpisode( const KURL &episode, const KURL &feed ) const;

        QPtrList<QListViewItem> dynamicEntries() const { return m_dynamicEntries; }
        DynamicMode *findDynamicModeByTitle( const QString &title ) const;
        QListViewItem *podcastCategory() const { return m_podcastCategory; }

        ViewMode viewMode() const { return m_viewMode; }

        static PlaylistBrowser *instance() {
            if(!s_instance)  s_instance = new PlaylistBrowser("PlaylistBrowser");
            return s_instance;
        }

        //following used by PlaylistSelection.cpp
        PlaylistBrowserView* getListView() const { return m_listview; }
        PlaylistCategory* getDynamicCategory() const { return m_dynamicCategory; }
        void saveDynamics();

    signals:
        void selectionChanged();

    public slots:
        void openPlaylist( QListViewItem *parent = 0 );
        void scanPodcasts();

    private slots:
        void abortPodcastQueue();
        void addToDynamic();
        void collectionScanDone();
        void currentItemChanged( QListViewItem * );
        void downloadPodcastQueue();
        void editStreamURL( StreamEntry *item, const bool readOnly=false );
        void removeSelectedItems();
        void renamePlaylist( QListViewItem*, const QString&, int );
        void renameSelectedItem();
        void slotDoubleClicked( QListViewItem *item );
        void subFromDynamic();

        void slotAddMenu( int id );
        void slotSave();
        void slotViewMenu( int id );
        void showContextMenu( QListViewItem*, const QPoint&, int );

        void loadDynamicItems();

    private:
        PlaylistBrowser( const char* name=0 );
        void polish();

        bool m_polished;

        PlaylistCategory* loadStreams();
        void loadCoolStreams();
        void saveStreams();

        PlaylistCategory* loadSmartPlaylists();
        void loadDefaultSmartPlaylists();
        void editSmartPlaylist( SmartPlaylist* );
        void saveSmartPlaylists( PlaylistCategory *smartCategory = NULL );
        void updateSmartPlaylists( QListViewItem *root );

        PlaylistCategory* loadDynamics();

        PlaylistCategory* loadPodcasts();
        QMap<int,PlaylistCategory*> loadPodcastFolders( PlaylistCategory *p );
        void changePodcastInterval();
        bool deletePodcastItems();
        bool deletePodcasts( QPtrList<PodcastChannel> items, const bool silent=false );
        void downloadSelectedPodcasts();
        void refreshPodcasts( QListViewItem *category );
        void removePodcastFolder( PlaylistCategory *item );
        void savePodcastFolderStates( PlaylistCategory *folder );
        PodcastChannel *findPodcastChannel( const KURL &feed, QListViewItem *parent=0 ) const;

        PlaylistCategory* loadPlaylists();
        void loadOldPlaylists();
        void savePlaylists();
        void savePlaylist( PlaylistEntry * );
        bool createPlaylist( QListViewItem *parent = 0, bool current = true, QString title = 0 );
        bool deletePlaylists( QPtrList<PlaylistEntry> items );
        bool deletePlaylists( KURL::List items );

        void customEvent( QCustomEvent* e );
        void saveM3U( PlaylistEntry *, bool append );
        void savePLS( PlaylistEntry *, bool append );
        void saveXSPF( PlaylistEntry *, bool append );

        static KURL::List recurse( const KURL &url );

        static PlaylistBrowser *s_instance;

        PlaylistCategory    *m_playlistCategory;
        PlaylistCategory    *m_streamsCategory;
        PlaylistCategory    *m_smartCategory;
        PlaylistCategory    *m_dynamicCategory;
        PlaylistCategory    *m_podcastCategory;
        PlaylistCategory    *m_coolStreams;
        PlaylistCategory    *m_smartDefaults;
        PlaylistEntry       *m_lastPlaylist;

        DynamicEntry          *m_randomDynamic;
        DynamicEntry          *m_suggestedDynamic;

        bool                 m_coolStreamsOpen;
        bool                 m_smartDefaultsOpen;

        PlaylistBrowserView *m_listview;
        KActionCollection   *m_ac;
        KAction             *removeButton, *renameButton;
        KActionMenu         *viewMenuButton;
        KActionMenu         *addMenuButton;
        KToolBar            *m_toolbar;
        ViewMode             m_viewMode;
        QDict<PodcastSettings> m_podcastSettings;
        QValueList<int>      m_dynamicSizeSave;
        QPtrList<QListViewItem> m_dynamicEntries;

        QTimer              *m_podcastTimer;
        int                  m_podcastTimerInterval;        //in ms
        QPtrList<PodcastChannel> m_podcastItemsToScan;
        QPtrList<PodcastEpisode> m_podcastDownloadQueue;

        InfoPane *m_infoPane;

        bool                 m_removeDirt;
};



class PlaylistBrowserView : public KListView
{
        Q_OBJECT

    friend class PlaylistEntry;

    public:
        PlaylistBrowserView( QWidget *parent, const char *name=0 );
        ~PlaylistBrowserView();
        void startAnimation( PlaylistEntry * );
        void stopAnimation( PlaylistEntry * );

        void rename( QListViewItem *item, int c );

    protected:
        virtual void keyPressEvent( QKeyEvent * );

    private slots:
        void mousePressed( int, QListViewItem *, const QPoint &, int );
        void moveSelectedItems( QListViewItem* newParent );
        void slotAnimation();

    private:
        void startDrag();
        void contentsDropEvent( QDropEvent* );
        void contentsDragEnterEvent( QDragEnterEvent* );
        void contentsDragMoveEvent( QDragMoveEvent* );
        void contentsDragLeaveEvent( QDragLeaveEvent* );
        void viewportPaintEvent( QPaintEvent* );
        void eraseMarker();

        QListViewItem   *m_marker;       //track that has the drag/drop marker under it
        QTimer          *m_animationTimer;
        QPtrList<QListViewItem> m_loadingItems;
        QPixmap         *m_loading1, *m_loading2;    //icons for loading animation
};

class PlaylistDialog: public KDialogBase
{
    Q_OBJECT
    public:
        static QString getSaveFileName( const QString &suggestion = QString::null );

    private:
        KLineEdit *edit;
        bool customChosen;
        QString result;
        PlaylistDialog();

    private slots:
       void slotOk();

       void slotTextChanged( const QString &s );

       void slotCustomPath();
};

// Returns true if item is Playlist, Stream, Smart Playlist or DynamicMode.
inline bool
isElement( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == ( PlaylistEntry::RTTI || StreamEntry::RTTI ||
                             SmartPlaylist::RTTI /*|| DynamicEntry::RTTI */) ? true : false;
}

inline bool
isCategory( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == PlaylistCategory::RTTI ? true : false;
}

inline bool
isDynamic( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == DynamicEntry::RTTI ? true : false;
}

inline bool
isPlaylist( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == PlaylistEntry::RTTI ? true : false;
}

inline bool
isSmartPlaylist( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == SmartPlaylist::RTTI ? true : false;
}

inline bool
isPlaylistTrackItem( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == PlaylistTrackItem::RTTI ? true : false;
}

inline bool
isPodcastChannel( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == PodcastChannel::RTTI ? true : false;
}

inline bool
isPodcastEpisode( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == PodcastEpisode::RTTI ? true : false;
}

inline bool
isStream( QListViewItem *item )
{
    if( !item )
        return false;
    return item->rtti() == StreamEntry::RTTI ? true : false;
}

inline QString
fileBaseName( const QString &filePath )
{
    // this function returns the file name without extension
    // (e.g. if the file path is "/home/user/playlist.m3u", "playlist" is returned
    QString fileName = filePath.right( filePath.length() - filePath.findRev( '/' ) - 1 );
    return fileName.mid( 0, fileName.findRev( '.' ) );
}

inline QString
fileDirPath( const QString &filePath )
{
    return filePath.left( filePath.findRev( '/' )+1 );
}



class InfoPane : public QVBox
{
    Q_OBJECT

public:
    InfoPane( PlaylistBrowser *parent );

public slots:
    void setInfo( const QString &info );

private slots:
    void toggle( bool );

private:
    HTMLView *m_infoBrowser;
};


#endif