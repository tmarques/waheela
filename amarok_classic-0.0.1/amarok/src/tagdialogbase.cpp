#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './tagdialogbase.ui'
**
** Created: Ter Fev 19 16:01:50 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "tagdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <klineedit.h>
#include <kcombobox.h>
#include <qframe.h>
#include <knuminput.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "klineedit.h"
#include "kcombobox.h"
#include "knuminput.h"

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
    spacer3 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Minimum );
    TagDialogBaseLayout->addItem( spacer3, 1, 0 );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    pushButton_previous = new QPushButton( this, "pushButton_previous" );
    layout5->addWidget( pushButton_previous );

    pushButton_next = new QPushButton( this, "pushButton_next" );
    layout5->addWidget( pushButton_next );
    spacer1 = new QSpacerItem( 99, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
    layout5->addItem( spacer1 );

    pushButton_ok = new QPushButton( this, "pushButton_ok" );
    pushButton_ok->setAutoDefault( TRUE );
    pushButton_ok->setDefault( TRUE );
    layout5->addWidget( pushButton_ok );

    pushButton_cancel = new QPushButton( this, "pushButton_cancel" );
    pushButton_cancel->setAutoMask( FALSE );
    pushButton_cancel->setAutoDefault( TRUE );
    pushButton_cancel->setDefault( FALSE );
    pushButton_cancel->setFlat( FALSE );
    layout5->addWidget( pushButton_cancel );

    TagDialogBaseLayout->addLayout( layout5, 2, 0 );

    layout8 = new QGridLayout( 0, 1, 1, 0, 6, "layout8"); 

    textLabel1_3 = new QLabel( this, "textLabel1_3" );

    layout8->addWidget( textLabel1_3, 2, 0 );

    layout5_2 = new QHBoxLayout( 0, 0, 6, "layout5_2"); 

    kLineEdit_bitrate = new KLineEdit( this, "kLineEdit_bitrate" );
    kLineEdit_bitrate->setReadOnly( TRUE );
    layout5_2->addWidget( kLineEdit_bitrate );

    samplerateLabel = new QLabel( this, "samplerateLabel" );
    layout5_2->addWidget( samplerateLabel );

    kLineEdit_samplerate = new KLineEdit( this, "kLineEdit_samplerate" );
    kLineEdit_samplerate->setReadOnly( TRUE );
    layout5_2->addWidget( kLineEdit_samplerate );

    layout8->addLayout( layout5_2, 11, 1 );

    kLineEdit_title = new KLineEdit( this, "kLineEdit_title" );

    layout8->addMultiCellWidget( kLineEdit_title, 0, 0, 1, 2 );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );

    layout8->addWidget( textLabel1_2, 1, 0 );

    kComboBox_genre = new KComboBox( FALSE, this, "kComboBox_genre" );
    kComboBox_genre->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_genre->sizePolicy().hasHeightForWidth() ) );
    kComboBox_genre->setEditable( TRUE );
    kComboBox_genre->setAutoCompletion( TRUE );

    layout8->addMultiCellWidget( kComboBox_genre, 3, 3, 1, 2 );

    kLineEdit_playcount = new KLineEdit( this, "kLineEdit_playcount" );
    kLineEdit_playcount->setFrameShadow( KLineEdit::Sunken );
    kLineEdit_playcount->setReadOnly( TRUE );

    layout8->addWidget( kLineEdit_playcount, 9, 1 );

    line1 = new QFrame( this, "line1" );
    line1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, line1->sizePolicy().hasHeightForWidth() ) );
    line1->setMinimumSize( QSize( 0, 16 ) );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setLineWidth( 1 );
    line1->setFrameShape( QFrame::HLine );

    layout8->addMultiCellWidget( line1, 7, 7, 0, 2 );

    pixmap_cover = new QLabel( this, "pixmap_cover" );
    pixmap_cover->setMinimumSize( QSize( 85, 85 ) );
    pixmap_cover->setMaximumSize( QSize( 85, 85 ) );
    pixmap_cover->setScaledContents( TRUE );

    layout8->addMultiCellWidget( pixmap_cover, 9, 11, 2, 2 );

    textLabel1_4 = new QLabel( this, "textLabel1_4" );

    layout8->addWidget( textLabel1_4, 3, 0 );

    lengthLabel = new QLabel( this, "lengthLabel" );

    layout8->addWidget( lengthLabel, 10, 0 );

    layout5_3 = new QHBoxLayout( 0, 0, 6, "layout5_3"); 

    kIntSpinBox_track = new KIntSpinBox( this, "kIntSpinBox_track" );
    kIntSpinBox_track->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_track->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_track->setMaxValue( 3000 );
    kIntSpinBox_track->setValue( 0 );
    layout5_3->addWidget( kIntSpinBox_track );

    textLabel1_5 = new QLabel( this, "textLabel1_5" );
    layout5_3->addWidget( textLabel1_5 );

    kIntSpinBox_year = new KIntSpinBox( this, "kIntSpinBox_year" );
    kIntSpinBox_year->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_year->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_year->setMaxValue( 3000 );
    kIntSpinBox_year->setValue( 0 );
    layout5_3->addWidget( kIntSpinBox_year );

    textLabel1_6 = new QLabel( this, "textLabel1_6" );
    layout5_3->addWidget( textLabel1_6 );

    kIntSpinBox_score = new KIntSpinBox( this, "kIntSpinBox_score" );
    kIntSpinBox_score->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kIntSpinBox_score->sizePolicy().hasHeightForWidth() ) );
    kIntSpinBox_score->setMaxValue( 100 );
    kIntSpinBox_score->setValue( 0 );
    layout5_3->addWidget( kIntSpinBox_score );

    layout8->addMultiCellLayout( layout5_3, 4, 4, 1, 2 );

    kComboBox_album = new KComboBox( FALSE, this, "kComboBox_album" );
    kComboBox_album->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_album->sizePolicy().hasHeightForWidth() ) );
    kComboBox_album->setEditable( TRUE );
    kComboBox_album->setAutoCompletion( TRUE );

    layout8->addMultiCellWidget( kComboBox_album, 2, 2, 1, 2 );

    kLineEdit_comment = new KLineEdit( this, "kLineEdit_comment" );

    layout8->addMultiCellWidget( kLineEdit_comment, 5, 5, 1, 2 );

    bitrateLabel = new QLabel( this, "bitrateLabel" );

    layout8->addWidget( bitrateLabel, 11, 0 );

    textLabel1_6_6 = new QLabel( this, "textLabel1_6_6" );
    textLabel1_6_6->setTextFormat( QLabel::PlainText );

    layout8->addWidget( textLabel1_6_6, 4, 0 );

    layout17 = new QHBoxLayout( 0, 0, 6, "layout17"); 

    kLineEdit_location = new KLineEdit( this, "kLineEdit_location" );
    kLineEdit_location->setReadOnly( TRUE );
    kLineEdit_location->setEnableSqueezedText( TRUE );
    layout17->addWidget( kLineEdit_location );

    pushButton_open = new QPushButton( this, "pushButton_open" );
    pushButton_open->setAutoDefault( FALSE );
    layout17->addWidget( pushButton_open );

    layout8->addMultiCellLayout( layout17, 12, 12, 1, 2 );

    textLabel1 = new QLabel( this, "textLabel1" );

    layout8->addWidget( textLabel1, 0, 0 );

    kLineEdit_length = new KLineEdit( this, "kLineEdit_length" );
    kLineEdit_length->setReadOnly( TRUE );

    layout8->addWidget( kLineEdit_length, 10, 1 );

    kComboBox_artist = new KComboBox( FALSE, this, "kComboBox_artist" );
    kComboBox_artist->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kComboBox_artist->sizePolicy().hasHeightForWidth() ) );
    kComboBox_artist->setEditable( TRUE );
    kComboBox_artist->setAutoCompletion( TRUE );

    layout8->addMultiCellWidget( kComboBox_artist, 1, 1, 1, 2 );

    playcountLabel = new QLabel( this, "playcountLabel" );

    layout8->addMultiCellWidget( playcountLabel, 8, 9, 0, 0 );

    pushButton_musicbrainz = new QPushButton( this, "pushButton_musicbrainz" );
    pushButton_musicbrainz->setAutoDefault( FALSE );

    layout8->addMultiCellWidget( pushButton_musicbrainz, 6, 6, 1, 2 );

    textLabel1_6_2 = new QLabel( this, "textLabel1_6_2" );
    textLabel1_6_2->setTextFormat( QLabel::AutoText );

    layout8->addWidget( textLabel1_6_2, 5, 0 );

    locationLabel = new QLabel( this, "locationLabel" );

    layout8->addWidget( locationLabel, 12, 0 );

    TagDialogBaseLayout->addLayout( layout8, 0, 0 );
    languageChange();
    resize( QSize(484, 442).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( kLineEdit_title, kComboBox_artist );
    setTabOrder( kComboBox_artist, kComboBox_album );
    setTabOrder( kComboBox_album, kComboBox_genre );
    setTabOrder( kComboBox_genre, kIntSpinBox_track );
    setTabOrder( kIntSpinBox_track, kIntSpinBox_year );
    setTabOrder( kIntSpinBox_year, kIntSpinBox_score );
    setTabOrder( kIntSpinBox_score, kLineEdit_comment );
    setTabOrder( kLineEdit_comment, kLineEdit_length );
    setTabOrder( kLineEdit_length, kLineEdit_bitrate );
    setTabOrder( kLineEdit_bitrate, kLineEdit_samplerate );
    setTabOrder( kLineEdit_samplerate, kLineEdit_location );
    setTabOrder( kLineEdit_location, pushButton_open );
    setTabOrder( pushButton_open, pushButton_ok );
    setTabOrder( pushButton_ok, pushButton_cancel );

    // buddies
    textLabel1_3->setBuddy( kComboBox_album );
    textLabel1_2->setBuddy( kComboBox_artist );
    textLabel1_4->setBuddy( kComboBox_genre );
    textLabel1_5->setBuddy( kIntSpinBox_year );
    textLabel1_6->setBuddy( kIntSpinBox_score );
    textLabel1_6_6->setBuddy( kIntSpinBox_track );
    textLabel1->setBuddy( kLineEdit_title );
    textLabel1_6_2->setBuddy( kLineEdit_comment );
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
    pushButton_ok->setText( tr2i18n( "Sa&ve && Close" ) );
    pushButton_cancel->setText( tr2i18n( "&Cancel" ) );
    textLabel1_3->setText( tr2i18n( "Al&bum:" ) );
    samplerateLabel->setText( tr2i18n( "Samplerate:" ) );
    textLabel1_2->setText( tr2i18n( "&Artist:" ) );
    pixmap_cover->setText( QString::null );
    textLabel1_4->setText( tr2i18n( "&Genre:" ) );
    lengthLabel->setText( tr2i18n( "Length:" ) );
    kIntSpinBox_track->setSpecialValueText( QString::null );
    textLabel1_5->setText( tr2i18n( "&Year:" ) );
    kIntSpinBox_year->setSpecialValueText( QString::null );
    textLabel1_6->setText( tr2i18n( "&Score:" ) );
    kIntSpinBox_score->setSpecialValueText( QString::null );
    bitrateLabel->setText( tr2i18n( "Bitrate:" ) );
    textLabel1_6_6->setText( tr2i18n( "Trac&k:" ) );
    pushButton_open->setText( QString::null );
    textLabel1->setText( tr2i18n( "&Title:" ) );
    playcountLabel->setText( tr2i18n( "Playcount:" ) );
    pushButton_musicbrainz->setText( tr2i18n( "Fill-In Tags &Using MusicBrainz" ) );
    QToolTip::add( pushButton_musicbrainz, tr2i18n( "Detect metadata from fingerprint." ) );
    textLabel1_6_2->setText( tr2i18n( "&Comment:" ) );
    locationLabel->setText( tr2i18n( "Location:" ) );
}

#include "tagdialogbase.moc"
