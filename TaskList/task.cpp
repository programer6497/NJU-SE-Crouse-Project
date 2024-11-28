#include "task.h"

Task::Task() {

}
Task::Task(QDateTime createDate,int id,const QString& title,const QString& description,QDateTime deadline,QDateTime lastModified)
    :createDate(createDate),id(id),title(title),description(description),deadline(deadline),lastModified(lastModified){}

void Task::rename(const QString& new_name){
    title=new_name;
    lastModified=QDateTime::currentDateTime();
}

void Task::edit(const QString& new_description){
    description=new_description;
    lastModified=QDateTime::currentDateTime();
}

void Task::edit(const QString& title,const QString& description,QDateTime deadline){
    this->title=title;
    this->description=description;
    this->deadline=deadline;
    this->lastModified=QDateTime::currentDateTime();
}

Task::~Task(){

}

int Task::getID() const{
    return id;
}
QString Task::getTitle() const{
    return title;
}
QString Task::getDescription() const{
    return description;
}
QDateTime Task::getDDL() const{
    return deadline;
}
QDateTime Task::getCreateDate() const{
    return createDate;
}
QDateTime Task::getLastModified() const{
    return lastModified;
}

QJsonObject Task::toJson() const {
    QJsonObject jsonObj;
    jsonObj["id"]=id;
    jsonObj["title"] = title;
    jsonObj["description"] = description;
    jsonObj["deadline"] = deadline.toString(Qt::ISODate);
    jsonObj["createDate"] = createDate.toString(Qt::ISODate);
    jsonObj["lastModified"] = lastModified.toString(Qt::ISODate);
    return jsonObj;
}

void Task::fromJson(const QJsonObject& jsonObj) {
    id=jsonObj["id"].toInt();
    title = jsonObj["title"].toString();
    description = jsonObj["description"].toString();
    deadline = QDateTime::fromString(jsonObj["deadline"].toString(), Qt::ISODate);
    createDate = QDateTime::fromString(jsonObj["createDate"].toString(), Qt::ISODate);
    lastModified = QDateTime::fromString(jsonObj["lastModified"].toString(), Qt::ISODate);
}

