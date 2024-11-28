#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

class Group;
class Task;

class GroupManager
{
private:
    int last_id;            //上一个创建的group的id
    std::vector<Group*> groups;
public:
    GroupManager();
    ~GroupManager();
    void createGroup(QString title,QString description="");
    void deleteGroup(int group_id);
    void addTaskToGroup(Task* t,int group_id);
    void removeTask(int group_id,int task_id);
    void removeTaskFromALL(int task_id);
};

#endif // GROUPMANAGER_H
