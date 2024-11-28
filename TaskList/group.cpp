#include "group.h"
#include "task.h"

Group::Group(int id,QString title,QString description):group_id(id),title(title),description(description){

}

void Group::addMember(Task* t){
    members.push_back(t);
}

void Group::removeMember(int id){
    members.erase(
        std::remove_if(members.begin(), members.end(),
                       [&](Task* p) { return p->getID()==id;}),
        members.end());
}
