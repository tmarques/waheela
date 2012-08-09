/****************************************************************************
**
** DCOP Stub Definition created by dcopidl2cpp from amarokdcopiface.kidl
**
** WARNING! All changes made in this file will be lost!
**
*****************************************************************************/

#ifndef __AMAROKDCOPIFACE_STUB__
#define __AMAROKDCOPIFACE_STUB__

#include <dcopstub.h>
#include <qstringlist.h>
#include <kurl.h>
#include <dcopobject.h>


class AmarokPlayerInterface_stub : virtual public DCOPStub
{
public:
    AmarokPlayerInterface_stub( const QCString& app, const QCString& id );
    AmarokPlayerInterface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit AmarokPlayerInterface_stub( const DCOPRef& ref );
    virtual bool dynamicModeStatus();
    virtual bool equalizerEnabled();
    virtual bool isPlaying();
    virtual bool randomModeStatus();
    virtual bool repeatPlaylistStatus();
    virtual bool repeatTrackStatus();
    virtual int getVolume();
    virtual int sampleRate();
    virtual int score();
    virtual int status();
    virtual int trackCurrentTime();
    virtual int trackPlayCounter();
    virtual int trackTotalTime();
    virtual QString album();
    virtual QString artist();
    virtual QString bitrate();
    virtual QString comment();
    virtual QString coverImage();
    virtual QString currentTime();
    virtual QString encodedURL();
    virtual QString engine();
    virtual QString genre();
    virtual QString lyrics();
    virtual QString lyricsByPath( QString path );
    virtual QString nowPlaying();
    virtual QString path();
    virtual QString setContextStyle( const QString&  );
    virtual QString title();
    virtual QString totalTime();
    virtual QString track();
    virtual QString type();
    virtual QString year();
    virtual void configEqualizer();
    virtual void enableDynamicMode( bool enable );
    virtual void enableOSD( bool enable );
    virtual void enableRandomMode( bool enable );
    virtual void enableRepeatPlaylist( bool enable );
    virtual void enableRepeatTrack( bool enable );
    virtual void mediaDeviceMount();
    virtual void mediaDeviceUmount();
    virtual void mute();
    virtual void next();
    virtual void pause();
    virtual void play();
    virtual void playPause();
    virtual void prev();
    virtual void queueForTransfer( KURL url );
    virtual void seek( int s );
    virtual void seekRelative( int s );
    virtual void setEqualizer( int , int , int , int , int , int , int , int , int , int , int  );
    virtual void setEqualizerEnabled( bool active );
    virtual void setEqualizerPreset( QString name );
    virtual void setLyricsByPath( const QString& url, const QString& lyrics );
    virtual void setScore( int score );
    virtual void setScoreByPath( const QString& url, int score );
    virtual void setVolume( int volume );
    virtual void showBrowser( QString browser );
    virtual void showOSD();
    virtual void stop();
    virtual void transferDeviceFiles();
    virtual void volumeDown();
    virtual void volumeUp();
    virtual void transferCliArgs( QStringList args );
protected:
    AmarokPlayerInterface_stub() : DCOPStub( never_use ) {}
};




class AmarokPlaylistInterface_stub : virtual public DCOPStub
{
public:
    AmarokPlaylistInterface_stub( const QCString& app, const QCString& id );
    AmarokPlaylistInterface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit AmarokPlaylistInterface_stub( const DCOPRef& ref );
    virtual int getActiveIndex();
    virtual int getTotalTrackCount();
    virtual QString saveCurrentPlaylist();
    virtual void addMedia( const KURL&  );
    virtual void addMediaList( const KURL::List&  );
    virtual void clearPlaylist();
    virtual void playByIndex( int  );
    virtual void playMedia( const KURL&  );
    virtual void popupMessage( const QString&  );
    virtual void removeCurrentTrack();
    virtual void repopulate();
    virtual void saveM3u( const QString& path, bool relativePaths );
    virtual void setStopAfterCurrent( bool  );
    virtual void shortStatusMessage( const QString&  );
    virtual void shufflePlaylist();
    virtual void togglePlaylist();
protected:
    AmarokPlaylistInterface_stub() : DCOPStub( never_use ) {}
};




class AmarokPlaylistBrowserInterface_stub : virtual public DCOPStub
{
public:
    AmarokPlaylistBrowserInterface_stub( const QCString& app, const QCString& id );
    AmarokPlaylistBrowserInterface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit AmarokPlaylistBrowserInterface_stub( const DCOPRef& ref );
    virtual void addPodcast( const QString&  );
    virtual void scanPodcasts();
    virtual void addPlaylist( const QString&  );
protected:
    AmarokPlaylistBrowserInterface_stub() : DCOPStub( never_use ) {}
};




class AmarokContextBrowserInterface_stub : virtual public DCOPStub
{
public:
    AmarokContextBrowserInterface_stub( const QCString& app, const QCString& id );
    AmarokContextBrowserInterface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit AmarokContextBrowserInterface_stub( const DCOPRef& ref );
    virtual void showHome();
    virtual void showCurrentTrack();
    virtual void showLyrics();
    virtual void showWiki();
protected:
    AmarokContextBrowserInterface_stub() : DCOPStub( never_use ) {}
};




class AmarokCollectionInterface_stub : virtual public DCOPStub
{
public:
    AmarokCollectionInterface_stub( const QCString& app, const QCString& id );
    AmarokCollectionInterface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit AmarokCollectionInterface_stub( const DCOPRef& ref );
    virtual int totalAlbums();
    virtual int totalArtists();
    virtual int totalCompilations();
    virtual int totalGenres();
    virtual int totalTracks();
    virtual QStringList query( const QString& sql );
    virtual QStringList similarArtists( int artists );
    virtual void migrateFile( const QString& oldURL, const QString& newURL );
    virtual void scanCollection();
    virtual void scanCollectionChanges();
protected:
    AmarokCollectionInterface_stub() : DCOPStub( never_use ) {}
};




class AmarokScriptInterface_stub : virtual public DCOPStub
{
public:
    AmarokScriptInterface_stub( const QCString& app, const QCString& id );
    AmarokScriptInterface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit AmarokScriptInterface_stub( const DCOPRef& ref );
    virtual bool runScript( const QString& name );
    virtual bool stopScript( const QString& name );
    virtual QStringList listRunningScripts();
    virtual void addCustomMenuItem( QString submenu, QString itemTitle );
    virtual void removeCustomMenuItem( QString submenu, QString itemTitle );
    virtual QString readConfig( const QString& key );
    virtual QStringList readListConfig( const QString& key );
protected:
    AmarokScriptInterface_stub() : DCOPStub( never_use ) {}
};


#endif
