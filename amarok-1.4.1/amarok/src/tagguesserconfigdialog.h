/****************************************************************************
** Form interface generated from reading ui file './tagguesserconfigdialog.ui'
**
** Created: Fri Mar 23 10:51:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TAGGUESSERCONFIGDIALOG_H
#define TAGGUESSERCONFIGDIALOG_H

#include <qvariant.h>
#include <kdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class KListView;
class QListViewItem;
class QToolButton;
class KPushButton;

class TagGuesserConfigDialog : public KDialog
{
    Q_OBJECT

public:
    TagGuesserConfigDialog( QWidget* parent = 0, const char* name = 0 );
    ~TagGuesserConfigDialog();

    KListView* lvSchemes;
    QToolButton* bMoveUp;
    QToolButton* bMoveDown;
    KPushButton* bModify;
    KPushButton* bRemove;
    KPushButton* bAdd;
    KPushButton* bOk;
    KPushButton* bCancel;

public slots:
    void slotCurrentChanged( QListViewItem * item );
    virtual void accept();
    virtual void reject();
    void slotRenameItem( QListViewItem * item, const QPoint &, int c );
    void slotMoveUpClicked();
    void slotMoveDownClicked();
    void slotAddClicked();
    void slotModifyClicked();
    void slotRemoveClicked();

protected:
    QGridLayout* TagGuesserConfigDialogLayout;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // TAGGUESSERCONFIGDIALOG_H
