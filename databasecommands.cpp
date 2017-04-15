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
                  " FROM mastercsv;";

    if(!query.exec(qry)){
        qDebug() << "error with query :" + query.lastError().text();
    }
    while(query.next()){
        QString value = query.value(0).toString();
        str_list.append(value);
    }
    return str_list;
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

//Create a function that returns all counted values for a column
//Create a function that returns all counted values with a statement
