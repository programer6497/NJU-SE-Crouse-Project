#include "appmanager.h"
#include "taskmanager.h"
#include "searchmanager.h"


AppManager::AppManager() {
    taskManager=new TaskManager();
    searchManager=new SearchManager(taskManager);
    dir_path="";            //TODO：以后可以在设置中调整

    load(dir_path);
}

AppManager::~AppManager(){
    save(dir_path);
}



void AppManager::load(QString dir_path){
    taskManager->load(dir_path+"/data.txt");
    searchManager->load(dir_path+"/search_his.txt");
}

void AppManager::save(QString dir_path){
    taskManager->save(dir_path+"/data.txt");
    searchManager->save(dir_path+"/search_his.txt");
}

