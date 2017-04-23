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

bool FileCommands::WriteFile( QString FileName, QStringList FileData)
{
    QFile write_file(FileName);

    if(!write_file.open(QFile::WriteOnly | QFile::Text)){
        return false;
    }

    QTextStream out(&write_file);

    foreach (QString str, FileData) {
        out << str << endl;
    }

    write_file.flush();
    write_file.close();
    return true;
}

//TODO Research how to create a CSV file using QT.
