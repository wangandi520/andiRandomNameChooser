#include "random.h"

MyQWidget::MyQWidget()
{
    this->setWindowTitle(tr("老王随机点名器v0.3"));

    topLayout = new QHBoxLayout;
    bottomLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    bottomLeftLayout = new QVBoxLayout;
    bottomRightLayout = new QVBoxLayout;
    mainLayout = new QVBoxLayout;
    openButton = new QPushButton(tr("打开文件"));
    clearButton = new QPushButton(tr("清空列表"));
    donateButton = new QPushButton(tr("捐赠"));
    startButton = new QPushButton(tr("开始"));
    absentButton = new QPushButton(tr("缺席"));
    resetButton = new QPushButton(tr("重置列表"));
    repeat = new QCheckBox(tr("不重复点名"));
    mesg = new QLabel(tr("文件列表"));
    showmsg = new QLabel;
    restName = new QLabel(tr("剩余数量0"));
    fileStatus = new QLabel(QDir::currentPath());
    fileList = new QListWidget;
    time = new QLabel;
    clockTimer = new QTimer(this);
    timer = new QTimer(this);
    donateMes = new QMessageBox;
    fontSize = new QSlider(Qt::Horizontal);
    fontSizeMsg = new QLabel(tr("字体大小:"));
    status = new QStatusBar;
    startShortCut = new QShortcut(QKeySequence(Qt::Key_Space), this); //设置开始停止按钮快捷键为空格键
    absentShortCut = new QShortcut(QKeySequence(Qt::Key_B), this);

    connect(startShortCut, SIGNAL(activated()), startButton, SLOT(click()));
    connect(absentShortCut, SIGNAL(activated()), absentButton, SLOT(click()));
    connect(donateButton, SIGNAL(clicked()), donateMes, SLOT(exec()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(nameChange()));
    connect(openButton, SIGNAL(clicked()), this, SLOT(setOpenFileName()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(absentButton, SIGNAL(clicked()), this, SLOT(absentAdd()));
    connect(fontSize, SIGNAL(valueChanged(int)), this, SLOT(setFont(int)));
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockChange()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetFileList()));

    clearButton->setDisabled(true);
    resetButton->setDisabled(true);
    startButton->setDisabled(true);
    absentButton->setDisabled(true);
    startButton->setToolTip(tr("快捷键：空格"));
    absentButton->setToolTip(tr("快捷键：B"));
    openButton->setToolTip(tr("支持文件：一行一个名字的txt文件"));
    resetButton->setToolTip(tr("重新读取文件列表中的所有文件"));
    clockTimer->start(1000);
    fontSize->setRange(20,150);
    fontSize->setValue(110);
    repeat->setChecked(true);
    time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
    donateMes->setText(tr("支付宝 30204977@qq.com"));
    donateMes->setWindowTitle(tr("多谢支持"));
    QFont use("WenQuanYi Micro Hei", 110);
    showmsg->setFont(use);
    QFont use1("WenQuanYi Micro Hei", 11);
    fileStatus->setFont(use1);
    time->setFont(use1);
    fileList->setFixedWidth(160);
    showmsg->setFixedWidth(600);
    showmsg->setAlignment(Qt::AlignCenter);
    status->addWidget(fileStatus, 100);
    status->addWidget(time,35);
    this->setFixedSize(800, 500);

    topLayout->addWidget(openButton);
    topLayout->addWidget(resetButton);
    topLayout->addWidget(clearButton);
    topLayout->addWidget(repeat);
    topLayout->addWidget(restName);
    topLayout->addStretch();
    topLayout->addWidget(fontSizeMsg);
    topLayout->addWidget(fontSize);
    topLayout->addWidget(donateButton);
    bottomLeftLayout->addWidget(mesg);
    bottomLeftLayout->addWidget(fileList);
    bottomRightLayout->addWidget(showmsg);
    bottomRightLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(absentButton);
    bottomRightLayout->setAlignment(Qt::AlignHCenter);
    bottomLayout->addLayout(bottomLeftLayout);
    bottomLayout->addStretch();
    bottomLayout->addLayout(bottomRightLayout);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(status);

    this->setLayout(mainLayout);
}

void MyQWidget::setOpenFileName()
{
    QString tempName;
    tempName = QFileDialog::getOpenFileName(this,  tr("打开姓名文件"), ".", tr("文本文件(*.txt)"));

    if (tempName == NULL)
        return;

    if (openFileName.size() == 0)
    {
        openFileName.push_back(tempName);
        addItemNameToList(pathCut(tempName));
    }
    else
        for (int i = 0; i != openFileName.size(); ++i)
        {
            if (openFileName[i] == tempName)
            {
                QMessageBox::warning(NULL, tr("错误"), tr("文件已打开"), tr("知道了"));
                break;
            }
            if (openFileName[i] != tempName && i == (openFileName.size() - 1))
            {
                openFileName.push_back(tempName);
                addItemNameToList(pathCut(tempName));
                break;
            }
        }
    connect(fileList, SIGNAL(currentRowChanged(int)), this, SLOT(openFile(int)));
    mesg->setText(tr("文件列表(") + QString::number(openFileName.size()) + tr(")"));
}

void MyQWidget::openFile(int x)
{
    if (openFileName.size() != 0)
    {
        clearButton->setEnabled(true);
        resetButton->setEnabled(true);
        startButton->setEnabled(true);
        absentButton->setEnabled(true);
    }
    showmsg->setText(tr(""));
    QVector<QString> list1;
    QFile file(openFileName[x]);
    currentFile = openFileName[x];
    fileSelectedNum = x;
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line;
    while (!in.atEnd())
    {
        line = in.readLine();
        if (line != "")
        {
            list1.push_back(line);
        }
    }
    nameList.push_back(list1);
    file.close();
    restName->setText(tr("剩余数量") + QString::number(nameList[x].size()));
    fileStatus->setText(openFileName[x]);
}

void MyQWidget::randomName()
{
    if (startButton->text() == tr("停止") && fileList->count() != 0 && !nameList[fileSelectedNum].isEmpty())
    {
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec() + t.second() * 1000);
        int n = 0;
        if (nameList[fileSelectedNum].size() != 0)
            n = qrand() % nameList[fileSelectedNum].size();
        showmsg->setText(nameList[fileSelectedNum][n]);
    }
    connect(startButton, SIGNAL(clicked()), this, SLOT(removeName()));
}

void MyQWidget::clearAll()
{

    disconnect(fileList, SIGNAL(currentRowChanged(int)), this, SLOT(openFile(int)));
    fileList->clearSelection();
    nameList.clear();
    openFileName.clear();
    showmsg->setText("");
    startButton->setText(tr("开始"));
    restName->setText(tr("剩余数量0"));
    mesg->setText(tr("文件列表"));
    fileStatus->setText(QDir::currentPath());
    fileList->clear();

    clearButton->setDisabled(true);
    resetButton->setDisabled(true);
    startButton->setDisabled(true);
    absentButton->setDisabled(true);
}

void MyQWidget::nameChange()
{
    if (openFileName.size() == 0)
        return;
    if (startButton->text() == tr("开始") && !nameList[fileSelectedNum].isEmpty())
    {
        startButton->setText(tr("停止"));
    }
    else
    {
        startButton->setText(tr("开始"));
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(randomName()));
    timer->start(80);
}

void MyQWidget::removeName()
{
    if (fileList->count() != 0 && startButton->text() == tr("开始") && repeat->isChecked())
    {
        for (int i = 0; i < nameList[fileSelectedNum].size(); ++i)
            if (nameList[fileSelectedNum][i] == showmsg->text())
                nameList[fileSelectedNum].remove(i);
        restName->setText(tr("剩余数量") + QString::number(nameList[fileSelectedNum].size()));
    }
}

void MyQWidget::addItemNameToList(QString temps)
{
    fileList->addItem(temps);
    fileList->item(fileList->count() - 1)->setSelected(true);
    openFile(fileList->count() - 1);
}

void MyQWidget::setFont(int x)
{

    QFont use("WenQuanYi Micro Hei", x);
    this->showmsg->setFont(use);
}

void MyQWidget::clockChange()
{
    time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
}

void MyQWidget::absentAdd()
{
    if (openFileName.size() == 0 || showmsg->text().isEmpty())
        return;
    if (showmsg->text() != "" && (startButton->text() == tr("开始")))
    {
        QFile file(tailCut(pathCut(currentFile)) + tr("缺席名单") + QDateTime::currentDateTime().toString("yyyy-MM-dd") + tr(".txt"));
        file.open(QFile::Append | QIODevice::Text);
        QTextStream write(&file);

        write << QDateTime::currentDateTime().toString("hh:mm:ss") << endl;
        write << showmsg->text() << endl;
        write << endl;

        file.close();
        showmsg->setText("");
    }
}

QString MyQWidget::pathCut(QString name)
{
    QString::iterator temp = name.begin();
    QString::iterator flag = name.begin();
    int size = 0;
    for (QString::iterator i = name.begin(); i != name.end(); ++i)
    {
        if (*i == '/')
            temp = i;
    }
    flag = temp;
    while (*temp != '\0')
    {
        ++temp;
        ++size;
    }
    QString temps(flag + 1,  size - 1);
    return temps;
}

QString MyQWidget::tailCut(QString temp)
{
    QString::iterator flag = temp.begin();
    for (QString::iterator i = temp.begin(); i != temp.end(); ++i)
    {
        if (*i == '.')
            flag = i;
    }
    QString temps(temp.begin(), flag - temp.begin());
    return temps;
}

void MyQWidget::resetFileList()
{
    startButton->setText(tr("开始"));
    if (openFileName.isEmpty())
        return;
    nameList.clear();
    for (int i = 0; i != openFileName.size(); ++i)
    {
        openFile(i);
    }
    restName->setText(tr("剩余数量") + QString::number(nameList[0].size()));
    fileStatus->setText(openFileName[0]);
    fileSelectedNum = 0;
    fileList->setCurrentRow(0);
}
