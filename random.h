#ifndef RANDOM_H
#define RANDOM_H

#include <QtGui>
#include <QApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QListWidget>
#include <QSlider>
#include <QShortcut>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>

class MyQWidget: public QWidget
{
    Q_OBJECT
public:
    MyQWidget();
    void addItemNameToList(QString temps);
    QString pathCut(QString name);
    QString tailCut(QString temp);
    QString tailSave(QString temp);

private:
    QWidget *setWidget;
    QLabel *setUploadAddressLabel;
    QLabel *setWeekLabel;
    QLabel *setMarkLabel;
    QVBoxLayout *setWidgetLayout;
    QHBoxLayout *setWidgetButtonLayout;
    QLineEdit *setUploadAddress;
    QLineEdit *setWeek;
    QLineEdit *setMark;
    QPushButton *setOk;
    QPushButton *setCancel;
    QPushButton *uploadButton;
    QVector<QString> configList;
    QCheckBox *writeOldFile;

    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *bottomLeftLayout;
    QVBoxLayout *bottomRightLayout;
    QVBoxLayout *mainLayout;
    QPushButton *openButton;
    QPushButton *clearButton;
    QPushButton *setButton;
    QPushButton *donateButton;
    QPushButton *startButton;
    QPushButton *absentButton;
    QPushButton *resetButton;
    QCheckBox *repeat;
    QLabel *mesg;
    QLabel *restName;
    QLabel *showmsg;
    QLabel *fontSizeMsg;
    QLabel *fileStatus;
    QLabel *time;
    QLabel *speedLabel;
    QListWidget *fileList;
    QVector<QString> openFileName;
    QVector<QString> openFileType;
    QVector<QMap<int, QString> > nameList;
    QTimer *timer;
    QTimer *clockTimer;
    QSlider *fontSize;
    QSlider *speed;
    QShortcut *startShortCut;
    QShortcut *absentShortCut;
    QStatusBar *status;
    QString currentFile;
    int fileSelectedNum;
    int randN;

private slots:
    void setOpenFileName();
    void openFile(int x);
    void randomName();
    void clearAll();
    void nameChange();
    void removeName();
    void setFont(int x);
    void setSpeed(int x);
    void clockChange();
    void absentAdd();
    void resetFileList();
    void readConfig();
    void writeConfig();
    void donateWindows();
    int uploadFile(QString fileName);
};

#endif // RANDOM_H
