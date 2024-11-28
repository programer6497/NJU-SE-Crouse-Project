#ifndef TASKMANAGER_H
#define TASKMANAGER_H

class Task;
class TrashManager;
class GroupManager;

class TaskManager
{
private:
    int last_id;            //上一个创建的任务的id
    std::vector<Task*> tasks;
    TrashManager* trashManager;
    GroupManager* groupManager;

public:
    TaskManager();
    ~TaskManager();
    void createtask(QString title,QString Description,QDateTime DDL);
    void removeTask(int id);            //移入回收站
    void removeTask(QString title);
    void deleteTask(int id);            //彻底删除
    void deleteTask(QString title);

    const std::vector<Task*>& get_tasks()const;

    void load(QString path);
    void save(QString path) const;
};
#endif // TASKMANAGER_H
