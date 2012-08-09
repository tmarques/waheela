/****************************************************************************
** Form interface generated from reading ui file './tagdialogbase.ui'
**
** Created: Sex Mar 23 10:37:27 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
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
class CoverLabel;
class QPushButton;
class QCheckBox;
class QLabel;
class KLineEdit;
class KTabWidget;
class QWidget;
class QFrame;
class KComboBox;
class KIntSpinBox;
class KTextEdit;

class TagDialogBase : public QDialog
{
    Q_OBJECT

public:
    TagDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~TagDialogBase();

    QPushButton* pushButton_previous;
    QPushButton* pushButton_next;
    QCheckBox* checkBox_perTrack;
    QPushButton* pushButton_ok;
    QPushButton* pushButton_cancel;
    QLabel* locationLabel;
    KLineEdit* kLineEdit_location;
    QPushButton* pushButton_open;
    KTabWidget* kTabWidget;
    QWidget* summaryTab;
    CoverLabel* pixmap_cover;
    QLabel* trackArtistAlbumLabel;
    QFrame* line1;
    QLabel* summaryLabel;
    QWidget* tagsTab;
    QLabel* textLabel1_2;
    QLabel* textLabel1;
    QLabel* textLabel1_6_6;
    QPushButton* pushButton_guessTags;
    QPushButton* pushButton_setFilenameSchemes;
    QLabel* textLabel_comment;
    QPushButton* pushButton_musicbrainz;
    QLabel* textLabel1_4;
    KComboBox* kComboBox_genre;
    KLineEdit* kLineEdit_title;
    KIntSpinBox* kIntSpinBox_track;
    QLabel* textLabel1_5;
    KIntSpinBox* kIntSpinBox_year;
    KTextEdit* kTextEdit_comment;
    QLabel* textLabel1_3;
    QLabel* textLabel1_3_2;
    KComboBox* kComboBox_album;
    QLabel* textLabel1_3_2_2;
    KIntSpinBox* kIntSpinBox_discNumber;
    KComboBox* kComboBox_composer;
    KComboBox* kComboBox_artist;
    QWidget* lyricsTab;
    KTextEdit* kTextEdit_lyrics;
    QWidget* statisticsTab;
    QLabel* trackArtistAlbumLabel2;
    QLabel* statisticsLabel;
    QLabel* scoreLabel;
    QLabel* ratingLabel;
    KIntSpinBox* kIntSpinBox_score;
    KComboBox* kComboBox_rating;

protected:
    QGridLayout* TagDialogBaseLayout;
    QHBoxLayout* layout5_3;
    QSpacerItem* spacer1;
    QHBoxLayout* layout6;
    QGridLayout* summaryTabLayout;
    QSpacerItem* spacer12;
    QGridLayout* tagsTabLayout;
    QHBoxLayout* layout14;
    QHBoxLayout* layout5_2;
    QHBoxLayout* layout11;
    QHBoxLayout* lyricsTabLayout;
    QGridLayout* statisticsTabLayout;
    QSpacerItem* spacer3_2;
    QSpacerItem* spacer5;

protected slots:
    virtual void languageChange();

};

#endif // TAGDIALOGBASE_H
