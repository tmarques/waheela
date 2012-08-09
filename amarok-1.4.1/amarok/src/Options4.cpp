#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './Options4.ui'
**
** Created: Fri Mar 23 10:56:33 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "Options4.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a Options4 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Options4::Options4( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "Options4" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, sizePolicy().hasHeightForWidth() ) );
    Options4Layout = new QVBoxLayout( this, 0, 12, "Options4Layout"); 

    opt_crossfade = new QButtonGroup( this, "opt_crossfade" );
    opt_crossfade->setFrameShape( QButtonGroup::GroupBoxPanel );
    opt_crossfade->setFrameShadow( QButtonGroup::Sunken );
    opt_crossfade->setColumnLayout(0, Qt::Vertical );
    opt_crossfade->layout()->setSpacing( 6 );
    opt_crossfade->layout()->setMargin( 11 );
    opt_crossfadeLayout = new QGridLayout( opt_crossfade->layout() );
    opt_crossfadeLayout->setAlignment( Qt::AlignTop );

    radioButtonNormalPlayback = new QRadioButton( opt_crossfade, "radioButtonNormalPlayback" );
    radioButtonNormalPlayback->setChecked( TRUE );

    opt_crossfadeLayout->addMultiCellWidget( radioButtonNormalPlayback, 0, 0, 0, 2 );

    kcfg_TrackDelayLength = new QSpinBox( opt_crossfade, "kcfg_TrackDelayLength" );
    kcfg_TrackDelayLength->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, kcfg_TrackDelayLength->sizePolicy().hasHeightForWidth() ) );
    kcfg_TrackDelayLength->setMinimumSize( QSize( 160, 0 ) );
    kcfg_TrackDelayLength->setMaxValue( 10000 );
    kcfg_TrackDelayLength->setLineStep( 100 );
    kcfg_TrackDelayLength->setValue( 0 );

    opt_crossfadeLayout->addWidget( kcfg_TrackDelayLength, 1, 2 );

    kcfg_CrossfadeLength = new QSpinBox( opt_crossfade, "kcfg_CrossfadeLength" );
    kcfg_CrossfadeLength->setEnabled( FALSE );
    kcfg_CrossfadeLength->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, kcfg_CrossfadeLength->sizePolicy().hasHeightForWidth() ) );
    kcfg_CrossfadeLength->setMinimumSize( QSize( 160, 0 ) );
    kcfg_CrossfadeLength->setMaxValue( 99999999 );
    kcfg_CrossfadeLength->setMinValue( 100 );
    kcfg_CrossfadeLength->setLineStep( 100 );
    kcfg_CrossfadeLength->setValue( 100 );

    opt_crossfadeLayout->addWidget( kcfg_CrossfadeLength, 3, 2 );

    kcfg_Crossfade = new QRadioButton( opt_crossfade, "kcfg_Crossfade" );
    kcfg_Crossfade->setChecked( FALSE );

    opt_crossfadeLayout->addMultiCellWidget( kcfg_Crossfade, 2, 2, 0, 2 );

    crossfadeLengthLabel = new QLabel( opt_crossfade, "crossfadeLengthLabel" );
    crossfadeLengthLabel->setEnabled( FALSE );
    crossfadeLengthLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, crossfadeLengthLabel->sizePolicy().hasHeightForWidth() ) );
    crossfadeLengthLabel->setMinimumSize( QSize( 80, 0 ) );

    opt_crossfadeLayout->addWidget( crossfadeLengthLabel, 3, 1 );

    kcfg_CrossfadeManualOnly = new QCheckBox( opt_crossfade, "kcfg_CrossfadeManualOnly" );
    kcfg_CrossfadeManualOnly->setEnabled( FALSE );

    opt_crossfadeLayout->addMultiCellWidget( kcfg_CrossfadeManualOnly, 4, 4, 1, 2 );
    spacer76 = new QSpacerItem( 16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    opt_crossfadeLayout->addItem( spacer76, 3, 0 );

    trackDelayLengthLabel = new QLabel( opt_crossfade, "trackDelayLengthLabel" );
    trackDelayLengthLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, trackDelayLengthLabel->sizePolicy().hasHeightForWidth() ) );
    trackDelayLengthLabel->setMinimumSize( QSize( 80, 0 ) );

    opt_crossfadeLayout->addWidget( trackDelayLengthLabel, 1, 1 );
    Options4Layout->addWidget( opt_crossfade );

    kcfg_ResumePlayback = new QCheckBox( this, "kcfg_ResumePlayback" );
    Options4Layout->addWidget( kcfg_ResumePlayback );
    spacer2 = new QSpacerItem( 31, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Options4Layout->addItem( spacer2 );
    languageChange();
    resize( QSize(320, 220).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( radioButtonNormalPlayback, SIGNAL( toggled(bool) ), kcfg_TrackDelayLength, SLOT( setEnabled(bool) ) );
    connect( kcfg_Crossfade, SIGNAL( toggled(bool) ), kcfg_CrossfadeLength, SLOT( setEnabled(bool) ) );
    connect( radioButtonNormalPlayback, SIGNAL( toggled(bool) ), trackDelayLengthLabel, SLOT( setEnabled(bool) ) );
    connect( kcfg_Crossfade, SIGNAL( toggled(bool) ), crossfadeLengthLabel, SLOT( setEnabled(bool) ) );
    connect( kcfg_Crossfade, SIGNAL( toggled(bool) ), kcfg_CrossfadeManualOnly, SLOT( setEnabled(bool) ) );

    // buddies
    crossfadeLengthLabel->setBuddy( kcfg_CrossfadeLength );
    trackDelayLengthLabel->setBuddy( kcfg_TrackDelayLength );
}

/*
 *  Destroys the object and frees any allocated resources
 */
Options4::~Options4()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Options4::languageChange()
{
    opt_crossfade->setTitle( tr2i18n( "Transition &Behavior" ) );
    QWhatsThis::add( opt_crossfade, tr2i18n( "<b>Transition Behavior</b>\n"
"<p>During playback, when Amarok transitions between tracks, it can either proceed to the next track instantly (with configurable gap), or crossfade (with configurable fade period).</p>" ) );
    radioButtonNormalPlayback->setText( tr2i18n( "&No crossfading" ) );
    QToolTip::add( radioButtonNormalPlayback, tr2i18n( "Enable normal track transition. You may insert a gap of silence between tracks." ) );
    kcfg_TrackDelayLength->setSuffix( tr2i18n( " ms" ) );
    QToolTip::add( kcfg_TrackDelayLength, tr2i18n( "Silence between tracks, in milliseconds." ) );
    kcfg_CrossfadeLength->setSuffix( tr2i18n( " ms" ) );
    QToolTip::add( kcfg_CrossfadeLength, tr2i18n( "The length of the crossfade between tracks, in milliseconds." ) );
    kcfg_Crossfade->setText( tr2i18n( "&Crossfading" ) );
    QToolTip::add( kcfg_Crossfade, tr2i18n( "Enable crossfading between tracks. This setting also enables fading to or from silence e.g when pressing stop." ) );
    crossfadeLengthLabel->setText( tr2i18n( "Crosso&ver period:" ) );
    kcfg_CrossfadeManualOnly->setText( tr2i18n( "Crossfade on man&ual track change only" ) );
    QToolTip::add( kcfg_CrossfadeManualOnly, tr2i18n( "When enabled, crossfading will only occur when manually changing tracks." ) );
    trackDelayLengthLabel->setText( tr2i18n( "Insert &gap:" ) );
    kcfg_ResumePlayback->setText( tr2i18n( "&Resume playback on start" ) );
    QToolTip::add( kcfg_ResumePlayback, tr2i18n( "If checked, Amarok will<br>resume playback from where you left it the previous session -- just like a tape-player." ) );
}

#include "Options4.moc"
