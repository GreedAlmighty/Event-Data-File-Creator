#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include "databasecommands.h"

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
}

//TODO Create QSqlQueries to read/calculate the data
//TODO Research how to calculate the data with similar Excel functions.
    //1ST - calculate all detected tags and calculate the detection rate for each location
    //2ND - create a list of all tags that were detected.
    //3RD - show on which location the tag has been detected and on which it wasnt.
    //4TH - show how many tags missed only one timeline.
    //5TH - show how many tags missed multiple timelines.
