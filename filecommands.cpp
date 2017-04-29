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
    uint size;

    if(!master_csv.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream in(&master_csv);
    bool first_row = true;

    while(!in.atEnd()){
        QString line = in.readLine();

        if(first_row){
            //First row wont be imported.
            //DB is created with standard headers of master csv file
            first_row = false;
            sql_db.createDatabase();
        }
        else{
            //import values into the created database
            QStringList line_split = line.split(';');

            size = line_split[0].size();
            line = "'" + createGroupId( size, line ) + "'";
            line.replace(";", "', '");
            sql_db.insertIntoDatabase( line );
        }
    }
    sql_db.endTransaction();
    qDebug() << "Done importing file...";
}

QString FileCommands::createGroupId( int chipcode_length, QString csv_line )
{
    if(chipcode_length==6){
        csv_line.insert(0, "0");
    }
    else if(chipcode_length==5){
        csv_line.insert(0,"00");
    }
    else if(chipcode_length==4){
        csv_line.insert(0,"000");
    }
    else if(chipcode_length==3){
        csv_line.insert(0,"0000");
    }
    else if(chipcode_length==2){
        csv_line.insert(0,"00000");
    }
    else {
        csv_line.insert(0,"000000");
    }
    csv_line.insert(2, ";");

    return csv_line;
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

//TODO Research how to create a XLS file using QT.
