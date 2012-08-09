/****************************************************************************
** Form interface generated from reading ui file './Options5.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OPTIONS5_H
#define OPTIONS5_H

#include <qvariant.h>
#include <qwidget.h>
#include "osd.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QCheckBox;
class QGroupBox;
class KFontRequester;
class QLabel;
class KColorButton;
class KTextEdit;
class KIntSpinBox;
class KComboBox;

class Options5 : public QWidget
{
    Q_OBJECT

public:
    Options5( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options5();

    QCheckBox* kcfg_OsdEnabled;
    QGroupBox* mainBox;
    QGroupBox* fontBox;
    KFontRequester* kcfg_OsdFont;
    QCheckBox* kcfg_OsdDrawShadow;
    QGroupBox* groupBox9;
    QCheckBox* kcfg_OsdUseCustomColors;
    QGroupBox* colorsBox;
    QLabel* textLabel2_2;
    KColorButton* kcfg_OsdTextColor;
    KColorButton* kcfg_OsdBackgroundColor;
    QLabel* textLabel2;
    QCheckBox* kcfg_OsdUseFakeTranslucency;
    QGroupBox* osdText;
    QCheckBox* kcfg_OsdUsePlaylistColumns;
    KTextEdit* kcfg_OsdText;
    QGroupBox* groupBox22;
    QLabel* textLabel1;
    KIntSpinBox* kcfg_OsdDuration;
    KComboBox* kcfg_OsdScreen;
    QLabel* textLabel2_3;

signals:
    void settingsChanged();

protected:
    virtual void hideEvent( QHideEvent * );
    virtual void showEvent( QShowEvent * );

    QVBoxLayout* Options5Layout;
    QHBoxLayout* layout2;
    QSpacerItem* spacer2;
    QVBoxLayout* mainBoxLayout;
    QVBoxLayout* fontBoxLayout;
    QVBoxLayout* groupBox9Layout;
    QVBoxLayout* layout3;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
    QGridLayout* colorsBoxLayout;
    QVBoxLayout* osdTextLayout;
    QGridLayout* groupBox22Layout;

protected slots:
    virtual void languageChange();

    virtual void slotPositionChanged();
    virtual void useCustomColorsToggled( bool on );


private:
    OSDPreviewWidget *m_pOSDPreview;

    void init();

};

#endif // OPTIONS5_H
