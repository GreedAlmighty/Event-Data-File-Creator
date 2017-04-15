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
    QString insert = "INSERT INTO mastercsv "
                     "VALUES (" + values + ");";

    if(!query.exec(insert)){
        qDebug() << "error with query :" + query.lastError().text();
    }
}

void DBCommands::endTransaction()
{
    QSqlQuery query(db);
    QString trans = "END TRANSACTION";

    if(!query.exec(trans)){
        qDebug() << "error with query :" + query.lastError().text();
    }
}

//TODO Create QSqlQueries to read/calculate the data
//TODO Research how to calculate the data with similar Excel functions.
    //1ST - calculate all detected tags and calculate the detection rate for each location
    //2ND - create a list of all tags that were detected.
    //3RD - show on which location the tag has been detected and on which it wasnt.
    //4TH - show how many tags missed only one timeline.
    //5TH - show how many tags missed multiple timelines.
