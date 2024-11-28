#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



/*
其他：
任务是允许重名的，所以只有id是键值
注意任务从回收站中恢复后，不会将其还原到各个组里。（这是特性，不是bug）

TODO:
析构函数有很多没有实现（主要是menu模块的）

分组功能
设置功能、清除数据功能
时间线显示


更详尽的设置
UI美化
重复规则
响铃提醒
新用户指引
搜索功能完善
任务列表中支持多选、ctrl/shift快捷键
ctrl+s 保存



*/
