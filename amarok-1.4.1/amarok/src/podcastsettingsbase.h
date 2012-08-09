/****************************************************************************
** Form interface generated from reading ui file './podcastsettingsbase.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FORM1_H
#define FORM1_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QRadioButton;
class QCheckBox;
class QLabel;
class QSpinBox;
class KURLRequester;

class PodcastSettingsDialogBase : public QWidget
{
    Q_OBJECT

public:
    PodcastSettingsDialogBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~PodcastSettingsDialogBase();

    QButtonGroup* buttonGroup1;
    QRadioButton* m_streamRadio;
    QRadioButton* m_downloadRadio;
    QCheckBox* m_addToMediaDeviceCheck;
    QCheckBox* m_purgeCheck;
    QLabel* m_purgeCountLabel;
    QSpinBox* m_purgeCountSpinBox;
    QCheckBox* m_autoFetchCheck;
    QLabel* textLabel1;
    KURLRequester* m_saveLocation;

protected:
    QGridLayout* Form1Layout;
    QSpacerItem* spacer16;
    QSpacerItem* spacer17;
    QVBoxLayout* buttonGroup1Layout;

protected slots:
    virtual void languageChange();

};

#endif // FORM1_H
