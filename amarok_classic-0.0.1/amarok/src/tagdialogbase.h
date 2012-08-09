/****************************************************************************
** Form interface generated from reading ui file './tagdialogbase.ui'
**
** Created: Ter Fev 19 15:57:45 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TAGDIALOGBASE_H
#define TAGDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class KLineEdit;
class KComboBox;
class QFrame;
class KIntSpinBox;

class TagDialogBase : public QDialog
{
    Q_OBJECT

public:
    TagDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~TagDialogBase();

    QPushButton* pushButton_previous;
    QPushButton* pushButton_next;
    QPushButton* pushButton_ok;
    QPushButton* pushButton_cancel;
    QLabel* textLabel1_3;
    KLineEdit* kLineEdit_bitrate;
    QLabel* samplerateLabel;
    KLineEdit* kLineEdit_samplerate;
    KLineEdit* kLineEdit_title;
    QLabel* textLabel1_2;
    KComboBox* kComboBox_genre;
    KLineEdit* kLineEdit_playcount;
    QFrame* line1;
    QLabel* pixmap_cover;
    QLabel* textLabel1_4;
    QLabel* lengthLabel;
    KIntSpinBox* kIntSpinBox_track;
    QLabel* textLabel1_5;
    KIntSpinBox* kIntSpinBox_year;
    QLabel* textLabel1_6;
    KIntSpinBox* kIntSpinBox_score;
    KComboBox* kComboBox_album;
    KLineEdit* kLineEdit_comment;
    QLabel* bitrateLabel;
    QLabel* textLabel1_6_6;
    KLineEdit* kLineEdit_location;
    QPushButton* pushButton_open;
    QLabel* textLabel1;
    KLineEdit* kLineEdit_length;
    KComboBox* kComboBox_artist;
    QLabel* playcountLabel;
    QPushButton* pushButton_musicbrainz;
    QLabel* textLabel1_6_2;
    QLabel* locationLabel;

protected:
    QGridLayout* TagDialogBaseLayout;
    QSpacerItem* spacer3;
    QHBoxLayout* layout5;
    QSpacerItem* spacer1;
    QGridLayout* layout8;
    QHBoxLayout* layout5_2;
    QHBoxLayout* layout5_3;
    QHBoxLayout* layout17;

protected slots:
    virtual void languageChange();

};

#endif // TAGDIALOGBASE_H
