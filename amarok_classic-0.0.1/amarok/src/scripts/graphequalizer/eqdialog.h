/****************************************************************************
** Form interface generated from reading ui file './eqdialog.ui'
**
** Created: Ter Fev 19 15:57:06 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef EQDIALOG_H
#define EQDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class EqualizerCanvasView;
class QGroupBox;
class QLabel;
class QSlider;

class EqDialog : public QDialog
{
    Q_OBJECT

public:
    EqDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~EqDialog();

    QGroupBox* eqGroupBox;
    QLabel* textLabel2;
    QSlider* preampSlider;
    QLabel* preampLabel;
    EqualizerCanvasView* canvasView;

    void init();

public slots:
    virtual void eqGroupBox_toggled( bool eqEnabled );

protected:
    QHBoxLayout* layout7;
    QVBoxLayout* layout3;
    QHBoxLayout* layout2;
    QSpacerItem* spacer2;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // EQDIALOG_H
