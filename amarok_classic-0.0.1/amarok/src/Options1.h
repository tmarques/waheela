/****************************************************************************
** Form interface generated from reading ui file './Options1.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
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
class QComboBox;

class Options1 : public QWidget
{
    Q_OBJECT

public:
    Options1( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options1();

    QGroupBox* groupBox1;
    QCheckBox* kcfg_ShowSplashscreen;
    QCheckBox* kcfg_ShowTrayIcon;
    QCheckBox* kcfg_AnimateTrayIcon;
    QCheckBox* kcfg_ShowPlayerWindow;
    QLabel* textLabel1;
    QSpinBox* kcfg_CoverPreviewSize;
    QGroupBox* groupBox2;
    QCheckBox* kcfg_SavePlaylist;
    QCheckBox* kcfg_RelativePlaylist;
    QCheckBox* kcfg_PlaylistFollowActive;
    QCheckBox* kcfg_AutoShowContextBrowser;
    QCheckBox* kcfg_ShowStatusBar;
    QCheckBox* kcfg_ShowStatByAlbums;
    QGroupBox* groupBox5;
    QLabel* textLabel2;
    QCheckBox* kcfg_RecodeID3v1Tags;
    QCheckBox* kcfg_RecodeShoutcastMetadata;
    QLabel* textLabel1_3;
    QComboBox* kcfg_RecodeEncoding;

protected:
    QVBoxLayout* GeneralLayout;
    QSpacerItem* spacer5;
    QVBoxLayout* groupBox1Layout;
    QHBoxLayout* layout5;
    QSpacerItem* spacer3_2;
    QHBoxLayout* layout4;
    QSpacerItem* spacer7;
    QVBoxLayout* groupBox2Layout;
    QVBoxLayout* groupBox5Layout;
    QHBoxLayout* layout3;
    QSpacerItem* spacer3;
    QVBoxLayout* layout2;
    QHBoxLayout* layout7;

protected slots:
    virtual void languageChange();

};

#endif // GENERAL_H
