#ifndef GROUP_H
#define GROUP_H

class Task;

class Group
{
    friend class GroupManager;
private:
    std::vector<Task*> members;         //不具备这些Task的实际管理权，所以析构时不需要释放它们
    int group_id;
    QString title;
    QString description;

public:
    Group(int id,QString title,QString description="");

    void addMember(Task* t);
    void removeMember(int id);
};

#endif // GROUP_H
