#include "menu.h"
#include "mainwindow.h"
#include "task.h"
#include "taskmanager.h"
#include "searchmanager.h"
#include "appmanager.h"

MainMenuPage::MainMenuPage(MainWindow* parent):QWidget(parent),parent(parent){
    // this->setStyleSheet("background-color: rgb(0, 0, 139);");
    main_label=new QLabel(this);
    main_label->setGeometry(380,50,100,50);
    main_label->setText("任务单");
    main_label->setAlignment(Qt::AlignCenter);
    main_label->show();

    list_button=new QPushButton(this);
    list_button->setGeometry(380,250,100,50);
    list_button->setText("任务列表");
    list_button->setStyleSheet("background-color: rgb(173, 216, 230);"
                               "color: black;");
    list_button->show();

    timeaxis_button=new QPushButton(this);
    timeaxis_button->setGeometry(380,350,100,50);
    timeaxis_button->setText("时间线");
    timeaxis_button->setStyleSheet("background-color: rgb(173, 216, 230);"
                    "color: black;");
    timeaxis_button->show();

    calendar_button=new QPushButton(this);
    calendar_button->setGeometry(380,450,100,50);
    calendar_button->setText("日历");
    calendar_button->setStyleSheet("background-color: rgb(173, 216, 230);"
                    "color: black;");
    calendar_button->show();


    /*todo：从硬盘加载*/

    connect(list_button,&QPushButton::clicked,this,[=](){
        parent->setPageIndex(TASKS_PAGE);
    });

    connect(timeaxis_button,&QPushButton::clicked,this,[=](){


    });

    connect(calendar_button,&QPushButton::clicked,this,[=](){
        parent->setPageIndex(CALENDAR_PAGE);
    });


}

MainMenuPage::~MainMenuPage(){
    delete main_label;
    delete list_button;
    delete timeaxis_button;
    delete calendar_button;
    // delete setting_button;

    //todo
}


SettingsPage::SettingsPage(MainWindow* parent):QWidget(parent),parent(parent){
    // temp_setting=new Setting(setting);

    // back_button=new QPushButton(this);
    // back_button->setGeometry(450,650,100,50);
    // back_button->setText("返回");
    // back_button->show();

    // confirm_button=new QPushButton(this);
    // confirm_button->setGeometry(650,650,100,50);
    // confirm_button->setText("确定");
    // confirm_button->show();

    // connect(back_button,&QPushButton::clicked,this,[=](){
    //     *temp_setting=setting;          //将临时设置重置为当前设置，方便下次调用
    //     parent->backPage();
    // });

    // connect(confirm_button,&QPushButton::clicked,this,[=](){
    //     setting=*temp_setting;          //修改设置
    //     /*todo：导出到硬盘*/
    //     parent->backPage();

    // });
}

SettingsPage::~SettingsPage(){
    // delete temp_setting;
    // delete back_button;

}


TaskItem::TaskItem(QString s, Task* t):QListWidgetItem(s),task(t){}
TasksPage::TasksPage(MainWindow* parent):parent(parent){
    manager=parent->get_manager()->taskManager;

    main_label=new QLabel(this);
    main_label->setGeometry(380,50,100,50);
    main_label->setText("任务列表");
    main_label->setAlignment(Qt::AlignCenter);
    main_label->show();

    listWidget = new QListWidget(this);
    listWidget->setFocusPolicy(Qt::NoFocus);            //避免直接将第一项当做当前项，导致初始时点击删除按钮的行为异常
    listWidget->setGeometry(230,150,400,300);
    listWidget->show();

    search_button=new QPushButton(this);
    search_button->setIcon(QIcon(":/images/src/search.png"));
    search_button->setGeometry(750,50,50,50);
    search_button->show();

    add_button=new QPushButton(this);
    add_button->setGeometry(750,520,50,50);
    add_button->setText("添加");
    add_button->setStyleSheet("background-color: rgb(173, 216, 230);"
                               "color: black;");
    add_button->show();

    back_button=new QPushButton(this);
    back_button->setGeometry(20,50,50,50);
    back_button->setText("返回");
    back_button->setStyleSheet("background-color: rgb(173, 216, 230);"
                               "color: black;");
    back_button->show();

    delete_button=new QPushButton(this);
    delete_button->setGeometry(680,520,50,50);
    delete_button->setText("删除");
    delete_button->setStyleSheet("background-color: rgb(230, 173, 186);"
                               "color: black;");
    delete_button->show();

    setListWidget();

    connect(listWidget, &QListWidget::itemDoubleClicked, this, &TasksPage::onItemDoubleClicked);

    connect(search_button,&QPushButton::clicked,this,[=](){
        parent->setPageIndex(SEARCH_PAGE);
    });

    connect(add_button,&QPushButton::clicked,this,[=](){
        parent->setPageIndex(ADD_PAGE);
    });

    connect(back_button,&QPushButton::clicked,this,[=](){
        parent->backPage();
    });

    connect(delete_button,&QPushButton::clicked,this,&TasksPage::deleteTask);
}

void TasksPage::setListWidget(){
    listWidget->clear();
    for (Task* t:manager->get_tasks()) {
        QListWidgetItem *item = new TaskItem(t->getTitle(),t);
        listWidget->addItem(item);
    }
    listWidget->clearSelection();
}

void TasksPage::deleteTask(){
    if(listWidget->currentItem()==nullptr){
        return;
    }
    QMessageBox messageBox;
    messageBox.setWindowTitle("提示");
    messageBox.setText("确认要删除吗？");

    QPushButton *button1 = messageBox.addButton("取消", QMessageBox::ActionRole);
    QPushButton *button2 = messageBox.addButton("移入回收站", QMessageBox::ActionRole);
    QPushButton *button3 = messageBox.addButton("彻底删除", QMessageBox::ActionRole);

    messageBox.exec();

    if (messageBox.clickedButton() == button1) {
        messageBox.close();
    } else if (messageBox.clickedButton() == button2) {
        TaskItem* i=(TaskItem*)listWidget->currentItem();       //强制类型转换
        parent->get_manager()->taskManager->removeTask(i->task->getID());
        setListWidget();
        messageBox.close();
    } else if (messageBox.clickedButton() == button3) {
        TaskItem* i=(TaskItem*)listWidget->currentItem();       //强制类型转换
        parent->get_manager()->taskManager->deleteTask(i->task->getID());
        setListWidget();
        messageBox.close();
    }

}

void TasksPage::showEvent(QShowEvent *event){
    QWidget::showEvent(event); // 调用基类方法，保持默认行为
    setListWidget();
}

void TasksPage::onItemDoubleClicked(QListWidgetItem *item){
    parent->infoPage->set_task(((TaskItem*)item)->task);            //强制类型转换，想想有没有更优雅的方式
    parent->setPageIndex(INFO_PAGE);
}

TasksPage::~TasksPage(){


}


AddPage::AddPage(MainWindow* parent):parent(parent){
    main_label=new QLabel(this);
    main_label->setGeometry(380,50,100,50);
    main_label->setText("添加任务");
    main_label->show();

    name_label=new QLabel(this);
    name_label->setGeometry(180,150,100,50);
    name_label->setText("名称");
    name_label->show();

    name_input=new QLineEdit(this);
    name_input->setGeometry(300,150,150,50);
    name_input->setText("新建任务");
    name_input->show();

    desc_label=new QLabel(this);
    desc_label->setGeometry(180,200,100,50);
    desc_label->setText("描述");
    desc_label->show();

    desc_input=new QTextEdit(this);
    desc_input->setGeometry(300,200,150,50);
    desc_input->setPlaceholderText("...");
    desc_input->show();

    ddl_label=new QLabel(this);
    ddl_label->setGeometry(180,250,100,50);
    ddl_label->setText("截止日期");
    ddl_label->show();

    ddl_input=new QDateTimeEdit(this);
    ddl_input->setGeometry(300,250,150,50);
    ddl_input->setDateTime(QDateTime(QDate(2024, 1, 1), QTime(0, 0, 0)));
    ddl_input->setStyleSheet(
        "QDateTimeEdit {"
        "  border: 1px solid #B0B0B0;"
        "  border-radius: 5px;"
        "  padding: 5px;"
        "  background-color: #F0F0F0;"
        "  font-size: 14px;"
        "}"
        "QDateTimeEdit:focus {"
        "  border: 1px solid #6A9EFD;"
        "  background-color: #E7F2FE;"
        "}"
        );
    ddl_input->show();

    commit_button=new QPushButton(this);
    commit_button->setGeometry(450,500,100,50);
    commit_button->setText("确定");
    commit_button->show();

    back_button=new QPushButton(this);
    back_button->setGeometry(300,500,100,50);
    back_button->setText("返回");
    back_button->show();

    connect(commit_button,&QPushButton::clicked,this,[=](){
        parent->get_manager()->taskManager->createtask(name_input->text(),desc_input->toPlainText(),ddl_input->dateTime());
        parent->backPage();
        name_input->setText("新建任务");                //还原输入控件的初始值
        desc_input->setText("");
        ddl_input->setDateTime(QDateTime(QDate(2024, 1, 1), QTime(0, 0, 0)));
    });

    connect(back_button,&QPushButton::clicked,this,[=](){
        parent->backPage();
        name_input->setText("新建任务");                //还原输入控件的初始值
        desc_input->setText("");
        ddl_input->setDateTime(QDateTime(QDate(2024, 1, 1), QTime(0, 0, 0)));
    });
}

AddPage::~AddPage(){
    //todo
}


CalendarPage::CalendarPage(MainWindow* parent):parent(parent){
    calendar=new QCalendarWidget(this);     //默认值为当前日期
    calendar->setGeometry(330,100,200,200);

    listWidget = new QListWidget(this);
    listWidget->setGeometry(230,350,400,200);

    back_button=new QPushButton("返回",this);
    back_button->setGeometry(20,20,50,50);

    update();

    connect(listWidget, &QListWidget::itemDoubleClicked, this, &CalendarPage::onItemDoubleClicked);

    connect(calendar, &QCalendarWidget::selectionChanged, this,[=](){
        update();
    });

    connect(back_button, &QPushButton::clicked, this,[=](){
        parent->backPage();
    });
}

void CalendarPage::onItemDoubleClicked(QListWidgetItem *item){
    parent->infoPage->set_task(((TaskItem*)item)->task);            //强制类型转换，想想有没有更优雅的方式
    parent->setPageIndex(INFO_PAGE);
}

void CalendarPage::update(){            //每次点击不同日期后，需要更新list的内容
    listWidget->clear();
    std::vector<Task*> tasks=parent->get_manager()->taskManager->get_tasks();
    for(Task* t:tasks){
        if(t->getDDL().date()==calendar->selectedDate()){
            listWidget->addItem(new TaskItem(t->getTitle(),t));
        }
    }
}

CalendarPage::~CalendarPage(){
    delete calendar;
    delete listWidget;
}

InfoPage::InfoPage(MainWindow* parent):parent(parent){
    main_label=new QLabel(this);
    main_label->setGeometry(380,50,100,50);
    main_label->setText("任务详情");
    main_label->show();

    name_label=new QLabel(this);
    name_label->setGeometry(180,150,100,50);
    name_label->setText("名称");
    name_label->show();

    name_input=new QLineEdit(this);
    name_input->setGeometry(300,150,150,50);
    name_input->show();

    desc_label=new QLabel(this);
    desc_label->setGeometry(180,200,100,50);
    desc_label->setText("描述");
    desc_label->show();

    desc_input=new QTextEdit(this);
    desc_input->setGeometry(300,200,150,50);
    desc_input->show();

    ddl_label=new QLabel(this);
    ddl_label->setGeometry(180,250,100,50);
    ddl_label->setText("截止日期");
    ddl_label->show();

    ddl_input=new QDateTimeEdit(this);
    ddl_input->setGeometry(300,250,150,50);
    ddl_input->setStyleSheet(
        "QDateTimeEdit {"
        "  border: 1px solid #B0B0B0;"
        "  border-radius: 5px;"
        "  padding: 5px;"
        "  background-color: #F0F0F0;"
        "  font-size: 14px;"
        "}"
        "QDateTimeEdit:focus {"
        "  border: 1px solid #6A9EFD;"
        "  background-color: #E7F2FE;"
        "}"
        );
    ddl_input->show();

    commit_button=new QPushButton(this);
    commit_button->setGeometry(450,500,100,50);
    commit_button->setText("确定");
    commit_button->show();

    back_button=new QPushButton(this);
    back_button->setGeometry(300,500,100,50);
    back_button->setText("返回");
    back_button->show();

    connect(commit_button,&QPushButton::clicked,this,[=](){
        task->edit(name_input->text(),desc_input->toPlainText(),ddl_input->dateTime());
        parent->backPage();
    });

    connect(back_button,&QPushButton::clicked,this,[=](){
        parent->backPage();
    });
}

void InfoPage::set_task(Task* t){
    task=t;
    name_input->setText(task->getTitle());
    desc_input->setText(task->getDescription());
    ddl_input->setDateTime(task->getDDL());
}

InfoPage::~InfoPage(){

}

SearchPage::SearchPage(MainWindow* parent):parent(parent){          //todo:历史记录的显示与选择(searchManager中相应接口已实现好)
    //todo:添加选项：仅在title中搜索，还是包含description（目前只能在title中搜索）
    //添加对正则表达式的支持
    //在搜索界面添加删除功能
    manager=parent->get_manager()->searchManager;

    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("输入搜索内容...");
    searchInput->setClearButtonEnabled(true);
    searchInput->setGeometry(80,20,680,50);

    // historyComboBox= new QComboBox(this);
    // historyComboBox->setGeometry(80,70,680,20);


    searchButton = new QPushButton(this);
    searchButton->setIcon(QIcon(":/images/src/search.png"));
    searchButton->setGeometry(760,20,50,50);

    backButton = new QPushButton("返回", this);
    backButton->setGeometry(5,20,60,50);

    resultsList = new QListWidget(this);
    resultsList->setGeometry(0,90,860,500);

    // 连接信号和槽
    connect(backButton, &QPushButton::clicked, this, [=](){
        parent->backPage();
        searchInput->setText("");       //重置输入
        resultsList->clear();           //重置结果
    });
    connect(searchButton, &QPushButton::clicked, this, &SearchPage::search);
    connect(searchInput, &QLineEdit::returnPressed, this, &SearchPage::search);
    connect(resultsList, &QListWidget::itemDoubleClicked, this, &SearchPage::onItemDoubleClicked);
    // connect(historyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SearchPage::onHistoryItemSelected);
}

SearchPage::~SearchPage(){
    delete searchInput;
    // delete historyComboBox;
    delete searchButton;
    delete backButton;
    delete resultsList;
}

void SearchPage::search() {
    QString query = searchInput->text();
    if (!query.isEmpty()) {
        std::vector<Task*> search_result=manager->search(query);
        resultsList->clear();
        for(Task* t:search_result){
            QListWidgetItem *item = new TaskItem(t->getTitle(),t);
            resultsList->addItem(item);
        }
    }
}

void SearchPage::onItemDoubleClicked(QListWidgetItem *item){
    parent->infoPage->set_task(((TaskItem*)item)->task);            //强制类型转换，想想有没有更优雅的方式
    parent->setPageIndex(INFO_PAGE);
}

// void SearchPage::onHistoryItemSelected() {

// }


