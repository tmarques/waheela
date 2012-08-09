#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './tagdialogbase.ui'
**
** Created: Fri Mar 23 10:56:58 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "tagdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <klineedit.h>
#include <ktabwidget.h>
#include <qwidget.h>
#include <qframe.h>
#include <kcombobox.h>
#include <knuminput.h>
#include <ktextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "ktabwidget.h"
#include "klineedit.h"
#include "knuminput.h"
#include "ktextedit.h"
#include "kcombobox.h"
#include "coverfetcher.h"
#include "./tagdialogbase.ui.h"
/*
 *  Constructs a TagDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
TagDialogBase::TagDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "TagDialogBase" );
    TagDialogBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "TagDialogBaseLayout"); 

    layout5_3 = new QHBoxLayout( 0, 0, 6, "layout5_3"); 

    pushButton_previous = new QPushButton( this, "pushButton_previous" );
    layout5_3->addWidget( pushButton_previous );

    pushButton_next = new QPushButton( this, "pushButton_next" );
    layout5_3->addWidget( pushButton_next );

    checkBox_perTrack = new QCheckBox( this, "checkBox_perTrack" );
    layout5_3->addWidget( checkBox_perTrack );
    spacer1 = new QSpacerItem( 215, 30, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
    layout5_3->addItem( spacer1 );

    pushButton_ok = new QPushButton( this, "pushButton_ok" );
    pushButton_ok->setAutoDefault( TRUE );
    pushButton_ok->setDefault( TRUE );
    layout5_3->addWidget( pushButton_ok );

    pushButton_cancel = new QPushButton( this, "pushButton_cancel" );
    pushButton_cancel->setAutoMask( FALSE );
    pushButton_cancel->setAutoDefault( TRUE );
    pushButton_cancel->setDefault( FALSE );
    pushButton_cancel->setFlat( FALSE );
    layout5_3->addWidget( pushButton_cancel );

    TagDialogBaseLayout->addLayout( layout5_3, 2, 0 );

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    locationLabel = new QLabel( this, "locationLabel" );
    layout6->addWidget( locationLabel );

    kLineEdit_location = new KLineEdit( this, "kLineEdit_location" );
    kLineEdit_location->setFocusPolicy( KLineEdit::NoFocus );
    kLineEdit_location->setReadOnly( TRUE );
    kLineEdit_location->setEnableSqueezedText( TRUE );
    layout6->addWidget( kLineEdit_location );

    pushButton_open = new QPushButton( this, "pushButton_open" );
    pushButton_open->setAutoDefault( FALSE );
    layout6->addWidget( pushButton_open );

    TagDialogBaseLayout->addLayout( layout6, 1, 0 );

    kTabWidget = new KTabWidget( this, "kTabWidget" );
    kTabWidget->setCurrentPage( 0 );

    summaryTab = new QWidget( kTabWidget, "summaryTab" );
    summaryTabLayout = new QGridLayout( summaryTab, 1, 1, 11, 6, "summaryTabLayout"); 

    pixmap_cover = new CoverLabel( summaryTab, "pixmap_cover" );
    pixmap_cover->setMinimumSize( QSize( 100, 100 ) );
    pixmap_cover->setMaximumSize( QSize( 85, 85 ) );

    summaryTabLayout->addWidget( pixmap_cover, 0, 0 );

    trackArtistAlbumLabel = new QLabel( summaryTab, "trackArtistAlbumLabel" );
    trackArtistAlbumLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter ) );

    summaryTabLayout->addWidget( trackArtistAlbumLabel, 0, 1 );

    line1 = new QFrame( summaryTab, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );

    summaryTabLayout->addMultiCellWidget( line1, 1, 1, 0, 1 );
    spacer12 = new QSpacerItem( 21, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    summaryTabLayout->addItem( spacer12, 3, 1 );

    summaryLabel = new QLabel( summaryTab, "summaryLabel" );
    summaryLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignTop ) );

    summaryTabLayout->addMultiCellWidget( summaryLabel, 2, 2, 0, 1 );

    tagsTab = new QWidget( kTabWidget, "tagsTab" );
    tagsTabLayout = new QGridLayout( tagsTab, 1, 1, 11, 6, "tagsTabLayout"); 

    textLabel1_2 = new QLabel( tagsTab, "textLabel1_2" );

    tagsTabLayout->addWidget( textLabel1_2, 1, 0 );

    textLabel1 = new QLabel( tagsTab, "textLabel1" );

    tagsTabLayout->addWidget( textLabel1, 0, 0 );

    textLabel1_6_6 = new QLabel( tagsTab, "textLabel1_6_6" );
    textLabel1_6_6->setTextFormat( QLabel::PlainText );

    tagsTabLayout->addWidget( textLabel1_6_6, 5, 0 );

    layout14 = new QHBoxLayout( 0, 0, 6, "layout14"); 

    pushButton_guessTags = new QPushButton( tagsTab, "pushButton_guessTags" );
    layout14->addWidget( pushButton_guessTags );

    pushButton_setFilenameSchemes = new QPushButton( tagsTab, "pushButton_setFilenameSchemes" );
    pushButton_setFilenameSchemes->setAutoDefault( FALSE );
    layout14->addWidget( pushButton_setFilenameSchemes );

    tagsTabLayout->addLayout( layout14, 8, 1 );

    textLabel_comment = new QLabel( tagsTab, "textLabel_comment" );
    textLabel_comment->setTextFormat( QLabel::PlainText );

    tagsTabLayout->addWidget( textLabel_comment, 6, 0 );

    pushButton_musicbrainz = new QPushButton( tagsTab, "pushButton_musicbrainz" );

    tagsTabLayout->addWidget( pushButton_musicbrainz, 7, 1 );

    textLabel1_4 = new QLabel( tagsTab, "textLabel1_4" );

    tagsTabLayout->addWidget( textLabel1_4, 4, 0 );

    kComboBox_genre = new KComboBox( FALSE, tagsTab, "kComboBox_genre" );
    kComboBox_genre->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_genre->sizePolicy().hasHeightForWidth() ) );
    kComboBox_genre->setEditable( TRUE );
    kComboBox_genre->setAutoCompletion( FALSE );

    tagsTabLayout->addWidget( kComboBox_genre, 4, 1 );

    kLineEdit_title = new KLineEdit( tagsTab, "kLineEdit_title" );

    tagsTabLayout->addWidget( kLineEdit_title, 0, 1 );

    layout5_2 = new QHBoxLayout( 0, 0, 6, "layout5_2"); 

    kIntSpinBox_track = new KIntSpinBox( tagsTab, "kIntSpinBox_track" );
    kIntSpinBox_track->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_track->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_track->setMaxValue( 3000 );
    kIntSpinBox_track->setValue( 0 );
    layout5_2->addWidget( kIntSpinBox_track );

    textLabel1_5 = new QLabel( tagsTab, "textLabel1_5" );
    layout5_2->addWidget( textLabel1_5 );

    kIntSpinBox_year = new KIntSpinBox( tagsTab, "kIntSpinBox_year" );
    kIntSpinBox_year->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_year->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_year->setMaxValue( 3000 );
    kIntSpinBox_year->setValue( 0 );
    layout5_2->addWidget( kIntSpinBox_year );

    tagsTabLayout->addLayout( layout5_2, 5, 1 );

    kTextEdit_comment = new KTextEdit( tagsTab, "kTextEdit_comment" );
    kTextEdit_comment->setTextFormat( KTextEdit::AutoText );
    kTextEdit_comment->setTabChangesFocus( TRUE );

    tagsTabLayout->addWidget( kTextEdit_comment, 6, 1 );

    textLabel1_3 = new QLabel( tagsTab, "textLabel1_3" );

    tagsTabLayout->addWidget( textLabel1_3, 3, 0 );

    textLabel1_3_2 = new QLabel( tagsTab, "textLabel1_3_2" );

    tagsTabLayout->addWidget( textLabel1_3_2, 2, 0 );

    layout11 = new QHBoxLayout( 0, 0, 6, "layout11"); 

    kComboBox_album = new KComboBox( FALSE, tagsTab, "kComboBox_album" );
    kComboBox_album->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_album->sizePolicy().hasHeightForWidth() ) );
    kComboBox_album->setEditable( TRUE );
    kComboBox_album->setAutoCompletion( FALSE );
    layout11->addWidget( kComboBox_album );

    textLabel1_3_2_2 = new QLabel( tagsTab, "textLabel1_3_2_2" );
    layout11->addWidget( textLabel1_3_2_2 );

    kIntSpinBox_discNumber = new KIntSpinBox( tagsTab, "kIntSpinBox_discNumber" );
    kIntSpinBox_discNumber->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_discNumber->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_discNumber->setMinimumSize( QSize( 50, 0 ) );
    kIntSpinBox_discNumber->setMaximumSize( QSize( 100, 32767 ) );
    kIntSpinBox_discNumber->setMaxValue( 3000 );
    kIntSpinBox_discNumber->setValue( 0 );
    layout11->addWidget( kIntSpinBox_discNumber );

    tagsTabLayout->addLayout( layout11, 3, 1 );

    kComboBox_composer = new KComboBox( FALSE, tagsTab, "kComboBox_composer" );
    kComboBox_composer->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_composer->sizePolicy().hasHeightForWidth() ) );
    kComboBox_composer->setEditable( TRUE );

    tagsTabLayout->addWidget( kComboBox_composer, 2, 1 );

    kComboBox_artist = new KComboBox( FALSE, tagsTab, "kComboBox_artist" );
    kComboBox_artist->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_artist->sizePolicy().hasHeightForWidth() ) );
    kComboBox_artist->setEditable( TRUE );
    kComboBox_artist->setAutoCompletion( FALSE );

    tagsTabLayout->addWidget( kComboBox_artist, 1, 1 );

    lyricsTab = new QWidget( kTabWidget, "lyricsTab" );
    lyricsTabLayout = new QHBoxLayout( lyricsTab, 11, 6, "lyricsTabLayout"); 

    kTextEdit_lyrics = new KTextEdit( lyricsTab, "kTextEdit_lyrics" );
    kTextEdit_lyrics->setTextFormat( KTextEdit::PlainText );
    kTextEdit_lyrics->setTabChangesFocus( TRUE );
    lyricsTabLayout->addWidget( kTextEdit_lyrics );

    statisticsTab = new QWidget( kTabWidget, "statisticsTab" );
    statisticsTabLayout = new QGridLayout( statisticsTab, 1, 1, 11, 6, "statisticsTabLayout"); 

    trackArtistAlbumLabel2 = new QLabel( statisticsTab, "trackArtistAlbumLabel2" );
    trackArtistAlbumLabel2->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter ) );

    statisticsTabLayout->addWidget( trackArtistAlbumLabel2, 0, 0 );
    spacer3_2 = new QSpacerItem( 20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding );
    statisticsTabLayout->addItem( spacer3_2, 4, 2 );

    statisticsLabel = new QLabel( statisticsTab, "statisticsLabel" );
    statisticsLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignTop ) );

    statisticsTabLayout->addMultiCellWidget( statisticsLabel, 3, 3, 0, 2 );
    spacer5 = new QSpacerItem( 431, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    statisticsTabLayout->addItem( spacer5, 2, 0 );

    scoreLabel = new QLabel( statisticsTab, "scoreLabel" );

    statisticsTabLayout->addWidget( scoreLabel, 0, 1 );

    ratingLabel = new QLabel( statisticsTab, "ratingLabel" );

    statisticsTabLayout->addWidget( ratingLabel, 1, 1 );

    kIntSpinBox_score = new KIntSpinBox( statisticsTab, "kIntSpinBox_score" );
    kIntSpinBox_score->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_score->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_score->setMaxValue( 100 );
    kIntSpinBox_score->setValue( 0 );

    statisticsTabLayout->addWidget( kIntSpinBox_score, 0, 2 );

    kComboBox_rating = new KComboBox( FALSE, statisticsTab, "kComboBox_rating" );

    statisticsTabLayout->addWidget( kComboBox_rating, 1, 2 );

    TagDialogBaseLayout->addWidget( kTabWidget, 0, 0 );
    languageChange();
    resize( QSize(741, 527).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( kTabWidget, kLineEdit_title );
    setTabOrder( kLineEdit_title, kComboBox_artist );
    setTabOrder( kComboBox_artist, kComboBox_composer );
    setTabOrder( kComboBox_composer, kComboBox_album );
    setTabOrder( kComboBox_album, kIntSpinBox_discNumber );
    setTabOrder( kIntSpinBox_discNumber, kComboBox_genre );
    setTabOrder( kComboBox_genre, kIntSpinBox_track );
    setTabOrder( kIntSpinBox_track, kIntSpinBox_year );
    setTabOrder( kIntSpinBox_year, kTextEdit_comment );
    setTabOrder( kTextEdit_comment, pushButton_musicbrainz );
    setTabOrder( pushButton_musicbrainz, pushButton_guessTags );
    setTabOrder( pushButton_guessTags, pushButton_setFilenameSchemes );
    setTabOrder( pushButton_setFilenameSchemes, kTextEdit_lyrics );
    setTabOrder( kTextEdit_lyrics, kIntSpinBox_score );
    setTabOrder( kIntSpinBox_score, kComboBox_rating );
    setTabOrder( kComboBox_rating, pushButton_open );
    setTabOrder( pushButton_open, pushButton_previous );
    setTabOrder( pushButton_previous, pushButton_next );
    setTabOrder( pushButton_next, checkBox_perTrack );
    setTabOrder( checkBox_perTrack, pushButton_ok );
    setTabOrder( pushButton_ok, pushButton_cancel );

    // buddies
    textLabel1_2->setBuddy( kComboBox_artist );
    textLabel1->setBuddy( kLineEdit_title );
    textLabel1_6_6->setBuddy( kIntSpinBox_track );
    textLabel_comment->setBuddy( kTextEdit_comment );
    textLabel1_4->setBuddy( kComboBox_genre );
    textLabel1_5->setBuddy( kIntSpinBox_year );
    textLabel1_3->setBuddy( kComboBox_album );
    textLabel1_3_2->setBuddy( kComboBox_composer );
    textLabel1_3_2_2->setBuddy( kIntSpinBox_discNumber );
}

/*
 *  Destroys the object and frees any allocated resources
 */
TagDialogBase::~TagDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TagDialogBase::languageChange()
{
    setCaption( tr2i18n( "Track Information" ) );
    pushButton_previous->setText( tr2i18n( "&Previous" ) );
    pushButton_next->setText( tr2i18n( "&Next" ) );
    checkBox_perTrack->setText( tr2i18n( "Per Trac&k" ) );
    pushButton_ok->setText( tr2i18n( "Sa&ve && Close" ) );
    pushButton_cancel->setText( tr2i18n( "&Cancel" ) );
    locationLabel->setText( tr2i18n( "Location:" ) );
    pushButton_open->setText( QString::null );
    trackArtistAlbumLabel->setText( tr2i18n( "Track by Artist on Album" ) );
    summaryLabel->setText( QString::null );
    textLabel1_2->setText( tr2i18n( "&Artist:" ) );
    textLabel1->setText( tr2i18n( "T&itle:" ) );
    textLabel1_6_6->setText( tr2i18n( "Trac&k:" ) );
    pushButton_guessTags->setText( tr2i18n( "Guess Tags From &Filename" ) );
    pushButton_setFilenameSchemes->setText( tr2i18n( "Filename &Schemes" ) );
    textLabel_comment->setText( tr2i18n( "Co&mment:" ) );
    pushButton_musicbrainz->setText( tr2i18n( "Fill-In Tags Using MusicBrain&z" ) );
    textLabel1_4->setText( tr2i18n( "&Genre:" ) );
    kIntSpinBox_track->setSpecialValueText( QString::null );
    textLabel1_5->setText( tr2i18n( "&Year:" ) );
    kIntSpinBox_year->setSpecialValueText( QString::null );
    kTextEdit_comment->setText( QString::null );
    textLabel1_3->setText( tr2i18n( "Al&bum:" ) );
    textLabel1_3_2->setText( tr2i18n( "&Composer:" ) );
    textLabel1_3_2_2->setText( tr2i18n( "&Disc Number:" ) );
    kIntSpinBox_discNumber->setSpecialValueText( QString::null );
    kTextEdit_lyrics->setText( QString::null );
    trackArtistAlbumLabel2->setText( tr2i18n( "Track by Artist on Album" ) );
    statisticsLabel->setText( QString::null );
    scoreLabel->setText( tr2i18n( "Score:" ) );
    ratingLabel->setText( tr2i18n( "Rating:" ) );
    kIntSpinBox_score->setSpecialValueText( QString::null );
}

#include "tagdialogbase.moc"
