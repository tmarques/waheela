/****************************************************************************
** Form interface generated from reading ui file './Options7.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MYSQL_H
#define MYSQL_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class DbSetup;
class QGroupBox;

class Options7 : public QWidget
{
    Q_OBJECT

public:
    Options7( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Options7();

    QGroupBox* collectionFoldersBox;
    QGroupBox* databaseBox;
    DbSetup* dbSetupFrame;

protected:
    QVBoxLayout* MySqlLayout;
    QVBoxLayout* databaseBoxLayout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // MYSQL_H
