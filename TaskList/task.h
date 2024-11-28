#ifndef TASK_H
#define TASK_H

class Task
{
private:
    QDateTime createDate;
    int id;
    QString title;
    QString description;
    QDateTime deadline;
    QDateTime lastModified;
public:
    Task();
    Task(QDateTime createDate,int id,const QString& title,const QString& description,QDateTime deadline,QDateTime lastModified);

    void rename(const QString& new_name);
    void edit(const QString& new_description);
    void edit(const QString& title,const QString& description,QDateTime deadline);
    ~Task();

    int getID()const;
    QString getTitle() const;
    QString getDescription() const;
    QDateTime getDDL() const;
    QDateTime getCreateDate() const;
    QDateTime getLastModified() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &jsonObj);
};

#endif // TASK_H
