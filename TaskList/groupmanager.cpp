#include "groupmanager.h"
#include "group.h"

GroupManager::GroupManager() {
    last_id=0;
}

GroupManager::~GroupManager(){
    for(auto group:groups){
        delete group;
    }
}

void GroupManager::createGroup(QString title, QString description){
    groups.push_back(new Group(++last_id,title,description));
}

void GroupManager::deleteGroup(int group_id){
    groups.erase(
        std::remove_if(groups.begin(), groups.end(),
                       [&](Group* p) { if(p->group_id==group_id){delete p;return true;}return false;}),
        groups.end());
}

void GroupManager::addTaskToGroup(Task* t, int group_id){
    for(auto group:groups){
        if(group->group_id==group_id){
            group->addMember(t);
            break;
        }
    }
}

void GroupManager::removeTask(int group_id, int task_id){
    for(auto group:groups){
        if(group->group_id==group_id){
            group->removeMember(task_id);
            break;
        }
    }
}

void GroupManager::removeTaskFromALL(int task_id){
    for(auto group:groups){
        group->removeMember(task_id);       //如果本来就没有则不会进行任何处理
    }
}


