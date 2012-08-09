/****************************************************************************
** Form interface generated from reading ui file './Options4.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OPTIONS4_H
#define OPTIONS4_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QRadioButton;
class QLabel;
class QSpinBox;
class QCheckBox;

class Options4 : public QWidget
{
    Q_OBJECT

public:
    Options4( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options4();

    QButtonGroup* opt_crossfade;
    QRadioButton* radioButtonNormalPlayback;
    QLabel* trackDelayLengthLabel;
    QSpinBox* kcfg_TrackDelayLength;
    QRadioButton* kcfg_Crossfade;
    QLabel* crossfadeLengthLabel;
    QSpinBox* kcfg_CrossfadeLength;
    QCheckBox* kcfg_ResumePlayback;

protected:
    QVBoxLayout* Options4Layout;
    QSpacerItem* spacer2;
    QVBoxLayout* opt_crossfadeLayout;
    QVBoxLayout* layout3;
    QHBoxLayout* layout2;
    QVBoxLayout* layout5;
    QHBoxLayout* layout4;
    QVBoxLayout* layout9;

protected slots:
    virtual void languageChange();

};

#endif // OPTIONS4_H
