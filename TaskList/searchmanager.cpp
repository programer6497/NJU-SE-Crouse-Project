#include "searchmanager.h"
#include "task.h"
#include "taskmanager.h"

SearchManager::SearchManager(TaskManager* taskManager):taskManager(taskManager) {

}

std::vector<Task*> SearchManager::search(QString query){
    search_history.push_back(query);
    const std::vector<Task*>& tasks=taskManager->get_tasks();
    std::vector<Task*> results;
    for (const auto& t : tasks) {
        // 使用find进行模糊匹配，忽略大小写
        if (t->getTitle().contains(query, Qt::CaseInsensitive)) {       //忽略大小写
            results.push_back(t);
        }
    }
    return results;
}

const std::vector<QString> SearchManager::get_history() const{
    return search_history;
}

void SearchManager::load(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file for reading");
        return;
    }
    QByteArray fileData = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();
    QJsonArray jsonArray = jsonObject["history"].toArray();
    for (const auto &jsonValue : jsonArray) {
        if (jsonValue.isString()) {
            search_history.push_back(jsonValue.toString());
        }
    }
}

void SearchManager::save(QString path) const{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open file for writing");
        return;
    }
    QJsonArray jsonArray;
    for (const QString& s : search_history) {
        jsonArray.append(s);
    }
    QJsonObject jsonObject;
    jsonObject["history"]=jsonArray;
    QJsonDocument jsonDoc(jsonObject);
    file.write(jsonDoc.toJson());
    file.close();
}
