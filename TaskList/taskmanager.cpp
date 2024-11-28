#include "taskmanager.h"
#include "task.h"
#include "trashmanager.h"
#include "groupmanager.h"

TaskManager::TaskManager() {
    last_id=0;
    trashManager=new TrashManager();
    groupManager=new GroupManager();
}
TaskManager::~TaskManager(){
    for(auto p:tasks){
        delete p;
    }
    delete trashManager;
    delete groupManager;
}
void TaskManager::createtask(QString title,QString Description,QDateTime DDL){
    QDateTime createTime=QDateTime::currentDateTime();
    tasks.push_back(new Task(createTime,++last_id,title,Description,DDL,createTime));
}
void TaskManager::removeTask(int id){
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
                       [&](Task* p) { if(p->getID()==id){trashManager->addTrash(p);groupManager->removeTaskFromALL(id);return true;}return false;}),
        tasks.end());
}
void TaskManager::removeTask(QString title){
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
                       [&](Task* p) {if(p->getTitle()==title){trashManager->addTrash(p);groupManager->removeTaskFromALL(p->getID());return true;}return false;}),
        tasks.end());
}

void TaskManager::deleteTask(int id){
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
                       [&](Task* p) { if(p->getID()==id){groupManager->removeTaskFromALL(id);delete p;return true;}return false;}),
        tasks.end());
}
void TaskManager::deleteTask(QString title){
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
                       [&](Task* p) {if(p->getTitle()==title){groupManager->removeTaskFromALL(p->getID());delete p;return true;}return false;}),
        tasks.end());
}

const std::vector<Task*>& TaskManager::get_tasks() const{
    return tasks;
}

void TaskManager::load(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file for reading");
        return;
    }
    QByteArray fileData = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();
    QJsonArray jsonArray = jsonObject["all_tasks"].toArray();
    for (const auto &jsonValue : jsonArray) {
        if (jsonValue.isObject()) {
            Task *t = new Task();
            t->fromJson(jsonValue.toObject());
            tasks.push_back(t);
        }
    }
}

void TaskManager::save(QString path) const{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open file for writing");
        return;
    }
    QJsonArray jsonArray;
    for (Task* t : tasks) {
        jsonArray.append(t->toJson());
    }
    QJsonObject jsonObject;
    jsonObject["all_tasks"]=jsonArray;
    QJsonDocument jsonDoc(jsonObject);
    file.write(jsonDoc.toJson());
    file.close();
}
