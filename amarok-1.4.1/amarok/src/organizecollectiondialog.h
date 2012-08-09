/****************************************************************************
** Form interface generated from reading ui file './organizecollectiondialog.ui'
**
** Created: Fri Mar 23 10:51:26 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ORGANIZECOLLECTIONDIALOG_H
#define ORGANIZECOLLECTIONDIALOG_H

#include <qvariant.h>
#include <qwidget.h>
#include <metabundle.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class KComboBox;
class QCheckBox;
class QGroupBox;
class KLineEdit;
class KActiveLabel;

class OrganizeCollectionDialog : public QWidget
{
    Q_OBJECT

public:
    OrganizeCollectionDialog( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~OrganizeCollectionDialog();

    QLabel* folderLabel;
    KComboBox* folderCombo;
    QCheckBox* coverCheck;
    QCheckBox* ignoreTheCheck;
    QGroupBox* groupingGroup;
    QCheckBox* customschemeCheck;
    QCheckBox* filetypeCheck;
    QCheckBox* initialCheck;
    QLabel* formatLabel;
    KLineEdit* formatEdit;
    KActiveLabel* formatHelp;
    QGroupBox* replacementGroup;
    QCheckBox* spaceCheck;
    QCheckBox* asciiCheck;
    QCheckBox* vfatCheck;
    QLabel* textLabel1;
    KLineEdit* regexpEdit;
    QLabel* textLabel2;
    KLineEdit* replaceEdit;
    QGroupBox* previewBox;
    QLabel* previewText;
    QCheckBox* overwriteCheck;

    virtual QString buildDestination( const QString & format, const MetaBundle & mb ) const;
    virtual QString buildFormatTip() const;
    virtual QString buildFormatString() const;
    virtual void setPreviewBundle( const MetaBundle & bundle );
    virtual QString cleanPath( const QString & component ) const;
    virtual void init();

public slots:
    virtual void preview( const QString & format );
    virtual void update( int dummy );
    virtual void update( const QString & dummy );
    virtual void slotDetails();

signals:
    void updatePreview( const QString & );

protected:
    MetaBundle previewBundle;
    bool detailed;

    QVBoxLayout* organizeCollectionDialogLayout;
    QHBoxLayout* folderLayout;
    QVBoxLayout* groupingGroupLayout;
    QHBoxLayout* customFormatLayout;
    QVBoxLayout* replacementGroupLayout;
    QHBoxLayout* layout4;
    QGridLayout* previewBoxLayout;
    QHBoxLayout* overwriteLayout;
    QSpacerItem* spacer2_2;

protected slots:
    virtual void languageChange();

};

#endif // ORGANIZECOLLECTIONDIALOG_H
