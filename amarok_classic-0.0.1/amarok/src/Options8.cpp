#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options8.ui'
**
** Created: Ter Fev 19 16:01:37 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "Options8.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <kactivelabel.h>
#include <qgroupbox.h>
#include <klineedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kactivelabel.h"
#include "klineedit.h"

/*
 *  Constructs a Options8 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Options8::Options8( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Options8" );
    setMinimumSize( QSize( 1, 1 ) );
    Options8Layout = new QVBoxLayout( this, 0, 12, "Options8Layout"); 

    layout2 = new QHBoxLayout( 0, 0, 12, "layout2"); 

    infoPixmap_2 = new QLabel( this, "infoPixmap_2" );
    infoPixmap_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)1, 0, 0, infoPixmap_2->sizePolicy().hasHeightForWidth() ) );
    infoPixmap_2->setAlignment( int( QLabel::AlignVCenter ) );
    layout2->addWidget( infoPixmap_2 );

    kActiveLabel3 = new KActiveLabel( this, "kActiveLabel3" );
    kActiveLabel3->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, kActiveLabel3->sizePolicy().hasHeightForWidth() ) );
    kActiveLabel3->setMinimumSize( QSize( -1, -1 ) );
    layout2->addWidget( kActiveLabel3 );
    Options8Layout->addLayout( layout2 );

    groupBox3 = new QGroupBox( this, "groupBox3" );
    groupBox3->setColumnLayout(0, Qt::Vertical );
    groupBox3->layout()->setSpacing( 6 );
    groupBox3->layout()->setMargin( 11 );
    groupBox3Layout = new QVBoxLayout( groupBox3->layout() );
    groupBox3Layout->setAlignment( Qt::AlignTop );

    kActiveLabel1 = new KActiveLabel( groupBox3, "kActiveLabel1" );
    kActiveLabel1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, kActiveLabel1->sizePolicy().hasHeightForWidth() ) );
    groupBox3Layout->addWidget( kActiveLabel1 );

    layout3 = new QGridLayout( 0, 1, 1, 0, 6, "layout3"); 

    kcfg_ScrobblerUsername = new KLineEdit( groupBox3, "kcfg_ScrobblerUsername" );
    kcfg_ScrobblerUsername->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kcfg_ScrobblerUsername->sizePolicy().hasHeightForWidth() ) );

    layout3->addWidget( kcfg_ScrobblerUsername, 0, 1 );

    labelPassword = new QLabel( groupBox3, "labelPassword" );
    labelPassword->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, labelPassword->sizePolicy().hasHeightForWidth() ) );

    layout3->addWidget( labelPassword, 1, 0 );

    labelUsername = new QLabel( groupBox3, "labelUsername" );
    labelUsername->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, labelUsername->sizePolicy().hasHeightForWidth() ) );

    layout3->addWidget( labelUsername, 0, 0 );

    kcfg_ScrobblerPassword = new KLineEdit( groupBox3, "kcfg_ScrobblerPassword" );
    kcfg_ScrobblerPassword->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kcfg_ScrobblerPassword->sizePolicy().hasHeightForWidth() ) );
    kcfg_ScrobblerPassword->setEchoMode( KLineEdit::Password );

    layout3->addWidget( kcfg_ScrobblerPassword, 1, 1 );
    groupBox3Layout->addLayout( layout3 );
    Options8Layout->addWidget( groupBox3 );

    groupBox2 = new QGroupBox( this, "groupBox2" );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( 6 );
    groupBox2->layout()->setMargin( 11 );
    groupBox2Layout = new QVBoxLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    textLabel1 = new QLabel( groupBox2, "textLabel1" );
    textLabel1->setTextFormat( QLabel::RichText );
    groupBox2Layout->addWidget( textLabel1 );

    kcfg_SubmitPlayedSongs = new QCheckBox( groupBox2, "kcfg_SubmitPlayedSongs" );
    kcfg_SubmitPlayedSongs->setEnabled( TRUE );
    kcfg_SubmitPlayedSongs->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, kcfg_SubmitPlayedSongs->sizePolicy().hasHeightForWidth() ) );
    groupBox2Layout->addWidget( kcfg_SubmitPlayedSongs );

    kcfg_RetrieveSimilarArtists = new QCheckBox( groupBox2, "kcfg_RetrieveSimilarArtists" );
    groupBox2Layout->addWidget( kcfg_RetrieveSimilarArtists );
    Options8Layout->addWidget( groupBox2 );

    kActiveLabel2 = new KActiveLabel( this, "kActiveLabel2" );
    kActiveLabel2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, kActiveLabel2->sizePolicy().hasHeightForWidth() ) );
    Options8Layout->addWidget( kActiveLabel2 );
    spacer4 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Options8Layout->addItem( spacer4 );
    languageChange();
    resize( QSize(425, 557).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // buddies
    labelPassword->setBuddy( kcfg_ScrobblerPassword );
    labelUsername->setBuddy( kcfg_ScrobblerUsername );
}

/*
 *  Destroys the object and frees any allocated resources
 */
Options8::~Options8()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Options8::languageChange()
{
    infoPixmap_2->setText( QString::null );
    kActiveLabel3->setText( tr2i18n( "amaroK can send the name of every song you play to last.fm. The system automatically matches you to people with similar musical tastes, and creates personalized recommendations. To learn more about last.fm, <A href='http://www.last.fm'>visit the homepage</A>." ) );
    groupBox3->setTitle( tr2i18n( "last.fm Profile" ) );
    kActiveLabel1->setText( tr2i18n( "<P>To use last.fm with amaroK, you need a <A href='http://www.last.fm:80/signup.php'>last.fm profile</A>." ) );
    labelPassword->setText( tr2i18n( "&Password:" ) );
    labelUsername->setText( tr2i18n( "&Username:" ) );
    groupBox2->setTitle( tr2i18n( "last.fm Services" ) );
    textLabel1->setText( tr2i18n( "Once registered, amaroK can tell the last.fm service about your listening habits; your profile can then provide statistics and recommendations. A profile is not required to retrieve similar-artists for display in the Context Browser." ) );
    kcfg_SubmitPlayedSongs->setText( tr2i18n( "Improve m&y profile by submitting the tracks I play" ) );
    kcfg_RetrieveSimilarArtists->setText( tr2i18n( "&Retrieve similar artists" ) );
    kActiveLabel2->setText( tr2i18n( "Why not join the <A href='http://www.last.fm:80/group/amaroK+users'>amaroK last.fm group</A> and share your musical tastes with other amaroK users?" ) );
}

#include "Options8.moc"
