#include "mainwindow.h"
#include "menu.h"
#include "appmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗口大小
    setFixedSize(860,600);            /*TEMP*/

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    manager=new AppManager();
/*todo：从硬盘导入数据*/     //应该在AppManager中导入
    //添加页面
    mainMenuPage = new MainMenuPage(this);
    stackedWidget->addWidget(mainMenuPage);
    settingsPage = new SettingsPage(this);
    stackedWidget->addWidget(settingsPage);
    tasksPage = new TasksPage(this);
    stackedWidget->addWidget(tasksPage);
    addPage= new AddPage(this);
    stackedWidget->addWidget(addPage);
    calendarPage= new CalendarPage(this);
    stackedWidget->addWidget(calendarPage);
    infoPage= new InfoPage(this);
    stackedWidget->addWidget(infoPage);
    searchPage= new SearchPage(this);
    stackedWidget->addWidget(searchPage);

    stackedWidget->setCurrentIndex(MAIN_PAGE);
}

MainWindow::~MainWindow(){
    delete stackedWidget;
    //注意各个page会由stackedWidget的析构一并释放，不能在这里再次手动析构

    delete manager;
}

void MainWindow::setPageIndex(int index){
    call_stack.push(stackedWidget->currentIndex());
    stackedWidget->setCurrentIndex(index);
}

void MainWindow::backPage(){
    stackedWidget->setCurrentIndex(call_stack.top());
    call_stack.pop();
}

AppManager* MainWindow::get_manager(){
    return manager;
}

