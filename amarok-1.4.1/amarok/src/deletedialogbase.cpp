#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './deletedialogbase.ui'
**
** Created: Fri Mar 23 10:56:44 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "deletedialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <klistbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "klistbox.h"

/*
 *  Constructs a DeleteDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
DeleteDialogBase::DeleteDialogBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "DeleteDialogBase" );
    setMinimumSize( QSize( 420, 320 ) );
    DeleteDialogBaseLayout = new QVBoxLayout( this, 0, 6, "DeleteDialogBaseLayout"); 

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    ddWarningIcon = new QLabel( this, "ddWarningIcon" );
    ddWarningIcon->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)4, 0, 0, ddWarningIcon->sizePolicy().hasHeightForWidth() ) );
    layout4->addWidget( ddWarningIcon );

    layout3 = new QVBoxLayout( 0, 0, 6, "layout3"); 

    ddDeleteText = new QLabel( this, "ddDeleteText" );
    ddDeleteText->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    layout3->addWidget( ddDeleteText );
    layout4->addLayout( layout3 );
    DeleteDialogBaseLayout->addLayout( layout4 );

    ddFileList = new KListBox( this, "ddFileList" );
    ddFileList->setSelectionMode( KListBox::NoSelection );
    DeleteDialogBaseLayout->addWidget( ddFileList );

    ddNumFiles = new QLabel( this, "ddNumFiles" );
    ddNumFiles->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );
    DeleteDialogBaseLayout->addWidget( ddNumFiles );

    ddShouldDelete = new QCheckBox( this, "ddShouldDelete" );
    DeleteDialogBaseLayout->addWidget( ddShouldDelete );
    languageChange();
    resize( QSize(542, 374).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( ddShouldDelete, SIGNAL( toggled(bool) ), this, SLOT( slotShouldDelete(bool) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
DeleteDialogBase::~DeleteDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void DeleteDialogBase::languageChange()
{
    ddWarningIcon->setText( tr2i18n( "Icon Placeholder, not in GUI" ) );
    ddDeleteText->setText( tr2i18n( "Deletion method placeholder, never shown to user." ) );
    QToolTip::add( ddFileList, tr2i18n( "List of files that are about to be deleted." ) );
    QWhatsThis::add( ddFileList, tr2i18n( "This is the list of items that are about to be deleted." ) );
    ddNumFiles->setText( tr2i18n( "Placeholder for number of files, not in GUI" ) );
    ddShouldDelete->setText( tr2i18n( "&Delete files instead of moving them to the trash" ) );
    QToolTip::add( ddShouldDelete, tr2i18n( "If checked, files will be permanently removed instead of being placed in the Trash Bin" ) );
    QWhatsThis::add( ddShouldDelete, tr2i18n( "<qt><p>If this box is checked, files will be <b>permanently removed</b> instead of being placed in the Trash Bin.</p>\n"
"\n"
"<p><em>Use this option with caution</em>: Most filesystems are unable to reliably undelete deleted files.</p></qt>" ) );
}

void DeleteDialogBase::slotShouldDelete(bool)
{
    qWarning( "DeleteDialogBase::slotShouldDelete(bool): Not implemented yet" );
}

#include "deletedialogbase.moc"
