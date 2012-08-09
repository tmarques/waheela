/****************************************************************************
** Form interface generated from reading ui file './Options4.ui'
**
** Created: Sex Mar 23 10:37:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
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
class QSpinBox;
class QLabel;
class QCheckBox;

class Options4 : public QWidget
{
    Q_OBJECT

public:
    Options4( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options4();

    QButtonGroup* opt_crossfade;
    QRadioButton* radioButtonNormalPlayback;
    QSpinBox* kcfg_TrackDelayLength;
    QSpinBox* kcfg_CrossfadeLength;
    QRadioButton* kcfg_Crossfade;
    QLabel* crossfadeLengthLabel;
    QCheckBox* kcfg_CrossfadeManualOnly;
    QLabel* trackDelayLengthLabel;
    QCheckBox* kcfg_ResumePlayback;

protected:
    QVBoxLayout* Options4Layout;
    QSpacerItem* spacer2;
    QGridLayout* opt_crossfadeLayout;
    QSpacerItem* spacer76;

protected slots:
    virtual void languageChange();

};

#endif // OPTIONS4_H
