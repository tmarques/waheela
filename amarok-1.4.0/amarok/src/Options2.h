/****************************************************************************
** Form interface generated from reading ui file './Options2.ui'
**
** Created: Sex Mar 23 10:37:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OPTIONS2_H
#define OPTIONS2_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QCheckBox;
class QLabel;
class KFontRequester;
class QButtonGroup;
class QRadioButton;
class KColorButton;
class KComboBox;
class QPushButton;

class Options2 : public QWidget
{
    Q_OBJECT

public:
    Options2( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options2();

    QGroupBox* groupBox6;
    QCheckBox* kcfg_UseCustomIconTheme;
    QGroupBox* groupBox4;
    QCheckBox* kcfg_UseCustomFonts;
    QGroupBox* fontGroupBox;
    QLabel* textLabel3;
    KFontRequester* kcfg_PlaylistWindowFont;
    QLabel* textLabel1;
    KFontRequester* kcfg_PlayerWidgetFont;
    QLabel* textLabel3_2;
    KFontRequester* kcfg_ContextBrowserFont;
    QGroupBox* groupBox3;
    QButtonGroup* radioGroup;
    QRadioButton* kcfg_SchemeCustom;
    QGroupBox* customSchemeBox;
    QLabel* fgLabel;
    KColorButton* kcfg_PlaylistWindowFgColor;
    QLabel* bgColor;
    KColorButton* kcfg_PlaylistWindowBgColor;
    QRadioButton* kcfg_SchemeKDE;
    QRadioButton* kcfg_SchemeAmarok;
    QGroupBox* contextGroupBox;
    QLabel* textLabel1_2;
    KComboBox* styleComboBox;
    QPushButton* installPushButton;
    QPushButton* retrievePushButton;
    QPushButton* uninstallPushButton;

public slots:
    virtual void installPushButton_clicked();
    virtual void retrievePushButton_clicked();
    virtual void uninstallPushButton_clicked();
    virtual void styleComboBox_activated( const QString & s );

protected:
    QVBoxLayout* Options2Layout;
    QSpacerItem* spacer1;
    QVBoxLayout* groupBox6Layout;
    QVBoxLayout* groupBox4Layout;
    QVBoxLayout* fontGroupBoxLayout;
    QHBoxLayout* layout5;
    QHBoxLayout* layout4;
    QHBoxLayout* layout6;
    QGridLayout* groupBox3Layout;
    QGridLayout* radioGroupLayout;
    QVBoxLayout* layout2;
    QGridLayout* customSchemeBoxLayout;
    QVBoxLayout* contextGroupBoxLayout;
    QHBoxLayout* layout6_2;
    QHBoxLayout* layout5_2;
    QSpacerItem* spacer2;

protected slots:
    virtual void languageChange();

private:
    void init();
    void updateStyleComboBox();

};

#endif // OPTIONS2_H
