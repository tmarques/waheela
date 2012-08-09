#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './firstrunwizard.ui'
**
** Created: Ter Fev 19 16:01:41 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "firstrunwizard.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <kactivelabel.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "kactivelabel.h"
#include "dbsetup.h"
#include "./firstrunwizard.ui.h"

/*
 *  Constructs a FirstRunWizard as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The wizard will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal wizard.
 */
FirstRunWizard::FirstRunWizard( QWidget* parent, const char* name, bool modal, WFlags fl )
    : KWizard( parent, name, modal, fl )
{
    if ( !name )
	setName( "FirstRunWizard" );

    WizardPage = new QWidget( this, "WizardPage" );
    WizardPageLayout = new QGridLayout( WizardPage, 1, 1, 11, 6, "WizardPageLayout"); 

    text1 = new KActiveLabel( WizardPage, "text1" );

    WizardPageLayout->addWidget( text1, 0, 0 );

    picture1 = new QLabel( WizardPage, "picture1" );
    picture1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)4, 0, 0, picture1->sizePolicy().hasHeightForWidth() ) );
    picture1->setFrameShape( QLabel::Box );
    picture1->setScaledContents( FALSE );

    WizardPageLayout->addWidget( picture1, 0, 2 );
    spacer3_2 = new QSpacerItem( 21, 320, QSizePolicy::Minimum, QSizePolicy::Expanding );
    WizardPageLayout->addItem( spacer3_2, 0, 1 );
    addPage( WizardPage, QString("") );

    WizardPage_1 = new QWidget( this, "WizardPage_1" );
    WizardPage_1Layout = new QGridLayout( WizardPage_1, 1, 1, 11, 6, "WizardPage_1Layout"); 

    group1 = new QButtonGroup( WizardPage_1, "group1" );
    group1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, group1->sizePolicy().hasHeightForWidth() ) );
    group1->setFrameShape( QButtonGroup::NoFrame );
    group1->setProperty( "selectedId", 0 );
    group1->setColumnLayout(0, Qt::Vertical );
    group1->layout()->setSpacing( 20 );
    group1->layout()->setMargin( 11 );
    group1Layout = new QVBoxLayout( group1->layout() );
    group1Layout->setAlignment( Qt::AlignTop );

    option_compact = new QRadioButton( group1, "option_compact" );
    option_compact->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, option_compact->sizePolicy().hasHeightForWidth() ) );
    group1Layout->addWidget( option_compact );

    option_xmms = new QRadioButton( group1, "option_xmms" );
    option_xmms->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, option_xmms->sizePolicy().hasHeightForWidth() ) );
    option_xmms->setChecked( FALSE );
    group1Layout->addWidget( option_xmms );

    WizardPage_1Layout->addWidget( group1, 2, 0 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    text2 = new KActiveLabel( WizardPage_1, "text2" );
    text2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, text2->sizePolicy().hasHeightForWidth() ) );
    text2->setResizePolicy( KActiveLabel::Manual );
    text2->setWrapPolicy( KActiveLabel::AtWordBoundary );
    layout3->addWidget( text2 );
    spacer4 = new QSpacerItem( 71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer4 );

    WizardPage_1Layout->addMultiCellLayout( layout3, 0, 0, 0, 1 );

    picture_modePreview = new QLabel( WizardPage_1, "picture_modePreview" );
    picture_modePreview->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)4, 0, 0, picture_modePreview->sizePolicy().hasHeightForWidth() ) );
    picture_modePreview->setBackgroundMode( QLabel::PaletteBackground );
    picture_modePreview->setFrameShape( QLabel::Box );
    picture_modePreview->setAlignment( int( QLabel::AlignTop | QLabel::AlignLeft ) );

    WizardPage_1Layout->addWidget( picture_modePreview, 2, 1 );
    spacer16 = new QSpacerItem( 21, 20, QSizePolicy::Minimum, QSizePolicy::Fixed );
    WizardPage_1Layout->addItem( spacer16, 1, 0 );
    spacer17 = new QSpacerItem( 21, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    WizardPage_1Layout->addItem( spacer17, 3, 0 );
    addPage( WizardPage_1, QString("") );

    WizardPage_2 = new QWidget( this, "WizardPage_2" );
    WizardPageLayout_2 = new QHBoxLayout( WizardPage_2, 11, 6, "WizardPageLayout_2"); 

    text3 = new KActiveLabel( WizardPage_2, "text3" );
    text3->setLineWidth( 1 );
    WizardPageLayout_2->addWidget( text3 );
    addPage( WizardPage_2, QString("") );

    WizardPage_3 = new QWidget( this, "WizardPage_3" );
    WizardPage_3Layout = new QGridLayout( WizardPage_3, 1, 1, 11, 6, "WizardPage_3Layout"); 
    spacer15 = new QSpacerItem( 20, 257, QSizePolicy::Minimum, QSizePolicy::Expanding );
    WizardPage_3Layout->addMultiCell( spacer15, 1, 2, 0, 0 );
    spacer14 = new QSpacerItem( 20, 194, QSizePolicy::Minimum, QSizePolicy::Expanding );
    WizardPage_3Layout->addItem( spacer14, 2, 1 );

    dbActiveLabel = new KActiveLabel( WizardPage_3, "dbActiveLabel" );

    WizardPage_3Layout->addWidget( dbActiveLabel, 0, 0 );

    dbSetup7 = new DbSetup( WizardPage_3, "dbSetup7" );

    WizardPage_3Layout->addMultiCellWidget( dbSetup7, 0, 1, 1, 1 );
    addPage( WizardPage_3, QString("") );

    WizardPage_4 = new QWidget( this, "WizardPage_4" );
    WizardPage_4Layout = new QHBoxLayout( WizardPage_4, 11, 6, "WizardPage_4Layout"); 

    text4 = new KActiveLabel( WizardPage_4, "text4" );
    text4->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, text4->sizePolicy().hasHeightForWidth() ) );
    text4->setMaximumSize( QSize( 32767, 32767 ) );
    WizardPage_4Layout->addWidget( text4 );
    spacer3 = new QSpacerItem( 21, 294, QSizePolicy::Minimum, QSizePolicy::Expanding );
    WizardPage_4Layout->addItem( spacer3 );

    picture4 = new QLabel( WizardPage_4, "picture4" );
    picture4->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)4, 0, 0, picture4->sizePolicy().hasHeightForWidth() ) );
    picture4->setFrameShape( QLabel::Box );
    picture4->setScaledContents( FALSE );
    WizardPage_4Layout->addWidget( picture4 );
    addPage( WizardPage_4, QString("") );
    languageChange();
    resize( QSize(830, 414).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( option_xmms, SIGNAL( toggled(bool) ), this, SLOT( xmmsModeToggled(bool) ) );

    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
FirstRunWizard::~FirstRunWizard()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FirstRunWizard::languageChange()
{
    setCaption( tr2i18n( "First-Run Wizard" ) );
    text1->setText( tr2i18n( "<h1>Welcome!</h1>\n"
"<p>There are many media-players around these days, this is true. But what's missing from most players is an interface that doesn't get in your way. How many buttons do you have to press when simply adding media to the playlist? amaroK tries to be a little different, providing a simple drag-and-drop interface that makes playlist handling really easy.</p>\n"
"<p align=\"right\"><i>\"amaroK is seriously super!\"</i> - Uncle Rodney</p>\n"
"<h2>First-run Wizard</h2>\n"
"<p>This wizard will help you setup amaroK in three easy steps. Click <i>Next</i> to begin, or if you do not like wizards, click <i>Skip</i>.</p>" ) );
    setTitle( WizardPage, QString::null );
    group1->setTitle( QString::null );
    option_compact->setText( tr2i18n( "Single window with player and playlist functionality\n"
"combined (like JuK)" ) );
    option_xmms->setText( tr2i18n( "Separate player and playlist-windows\n"
"(like XMMS or Winamp)" ) );
    text2->setText( tr2i18n( "<p>With amaroK you can use the window layout that you find most comfortable.</p>\n"
"<p>You can change these settings at a later time using the configuration dialog.</p>" ) );
    picture_modePreview->setText( QString::null );
    setTitle( WizardPage_1, tr2i18n( "Interface (1 of 3)" ) );
    text3->setText( tr2i18n( "<p>Please select the folders on the right where your music files are stored.</p>\n"
"<p>Doing so is highly recommended, and will enhance the features available to you.</p>\n"
"<p>If you wish, amaroK is able to monitor these folders for new files and can automatically add them to the collection.</p>" ) );
    setTitle( WizardPage_2, tr2i18n( "Collection (2 of 3)" ) );
    dbActiveLabel->setText( tr2i18n( "amaroK uses a database to store information about your music. If you are not sure which to use, press Next.\n"
"<p><b>MySQL</b> or <b>Postgresql</b> are faster than <b>sqlite</b>, but require additional setup.</p>\n"
"<ul>\n"
"<li><a href=\"http://amarok.kde.org/amarokwiki/index.php/MySQL_HowTo\">Instructions for configuring MySQL</a>.</li>\n"
"<li><a href=\"http://amarok.kde.org/amarokwiki/index.php/Postgresql_HowTo\">Instructions for configuring Postgresql</a>.</li>\n"
"</ul>" ) );
    setTitle( WizardPage_3, tr2i18n( "Database (3 of 3)" ) );
    text4->setText( tr2i18n( "<h1>Congratulations!</h1>\n"
"<p>amaroK is ready for use! When you click finish amaroK will appear and begin scanning the folders in your collection.</p>\n"
"<p>amaroK's playlist-window will show your <b>Collection</b> on the left and the <b>Playlist</b> on the right. Drag and drop music from the Collection to the Playlist and press <b>Play</b>.</p>\n"
"<p>If you want more help or a tutorial, please check out the <a href=\"help:/amarok\">amaroK handbook</a>. We hope you enjoy using amaroK.</p>\n"
"<p align=\"right\">The amaroK developers</p>" ) );
    setTitle( WizardPage_4, QString::null );
}

#include "firstrunwizard.moc"
