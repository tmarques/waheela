/****************************************************************************
** Form interface generated from reading ui file './dbsetup.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DBSETUP_H
#define DBSETUP_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class KComboBox;
class QFrame;
class QGroupBox;
class KLineEdit;
class KIntSpinBox;

class DbSetup : public QWidget
{
    Q_OBJECT

public:
    DbSetup( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~DbSetup();

    QLabel* textLabel1_2;
    KComboBox* databaseEngine;
    QFrame* postgreSqlFrame;
    QGroupBox* postgresqlConfig;
    QLabel* textLabel1_3;
    KLineEdit* kcfg_PostgresqlConninfo;
    QFrame* mySqlFrame;
    QGroupBox* mysqlConfig;
    QLabel* textLabel1;
    QLabel* textLabel5;
    KIntSpinBox* kcfg_MySqlPort;
    QLabel* textLabel2;
    KLineEdit* kcfg_MySqlHost;
    KLineEdit* kcfg_MySqlDbName;
    QFrame* line1;
    QLabel* textLabel3;
    KLineEdit* kcfg_MySqlUser;
    QLabel* textLabel4;
    KLineEdit* kcfg_MySqlPassword;

protected:
    QGridLayout* DbSetupLayout;
    QHBoxLayout* layout2;
    QGridLayout* postgreSqlFrameLayout;
    QHBoxLayout* postgresqlConfigLayout;
    QGridLayout* mySqlFrameLayout;
    QGridLayout* mysqlConfigLayout;
    QHBoxLayout* layout4;

protected slots:
    virtual void languageChange();

private:
    virtual void init();

private slots:
    void databaseEngineChanged();

};

#endif // DBSETUP_H
