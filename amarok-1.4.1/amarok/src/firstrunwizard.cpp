#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './firstrunwizard.ui'
**
** Created: Fri Mar 23 10:56:46 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "firstrunwizard.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <kactivelabel.h>
#include <qlabel.h>
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

    WizardPageLayout->addMultiCellWidget( text1, 0, 1, 0, 0 );

    picture1 = new QLabel( WizardPage, "picture1" );
    picture1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)4, 0, 0, picture1->sizePolicy().hasHeightForWidth() ) );
    picture1->setFrameShape( QLabel::Box );
    picture1->setScaledContents( FALSE );

    WizardPageLayout->addWidget( picture1, 0, 2 );

    text1_2 = new KActiveLabel( WizardPage, "text1_2" );

    WizardPageLayout->addMultiCellWidget( text1_2, 2, 2, 0, 2 );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    WizardPageLayout->addItem( spacer1, 1, 1 );
    addPage( WizardPage, QString("") );

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
    resize( QSize(824, 410).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections

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
    text1->setText( tr2i18n( "<h1>Welcome to Amarok!</h1>\n"
"<p>There are many media-players around these days, this is true. Amarok however provides an aural experience so pleasurable it always has you coming back for more. What is missing from most players is an interface that does not get in your way. Amarok tries to be a little different, and at the same time intuitive. It provides a simple drag-and-drop interface that makes playlist handling simple and fun. By using Amarok we truly hope you will:</p>\n"
"<p align=\"center\"><i><b>\"Rediscover your music!\"</b></i> </p>" ) );
    text1_2->setText( tr2i18n( "<h2>First-run Wizard</h2>\n"
"<p>This wizard will help you setup Amarok in three easy steps. Click <i>Next</i> to begin, or if you do not like wizards, click <i>Skip</i>.</p>" ) );
    setTitle( WizardPage, QString::null );
    text3->setText( tr2i18n( "<p>Please select the folders on the right where your music files are stored.</p>\n"
"<p>Doing so is highly recommended, and will enhance the features available to you.</p>\n"
"<p>If you wish, Amarok is able to monitor these folders for new files and can automatically add them to the collection.</p>" ) );
    setTitle( WizardPage_2, tr2i18n( "Locate your Music" ) );
    dbActiveLabel->setText( tr2i18n( "Amarok uses a database to store information about your music. If you are not sure which to use, press Next.\n"
"<p><b>MySQL</b> or <b>Postgresql</b> are faster than <b>sqlite</b>, but require additional setup.</p>\n"
"<ul>\n"
"<li><a href=\"http://amarok.kde.org/amarokwiki/index.php/MySQL_HowTo\">Instructions for configuring MySQL</a>.</li>\n"
"<li><a href=\"http://amarok.kde.org/amarokwiki/index.php/Postgresql_HowTo\">Instructions for configuring Postgresql</a>.</li>\n"
"</ul>" ) );
    setTitle( WizardPage_3, tr2i18n( "Database Setup" ) );
    text4->setText( tr2i18n( "<h1>Congratulations!</h1>\n"
"<p>Amarok is ready for use! When you click finish Amarok will appear and begin scanning the folders in your collection.</p>\n"
"<p>Amarok's playlist-window will show your <b>Collection</b> on the left and the <b>Playlist</b> on the right. Drag and drop music from the Collection to the Playlist and press <b>Play</b>.</p>\n"
"<p>If you want more help or a tutorial, please check out the <a href=\"help:/amarok\">Amarok handbook</a>. We hope you enjoy using Amarok.</p>\n"
"<p align=\"right\">The Amarok developers</p>" ) );
    setTitle( WizardPage_4, QString::null );
}

#include "firstrunwizard.moc"
