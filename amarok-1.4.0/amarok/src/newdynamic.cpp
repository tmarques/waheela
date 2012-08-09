#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './newdynamic.ui'
**
** Created: Sex Mar 23 10:42:42 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "newdynamic.h"

#include <qvariant.h>
#include <qlabel.h>
#include <knuminput.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "knuminput.h"
#include "playlistselection.h"

/*
 *  Constructs a NewDynamic as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
NewDynamic::NewDynamic( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "NewDynamic" );
    NewDynamicLayout = new QGridLayout( this, 1, 1, 0, 6, "NewDynamicLayout"); 

    textLabel3 = new QLabel( this, "textLabel3" );

    NewDynamicLayout->addWidget( textLabel3, 7, 1 );

    textLabel1 = new QLabel( this, "textLabel1" );

    NewDynamicLayout->addWidget( textLabel1, 5, 1 );
    spacer5_2 = new QSpacerItem( 21, 5, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding );
    NewDynamicLayout->addItem( spacer5_2, 8, 3 );
    spacer3 = new QSpacerItem( 80, 21, QSizePolicy::Preferred, QSizePolicy::Minimum );
    NewDynamicLayout->addMultiCell( spacer3, 5, 5, 2, 4 );

    m_upcomingIntSpinBox = new KIntSpinBox( this, "m_upcomingIntSpinBox" );
    m_upcomingIntSpinBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, m_upcomingIntSpinBox->sizePolicy().hasHeightForWidth() ) );
    m_upcomingIntSpinBox->setMaxValue( 50 );
    m_upcomingIntSpinBox->setMinValue( 1 );
    m_upcomingIntSpinBox->setValue( 10 );
    m_upcomingIntSpinBox->setBase( 10 );

    NewDynamicLayout->addWidget( m_upcomingIntSpinBox, 6, 5 );

    textLabel2 = new QLabel( this, "textLabel2" );

    NewDynamicLayout->addWidget( textLabel2, 6, 1 );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );

    NewDynamicLayout->addWidget( textLabel1_2, 2, 1 );

    m_name = new QLineEdit( this, "m_name" );
    m_name->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, m_name->sizePolicy().hasHeightForWidth() ) );

    NewDynamicLayout->addMultiCellWidget( m_name, 2, 2, 2, 5 );
    spacer4 = new QSpacerItem( 110, 21, QSizePolicy::Preferred, QSizePolicy::Minimum );
    NewDynamicLayout->addMultiCell( spacer4, 6, 6, 2, 4 );

    m_previousIntSpinBox = new KIntSpinBox( this, "m_previousIntSpinBox" );
    m_previousIntSpinBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, m_previousIntSpinBox->sizePolicy().hasHeightForWidth() ) );
    m_previousIntSpinBox->setMinimumSize( QSize( 60, 0 ) );
    m_previousIntSpinBox->setButtonSymbols( KIntSpinBox::UpDownArrows );
    m_previousIntSpinBox->setMaxValue( 100 );
    m_previousIntSpinBox->setMinValue( 1 );
    m_previousIntSpinBox->setValue( 5 );
    m_previousIntSpinBox->setBase( 10 );

    NewDynamicLayout->addWidget( m_previousIntSpinBox, 5, 5 );
    spacer5 = new QSpacerItem( 90, 21, QSizePolicy::Preferred, QSizePolicy::Minimum );
    NewDynamicLayout->addMultiCell( spacer5, 7, 7, 2, 4 );

    m_appendCountIntSpinBox = new KIntSpinBox( this, "m_appendCountIntSpinBox" );
    m_appendCountIntSpinBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, m_appendCountIntSpinBox->sizePolicy().hasHeightForWidth() ) );
    m_appendCountIntSpinBox->setMaxValue( 10 );
    m_appendCountIntSpinBox->setMinValue( 1 );

    NewDynamicLayout->addWidget( m_appendCountIntSpinBox, 7, 5 );

    m_cycleTracks = new QCheckBox( this, "m_cycleTracks" );

    NewDynamicLayout->addMultiCellWidget( m_cycleTracks, 3, 3, 1, 2 );

    selectPlaylist = new PlaylistSelection( this, "selectPlaylist" );
    selectPlaylist->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 1, 0, selectPlaylist->sizePolicy().hasHeightForWidth() ) );
    selectPlaylist->setMinimumSize( QSize( 250, 250 ) );

    NewDynamicLayout->addMultiCellWidget( selectPlaylist, 2, 8, 0, 0 );

    line1 = new QFrame( this, "line1" );
    line1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, line1->sizePolicy().hasHeightForWidth() ) );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );

    NewDynamicLayout->addMultiCellWidget( line1, 4, 4, 1, 5 );

    line1_2 = new QFrame( this, "line1_2" );
    line1_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, line1_2->sizePolicy().hasHeightForWidth() ) );
    line1_2->setFrameShape( QFrame::HLine );
    line1_2->setFrameShadow( QFrame::Sunken );
    line1_2->setFrameShape( QFrame::HLine );

    NewDynamicLayout->addMultiCellWidget( line1_2, 1, 1, 0, 5 );

    m_mixLabel = new QLabel( this, "m_mixLabel" );
    QFont m_mixLabel_font(  m_mixLabel->font() );
    m_mixLabel_font.setBold( TRUE );
    m_mixLabel->setFont( m_mixLabel_font ); 
    m_mixLabel->setAlignment( int( QLabel::AlignVCenter ) );

    NewDynamicLayout->addMultiCellWidget( m_mixLabel, 0, 0, 0, 4 );
    spacer7 = new QSpacerItem( 60, 21, QSizePolicy::Preferred, QSizePolicy::Minimum );
    NewDynamicLayout->addItem( spacer7, 3, 3 );

    m_markHistory = new QCheckBox( this, "m_markHistory" );

    NewDynamicLayout->addMultiCellWidget( m_markHistory, 3, 3, 4, 5 );
    languageChange();
    resize( QSize(560, 287).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NewDynamic::~NewDynamic()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NewDynamic::languageChange()
{
    textLabel3->setText( tr2i18n( "Tracks to append:" ) );
    QToolTip::add( textLabel3, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    QWhatsThis::add( textLabel3, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    textLabel1->setText( tr2i18n( "Played tracks to show:" ) );
    QToolTip::add( textLabel1, tr2i18n( "How many played items to show before removal" ) );
    QWhatsThis::add( textLabel1, tr2i18n( "How many played items to show before removal" ) );
    QToolTip::add( m_upcomingIntSpinBox, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    QWhatsThis::add( m_upcomingIntSpinBox, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    textLabel2->setText( tr2i18n( "Upcoming tracks:" ) );
    QToolTip::add( textLabel2, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    QWhatsThis::add( textLabel2, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    textLabel1_2->setText( tr2i18n( "Dynamic playlist name:" ) );
    m_name->setText( tr2i18n( "Untitled" ) );
    QToolTip::add( m_previousIntSpinBox, tr2i18n( "How many played items to show before removal" ) );
    QWhatsThis::add( m_previousIntSpinBox, tr2i18n( "How many played items to show before removal" ) );
    QToolTip::add( m_appendCountIntSpinBox, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    QWhatsThis::add( m_appendCountIntSpinBox, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    m_cycleTracks->setText( tr2i18n( "Remove pla&yed tracks" ) );
    QToolTip::add( m_cycleTracks, tr2i18n( "Automatically remove played tracks from the playlist" ) );
    QWhatsThis::add( m_cycleTracks, tr2i18n( "Automatically remove played tracks to the playlist" ) );
    m_mixLabel->setText( QString::null );
    m_markHistory->setText( tr2i18n( "M&ark history" ) );
    QToolTip::add( m_markHistory, tr2i18n( "Once played, tracks will be greyed out" ) );
    QWhatsThis::add( m_markHistory, tr2i18n( "Once played, tracks will be greyed out" ) );
}

#include "newdynamic.moc"
