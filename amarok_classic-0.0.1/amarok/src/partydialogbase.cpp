#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './partydialogbase.ui'
**
** Created: Ter Fev 19 16:01:43 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "partydialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <knuminput.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "knuminput.h"

/*
 *  Constructs a PartyDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PartyDialogBase::PartyDialogBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "PartyDialogBase" );
    PartyDialogBaseLayout = new QVBoxLayout( this, 10, KDialog::spacingHint(), "PartyDialogBaseLayout"); 

    m_buttonGroup = new QButtonGroup( this, "m_buttonGroup" );
    m_buttonGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, m_buttonGroup->sizePolicy().hasHeightForWidth() ) );
    m_buttonGroup->setMinimumSize( QSize( 0, 0 ) );
    m_buttonGroup->setLineWidth( 1 );
    m_buttonGroup->setCheckable( FALSE );
    m_buttonGroup->setColumnLayout(0, Qt::Vertical );
    m_buttonGroup->layout()->setSpacing( KDialog::spacingHint() );
    m_buttonGroup->layout()->setMargin( 9 );
    m_buttonGroupLayout = new QVBoxLayout( m_buttonGroup->layout() );
    m_buttonGroupLayout->setAlignment( Qt::AlignTop );

    m_appendType = new QComboBox( FALSE, m_buttonGroup, "m_appendType" );
    m_buttonGroupLayout->addWidget( m_appendType );
    PartyDialogBaseLayout->addWidget( m_buttonGroup );

    layout13 = new QHBoxLayout( 0, 0, KDialog::spacingHint(), "layout13"); 

    m_cycleTracks = new QCheckBox( this, "m_cycleTracks" );
    layout13->addWidget( m_cycleTracks );
    spacer7 = new QSpacerItem( 180, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout13->addItem( spacer7 );

    m_markHistory = new QCheckBox( this, "m_markHistory" );
    layout13->addWidget( m_markHistory );
    PartyDialogBaseLayout->addLayout( layout13 );

    line1 = new QFrame( this, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );
    PartyDialogBaseLayout->addWidget( line1 );

    layout11 = new QHBoxLayout( 0, 0, KDialog::spacingHint(), "layout11"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout11->addWidget( textLabel1 );
    spacer3 = new QSpacerItem( 180, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout11->addItem( spacer3 );

    m_previousIntSpinBox = new KIntSpinBox( this, "m_previousIntSpinBox" );
    m_previousIntSpinBox->setButtonSymbols( KIntSpinBox::UpDownArrows );
    m_previousIntSpinBox->setMaxValue( 100 );
    m_previousIntSpinBox->setMinValue( 1 );
    layout11->addWidget( m_previousIntSpinBox );
    PartyDialogBaseLayout->addLayout( layout11 );

    layout12 = new QHBoxLayout( 0, 0, KDialog::spacingHint(), "layout12"); 

    textLabel2 = new QLabel( this, "textLabel2" );
    layout12->addWidget( textLabel2 );
    spacer4 = new QSpacerItem( 171, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout12->addItem( spacer4 );

    m_upcomingIntSpinBox = new KIntSpinBox( this, "m_upcomingIntSpinBox" );
    m_upcomingIntSpinBox->setMaxValue( 50 );
    m_upcomingIntSpinBox->setMinValue( 1 );
    m_upcomingIntSpinBox->setBase( 10 );
    layout12->addWidget( m_upcomingIntSpinBox );
    PartyDialogBaseLayout->addLayout( layout12 );

    layout13_2 = new QHBoxLayout( 0, 0, KDialog::spacingHint(), "layout13_2"); 

    textLabel3 = new QLabel( this, "textLabel3" );
    layout13_2->addWidget( textLabel3 );
    spacer5 = new QSpacerItem( 191, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout13_2->addItem( spacer5 );

    m_appendCountIntSpinBox = new KIntSpinBox( this, "m_appendCountIntSpinBox" );
    m_appendCountIntSpinBox->setMaxValue( 10 );
    m_appendCountIntSpinBox->setMinValue( 1 );
    layout13_2->addWidget( m_appendCountIntSpinBox );
    PartyDialogBaseLayout->addLayout( layout13_2 );
    languageChange();
    resize( QSize(306, 211).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
PartyDialogBase::~PartyDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PartyDialogBase::languageChange()
{
    setCaption( tr2i18n( "partyDialogBase" ) );
    m_buttonGroup->setTitle( tr2i18n( "Type of Song to Append to Playlist" ) );
    m_appendType->clear();
    m_appendType->insertItem( tr2i18n( "Random Song" ) );
    m_appendType->insertItem( tr2i18n( "Suggested Song" ) );
    m_appendType->insertItem( tr2i18n( "Playlist Shuffle" ) );
    QToolTip::add( m_appendType, tr2i18n( "Select which type of song you would like to add to the playlist" ) );
    QWhatsThis::add( m_appendType, tr2i18n( "Select which type of song you would like to add to the playlist" ) );
    m_cycleTracks->setText( tr2i18n( "&Remove played tracks" ) );
    QToolTip::add( m_cycleTracks, tr2i18n( "Automatically remove played tracks to the playlist" ) );
    QWhatsThis::add( m_cycleTracks, tr2i18n( "Automatically remove played tracks to the playlist" ) );
    m_markHistory->setText( tr2i18n( "Mar&k history" ) );
    QToolTip::add( m_markHistory, tr2i18n( "Once played, tracks will be greyed out" ) );
    QWhatsThis::add( m_markHistory, tr2i18n( "Once played, tracks will be greyed out" ) );
    textLabel1->setText( tr2i18n( "Played tracks to show:" ) );
    QToolTip::add( textLabel1, tr2i18n( "How many played items to show before removal" ) );
    QWhatsThis::add( textLabel1, tr2i18n( "How many played items to show before removal" ) );
    QToolTip::add( m_previousIntSpinBox, tr2i18n( "How many played items to show before removal" ) );
    QWhatsThis::add( m_previousIntSpinBox, tr2i18n( "How many played items to show before removal" ) );
    textLabel2->setText( tr2i18n( "Upcoming tracks:" ) );
    QToolTip::add( textLabel2, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    QWhatsThis::add( textLabel2, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    QToolTip::add( m_upcomingIntSpinBox, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    QWhatsThis::add( m_upcomingIntSpinBox, tr2i18n( "Minimum number of upcoming tracks to keep in the playlist" ) );
    textLabel3->setText( tr2i18n( "Tracks to append:" ) );
    QToolTip::add( textLabel3, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    QWhatsThis::add( textLabel3, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    QToolTip::add( m_appendCountIntSpinBox, tr2i18n( "How many tracks to add to the playlist after each song" ) );
    QWhatsThis::add( m_appendCountIntSpinBox, tr2i18n( "How many tracks to add to the playlist after each song" ) );
}

void PartyDialogBase::kURLLabel2_leftClickedURL()
{
    qWarning( "PartyDialogBase::kURLLabel2_leftClickedURL(): Not implemented yet" );
}

#include "partydialogbase.moc"
