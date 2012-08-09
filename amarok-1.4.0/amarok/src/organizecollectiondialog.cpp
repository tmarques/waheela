#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './organizecollectiondialog.ui'
**
** Created: Sex Mar 23 10:42:44 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "organizecollectiondialog.h"

#include <qvariant.h>
#include <qdialog.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <klineedit.h>
#include <kactivelabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kcombobox.h"
#include "klineedit.h"
#include "kactivelabel.h"
#include "./organizecollectiondialog.ui.h"

/*
 *  Constructs a OrganizeCollectionDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
OrganizeCollectionDialog::OrganizeCollectionDialog( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "organizeCollectionDialog" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, sizePolicy().hasHeightForWidth() ) );
    organizeCollectionDialogLayout = new QVBoxLayout( this, 0, 6, "organizeCollectionDialogLayout"); 

    folderLayout = new QHBoxLayout( 0, 5, 6, "folderLayout"); 

    folderLabel = new QLabel( this, "folderLabel" );
    folderLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, folderLabel->sizePolicy().hasHeightForWidth() ) );
    folderLayout->addWidget( folderLabel );

    folderCombo = new KComboBox( FALSE, this, "folderCombo" );
    folderCombo->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, folderCombo->sizePolicy().hasHeightForWidth() ) );
    folderLayout->addWidget( folderCombo );
    organizeCollectionDialogLayout->addLayout( folderLayout );

    coverCheck = new QCheckBox( this, "coverCheck" );
    organizeCollectionDialogLayout->addWidget( coverCheck );

    ignoreTheCheck = new QCheckBox( this, "ignoreTheCheck" );
    organizeCollectionDialogLayout->addWidget( ignoreTheCheck );

    groupingGroup = new QGroupBox( this, "groupingGroup" );
    groupingGroup->setMargin( 0 );
    groupingGroup->setColumnLayout(0, Qt::Vertical );
    groupingGroup->layout()->setSpacing( 6 );
    groupingGroup->layout()->setMargin( 5 );
    groupingGroupLayout = new QVBoxLayout( groupingGroup->layout() );
    groupingGroupLayout->setAlignment( Qt::AlignTop );

    customschemeCheck = new QCheckBox( groupingGroup, "customschemeCheck" );
    groupingGroupLayout->addWidget( customschemeCheck );

    filetypeCheck = new QCheckBox( groupingGroup, "filetypeCheck" );
    groupingGroupLayout->addWidget( filetypeCheck );

    initialCheck = new QCheckBox( groupingGroup, "initialCheck" );
    groupingGroupLayout->addWidget( initialCheck );

    customFormatLayout = new QHBoxLayout( 0, 0, 6, "customFormatLayout"); 

    formatLabel = new QLabel( groupingGroup, "formatLabel" );
    formatLabel->setEnabled( FALSE );
    customFormatLayout->addWidget( formatLabel );

    formatEdit = new KLineEdit( groupingGroup, "formatEdit" );
    formatEdit->setEnabled( FALSE );
    customFormatLayout->addWidget( formatEdit );

    formatHelp = new KActiveLabel( groupingGroup, "formatHelp" );
    formatHelp->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, formatHelp->sizePolicy().hasHeightForWidth() ) );
    customFormatLayout->addWidget( formatHelp );
    groupingGroupLayout->addLayout( customFormatLayout );
    organizeCollectionDialogLayout->addWidget( groupingGroup );

    replacementGroup = new QGroupBox( this, "replacementGroup" );
    replacementGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, replacementGroup->sizePolicy().hasHeightForWidth() ) );
    replacementGroup->setMargin( 0 );
    replacementGroup->setColumnLayout(0, Qt::Vertical );
    replacementGroup->layout()->setSpacing( 6 );
    replacementGroup->layout()->setMargin( 5 );
    replacementGroupLayout = new QVBoxLayout( replacementGroup->layout() );
    replacementGroupLayout->setAlignment( Qt::AlignTop );

    spaceCheck = new QCheckBox( replacementGroup, "spaceCheck" );
    replacementGroupLayout->addWidget( spaceCheck );

    asciiCheck = new QCheckBox( replacementGroup, "asciiCheck" );
    replacementGroupLayout->addWidget( asciiCheck );

    vfatCheck = new QCheckBox( replacementGroup, "vfatCheck" );
    replacementGroupLayout->addWidget( vfatCheck );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    textLabel1 = new QLabel( replacementGroup, "textLabel1" );
    layout4->addWidget( textLabel1 );

    regexpEdit = new KLineEdit( replacementGroup, "regexpEdit" );
    layout4->addWidget( regexpEdit );

    textLabel2 = new QLabel( replacementGroup, "textLabel2" );
    layout4->addWidget( textLabel2 );

    replaceEdit = new KLineEdit( replacementGroup, "replaceEdit" );
    layout4->addWidget( replaceEdit );
    replacementGroupLayout->addLayout( layout4 );
    organizeCollectionDialogLayout->addWidget( replacementGroup );

    previewBox = new QGroupBox( this, "previewBox" );
    previewBox->setColumnLayout(0, Qt::Vertical );
    previewBox->layout()->setSpacing( 0 );
    previewBox->layout()->setMargin( 5 );
    previewBoxLayout = new QGridLayout( previewBox->layout() );
    previewBoxLayout->setAlignment( Qt::AlignTop );

    previewText = new QLabel( previewBox, "previewText" );
    previewText->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, previewText->sizePolicy().hasHeightForWidth() ) );

    previewBoxLayout->addWidget( previewText, 0, 1 );
    organizeCollectionDialogLayout->addWidget( previewBox );

    overwriteLayout = new QHBoxLayout( 0, 5, 6, "overwriteLayout"); 
    spacer2_2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    overwriteLayout->addItem( spacer2_2 );

    overwriteCheck = new QCheckBox( this, "overwriteCheck" );
    overwriteLayout->addWidget( overwriteCheck );
    organizeCollectionDialogLayout->addLayout( overwriteLayout );
    languageChange();
    resize( QSize(476, 561).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( customschemeCheck, SIGNAL( toggled(bool) ), formatEdit, SLOT( setEnabled(bool) ) );
    connect( customschemeCheck, SIGNAL( toggled(bool) ), formatLabel, SLOT( setEnabled(bool) ) );
    connect( customschemeCheck, SIGNAL( toggled(bool) ), filetypeCheck, SLOT( setDisabled(bool) ) );
    connect( customschemeCheck, SIGNAL( toggled(bool) ), initialCheck, SLOT( setDisabled(bool) ) );
    connect( formatEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( preview(const QString&) ) );
    connect( this, SIGNAL( updatePreview( const QString & ) ), previewText, SLOT( setText(const QString&) ) );
    connect( customschemeCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( filetypeCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( initialCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( spaceCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( asciiCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( vfatCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( ignoreTheCheck, SIGNAL( stateChanged(int) ), this, SLOT( update(int) ) );
    connect( folderCombo, SIGNAL( activated(int) ), this, SLOT( update(int) ) );
    connect( regexpEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( update(const QString&) ) );
    connect( replaceEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( update(const QString&) ) );

    // buddies
    folderLabel->setBuddy( folderCombo );
    formatLabel->setBuddy( formatEdit );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
OrganizeCollectionDialog::~OrganizeCollectionDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OrganizeCollectionDialog::languageChange()
{
    setCaption( tr2i18n( "Organize Files" ) );
    folderLabel->setText( tr2i18n( "C&ollection Folder:" ) );
    QToolTip::add( folderLabel, tr2i18n( "Base directory under which to put files" ) );
    QToolTip::add( folderCombo, QString::null );
    coverCheck->setText( tr2i18n( "&Use Cover Art for Folder Icons" ) );
    ignoreTheCheck->setText( tr2i18n( "I&gnore 'The' in Artist Names" ) );
    QToolTip::add( ignoreTheCheck, tr2i18n( "If checked, postfix artists' names starting with 'The' with ', The'." ) );
    groupingGroup->setTitle( tr2i18n( "File Naming Scheme" ) );
    customschemeCheck->setText( tr2i18n( "Custo&m Format" ) );
    QToolTip::add( customschemeCheck, tr2i18n( "If checked, use a custom format string for naming the files in the collection" ) );
    filetypeCheck->setText( tr2i18n( "Group b&y File Type" ) );
    QToolTip::add( filetypeCheck, tr2i18n( "If checked, create a directory hierarchy using the filename extension." ) );
    initialCheck->setText( tr2i18n( "Group &by Artist's Initial" ) );
    QToolTip::add( initialCheck, tr2i18n( "If checked, introduce another directory hierarchy for the artists' initials." ) );
    formatLabel->setText( tr2i18n( "F&ilename Format:" ) );
    formatEdit->setText( QString::null );
    formatHelp->setText( tr2i18n( "(Help)" ) );
    replacementGroup->setTitle( tr2i18n( "Character Replacement" ) );
    spaceCheck->setText( tr2i18n( "&Replace Spaces with Underscores" ) );
    QToolTip::add( spaceCheck, tr2i18n( "If checked, convert spaces to underscores." ) );
    asciiCheck->setText( tr2i18n( "Restrict to &ASCII" ) );
    QToolTip::add( asciiCheck, tr2i18n( "If checked, replace characters that are unavailable in the 7-bit ASCII code." ) );
    vfatCheck->setText( tr2i18n( "VFAT Safe &Names" ) );
    QToolTip::add( vfatCheck, tr2i18n( "If checked, replace characters that are incompatible with MS-DOS/VFAT file systems." ) );
    textLabel1->setText( tr2i18n( "Replace" ) );
    QToolTip::add( regexpEdit, tr2i18n( "Regular expression" ) );
    textLabel2->setText( tr2i18n( "with" ) );
    QToolTip::add( replaceEdit, tr2i18n( "Character string" ) );
    previewBox->setTitle( tr2i18n( "Destination Preview" ) );
    previewText->setText( QString::null );
    QToolTip::add( previewText, tr2i18n( "This is what the file names will look like after renaming." ) );
    overwriteCheck->setText( tr2i18n( "Overwrite &Destination" ) );
    QToolTip::add( overwriteCheck, tr2i18n( "If checked, overwrite files of the same name without asking." ) );
}

#include "organizecollectiondialog.moc"
