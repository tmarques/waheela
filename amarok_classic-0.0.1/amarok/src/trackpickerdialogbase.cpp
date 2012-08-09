#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './trackpickerdialogbase.ui'
**
** Created: Ter Fev 19 16:01:52 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "trackpickerdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qheader.h>
#include <klistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "klistview.h"

/*
 *  Constructs a TrackPickerDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TrackPickerDialogBase::TrackPickerDialogBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "trackPickerDialogBase" );
    trackPickerDialogBaseLayout = new QVBoxLayout( this, 11, 6, "trackPickerDialogBaseLayout"); 

    fileLayout = new QHBoxLayout( 0, 0, 6, "fileLayout"); 

    fileInfoGroup = new QGroupBox( this, "fileInfoGroup" );
    fileInfoGroup->setAlignment( int( QGroupBox::AlignTop ) );
    fileInfoGroup->setColumnLayout(0, Qt::Vertical );
    fileInfoGroup->layout()->setSpacing( 6 );
    fileInfoGroup->layout()->setMargin( 11 );
    fileInfoGroupLayout = new QHBoxLayout( fileInfoGroup->layout() );
    fileInfoGroupLayout->setAlignment( Qt::AlignTop );

    fileLabel = new QLabel( fileInfoGroup, "fileLabel" );
    QFont fileLabel_font(  fileLabel->font() );
    fileLabel_font.setBold( TRUE );
    fileLabel->setFont( fileLabel_font ); 
    fileLabel->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );
    fileLabel->setIndent( 9 );
    fileInfoGroupLayout->addWidget( fileLabel );
    fileLayout->addWidget( fileInfoGroup );
    trackPickerDialogBaseLayout->addLayout( fileLayout );

    trackLayout = new QHBoxLayout( 0, 0, 6, "trackLayout"); 

    trackInfoGroup = new QGroupBox( this, "trackInfoGroup" );
    trackInfoGroup->setAlignment( int( QGroupBox::AlignTop ) );
    trackInfoGroup->setColumnLayout(0, Qt::Vertical );
    trackInfoGroup->layout()->setSpacing( 6 );
    trackInfoGroup->layout()->setMargin( 11 );
    trackInfoGroupLayout = new QVBoxLayout( trackInfoGroup->layout() );
    trackInfoGroupLayout->setAlignment( Qt::AlignTop );

    trackList = new KListView( trackInfoGroup, "trackList" );
    trackList->addColumn( tr2i18n( "Filename" ) );
    trackList->header()->setResizeEnabled( FALSE, trackList->header()->count() - 1 );
    trackList->addColumn( tr2i18n( "Artist" ) );
    trackList->header()->setResizeEnabled( FALSE, trackList->header()->count() - 1 );
    trackList->addColumn( tr2i18n( "Album" ) );
    trackList->header()->setResizeEnabled( FALSE, trackList->header()->count() - 1 );
    trackList->addColumn( tr2i18n( "Track" ) );
    trackList->addColumn( tr2i18n( "Year" ) );
    trackList->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)7, 0, 0, trackList->sizePolicy().hasHeightForWidth() ) );
    trackList->setAllColumnsShowFocus( TRUE );
    trackList->setItemMargin( 1 );
    trackList->setResizeMode( KListView::LastColumn );
    trackList->setFullWidth( FALSE );
    trackInfoGroupLayout->addWidget( trackList );
    trackLayout->addWidget( trackInfoGroup );
    trackPickerDialogBaseLayout->addLayout( trackLayout );
    languageChange();
    resize( QSize(556, 310).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
}

/*
 *  Destroys the object and frees any allocated resources
 */
TrackPickerDialogBase::~TrackPickerDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TrackPickerDialogBase::languageChange()
{
    setCaption( tr2i18n( "trackPickerDialogBase" ) );
    fileInfoGroup->setTitle( tr2i18n( "File Name" ) );
    fileLabel->setText( QString::null );
    trackInfoGroup->setTitle( tr2i18n( "Select Best Possible Match" ) );
    trackList->header()->setLabel( 0, tr2i18n( "Filename" ) );
    trackList->header()->setLabel( 1, tr2i18n( "Artist" ) );
    trackList->header()->setLabel( 2, tr2i18n( "Album" ) );
    trackList->header()->setLabel( 3, tr2i18n( "Track" ) );
    trackList->header()->setLabel( 4, tr2i18n( "Year" ) );
}

#include "trackpickerdialogbase.moc"
