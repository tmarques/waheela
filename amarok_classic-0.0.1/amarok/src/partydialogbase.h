/****************************************************************************
** Form interface generated from reading ui file './partydialogbase.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef PARTYDIALOGBASE_H
#define PARTYDIALOGBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QComboBox;
class QCheckBox;
class QFrame;
class QLabel;
class KIntSpinBox;

class PartyDialogBase : public QWidget
{
    Q_OBJECT

public:
    PartyDialogBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~PartyDialogBase();

    QButtonGroup* m_buttonGroup;
    QComboBox* m_appendType;
    QCheckBox* m_cycleTracks;
    QCheckBox* m_markHistory;
    QFrame* line1;
    QLabel* textLabel1;
    KIntSpinBox* m_previousIntSpinBox;
    QLabel* textLabel2;
    KIntSpinBox* m_upcomingIntSpinBox;
    QLabel* textLabel3;
    KIntSpinBox* m_appendCountIntSpinBox;

public slots:
    virtual void kURLLabel2_leftClickedURL();

protected:
    QVBoxLayout* PartyDialogBaseLayout;
    QVBoxLayout* m_buttonGroupLayout;
    QHBoxLayout* layout13;
    QSpacerItem* spacer7;
    QHBoxLayout* layout11;
    QSpacerItem* spacer3;
    QHBoxLayout* layout12;
    QSpacerItem* spacer4;
    QHBoxLayout* layout13_2;
    QSpacerItem* spacer5;

protected slots:
    virtual void languageChange();

};

#endif // PARTYDIALOGBASE_H
