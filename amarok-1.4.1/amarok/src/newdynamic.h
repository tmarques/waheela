/****************************************************************************
** Form interface generated from reading ui file './newdynamic.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NEWDYNAMIC_H
#define NEWDYNAMIC_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class PlaylistSelection;
class QLabel;
class KIntSpinBox;
class QLineEdit;
class QCheckBox;
class QFrame;

class NewDynamic : public QWidget
{
    Q_OBJECT

public:
    NewDynamic( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~NewDynamic();

    QLabel* textLabel1;
    KIntSpinBox* m_upcomingIntSpinBox;
    QLabel* textLabel2;
    QLabel* m_playlistName_label;
    QLineEdit* m_name;
    KIntSpinBox* m_previousIntSpinBox;
    QCheckBox* m_cycleTracks;
    PlaylistSelection* selectPlaylist;
    QFrame* line1;
    QFrame* line1_2;
    QLabel* m_mixLabel;
    QCheckBox* m_markHistory;

protected:
    QGridLayout* NewDynamicLayout;
    QSpacerItem* spacer5_2;
    QSpacerItem* spacer3;
    QSpacerItem* spacer4;
    QSpacerItem* spacer5;
    QSpacerItem* spacer7;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // NEWDYNAMIC_H
