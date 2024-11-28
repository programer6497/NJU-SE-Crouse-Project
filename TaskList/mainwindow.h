#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class MainMenuPage;
class SettingsPage;
class TasksPage;
class AddPage;
class AppManager;
class CalendarPage;
class InfoPage;
class SearchPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class TasksPage;
    friend class CalendarPage;
    friend class SearchPage;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPageIndex(int index);
    void backPage();        //返回

    AppManager* get_manager();

private:
    QStackedWidget* stackedWidget;
    MainMenuPage* mainMenuPage;
    SettingsPage* settingsPage;
    TasksPage* tasksPage;
    AddPage* addPage;
    CalendarPage* calendarPage;
    InfoPage* infoPage;
    SearchPage* searchPage;

    AppManager* manager;

    std::stack<int> call_stack;         //因为C++不支持enum的前向声明，所以没有设为PAGE_INDEX类型（其实可以把声明放到单独的enum.h中）
    //记录上一个页面，在返回时使用

};
#endif // MAINWINDOW_H
