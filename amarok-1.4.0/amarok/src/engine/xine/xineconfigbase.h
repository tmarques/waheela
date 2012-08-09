/****************************************************************************
** Form interface generated from reading ui file './xineconfigbase.ui'
**
** Created: Sex Mar 23 10:36:11 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef XINECONFIGBASE_H
#define XINECONFIGBASE_H

#include <qvariant.h>
#include <qwidget.h>
#include "plugin/pluginconfig.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class KComboBox;
class QGroupBox;
class QLineEdit;
class QComboBox;
class KIntSpinBox;

class XineConfigBase : public QWidget
{
    Q_OBJECT

public:
    XineConfigBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~XineConfigBase();

    QLabel* xineLogo;
    QLabel* textLabel2;
    KComboBox* deviceComboBox;
    QLabel* textLabel3;
    QGroupBox* alsaGroupBox;
    QLabel* textLabel2_3;
    QLabel* textLabel3_3;
    QLabel* textLabel4_2;
    QLabel* chan5Label;
    QLineEdit* monoLineEdit;
    QLineEdit* stereoLineEdit;
    QLineEdit* chan4LineEdit;
    QLineEdit* chan5LineEdit;
    QGroupBox* ossGroupBox;
    QLabel* textLabel1;
    QComboBox* ossDeviceComboBox;
    QLabel* textLabel1_2;
    QComboBox* speakerComboBox;
    QGroupBox* groupBox1;
    QLabel* textLabel2_2;
    QLineEdit* hostLineEdit;
    KIntSpinBox* portIntBox;
    QLabel* textLabel3_2;
    QLineEdit* userLineEdit;
    QLabel* textLabel4;
    QLineEdit* passLineEdit;
    QGroupBox* audiocdGroupBox;
    QLabel* textLabel2_3_2;
    QLabel* textLabel2_2_2;
    QLabel* textLabel2_3_2_2;
    QLineEdit* audiocd_device;
    QLineEdit* cddb_server;
    KIntSpinBox* cddb_port;
    QLineEdit* cddb_cache_dir;

protected:
    QVBoxLayout* XineConfigBaseLayout;
    QHBoxLayout* layout11;
    QVBoxLayout* layout10;
    QSpacerItem* spacer3;
    QVBoxLayout* layout10_2;
    QHBoxLayout* layout2;
    QGridLayout* alsaGroupBoxLayout;
    QHBoxLayout* ossGroupBoxLayout;
    QHBoxLayout* layout5;
    QVBoxLayout* groupBox1Layout;
    QHBoxLayout* layout4;
    QHBoxLayout* layout2_2;
    QHBoxLayout* audiocdGroupBoxLayout;
    QVBoxLayout* layout11_2;
    QVBoxLayout* layout12;
    QHBoxLayout* layout10_3;

protected slots:
    virtual void languageChange();

};

#endif // XINECONFIGBASE_H
