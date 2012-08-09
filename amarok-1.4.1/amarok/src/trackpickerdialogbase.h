/****************************************************************************
** Form interface generated from reading ui file './trackpickerdialogbase.ui'
**
** Created: Fri Mar 23 10:51:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TRACKPICKERDIALOGBASE_H
#define TRACKPICKERDIALOGBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QLabel;
class KListView;
class QListViewItem;

class TrackPickerDialogBase : public QWidget
{
    Q_OBJECT

public:
    TrackPickerDialogBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~TrackPickerDialogBase();

    QGroupBox* fileInfoGroup;
    QLabel* fileLabel;
    QGroupBox* trackInfoGroup;
    KListView* trackList;

protected:
    QVBoxLayout* trackPickerDialogBaseLayout;
    QHBoxLayout* fileLayout;
    QHBoxLayout* fileInfoGroupLayout;
    QHBoxLayout* trackLayout;
    QVBoxLayout* trackInfoGroupLayout;

protected slots:
    virtual void languageChange();

};

#endif // TRACKPICKERDIALOGBASE_H
