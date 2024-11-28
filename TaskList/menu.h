#ifndef MENU_H
#define MENU_H

class MainWindow;
class TaskManager;
class SearchManager;
class Task;


enum PAGE_INDEX{        //注意要与MainWindow的stackedWidget中的顺序一致
    MAIN_PAGE,
    SETTING_PAGE,
    TASKS_PAGE,
    ADD_PAGE,
    CALENDAR_PAGE,
    INFO_PAGE,
    SEARCH_PAGE
};


class MainMenuPage:public QWidget{
    Q_OBJECT
public:
    MainMenuPage(MainWindow* parent);
    ~MainMenuPage();

private:
    MainWindow* parent;
    QLabel* main_label;
    QPushButton* list_button;
    QPushButton* timeaxis_button;
    QPushButton* calendar_button;
    QPushButton* setting_button;
};

class Setting;
class SettingsPage:public QWidget{
    Q_OBJECT
public:
    SettingsPage(MainWindow* parent);
    ~SettingsPage();
private:
    MainWindow* parent;

    QPushButton* back_button;
    QPushButton* confirm_button;

    Setting* temp_setting;
};

class TaskItem:public QListWidgetItem{
    friend class TasksPage;
    friend class CalendarPage;
    friend class SearchPage;
public:
    TaskItem(QString s,Task* t);
private:
    Task* task;
};

class TasksPage:public QWidget{
    Q_OBJECT
public:
    TasksPage(MainWindow* parent);
    ~TasksPage();

    void setListWidget();
protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void onItemDoubleClicked(QListWidgetItem *item);
    void deleteTask();


private:
    MainWindow* parent;
    QLabel* main_label;
    QPushButton* search_button;
    QPushButton* add_button;
    QPushButton* back_button;
    QPushButton* delete_button;
    QListWidget* listWidget;

    TaskManager* manager;
};

class AddPage:public QWidget{
    Q_OBJECT
public:
    AddPage(MainWindow* parent);
    ~AddPage();
private:
    MainWindow* parent;

    QLabel* main_label;
    QLabel* name_label;
    QLineEdit* name_input;
    QLabel* desc_label;
    QTextEdit* desc_input;
    QLabel* ddl_label;
    QDateTimeEdit* ddl_input;
    QPushButton* commit_button;
    QPushButton* back_button;
};

class CalendarPage:public QWidget{
    Q_OBJECT
public:
    CalendarPage(MainWindow* parent);
    ~CalendarPage();

    void onItemDoubleClicked(QListWidgetItem *item);

private:
    void update();

    MainWindow* parent;

    QCalendarWidget* calendar;
    QListWidget* listWidget;
    QPushButton* back_button;
};

class InfoPage:public QWidget{
    Q_OBJECT
public:
    InfoPage(MainWindow* parent);
    ~InfoPage();

    void set_task(Task *t);

private:
    MainWindow* parent;
    Task* task;

    QLabel* main_label;
    QLabel* name_label;
    QLineEdit* name_input;
    QLabel* desc_label;
    QTextEdit* desc_input;
    QLabel* ddl_label;
    QDateTimeEdit* ddl_input;
    QPushButton* commit_button;
    QPushButton* back_button;
};

class SearchPage:public QWidget{                //该页面在ChatGPT辅助下完成，故代码风格有所不同
    Q_OBJECT
public:
    SearchPage(MainWindow* parent);
    ~SearchPage();

private slots:
    void search();
    void onItemDoubleClicked(QListWidgetItem *item);
    // void onHistoryItemSelected();

private:
    MainWindow* parent;
    SearchManager* manager;

    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *backButton;
    // QComboBox *historyComboBox;
    QListWidget *resultsList;
};


#endif // MENU_H
