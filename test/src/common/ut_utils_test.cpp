#include "ut_utils_test.h"
#include "termproperties.h"

#include "utils.h"

//Google GTest 相关头文件
#include <gtest/gtest.h>

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>
#include <QDebug>
#include <utility>
#include <memory>
#include <QWidget>
#include <QtConcurrent/QtConcurrent>

//DTK相关头文件
#include <DFileDialog>
DWIDGET_USE_NAMESPACE

UT_Utils_Test::UT_Utils_Test()
{
}

void UT_Utils_Test::SetUp()
{
}

void UT_Utils_Test::TearDown()
{
}

#ifdef UT_UTILS_TEST

TEST(UT_Utils_Test, getQssContentEmpty)
{
    EXPECT_TRUE(Utils::getQssContent(QString()).isEmpty());
}

TEST(UT_Utils_Test, getQssContentNoFile)
{
    EXPECT_TRUE(Utils::getQssContent(QString("/opt/qt.qss")).isEmpty());
}

TEST(UT_Utils_Test, getQssContentOKFile)
{
    system("echo '' > qts.qss");
    EXPECT_FALSE(Utils::getQssContent(QString("./qts.qss")).isEmpty());
}


TEST(UT_Utils_Test, getConfigPath)
{
    EXPECT_FALSE(Utils::getConfigPath().isEmpty());
}


TEST(UT_Utils_Test, suffixList)
{
    EXPECT_FALSE(Utils::suffixList().isEmpty());
}

TEST(UT_Utils_Test, getRandString)
{
    EXPECT_FALSE(Utils::getRandString().isEmpty());

    QString allGenText = "";
    for (int i = 0; i < 20; i++) {
        QString str = Utils::getRandString();
        allGenText.append(str);
        EXPECT_EQ(str.length(), 6);
        //加个延时用于提高Utils::getRandString()函数生成的随机性，因为随机函数使用时间作为随机数的种子
        QTest::qWait(UT_WAIT_TIME);
    }
}

TEST(UT_Utils_Test, showDirDialog)
{
#ifdef ENABLE_UI_TEST
    QWidget *parentWidget = new QWidget;

    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    QString dirName = Utils::showDirDialog(parentWidget);
    EXPECT_GE(dirName.length(), 0);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

//static void setSpaceInWord(DPushButton *button);

//static void showRenameTitleDialog(QString oldTitle, QWidget *parentWidget);

//static void showSameNameDialog(QWidget *parent, const QString &firstLine, const QString &secondLine);
TEST(UT_Utils_Test, showFilesSelectDialog)
{
#ifdef ENABLE_UI_TEST
    QWidget *parentWidget = new QWidget;

    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            parentWidget->deleteLater();
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    QStringList fileList = Utils::showFilesSelectDialog(parentWidget);
    EXPECT_GE(fileList.size(), 0);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, showExitConfirmDialogTab_CloseTypeTab)
{
#ifdef ENABLE_UI_TEST
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });


    bool isAccepted = Utils::showExitConfirmDialog(Utils::CloseType::CloseType_Tab);
    EXPECT_EQ(isAccepted, false);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, showExitConfirmDialog_CloseTypeWindow)
{
#ifdef ENABLE_UI_TEST
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    bool isAccepted = Utils::showExitConfirmDialog(Utils::CloseType::CloseType_Window);
    EXPECT_EQ(isAccepted, false);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, getExitDialogText)
{
    QString title;
    QString txt;
    Utils::CloseType temtype = Utils::CloseType::CloseType_Window;
    Utils::getExitDialogText(temtype, title, txt, 0);

    QString titleWindow = QObject::tr("Close this window?");
    QString txtWindow = QObject::tr("There are still processes running in this window. Closing the window will kill all of them.");

    EXPECT_NE(title, titleWindow);
    EXPECT_NE(txt, txtWindow);

    Utils::getExitDialogText(temtype, title, txt, 1);
    EXPECT_EQ(title, titleWindow);
    EXPECT_EQ(txt, txtWindow);


    QString titleDefault = QObject::tr("Close this terminal?");
    QString txtDefault = QObject::tr("There is still a process running in this terminal. "
                                     "Closing the terminal will kill it.");
    temtype = Utils::CloseType::CloseType_Terminal;
    Utils::getExitDialogText(temtype, title, txt, 1);
    EXPECT_EQ(title, titleDefault);
    EXPECT_EQ(txt, txtDefault);

    Utils::getExitDialogText(temtype, title, txt, 2);
    EXPECT_EQ(title, titleDefault);
    EXPECT_NE(txt, txtDefault);
}


TEST(UT_Utils_Test, showExitUninstallConfirmDialog)
{
#ifdef ENABLE_UI_TEST
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    bool isAccepted = Utils::showExitUninstallConfirmDialog();
    EXPECT_EQ(isAccepted, false);

    QTest::qWait(UT_WAIT_TIME);
#endif
}


TEST(UT_Utils_Test, showUnistallConfirmDialog)
{
#ifdef ENABLE_UI_TEST
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    QString commandName = "python";
    bool isAccepted = Utils::showUnistallConfirmDialog(commandName);
    EXPECT_EQ(isAccepted, false);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, showShortcutConflictDialog)
{
#ifdef ENABLE_UI_TEST
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    QString shortcutName = "Ctrl+A";
    bool isAccepted = Utils::showShortcutConflictDialog(shortcutName);
    EXPECT_EQ(isAccepted, false);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, showShortcutConflictMsgbox)
{
#ifdef ENABLE_UI_TEST
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    QString shortcutName = "Ctrl+C";
    bool isAccepted = Utils::showShortcutConflictMsgbox(shortcutName);
    EXPECT_EQ(isAccepted, true);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, showRenameTitleDialog)
{
#ifdef ENABLE_UI_TEST
    QWidget *parentWidget = new QWidget;
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            parentWidget->deleteLater();
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    Utils::showRenameTitleDialog("QTermWidget", parentWidget);

    QTest::qWait(UT_WAIT_TIME);
#endif
}

TEST(UT_Utils_Test, showSameNameDialog)
{
#ifdef ENABLE_UI_TEST
    QWidget *parentWidget = new QWidget;
    //要自己退出，否则对话框窗口会一直阻塞
    QtConcurrent::run([ = ]() {
        QTimer timer;
        timer.setSingleShot(true);

        QEventLoop *loop = new QEventLoop;

        QObject::connect(&timer, &QTimer::timeout, [ = ]() {
            parentWidget->deleteLater();
            loop->quit();
            qApp->exit();
        });

        timer.start(1000);
        loop->exec();

        delete loop;
    });

    Utils::showSameNameDialog(parentWidget, "servername1", "servername1");

    QTest::qWait(UT_WAIT_TIME);
#endif
}

// 参数解析
TEST(UT_Utils_Test, parseCommandLine)
{
    QStringList appArguments;
    appArguments << "deepin-terminal" << QString("-h");

    TermProperties properties;
    Utils::parseCommandLine(appArguments, properties, false);

    appArguments.clear();
    appArguments << "deepin-terminal" << QString("-v");
    Utils::parseCommandLine(appArguments, properties, false);

    appArguments.clear();
    appArguments << "deepin-terminal" << QString("-q");
    Utils::parseCommandLine(appArguments, properties, false);

    appArguments.clear();
    appArguments << "deepin-terminal" << "-e" << "ls" << "-w" << "/home/";
    Utils::parseCommandLine(appArguments, properties, false);
}

TEST(UT_Utils_Test, parseExecutePara)
{
    QStringList appArguments;
    appArguments << "deepin-terminal" << "-e" << "ls /home/";
    QStringList paraList = Utils::parseExecutePara(appArguments);
    EXPECT_EQ(paraList.size(), 2);

    appArguments.clear();
    appArguments << "deepin-terminal" << "-e" << "ping  127.0.0.1  -c 5";
    paraList = Utils::parseExecutePara(appArguments);
    EXPECT_EQ(paraList.size(), 4);

    appArguments.clear();
    appArguments << "deepin-terminal" << "-e" << "bash -c 'ping 127.0.0.1 -c 5'";
    paraList = Utils::parseExecutePara(appArguments);
    EXPECT_EQ(paraList.size(), 3);
}

TEST(UT_Utils_Test, parseNestedQString)
{
    QString str = QString("bash -c 'ping 127.0.0.1'");
    QStringList paraList = Utils::parseNestedQString(str);
    EXPECT_EQ(paraList.size(), 3);

    str = QString("bash -c ping 127.0.0.1");
    QStringList paraList2 = Utils::parseNestedQString(str);
    EXPECT_EQ(paraList.size(), 3);
}

TEST(UT_Utils_Test, FontFilterTest)
{
    FontFilter *ff = FontFilter::instance();
    ff->HandleWidthFont();

    ff->setStop(true);
    EXPECT_EQ(ff->m_bstop, true);

    ff->CompareWhiteList();
}

#endif
