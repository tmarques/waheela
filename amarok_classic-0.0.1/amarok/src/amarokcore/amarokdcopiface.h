/***************************************************************************
                          amarokdcopiface.h  -  DCOP Interface
                             -------------------
    begin                : Sat Oct 11 2003
    copyright            : (C) 2003 by Stanislav Karchebny
                           (C) 2005 Ian Monroe
                           (C) 2005 Seb Ruiz
    email                : berkus@users.sf.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef AMAROK_DCOPIFACE_H
#define AMAROK_DCOPIFACE_H

#include <dcopobject.h>
#include <kurl.h>
#include <qstringlist.h>

///////////////////////////////////////////////////////////////////////
// WARNING! Please ask on #amarok before modifying the DCOP interface!
///////////////////////////////////////////////////////////////////////


class AmarokPlayerInterface : virtual public DCOPObject
{
   K_DCOP

k_dcop:

   virtual bool dynamicModeStatus() = 0;                    ///< Return dynamic mode status.
   virtual bool equalizerEnabled() = 0;                     ///< Return the equalizer status.
   virtual bool isPlaying() = 0;                            ///< Return true if something is playing now.
   virtual bool randomModeStatus() = 0;                     ///< Return random mode status.
   virtual bool repeatPlaylistStatus() = 0;                 ///< Return repeat playlist status.
   virtual bool repeatTrackStatus() = 0;                    ///< Return repeat track status.
   virtual int  getVolume() = 0;                            ///< Return volume in range 0-100%.
   virtual int  sampleRate() = 0;                           ///< Return the sample rate of the currently playing track.
   virtual int  score() = 0;                                ///< Return the score of the currently playing track.
   virtual int  status() = 0;                               ///< Return playback status: 0 - stopped, 1 - paused, 2 - playing. < 0 - error
   virtual int  trackCurrentTime() = 0;                     ///< Return current play position in seconds.
   virtual int  trackPlayCounter() = 0;                     ///< Return play counter for current song.
   virtual int  trackTotalTime() = 0;                       ///< Return track length in seconds.

   /* New player API */
   virtual QString album() = 0;                             ///< Return the album of the currently playing track.
   virtual QString artist() = 0;                            ///< Return the artist of the currently playing track.
   virtual QString bitrate() = 0;                           ///< Return the bitrate of the currently playing track (XX kbps).
   virtual QString comment() = 0;                           ///< Return the comment of the currently playing track.
   virtual QString coverImage() = 0;                        ///< Return the encoded URL of the current track's cover image
   virtual QString currentTime() = 0;                       ///< Return the position of the currently playing track ([h:]mm:ss format).
   virtual QString encodedURL() = 0;                        ///< Return the encoded URL of the currently playing track.
   virtual QString engine() = 0;                        ///<Return the current sound engine.
   virtual QString genre() = 0;                             ///< Return the genre of the currently playing track.
   virtual QString lyrics() = 0;                            ///< Return the lyrics of the currently playing track.
   virtual QString lyricsByPath( QString path ) = 0;        ///< Return the lyrics of a track by path.

   /* Compatibility method (used by mediacontrol as well). DO NOT TOUCH! */
   virtual QString nowPlaying() = 0;                        ///< The title of now playing media.
   virtual QString path() = 0;                              ///< Return the unencoded path of the currently playing track.
   virtual QString setContextStyle(const QString& ) = 0;     ///< Set the CSS style for the context browser
   virtual QString title() = 0;                             ///< Return the title of the currently playing track.
   virtual QString totalTime() = 0;                         ///< Return the total length of the currently playing track ([h:]mm:ss format).
   virtual QString track() = 0;                             ///< Return the track number.
   virtual QString type() = 0;                             ///< Return the file type.
   virtual QString year() = 0;                              ///< Return the year of the currently playing track.
   virtual void configEqualizer() = 0;                      ///< Toggle equalizer config dialog.
   virtual void enableDynamicMode(bool enable) = 0;         ///< Switch Dynamic Mode on or off.
   virtual void enableOSD(bool enable) = 0;                 ///< Switch OSD display on or off.
   virtual void enableRandomMode(bool enable) = 0;          ///< Switch Random Mode on or off.
   virtual void enableRepeatPlaylist(bool enable) = 0;      ///< Switch Repeat Playlist on or off.
   virtual void enableRepeatTrack(bool enable) = 0;         ///< Switch Repeat Track on or off.
   virtual void mediaDeviceMount() = 0;               ///< Sets the command used for mounting media device.
   virtual void mediaDeviceUmount() = 0;             ///< Sets the comment used for umounting media device.
   virtual void mute() = 0;                                 ///< Toggle mute.
   virtual void next() = 0;                                 ///< Equivalent to pressing "Next" button.
   virtual void pause() = 0;                                ///< Equivalent to pressing "Pause" button.
   virtual void play() = 0;                                 ///< Equivalent to pressing "Play" button.
   virtual void playPause() = 0;                            ///< Toggle play/pause state (good for mm keyboard users)
   virtual void prev() = 0;                                 ///< Equivalent to pressing "Prev" button.
   virtual void queueForTransfer( KURL url ) = 0;           ///< Queue file for transfer to Media Device.
   virtual void seek(int s) = 0;                            ///< Seek track to seconds position.
   virtual void seekRelative(int s) = 0;                    ///< Seek to a position relative to the current track position.
   virtual void setEqualizer(int, int, int, int, int, int, int, int, int, int, int) = 0;  ///< Set the equalizer bands
   virtual void setEqualizerEnabled( bool active ) = 0;     ///< Toggle equalizer.
   virtual void setEqualizerPreset( QString name ) = 0;     ///< Set the equalizer preset
   virtual void setLyricsByPath( const QString& url, const QString& lyrics ) = 0;   ///< Set the lyrics of a track by it's path.
   virtual void setScore( int score ) = 0;                  ///< Set the score of the currently playing track.
   virtual void setScoreByPath( const QString &url, int score ) = 0;  ///< Set the score of a track by it's path.
   virtual void setVolume(int volume) = 0;                  ///< Set volume in range 0-100%.
   virtual void showBrowser( QString browser ) = 0;   ///<Shows browsers in the playlist window.
   virtual void showOSD() = 0;                              ///< Show the OSD display on the screen.
   virtual void stop() = 0;                                 ///< Equivalent to pressing "Stop" button.
   virtual void transferDeviceFiles() = 0;                  ///< Transfer files to media device.
   virtual void volumeDown() = 0;                           ///< Decrease volume by a reasonable step.
   virtual void volumeUp() = 0;                             ///< Increase volume by a reasonable step.
   virtual void transferCliArgs( QStringList args ) = 0;
};


class AmarokPlaylistInterface : virtual public DCOPObject
{
   K_DCOP

k_dcop:

   virtual int  getActiveIndex() = 0;                       ///< Return the index of the currently active track. -1 if none.
   virtual int  getTotalTrackCount() = 0;                   ///< Return number of tracks in playlist. 0 if none.
   virtual QString saveCurrentPlaylist() = 0;               ///< Saves the current playlist to current.xml and returns its path.

   /* These two methods are used by mediacontrol. DO NOT TOUCH! */
   virtual void addMedia(const KURL &) = 0;                 ///< Add audio media specified by the url.
   virtual void addMediaList(const KURL::List &) = 0;       ///< Add some audio media specified by the url.
   virtual void clearPlaylist() = 0;                        ///< Clears the playlist.
   virtual void playByIndex(int) = 0;                       ///< Starts playing the track at the specified index.
   virtual void playMedia(const KURL &) = 0;                ///< Add audio media specified by the url.
   virtual void popupMessage(const QString&) = 0;           ///< Shows a temporary popup message.
   virtual void removeCurrentTrack() = 0;                   ///< Removes the current-track item from the playlist.
   virtual void repopulate() = 0;               ///< Repopulate the playlist with random tracks.
   virtual void saveM3u(const QString& path, bool relativePaths) = 0;  ///< Saves the current playlist as m3u.
                                                            ///< path = path for saving,  relativePaths = whether to write relative paths.
   virtual void setStopAfterCurrent( bool ) = 0;            ///< Enables/disables the "Stop After Current Track" feature.
   virtual void shortStatusMessage(const QString&) = 0;     ///< Shows a temporary message on the statusbar.
   virtual void shufflePlaylist() = 0;                      ///< Shuffles the playlist.
   virtual void togglePlaylist() = 0;                       ///< Toggle the Playlist-window.
};

class AmarokPlaylistBrowserInterface : virtual public DCOPObject
{
   K_DCOP

k_dcop:
   virtual void addPodcast(const QString &) = 0;            ///< Add a podcast entry to the playlist browser.
   virtual void scanPodcasts() = 0;                         ///< Scan all podcasts for updates.
   virtual void addPlaylist(const QString &) = 0;           ///< Add a playlist to the playlist browser.
};

class AmarokContextBrowserInterface : virtual public DCOPObject
{
   K_DCOP

k_dcop:
   virtual void showHome() = 0;                             ///< Show the home tab in the context browser.
   virtual void showCurrentTrack() = 0;                     ///< Show the current track in the context browser.
   virtual void showLyrics() = 0;                           ///< Show the lyrics tab in the context browser.
   virtual void showWiki() = 0;                             ///< Show the wikipedia tab in the context browser.
};

class AmarokCollectionInterface : virtual public DCOPObject
{
   K_DCOP

k_dcop:
   virtual int totalAlbums() = 0;                       ///< Returns the total of albums in the collection.
   virtual int totalArtists() = 0;                       ///< Returns the total of artists in the collection.
   virtual int totalCompilations() = 0;                       ///< Returns the total of compilations in the collection.
   virtual int totalGenres() = 0;                       ///< Returns the total of genres in the collection.
   virtual int totalTracks() = 0;                       ///< Returns the total of tracks in the collection.
   virtual QStringList query(const QString& sql) = 0;       ///< Queries the database via SQL.
   virtual QStringList similarArtists( int artists ) = 0;       ///< Return similar artists of the current tracks, limit to int artists.
   virtual void migrateFile( const QString &oldURL, const QString &newURL ) = 0; ///<Move a file in the collection, keeping stats intact.
   virtual void scanCollection() = 0;                       ///< Scan the collection.
   virtual void scanCollectionChanges() = 0;                ///< Scan the collection for changes only.
};


class AmarokScriptInterface : virtual public DCOPObject
{
   K_DCOP

k_dcop:
   virtual bool runScript(const QString& name) = 0;         ///< Starts the script with the given name. Returns true on success.
   virtual bool stopScript(const QString& name) = 0;        ///< Stops the script with the given name. Returns true on success.
   virtual QStringList listRunningScripts() = 0;            ///< Returns a list of all currently running scripts.
   virtual void addCustomMenuItem(QString submenu, QString itemTitle ) = 0;  ///< Enables and sets custom menu item title.
   virtual void removeCustomMenuItem(QString submenu, QString itemTitle ) = 0;  ///< Removes the custom menu item.
   virtual QString readConfig(const QString& key) = 0; ///< returns a AmarokConfig configuration entry value from the given key
   virtual QStringList readListConfig(const QString& key) = 0; ///< AmarokConfig lists must use this function

};


#endif
