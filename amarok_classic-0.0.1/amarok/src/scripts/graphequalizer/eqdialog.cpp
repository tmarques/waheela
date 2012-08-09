#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './eqdialog.ui'
**
** Created: Ter Fev 19 15:57:10 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "eqdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qslider.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "equalizercanvasview.h"
#include "./eqdialog.ui.h"

/*
 *  Constructs a EqDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
EqDialog::EqDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "EqDialog" );

    eqGroupBox = new QGroupBox( this, "eqGroupBox" );
    eqGroupBox->setGeometry( QRect( 20, 20, 511, 331 ) );
    eqGroupBox->setCheckable( TRUE );
    eqGroupBox->setChecked( TRUE );

    textLabel2 = new QLabel( eqGroupBox, "textLabel2" );
    textLabel2->setGeometry( QRect( 10, 288, 474, 35 ) );

    QWidget* privateLayoutWidget = new QWidget( eqGroupBox, "layout7" );
    privateLayoutWidget->setGeometry( QRect( 10, 20, 474, 262 ) );
    layout7 = new QHBoxLayout( privateLayoutWidget, 11, 6, "layout7"); 

    layout3 = new QVBoxLayout( 0, 0, 6, "layout3"); 

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 
    spacer2 = new QSpacerItem( 20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum );
    layout2->addItem( spacer2 );

    preampSlider = new QSlider( privateLayoutWidget, "preampSlider" );
    preampSlider->setMinValue( -100 );
    preampSlider->setMaxValue( 100 );
    preampSlider->setOrientation( QSlider::Vertical );
    layout2->addWidget( preampSlider );
    spacer1 = new QSpacerItem( 20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum );
    layout2->addItem( spacer1 );
    layout3->addLayout( layout2 );

    preampLabel = new QLabel( privateLayoutWidget, "preampLabel" );
    layout3->addWidget( preampLabel );
    layout7->addLayout( layout3 );

    canvasView = new EqualizerCanvasView( privateLayoutWidget, "canvasView" );
    canvasView->setMinimumSize( QSize( 404, 200 ) );
    canvasView->setMaximumSize( QSize( 404, 200 ) );
    layout7->addWidget( canvasView );
    languageChange();
    resize( QSize(542, 365).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( eqGroupBox, SIGNAL( toggled(bool) ), this, SLOT( eqGroupBox_toggled(bool) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
EqDialog::~EqDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void EqDialog::languageChange()
{
    setCaption( tr2i18n( "Graph Equalizer" ) );
    eqGroupBox->setTitle( tr2i18n( "Enable Equalizer" ) );
    textLabel2->setText( tr2i18n( "<p align=\"center\">The blue drag points can be dragged to adjust the equalizer. Double-click on the line to add a new drag point.</p>" ) );
    preampLabel->setText( tr2i18n( "<p align=\"center\">Pre-amp</p>" ) );
}

#include "eqdialog.moc"
