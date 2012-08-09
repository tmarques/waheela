/****************************************************************************
** Form interface generated from reading ui file './dbsetup.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
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
class QWidgetStack;
class QFrame;
class QGroupBox;
class QLabel;
class KIntSpinBox;
class KLineEdit;
class KComboBox;

class DbSetup : public QWidget
{
    Q_OBJECT

public:
    DbSetup( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~DbSetup();

    QWidgetStack* configStack;
    QWidget* SQLLite;
    QWidget* MySQL;
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
    KLineEdit* kcfg_MySqlPassword2;
    QWidget* PostgreSQL;
    QFrame* postgreSqlFrame;
    QGroupBox* postgresqlConfig;
    QLabel* textLabel1_2;
    QLabel* textLabel5_2;
    KIntSpinBox* kcfg_PostgresqlPort;
    QLabel* textLabel2_2;
    KLineEdit* kcfg_PostgresqlHost;
    KLineEdit* kcfg_PostgresqlDbName;
    QFrame* line1_2;
    QLabel* textLabel3_2;
    KLineEdit* kcfg_PostgresqlUser;
    QLabel* textLabel4_2;
    KLineEdit* kcfg_PostgresqlPassword2;
    QLabel* textLabel1_2_2;
    KComboBox* databaseEngine;

protected:
    QGridLayout* DbSetupLayout;
    QHBoxLayout* MySQLLayout;
    QGridLayout* mySqlFrameLayout;
    QGridLayout* mysqlConfigLayout;
    QHBoxLayout* layout4;
    QHBoxLayout* PostgreSQLLayout;
    QGridLayout* postgreSqlFrameLayout;
    QGridLayout* postgresqlConfigLayout;
    QHBoxLayout* layout4_2;

protected slots:
    virtual void languageChange();

private:
    virtual void init();

};

#endif // DBSETUP_H
