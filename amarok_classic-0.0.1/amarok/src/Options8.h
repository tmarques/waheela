/****************************************************************************
** Form interface generated from reading ui file './Options8.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OPTIONS8_H
#define OPTIONS8_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class KActiveLabel;
class QGroupBox;
class KLineEdit;
class QCheckBox;

class Options8 : public QWidget
{
    Q_OBJECT

public:
    Options8( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options8();

    QLabel* infoPixmap_2;
    KActiveLabel* kActiveLabel3;
    QGroupBox* groupBox3;
    KActiveLabel* kActiveLabel1;
    KLineEdit* kcfg_ScrobblerUsername;
    QLabel* labelPassword;
    QLabel* labelUsername;
    KLineEdit* kcfg_ScrobblerPassword;
    QGroupBox* groupBox2;
    QLabel* textLabel1;
    QCheckBox* kcfg_SubmitPlayedSongs;
    QCheckBox* kcfg_RetrieveSimilarArtists;
    KActiveLabel* kActiveLabel2;

protected:
    QVBoxLayout* Options8Layout;
    QSpacerItem* spacer4;
    QHBoxLayout* layout2;
    QVBoxLayout* groupBox3Layout;
    QGridLayout* layout3;
    QVBoxLayout* groupBox2Layout;

protected slots:
    virtual void languageChange();

};

#endif // OPTIONS8_H
