#ifndef RANDOM_H
#define RANDOM_H

#include <QtGui>

class MyQWidget: public QWidget
{
    Q_OBJECT
public:
    MyQWidget();
    void addItemNameToList(QString temps);
    QString pathCut(QString name);
    QString tailCut(QString temp);

private:
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *bottomLeftLayout;
    QVBoxLayout *bottomRightLayout;
    QVBoxLayout *mainLayout;
    QPushButton *openButton;
    QPushButton *clearButton;
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
    QListWidget *fileList;
    QVector<QString> openFileName;
    QVector<QVector<QString> > nameList;
    QTimer *timer;
    QTimer *clockTimer;
    QMessageBox *donateMes;
    QSlider *fontSize;
    QShortcut *startShortCut;
    QShortcut *absentShortCut;
    QStatusBar *status;
    QString currentFile;
    int fileSelectedNum;

private slots:
    void setOpenFileName();
    void openFile(int x);
    void randomName();
    void clearAll();
    void nameChange();
    void removeName();
    void setFont(int x);
    void clockChange();
    void absentAdd();
    void resetFileList();
};

#endif // RANDOM_H
