/****************************************************************************
** Form interface generated from reading ui file './firstrunwizard.ui'
**
** Created: Sex Mar 23 10:37:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FIRSTRUNWIZARD_H
#define FIRSTRUNWIZARD_H

#include <qvariant.h>
#include <qpixmap.h>
#include <kwizard.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class DbSetup;
class QWidget;
class KActiveLabel;
class QLabel;
class QButtonGroup;
class QRadioButton;
class CollectionSetup;

class FirstRunWizard : public KWizard
{
    Q_OBJECT

public:
    FirstRunWizard( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FirstRunWizard();

    QWidget* WizardPage;
    KActiveLabel* text1;
    QLabel* picture1;
    KActiveLabel* text1_2;
    QWidget* WizardPage_1;
    QButtonGroup* group1;
    QRadioButton* option_compact;
    QRadioButton* option_xmms;
    KActiveLabel* text2;
    QLabel* picture_modePreview;
    QWidget* WizardPage_2;
    KActiveLabel* text3;
    QWidget* WizardPage_3;
    KActiveLabel* dbActiveLabel;
    DbSetup* dbSetup7;
    QWidget* WizardPage_4;
    KActiveLabel* text4;
    QLabel* picture4;

    enum Interface { XMMS, Compact };

    FirstRunWizard::Interface interface();
    void writeCollectionConfig();

public slots:
    virtual void openLink( const QString & s );

protected:
    virtual void showPage( QWidget * w );

    QGridLayout* WizardPageLayout;
    QSpacerItem* spacer1;
    QGridLayout* WizardPage_1Layout;
    QSpacerItem* spacer16;
    QSpacerItem* spacer17;
    QVBoxLayout* group1Layout;
    QHBoxLayout* layout3;
    QSpacerItem* spacer4;
    QHBoxLayout* WizardPageLayout_2;
    QGridLayout* WizardPage_3Layout;
    QSpacerItem* spacer15;
    QSpacerItem* spacer14;
    QHBoxLayout* WizardPage_4Layout;
    QSpacerItem* spacer3;

protected slots:
    virtual void languageChange();

private:
    CollectionSetup* m_folderSetup;

    QPixmap image0;

    void init();

private slots:
    void invokeHandbook();
    void xmmsModeToggled( bool on );

};

#endif // FIRSTRUNWIZARD_H
