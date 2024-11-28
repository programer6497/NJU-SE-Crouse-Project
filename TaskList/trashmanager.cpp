#include "trashmanager.h"
#include "task.h"

TrashManager::TrashManager(){

}
TrashManager::~TrashManager(){
    for(auto p: trashes){
        delete p;
    }
}
void TrashManager::addTrash(Task* t){
    trashes.push_back(t);
}
void TrashManager::deleteTask(int id){
    trashes.erase(
        std::remove_if(trashes.begin(), trashes.end(),
                      [=](Task* p) { if(p->getID()==id){delete p;return true;}return false;}),
        trashes.end());
}
void TrashManager::autoDelete(){                //每次应用启动时进行检测
    trashes.erase(
        std::remove_if(trashes.begin(), trashes.end(),
                       [=](Task* p) { if(p->getLastModified().secsTo(QDateTime::currentDateTime())>30*24*3600){delete p;return true;}return false;}),
        trashes.end());
    //删除30天之前加入回收站的任务
}
