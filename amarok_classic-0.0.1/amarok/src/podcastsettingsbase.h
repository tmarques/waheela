/****************************************************************************
** Form interface generated from reading ui file './podcastsettingsbase.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
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
class QCheckBox;
class QLabel;
class QLineEdit;
class QButtonGroup;
class QRadioButton;
class KURLRequester;
class QSpinBox;

class PodcastSettingsDialogBase : public QWidget
{
    Q_OBJECT

public:
    PodcastSettingsDialogBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~PodcastSettingsDialogBase();

    QCheckBox* m_autoFetchCheck;
    QLabel* textLabel9;
    QLineEdit* m_urlLine;
    QButtonGroup* buttonGroup1;
    QRadioButton* m_streamRadio;
    QRadioButton* m_downloadRadio;
    QLabel* textLabel1;
    KURLRequester* m_saveLocation;
    QCheckBox* m_purgeCheck;
    QLabel* textLabel8;
    QSpinBox* m_purgeCountSpinBox;

protected:
    QGridLayout* Form1Layout;
    QHBoxLayout* layout32;
    QHBoxLayout* layout6;
    QGridLayout* buttonGroup1Layout;
    QHBoxLayout* layout5;
    QHBoxLayout* layout34;
    QSpacerItem* spacer16;

protected slots:
    virtual void languageChange();

};

#endif // FORM1_H
