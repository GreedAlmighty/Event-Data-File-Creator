#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include "databasecommands.h"
#include "querycommands.h"

QSqlDatabase db;

void DBCommands::createDatabase()
{
    QDir database_path;
    QueryCommands qry_cmd;
    QString path = database_path.currentPath()+"/tempdb.db";

    qDebug() << path;

    db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName(path);
    if(!db.open()){
        qDebug() << "error opening database";
    }

    QSqlQuery query(db);

    if(!query.exec(create_table_query)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    query.exec("BEGIN TRANSACTION");
    qry_cmd.clearQueryString();
}

void DBCommands::deleteDatabase()
{
    QDir database_path;

    db.close();

    if( database_path.remove( database_path.currentPath()+"/tempdb.db" ) ){
        qDebug() << "database removed";
    }
    else{
        qDebug() << database_path.currentPath()+"/tempdb.db";
    }
}

void DBCommands::insertIntoDatabase( QString values )
{
    QSqlQuery query(db);
    QueryCommands qry_cmd;

    qry_cmd.addInsertToQuery("mastercsv", values);

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
}

void DBCommands::endTransaction()
{
    QSqlQuery query(db);
    QueryCommands qry_cmd;
    QString qry = "END TRANSACTION";
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
}

QList<QString> DBCommands::retrieveListOfUniqueText( QString column )
{
    QStringList str_list;
    QueryCommands qry_cmd;

    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( "mastercsv", column );
    qry_cmd.addOrderByToQuery( column );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while(query.next()){
        QString value = query.value(0).toString();
        str_list.append(value);
    }
    return str_list;
}

QList<QString> DBCommands::performListofDetections( QString column, QString order_by )
{
    QueryCommands qry_cmd;
    QStringList str_data_list;

    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( "mastercsv", column);
    qry_cmd.addOrderByToQuery( order_by );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

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
    QueryCommands qry_cmd;
    QStringList str_list;

    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery("mastercsv", column);
    qry_cmd.addWhereToQuery( condition );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while (query.next()) {
        str_list.append( query.value(0).toString() );
    }
    return str_list;
}

QList<int> DBCommands::retrieveListOfUniqueNumbers( QString column )
{
    QList<int> int_list;
    QueryCommands qry_cmd;

    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( "mastercsv", column );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

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
    QueryCommands qry_cmd;

    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery("mastercsv", column);
    qry_cmd.addWhereToQuery( condition );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

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
    QueryCommands qry_cmd;

    QSqlQuery query(db);

    qry_cmd.addSelectToQuery( "mastercsv", column );
    qry_cmd.addWhereToQuery( condition );

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

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
    QueryCommands qry_cmd;

    QSqlQuery query(db);

    qry_cmd.addDistinctToQuery( "mastercsv", column);

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}

int DBCommands::countAllValues(){
    QueryCommands qry_cmd;

    QSqlQuery query(db);

    qry_cmd.addSelectToQuery( "mastercsv", "*");

    QString qry = qry_cmd.getQueryString();
    qry_cmd.clearQueryString();

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    if(query.last()){
        return query.at() + 1;
    }
    return -1;
}
