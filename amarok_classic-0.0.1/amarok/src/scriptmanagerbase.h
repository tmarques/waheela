/****************************************************************************
** Form interface generated from reading ui file './scriptmanagerbase.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SCRIPTMANAGERBASE_H
#define SCRIPTMANAGERBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class KListView;
class QListViewItem;
class QPushButton;
class QFrame;
class QCheckBox;

class ScriptManagerBase : public QWidget
{
    Q_OBJECT

public:
    ScriptManagerBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ScriptManagerBase();

    KListView* listView;
    QPushButton* installButton;
    QPushButton* retrieveButton;
    QFrame* line2_2;
    QPushButton* aboutButton;
    QPushButton* runButton;
    QPushButton* stopButton;
    QPushButton* configureButton;
    QPushButton* uninstallButton;
    QFrame* line2;
    QCheckBox* checkBox_autoRun;

protected:
    QVBoxLayout* ScriptManagerBaseLayout;
    QHBoxLayout* layout6;
    QVBoxLayout* layout5;
    QSpacerItem* spacer2;
    QVBoxLayout* layout3;

protected slots:
    virtual void languageChange();

};

#endif // SCRIPTMANAGERBASE_H
