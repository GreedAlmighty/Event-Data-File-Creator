#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include "databasecommands.h"

QSqlDatabase db;
QSqlQuery query;

void DBCommands::createDatabase()
{
    QDir database_path;
    QString path = database_path.currentPath()+"tempdb.db";

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName(path);
    if(!db.open()){
        qDebug() << "error opening database";
    }

    QSqlQuery query(db);

    if(!query.exec(create_table_query)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    query.exec("BEGIN TRANSACTION");
}

void DBCommands::insertIntoDatabase( QString values )
{
    QSqlQuery query(db);
    QString qry = "INSERT INTO mastercsv "
                     "VALUES (" + values + ");";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
}

void DBCommands::endTransaction()
{
    QSqlQuery query(db);
    QString qry = "END TRANSACTION";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
}

QList<QString> DBCommands::retrieveListOfUniqueText( QString column )
{
    QStringList str_list;

    QSqlQuery query(db);
    QString qry = "SELECT DISTINCT " + column +
                  " FROM mastercsv" +
                  " ORDER BY " + column;

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while(query.next()){
        QString value = query.value(0).toString();
        str_list.append(value);
    }
    return str_list;
}

QList<QString> DBCommands::performListofDetections( QString condition, QString order_by )
{
    QSqlQuery query(db);
    QStringList str_data_list;

    QString qry = "SELECT DISTINCT " + condition +
                  " FROM mastercsv"
                  " ORDER BY " + order_by +
                  ";";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while(query.next()){
        str_data_list.append( query.value(0).toString() );
        str_data_list.append( query.value(1).toString() );
        str_data_list.append( query.value(2).toString() );
    }
    return str_data_list;
}

QList<QString> DBCommands::getListofDistinctTextWithCondition( QString column, QString condition)
{
    QSqlQuery query(db);
    QStringList str_list;

    QString qry = "SELECT DISTINCT " + column +
                  " FROM mastercsv"
                  " WHERE " + condition +
                  ";";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while (query.next()) {
        str_list.append( query.value(0).toString() );
    }
    return str_list;
}

QString DBCommands::retrieveValueFromQuery()
{
    QString str;

    if(query.next()){
        QString value0 = query.value(0).toString();
        QString value1 = query.value(1).toString();
        QString value2 = query.value(2).toString();
        str = value0 + "-" + value1 + "-" + value2;
        return str;
    }
    else
        return "end";
}

QList<int> DBCommands::retrieveListOfUniqueNumbers( QString column )
{
    QList<int> int_list;

    QSqlQuery query(db);
    QString qry = "SELECT DISTINCT " + column +
                  " FROM mastercsv;";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while(query.next()){
        int value = query.value(0).toInt();
        int_list.append(value);
    }
    return int_list;
}

int DBCommands::countDistinctValuesWithCondition( QString column, QString condition)
{
    QSqlQuery query(db);

    QString qry = "SELECT DISTINCT " + column +
                  " FROM mastercsv"
                  " WHERE " + condition +
                  ";";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

int DBCommands::countValuesWithCondition( QString column, QString condition )
{
    QSqlQuery query(db);

    QString qry = "SELECT " + column +
                  " FROM mastercsv"
                  " WHERE " + condition +
                  ";";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

int DBCommands::countAllDistinctValues( QString column )
{
    QSqlQuery query(db);
    QString qry = "SELECT DISTINCT " + column +
                  " FROM mastercsv;";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

int DBCommands::countAllValues(){
    QSqlQuery query(db);

    QString qry = "SELECT * FROM mastercsv";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

//TODO CLEAN UP THIS CODE
