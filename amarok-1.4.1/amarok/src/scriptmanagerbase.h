/****************************************************************************
** Form interface generated from reading ui file './scriptmanagerbase.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
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

class ScriptManagerBase : public QWidget
{
    Q_OBJECT

public:
    ScriptManagerBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ScriptManagerBase();

    KListView* listView;
    QPushButton* retrieveButton;
    QPushButton* installButton;
    QFrame* line2_2;
    QPushButton* aboutButton;
    QPushButton* runButton;
    QPushButton* stopButton;
    QPushButton* configureButton;
    QPushButton* uninstallButton;

protected:
    QGridLayout* ScriptManagerBaseLayout;
    QSpacerItem* spacer2;

protected slots:
    virtual void languageChange();

};

#endif // SCRIPTMANAGERBASE_H
