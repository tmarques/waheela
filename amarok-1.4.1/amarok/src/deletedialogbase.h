/****************************************************************************
** Form interface generated from reading ui file './deletedialogbase.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DELETEDIALOGBASE_H
#define DELETEDIALOGBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class KListBox;
class QListBoxItem;
class QCheckBox;

class DeleteDialogBase : public QWidget
{
    Q_OBJECT

public:
    DeleteDialogBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~DeleteDialogBase();

    QLabel* ddWarningIcon;
    QLabel* ddDeleteText;
    KListBox* ddFileList;
    QLabel* ddNumFiles;
    QCheckBox* ddShouldDelete;

protected:
    QVBoxLayout* DeleteDialogBaseLayout;
    QHBoxLayout* layout4;
    QVBoxLayout* layout3;

protected slots:
    virtual void languageChange();

    virtual void slotShouldDelete(bool);


};

#endif // DELETEDIALOGBASE_H
