#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './tagguesserconfigdialog.ui'
**
** Created: Sex Mar 23 10:42:55 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "tagguesserconfigdialog.h"

#include <qvariant.h>
#include <kdialog.h>
#include <qheader.h>
#include <klistview.h>
#include <qtoolbutton.h>
#include <kpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kdialog.h"
#include "klistview.h"
#include "kpushbutton.h"
#include "./tagguesserconfigdialog.ui.h"

/*
 *  Constructs a TagGuesserConfigDialog which is a child of 'parent', with the
 *  name 'name'.' 
 */
TagGuesserConfigDialog::TagGuesserConfigDialog( QWidget* parent,  const char* name )
    : KDialog( parent, name )
{
    if ( !name )
	setName( "TagGuesserConfigDialog" );
    TagGuesserConfigDialogLayout = new QGridLayout( this, 1, 1, 0, KDialog::spacingHint(), "TagGuesserConfigDialogLayout"); 

    lvSchemes = new KListView( this, "lvSchemes" );
    lvSchemes->addColumn( tr2i18n( "File Name Scheme" ) );
    lvSchemes->header()->setClickEnabled( FALSE, lvSchemes->header()->count() - 1 );
    lvSchemes->header()->setResizeEnabled( FALSE, lvSchemes->header()->count() - 1 );
    lvSchemes->setFrameShape( KListView::StyledPanel );
    lvSchemes->setFrameShadow( KListView::Sunken );
    lvSchemes->setFullWidth( TRUE );

    TagGuesserConfigDialogLayout->addMultiCellWidget( lvSchemes, 0, 6, 0, 0 );

    bMoveUp = new QToolButton( this, "bMoveUp" );

    TagGuesserConfigDialogLayout->addWidget( bMoveUp, 0, 1 );

    bMoveDown = new QToolButton( this, "bMoveDown" );

    TagGuesserConfigDialogLayout->addWidget( bMoveDown, 0, 3 );

    bModify = new KPushButton( this, "bModify" );

    TagGuesserConfigDialogLayout->addMultiCellWidget( bModify, 2, 2, 1, 3 );

    bRemove = new KPushButton( this, "bRemove" );

    TagGuesserConfigDialogLayout->addMultiCellWidget( bRemove, 3, 3, 1, 3 );

    bAdd = new KPushButton( this, "bAdd" );

    TagGuesserConfigDialogLayout->addMultiCellWidget( bAdd, 1, 1, 1, 3 );
    spacer1 = new QSpacerItem( 20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding );
    TagGuesserConfigDialogLayout->addItem( spacer1, 4, 2 );

    bOk = new KPushButton( this, "bOk" );

    TagGuesserConfigDialogLayout->addMultiCellWidget( bOk, 5, 5, 1, 3 );

    bCancel = new KPushButton( this, "bCancel" );

    TagGuesserConfigDialogLayout->addMultiCellWidget( bCancel, 6, 6, 1, 3 );
    languageChange();
    resize( QSize(467, 260).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TagGuesserConfigDialog::~TagGuesserConfigDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TagGuesserConfigDialog::languageChange()
{
    setCaption( tr2i18n( "Tag Guesser" ) );
    lvSchemes->header()->setLabel( 0, tr2i18n( "File Name Scheme" ) );
    QToolTip::add( lvSchemes, tr2i18n( "Here you can see the currently configured file name schemes which the \"Guess Tags From Filename\" button uses to extract tag information from a file name. Each string may contain one of the following placeholders:<ul>\n"
"<li>%title: Song Title</li>\n"
"<li>%artist: Artist</li>\n"
"<li>%album: Album</li>\n"
"<li>%track: Track Number</li>\n"
"<li>%comment: Comment</li>\n"
"</ul>\n"
"For example, the file name scheme \"[%track] %artist - %title\" would match \"[01] Deep Purple - Smoke on the water\" but not \"(Deep Purple) Smoke on the water\". For that second name, you would use the scheme \"(%a) %t\".<p/>\n"
"Note that the order in which the schemes appear in the list is relevant, since the tag guesser will go through the list from the top to the bottom, and use the first matching scheme." ) );
    QWhatsThis::add( lvSchemes, tr2i18n( "Here you can see the currently configured file name schemes which the \"Guess Tags From Filename\" button uses to extract tag information from a file name. Each string may contain one of the following placeholders:<ul>\n"
"<li>%title: Song Title</li>\n"
"<li>%artist: Artist</li>\n"
"<li>%album: Album</li>\n"
"<li>%track: Track Number</li>\n"
"<li>%comment: Comment</li>\n"
"</ul>\n"
"For example, the file name scheme \"[%track] %artist - %title\" would match \"[01] Deep Purple - Smoke on the water\" but not \"(Deep Purple) Smoke on the water\". For that second name, you would use the scheme \"(%a) %t\".<p/>\n"
"Note that the order in which the schemes appear in the list is relevant, since the tag guesser will go through the list from the top to the bottom, and use the first matching scheme." ) );
    bMoveUp->setText( QString::null );
    QToolTip::add( bMoveUp, tr2i18n( "Move scheme up" ) );
    QWhatsThis::add( bMoveUp, tr2i18n( "Press this button to move the currently selected scheme one step upwards." ) );
    bMoveDown->setText( QString::null );
    QToolTip::add( bMoveDown, tr2i18n( "Move scheme down" ) );
    QWhatsThis::add( bMoveDown, tr2i18n( "Press this button to move the currently selected scheme one step downwards." ) );
    bModify->setText( tr2i18n( "Mo&dify" ) );
    QToolTip::add( bModify, tr2i18n( "Modify scheme" ) );
    QWhatsThis::add( bModify, tr2i18n( "Press this button to modify the currently selected scheme." ) );
    bRemove->setText( tr2i18n( "&Remove" ) );
    QToolTip::add( bRemove, tr2i18n( "Remove scheme" ) );
    QWhatsThis::add( bRemove, tr2i18n( "Press this button to remove the currently selected scheme from the list." ) );
    bAdd->setText( tr2i18n( "&Add" ) );
    QToolTip::add( bAdd, tr2i18n( "Add a new scheme" ) );
    QWhatsThis::add( bAdd, tr2i18n( "Press this button to add a new file name scheme to the end of the list." ) );
    bOk->setText( tr2i18n( "O&k" ) );
    QToolTip::add( bOk, tr2i18n( "Add a new scheme" ) );
    QWhatsThis::add( bOk, tr2i18n( "Press this button to add a new file name scheme to the end of the list." ) );
    bCancel->setText( tr2i18n( "&Cancel" ) );
    QToolTip::add( bCancel, tr2i18n( "Add a new scheme" ) );
    QWhatsThis::add( bCancel, tr2i18n( "Press this button to add a new file name scheme to the end of the list." ) );
}

#include "tagguesserconfigdialog.moc"
