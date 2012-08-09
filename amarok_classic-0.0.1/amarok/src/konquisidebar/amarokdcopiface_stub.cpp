/****************************************************************************
**
** DCOP Stub Implementation created by dcopidl2cpp from amarokdcopiface.kidl
**
** WARNING! All changes made in this file will be lost!
**
*****************************************************************************/

#include "amarokdcopiface_stub.h"
#include <dcopclient.h>

#include <kdatastream.h>


AmarokPlayerInterface_stub::AmarokPlayerInterface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

AmarokPlayerInterface_stub::AmarokPlayerInterface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

AmarokPlayerInterface_stub::AmarokPlayerInterface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

bool AmarokPlayerInterface_stub::dynamicModeStatus()
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "dynamicModeStatus()", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

bool AmarokPlayerInterface_stub::equalizerEnabled()
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "equalizerEnabled()", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

bool AmarokPlayerInterface_stub::isPlaying()
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "isPlaying()", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

bool AmarokPlayerInterface_stub::randomModeStatus()
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "randomModeStatus()", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

bool AmarokPlayerInterface_stub::repeatPlaylistStatus()
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "repeatPlaylistStatus()", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

bool AmarokPlayerInterface_stub::repeatTrackStatus()
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "repeatTrackStatus()", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::getVolume()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "getVolume()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::sampleRate()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "sampleRate()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::score()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "score()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::status()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "status()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::trackCurrentTime()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "trackCurrentTime()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::trackPlayCounter()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "trackPlayCounter()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlayerInterface_stub::trackTotalTime()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "trackTotalTime()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::album()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "album()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::artist()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "artist()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::bitrate()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "bitrate()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::comment()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "comment()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::coverImage()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "coverImage()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::currentTime()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "currentTime()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::encodedURL()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "encodedURL()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::engine()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "engine()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::genre()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "genre()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::lyrics()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "lyrics()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::lyricsByPath( QString arg0 )
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "lyricsByPath(QString)", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::nowPlaying()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "nowPlaying()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::path()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "path()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::setContextStyle( const QString& arg0 )
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setContextStyle(QString)", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::title()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "title()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::totalTime()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "totalTime()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::track()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "track()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::type()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "type()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlayerInterface_stub::year()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "year()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

void AmarokPlayerInterface_stub::configEqualizer()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "configEqualizer()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::enableDynamicMode( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "enableDynamicMode(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::enableOSD( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "enableOSD(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::enableRandomMode( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "enableRandomMode(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::enableRepeatPlaylist( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "enableRepeatPlaylist(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::enableRepeatTrack( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "enableRepeatTrack(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::mediaDeviceMount()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "mediaDeviceMount()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::mediaDeviceUmount()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "mediaDeviceUmount()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::mute()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "mute()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::next()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "next()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::pause()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "pause()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::play()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "play()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::playPause()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "playPause()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::prev()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "prev()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::queueForTransfer( KURL arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "queueForTransfer(KURL)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::seek( int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "seek(int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::seekRelative( int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "seekRelative(int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setEqualizer( int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    arg << arg2;
    arg << arg3;
    arg << arg4;
    arg << arg5;
    arg << arg6;
    arg << arg7;
    arg << arg8;
    arg << arg9;
    arg << arg10;
    if ( dcopClient()->call( app(), obj(), "setEqualizer(int,int,int,int,int,int,int,int,int,int,int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setEqualizerEnabled( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setEqualizerEnabled(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setEqualizerPreset( QString arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setEqualizerPreset(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setLyricsByPath( const QString& arg0, const QString& arg1 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "setLyricsByPath(QString,QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setScore( int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setScore(int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setScoreByPath( const QString& arg0, int arg1 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "setScoreByPath(QString,int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::setVolume( int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setVolume(int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::showBrowser( QString arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "showBrowser(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::showOSD()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "showOSD()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::stop()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "stop()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::transferDeviceFiles()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "transferDeviceFiles()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::volumeDown()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "volumeDown()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::volumeUp()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "volumeUp()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlayerInterface_stub::transferCliArgs( QStringList arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "transferCliArgs(QStringList)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}




AmarokPlaylistInterface_stub::AmarokPlaylistInterface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

AmarokPlaylistInterface_stub::AmarokPlaylistInterface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

AmarokPlaylistInterface_stub::AmarokPlaylistInterface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

int AmarokPlaylistInterface_stub::getActiveIndex()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "getActiveIndex()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokPlaylistInterface_stub::getTotalTrackCount()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "getTotalTrackCount()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QString AmarokPlaylistInterface_stub::saveCurrentPlaylist()
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "saveCurrentPlaylist()", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

void AmarokPlaylistInterface_stub::addMedia( const KURL& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "addMedia(KURL)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::addMediaList( const KURL::List& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "addMediaList(KURL::List)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::clearPlaylist()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "clearPlaylist()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::playByIndex( int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "playByIndex(int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::playMedia( const KURL& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "playMedia(KURL)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::popupMessage( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "popupMessage(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::removeCurrentTrack()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "removeCurrentTrack()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::repopulate()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "repopulate()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::saveM3u( const QString& arg0, bool arg1 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "saveM3u(QString,bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::setStopAfterCurrent( bool arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setStopAfterCurrent(bool)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::shortStatusMessage( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "shortStatusMessage(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::shufflePlaylist()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "shufflePlaylist()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistInterface_stub::togglePlaylist()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "togglePlaylist()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}




AmarokPlaylistBrowserInterface_stub::AmarokPlaylistBrowserInterface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

AmarokPlaylistBrowserInterface_stub::AmarokPlaylistBrowserInterface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

AmarokPlaylistBrowserInterface_stub::AmarokPlaylistBrowserInterface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

void AmarokPlaylistBrowserInterface_stub::addPodcast( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "addPodcast(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistBrowserInterface_stub::scanPodcasts()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "scanPodcasts()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokPlaylistBrowserInterface_stub::addPlaylist( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "addPlaylist(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}




AmarokContextBrowserInterface_stub::AmarokContextBrowserInterface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

AmarokContextBrowserInterface_stub::AmarokContextBrowserInterface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

AmarokContextBrowserInterface_stub::AmarokContextBrowserInterface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

void AmarokContextBrowserInterface_stub::showHome()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "showHome()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokContextBrowserInterface_stub::showCurrentTrack()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "showCurrentTrack()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokContextBrowserInterface_stub::showLyrics()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "showLyrics()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokContextBrowserInterface_stub::showWiki()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "showWiki()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}




AmarokCollectionInterface_stub::AmarokCollectionInterface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

AmarokCollectionInterface_stub::AmarokCollectionInterface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

AmarokCollectionInterface_stub::AmarokCollectionInterface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

int AmarokCollectionInterface_stub::totalAlbums()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "totalAlbums()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokCollectionInterface_stub::totalArtists()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "totalArtists()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokCollectionInterface_stub::totalCompilations()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "totalCompilations()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokCollectionInterface_stub::totalGenres()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "totalGenres()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int AmarokCollectionInterface_stub::totalTracks()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "totalTracks()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QStringList AmarokCollectionInterface_stub::query( const QString& arg0 )
{
    QStringList result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "query(QString)", data, replyType, replyData ) ) {
	if ( replyType == "QStringList" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QStringList AmarokCollectionInterface_stub::similarArtists( int arg0 )
{
    QStringList result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "similarArtists(int)", data, replyType, replyData ) ) {
	if ( replyType == "QStringList" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

void AmarokCollectionInterface_stub::migrateFile( const QString& arg0, const QString& arg1 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "migrateFile(QString,QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokCollectionInterface_stub::scanCollection()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "scanCollection()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokCollectionInterface_stub::scanCollectionChanges()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "scanCollectionChanges()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}




AmarokScriptInterface_stub::AmarokScriptInterface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

AmarokScriptInterface_stub::AmarokScriptInterface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

AmarokScriptInterface_stub::AmarokScriptInterface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

bool AmarokScriptInterface_stub::runScript( const QString& arg0 )
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "runScript(QString)", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

bool AmarokScriptInterface_stub::stopScript( const QString& arg0 )
{
    bool result = false;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "stopScript(QString)", data, replyType, replyData ) ) {
	if ( replyType == "bool" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QStringList AmarokScriptInterface_stub::listRunningScripts()
{
    QStringList result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "listRunningScripts()", data, replyType, replyData ) ) {
	if ( replyType == "QStringList" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

void AmarokScriptInterface_stub::addCustomMenuItem( QString arg0, QString arg1 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "addCustomMenuItem(QString,QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void AmarokScriptInterface_stub::removeCustomMenuItem( QString arg0, QString arg1 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "removeCustomMenuItem(QString,QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

QString AmarokScriptInterface_stub::readConfig( const QString& arg0 )
{
    QString result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "readConfig(QString)", data, replyType, replyData ) ) {
	if ( replyType == "QString" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

QStringList AmarokScriptInterface_stub::readListConfig( const QString& arg0 )
{
    QStringList result;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "readListConfig(QString)", data, replyType, replyData ) ) {
	if ( replyType == "QStringList" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}


