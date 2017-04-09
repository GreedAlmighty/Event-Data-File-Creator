#include "filecommands.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

void FileCommands::ReadFile( QString FileName)
{
    QFile master_csv(FileName);

    if(!master_csv.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream in(&master_csv);

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList sList = line.split(";", QString::SkipEmptyParts);

        //TODO replace foreach loop with SQL insert command
        foreach( QString itm, sList)
        {
            qDebug() << itm;
        }
    }
}

//TODO Create a SQL database to import the CSV data in
//TODO Research how to create a CSV file using QT.
//TODO Research how to create a well structured CSV/Excel file.

