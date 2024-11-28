#ifndef APPMANAGER_H
#define APPMANAGER_H

class TaskManager;
class SearchManager;

class AppManager
{
private:
    QString dir_path;

public:
    AppManager();
    ~AppManager();

    TaskManager* taskManager;
    SearchManager* searchManager;

    void load(QString dir_path);
    void save(QString dir_path);

};

#endif // APPMANAGER_H
