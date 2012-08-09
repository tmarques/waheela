/****************************************************************************
** Form interface generated from reading ui file './Options1.ui'
**
** Created: Sex Mar 23 10:37:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GENERAL_H
#define GENERAL_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QCheckBox;
class QLabel;
class QSpinBox;
class KComboBox;
class KLineEdit;
class QFrame;
class QComboBox;

class Options1 : public QWidget
{
    Q_OBJECT

public:
    Options1( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options1();

    QGroupBox* generalBox;
    QCheckBox* kcfg_ShowSplashscreen;
    QCheckBox* kcfg_ShowTrayIcon;
    QCheckBox* kcfg_AnimateTrayIcon;
    QCheckBox* kcfg_ShowPlayerWindow;
    QLabel* textLabel1;
    QSpinBox* kcfg_CoverPreviewSize;
    QLabel* textLabel1_2;
    KComboBox* kComboBox_browser;
    QCheckBox* checkBox_customBrowser;
    KLineEdit* kLineEdit_customBrowser;
    QGroupBox* componentsBox;
    QCheckBox* kcfg_UseScores;
    QCheckBox* kcfg_UseRatings;
    QFrame* moodFrame;
    QCheckBox* kcfg_ShowMoodbar;
    QCheckBox* kcfg_MakeMoodier;
    QComboBox* kcfg_AlterMood;
    QCheckBox* kcfg_MoodsWithMusic;
    QGroupBox* groupBox2;
    QCheckBox* kcfg_SavePlaylist;
    QCheckBox* kcfg_RelativePlaylist;
    QCheckBox* kcfg_PlaylistFollowActive;
    QCheckBox* kcfg_AutoShowContextBrowser;

public slots:
    virtual void slotUpdateMoodFrame();

protected:
    QVBoxLayout* GeneralLayout;
    QSpacerItem* spacer5;
    QVBoxLayout* generalBoxLayout;
    QHBoxLayout* layout5;
    QSpacerItem* spacer3_2;
    QHBoxLayout* layout4;
    QSpacerItem* spacer7;
    QHBoxLayout* layout7;
    QSpacerItem* spacer7_2;
    QHBoxLayout* layout8;
    QSpacerItem* spacer7_2_3;
    QVBoxLayout* componentsBoxLayout;
    QVBoxLayout* moodFrameLayout;
    QHBoxLayout* layout8_2;
    QSpacerItem* spacerMoodier;
    QSpacerItem* spacer7_2_2;
    QHBoxLayout* layout7_2;
    QSpacerItem* spacerWithMusic;
    QVBoxLayout* groupBox2Layout;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // GENERAL_H
