#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include "databasecommands.h"
#include "querycommands.h"

QSqlDatabase db;
QueryCommands qry_cmd;

DBCommands::DBCommands()
{

}

DBCommands::~DBCommands()
{

}

void DBCommands::beginTransaction(){
    QSqlQuery query(db);

    query.exec("BEGIN TRANSACTION");
    qry_cmd.clearQueryString();
}

void DBCommands::createTable( QString table_name, QString table_columns)
{
    QString qry = "create table " + table_name +
                        " (" + table_columns + ");";

    QSqlQuery query(db);

    if(!query.exec(qry)){
        qDebug() << query.lastError().text();
        qDebug() << qry;
    }
}

void DBCommands::createDatabase()
{
    QDir database_path;
    QString path = database_path.currentPath()+"/tempdb.db";

    db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName(path);
    if(!db.open()){
        qDebug() << "error opening database";
    }
}

void DBCommands::deleteDatabase()
{
    QDir database_path;

    db.close();

    if( database_path.remove( database_path.currentPath()+"/tempdb.db" ) ){
        qDebug() << "database removed";
    }
    else{
        qDebug() << "database not removed";
    }
}

void DBCommands::insertIntoDatabase( QString table, QString values )
{
    QSqlQuery query(db);

    qry_cmd.addInsertToQuery(table, values);

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
}

void DBCommands::endTransaction()
{
    QSqlQuery query(db);

    QString qry = "END TRANSACTION";
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
}

QList<QString> *DBCommands::retrieveListOfUniqueText( QString table, QString column )
{
    QStringList *str_list;
    str_list = new QStringList;
    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( table, column );
    qry_cmd.addOrderByToQuery( column );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    while(query.next()){
        QString value = query.value(0).toString();
        str_list->append(value);
    }
    return str_list;
}

QList<QString> *DBCommands::performListofDetections( QString table, QString column, QString order_by )
{
    QStringList *str_data_list;
    str_data_list = new QStringList;
    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( table, column);
    qry_cmd.addOrderByToQuery( order_by );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    while(query.next()){
        str_data_list->append( query.value(0).toString() );
        str_data_list->append( query.value(1).toString() );
        str_data_list->append( query.value(2).toString() );
    }
    return str_data_list;
}

QList<QString> *DBCommands::getListofDistinctTextWithCondition( QString table, QString column, QString condition)
{
    QStringList *str_list;
    str_list = new QStringList;
    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery(table, column);
    qry_cmd.addWhereToQuery( condition );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    while (query.next()) {
        str_list->append( query.value(0).toString() );
    }
    return str_list;
}

QList<int> *DBCommands::retrieveListOfUniqueNumbers( QString table, QString column )
{
    QList<int> *int_list;
    QSqlQuery query(db);

    int_list = new QList<int>;

    qry_cmd.addDistinctToQuery( table, column );
    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    while(query.next()){
        int value = query.value(0).toInt();
        int_list->append(value);
    }
    return int_list;
}

int DBCommands::countDistinctValuesWithCondition( QString table, QString column, QString condition)
{
    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery(table, column);
    qry_cmd.addWhereToQuery( condition );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    if(query.last()){
        return query.at() + 1;
    }
    return 0;
}

int DBCommands::countValuesWithCondition( QString table, QString column, QString condition )
{
    QSqlQuery query(db);

    qry_cmd.addSelectToQuery( table, column );
    qry_cmd.addWhereToQuery( condition );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

int DBCommands::countAllDistinctValues( QString table, QString column )
{
    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( table, column);

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

int DBCommands::countAllValues(QString table){
    QSqlQuery query(db);

    qry_cmd.addSelectToQuery( table, "*");

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
        qDebug() << qry;
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}
