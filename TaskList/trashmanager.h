#ifndef TRASHMANAGER_H
#define TRASHMANAGER_H

class Task;

class TrashManager
{
private:
    std::vector<Task*> trashes;

public:
    TrashManager();
    ~TrashManager();
    void addTrash(Task* t);
    void deleteTask(int id);
    void autoDelete();
};

#endif
