#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include "filecommands.h"
#include "databasecommands.h"

void FileCommands::ReadFile( QString FileName)
{
    QFile master_csv(FileName);
    DBCommands sql_db;

    if(!master_csv.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream in(&master_csv);
    bool first_row = true;

    while(!in.atEnd()){
        QString line = "'" + in.readLine() + "'";

        if(first_row){
            //First row wont be imported.
            //DB is created with standard headers of master csv file
            first_row = false;
            sql_db.createDatabase();
        }
        else{
            //import values into the created database
            line.replace(";", "', '");
            sql_db.insertIntoDatabase( line );
        }
    }
    sql_db.endTransaction();
    qDebug() << "Done importing file...";
    qDebug() << sql_db.retrieveListOfUniqueNumbers( "chipcode" );
}

//TODO Research how to create a CSV file using QT.
//TODO Research how to create a well structured CSV/Excel file.

