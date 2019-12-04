#include "random.h"
#include "excelengine.h"

MyQWidget::MyQWidget()
{

    this->setWindowTitle(tr("老王随机点名器v0.42"));

    topLayout = new QHBoxLayout;
    bottomLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    bottomLeftLayout = new QVBoxLayout;
    bottomRightLayout = new QVBoxLayout;
    mainLayout = new QVBoxLayout;
    openButton = new QPushButton(tr("打开文件"));
    clearButton = new QPushButton(tr("清空列表"));
    setButton = new QPushButton(tr("设置"));
    donateButton = new QPushButton(tr("捐赠"));
    startButton = new QPushButton(tr("开始"));
    absentButton = new QPushButton(tr("缺席"));
    resetButton = new QPushButton(tr("重置列表"));
    uploadButton = new QPushButton(tr("上传"));
    repeat = new QCheckBox(tr("不重复点名"));
    mesg = new QLabel(tr("文件列表"));
    speedLabel = new QLabel(tr("速度"));
    showmsg = new QLabel;
    restName = new QLabel(tr("剩余数量0"));
    fileStatus = new QLabel(QDir::currentPath());
    fileList = new QListWidget;
    time = new QLabel;
    clockTimer = new QTimer(this);
    timer = new QTimer(this);
    fontSize = new QSlider(Qt::Horizontal);
    speed = new QSlider(Qt::Horizontal);
    fontSizeMsg = new QLabel(tr(" 字号"));
    status = new QStatusBar;
    startShortCut = new QShortcut(QKeySequence(Qt::Key_Space), this); //设置开始停止按钮快捷键为空格键
    absentShortCut = new QShortcut(QKeySequence(Qt::Key_B), this);

    //设置窗口
    setUploadAddressLabel = new QLabel(tr("设置文件上传路径"));
    setWeekLabel = new QLabel(tr("设置点名周"));
    setMarkLabel = new QLabel(tr("设置标记（例X为缺席，O为已到，只对xls有效）"));
    setWidgetLayout = new QVBoxLayout;
    setWidgetButtonLayout  = new QHBoxLayout;
    setWidget = new QWidget;
    setUploadAddress = new QLineEdit("NULL");
    setWeek = new QLineEdit("1");
    setMark = new QLineEdit("X");
    writeOldFile = new QCheckBox(tr("缺席名单写到原文件中（xls默认选中）"));
    writeOldFile->setChecked(false);

    setWidget->setAttribute(Qt::WA_QuitOnClose, false);
    setOk = new QPushButton(tr("确定"));
    setCancel = new QPushButton(tr("取消"));
    setWidget->setLayout(setWidgetLayout);
    setWidgetButtonLayout->addWidget(setOk);
    setWidgetButtonLayout->addWidget(setCancel);
    setWidgetLayout->addWidget(setWeekLabel);
    setWidgetLayout->addWidget(setWeek);
    setWidgetLayout->addWidget(setMarkLabel);
    setWidgetLayout->addWidget(setMark);
    setWidgetLayout->addWidget(writeOldFile);
    setWidgetLayout->addLayout(setWidgetButtonLayout);
    setWidget->setFixedWidth(300);

    //信号和槽的连接
    connect(startShortCut, SIGNAL(activated()), startButton, SLOT(click()));
    connect(absentShortCut, SIGNAL(activated()), absentButton, SLOT(click()));
    connect(donateButton, SIGNAL(clicked()), this, SLOT(donateWindows()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(nameChange()));
    connect(openButton, SIGNAL(clicked()), this, SLOT(setOpenFileName()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(absentButton, SIGNAL(clicked()), this, SLOT(absentAdd()));
    connect(fontSize, SIGNAL(valueChanged(int)), this, SLOT(setFont(int)));
    connect(speed, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockChange()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetFileList()));

    connect(setButton, SIGNAL(clicked()), setWidget, SLOT(show()));
    connect(setButton, SIGNAL(clicked()), this, SLOT(readConfig()));
    connect(setOk, SIGNAL(clicked()), this, SLOT(writeConfig()));
    connect(setCancel, SIGNAL(clicked()), setWidget, SLOT(close()));

    //按钮设置为不可用
    clearButton->setDisabled(true);
    resetButton->setDisabled(true);
    startButton->setDisabled(true);
    absentButton->setDisabled(true);
    //设置鼠标悬停提醒
    startButton->setToolTip(tr("快捷键：空格"));
    //startButton->setMaximumWidth(300);
    absentButton->setToolTip(tr("快捷键：B"));
    //absentButton->setMaximumWidth(300);
    openButton->setToolTip(tr("支持文件：一行一个名字的txt文件"));
    resetButton->setToolTip(tr("重新读取文件列表中的所有文件"));
    clockTimer->start(1000);
    //设置字体尺寸范围
    fontSize->setRange(20,600);
    fontSize->setValue(110);
    speed->setRange(5,5000);
    speed->setValue(40);
    repeat->setChecked(true);
    //设置时间
    time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
    //设置字体
    QFont use("WenQuanYi Micro Hei", 110);
    showmsg->setFont(use);
    QFont use1("WenQuanYi Micro Hei", 11);
    fileStatus->setFont(use1);
    time->setFont(use1);
    //设置大小
    //fileList->setFixedWidth(160);
    showmsg->setMinimumWidth(600);
    showmsg->setAlignment(Qt::AlignCenter);
    //设置状态栏
    status->addWidget(fileStatus, 100);
    status->addWidget(time,35);
    this->setMinimumSize(800, 600);

    topLayout->addWidget(openButton);
    topLayout->addWidget(resetButton);
    topLayout->addWidget(clearButton);
    topLayout->addWidget(setButton);
    topLayout->addWidget(repeat);
    topLayout->addWidget(restName);
    topLayout->addWidget(fontSizeMsg);
    topLayout->addWidget(fontSize);
    topLayout->addWidget(speedLabel);
    topLayout->addWidget(speed);
    topLayout->addWidget(donateButton);
    bottomLeftLayout->addWidget(mesg);
    bottomLeftLayout->addWidget(fileList);
    bottomRightLayout->addWidget(showmsg);
    bottomRightLayout->addLayout(buttonLayout);
    bottomRightLayout->setAlignment(Qt::AlignHCenter);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(absentButton);
    buttonLayout->setStretchFactor(startButton,1);
    buttonLayout->setStretchFactor(absentButton,1);

    bottomLayout->addLayout(bottomLeftLayout);
    bottomLayout->addLayout(bottomRightLayout);
    //bottomLayout->setStretch(1,4);
    bottomLayout->setStretchFactor(bottomLeftLayout,1);
    bottomLayout->setStretchFactor(bottomRightLayout,4);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(status);

    this->setLayout(mainLayout);
}

void MyQWidget::setOpenFileName()
{
    QString tempName;
    tempName = QFileDialog::getOpenFileName(this,  tr("打开姓名文件"), ".", tr("文本文件(*.txt *.xls *.xlsx)"));

    if (tempName == NULL)
        return;

    if (openFileName.size() == 0)
    {
        openFileName.push_back(tempName);
        openFileType.push_back(tailSave(pathCut(tempName)));
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
                openFileType.push_back(tailSave(pathCut(tempName)));
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
    QMap<int, QString> list1;
    int num = 0;
    int row = 3;
    currentFile = openFileName[x];
    fileSelectedNum = x;
    if (openFileType[x] == "txt")
    {
    QFile file(openFileName[x]);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line;
    while (!in.atEnd())
    {
        line = in.readLine();
        if (line != "")
        {
            list1[num] = line;
            ++num;
        }
    }
    file.close();
    }
    else
    {
        ExcelEngine excel;
        excel.Open(openFileName[x],1,false);

        while (excel.GetCellData(row, 1).toString() != "")
        {
            list1[num] = excel.GetCellData(row,1).toString();
            ++num;
            ++row;
        }
        excel.Save();
        excel.Close();
    }
    nameList.push_back(list1);
    restName->setText(tr("剩余数量") + QString::number(nameList[fileSelectedNum].size()));
    fileStatus->setText(openFileName[fileSelectedNum]);
}

void MyQWidget::randomName()
{
    if (startButton->text() == tr("停止") && fileList->count() != 0 && nameList[fileSelectedNum].size() != 0)
    {
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec() + t.second() * 1000);

        randN = qrand() % nameList[fileSelectedNum].size();
        QMap<int, QString>::iterator it = nameList[fileSelectedNum].begin() + randN;

        showmsg->setText(it.value());
    }
    connect(startButton, SIGNAL(clicked()), this, SLOT(removeName()));
}

void MyQWidget::nameChange()
{
    if (openFileName.size() == 0)
        return;
    if (startButton->text() == tr("开始") && !nameList[fileSelectedNum].isEmpty())
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(randomName()));
        startButton->setText(tr("停止"));
    }
    else
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(randomName()));
        startButton->setText(tr("开始"));
    }
}

void MyQWidget::removeName()
{
    if (fileList->count() != 0 && startButton->text() == tr("开始") && repeat->isChecked())
    {
        QMap<int, QString>::iterator it = nameList[fileSelectedNum].begin() + randN;
        nameList[fileSelectedNum].remove(it.key());
        restName->setText(tr("剩余数量") + QString::number(nameList[fileSelectedNum].size()));
    }
    disconnect(startButton, SIGNAL(clicked()), this, SLOT(removeName()));
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

void MyQWidget::setSpeed(int x)
{
    timer->start(x);
}

void MyQWidget::clockChange()
{
    time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
}

void MyQWidget::absentAdd()
{
    if (openFileName.size() == 0 || showmsg->text().isEmpty())
        return;
    if (showmsg->text() != "" && (startButton->text() == tr("开始")) && tailSave(currentFile) == "txt")
    {
        if (writeOldFile->isChecked())
        {
            QFile file(currentFile);
            file.open(QFile::Append | QIODevice::Text);
            QTextStream write(&file);

            write << endl;
            write << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << endl;
            write << showmsg->text() << endl;
            write << endl;
            file.close();
        }
        else
        {
            QFile file(tailCut(pathCut(currentFile)) + tr("缺席名单") + QDateTime::currentDateTime().toString("yyyy-MM-dd") + tr(".txt"));
            file.open(QFile::Append | QIODevice::Text);
            QTextStream write(&file);

            write << endl;
            write << QDateTime::currentDateTime().toString("hh:mm:ss") << endl;
            write << showmsg->text() << endl;
            write << endl;
            file.close();
        }
    }
    else if (tailSave(currentFile).contains("xls"))
    {
        ExcelEngine excel;
        excel.Open(currentFile);
        excel.SetCellData(randN, setWeek->text().toInt() + 1, setMark->text());
        excel.Save();
        excel.Close();
    }

    showmsg->setText("");
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

QString MyQWidget::tailSave(QString temp)
{
    QString::iterator flag = temp.begin();
    for (QString::iterator i = temp.begin(); i != temp.end(); ++i)
    {
        if (*i == '.')
            flag = ++i;
    }
    int length = 0;
    for (QString::iterator i = flag; i != temp.end(); ++i)
    {
            length++;
    }
    QString temps(flag ,length);
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

void MyQWidget::clearAll()
{

    disconnect(fileList, SIGNAL(currentRowChanged(int)), this, SLOT(openFile(int)));
    fileList->clearSelection();
    nameList.clear();
    openFileName.clear();
    openFileType.clear();
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

void MyQWidget::readConfig()
{
    QFile file("config.ini");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line;
    configList.push_back("NULL");
    while (!in.atEnd())
    {
        line = in.readLine();
        if (line != "")
        {
            configList[0] = line;
        }
    }
    file.close();

    QString::iterator temp = configList[0].begin();
    QString::iterator flag = configList[0].begin();
    int size = 0;
    for (QString::iterator i = configList[0].begin(); i != configList[0].end(); ++i)
    {
        if (*i == '=')
            temp = i;
    }
    flag = temp;
    while (*temp != '\0')
    {
        ++temp;
        ++size;
    }
    QString temps(flag + 1,  size - 1);
    setUploadAddress->setText(temps);
}

void MyQWidget::writeConfig()
{
    QFile file("config.ini");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream write(&file);
    write << "uploadPath=" + setUploadAddress->text();
    file.close();
    setWidget->close();
}

int MyQWidget::uploadFile(QString fileName)
{
    if (fileName == "")
        return -1;

    QNetworkRequest req(configList[0]);
    QByteArray boundary = "-------------------------87142694621188";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    QByteArray fileContent(file.readAll());

    QByteArray data = "--" + boundary + "\r\n";
    data += "Content-Disposition: form-data; name=\"file\"; filename=\"" + fileName +"\";\r\n";
    //add picture to data
    data += "Content-Type: text/plain\r\n\r\n" + fileContent + "\r\n";


    data += "--" + boundary + "\r\n";
    data += "Content-Disposition: form-data; name=\"id\"\r\n\r\n";


    data += "--" + boundary + "--";

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=" + boundary);
    req.setRawHeader("Content-Length", QString::number(data.size()).toLatin1());
    file.close();
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = networkManager->post(req, data);
    if (!reply->error())
        return -1;
    return 0;
}

void MyQWidget::donateWindows()
{
    QMessageBox *donateMes = new QMessageBox;
    //捐赠按钮
    //donateMes->setText(tr("支付宝 : 30204977@qq.com"));
    //donateMes->setInformativeText(tr("点击访问我的支付宝首页"));
    donateMes->setWindowTitle(tr("支付宝:30204977@qq.com，扫二维码捐赠，多谢支持。"));
    donateMes->setIconPixmap(QPixmap(":/img/alipay.png"));
    QPushButton *yesButton = donateMes->addButton(tr("关闭"),QMessageBox::YesRole);
    donateMes->exec();

 if (donateMes->clickedButton() == yesButton)
    {
        donateMes->close();
    }
    //else if (donateMes->clickedButton() == noButton)
    //{
    //    donateMes->close();
    //}
}
