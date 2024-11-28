#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H
class Task;
class TaskManager;

class SearchManager
{
    friend class SearchPage;
private:
    std::vector<QString> search_history;

    TaskManager* taskManager;

public:
    SearchManager(TaskManager* taskManager);

    std::vector<Task*> search(QString query);
    const std::vector<QString> get_history() const;

    void save(QString path) const;
    void load(QString path);
};

#endif // SEARCHMANAGER_H
