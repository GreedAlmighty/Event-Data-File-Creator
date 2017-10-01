#include <QString>
#include <QStringList>
#include <QDebug>
#include "textedits.h"
#include "databasecommands.h"

DBCommands sql_db;

TextEdit::~TextEdit()
{

}

TextEdit::TextEdit()
{
    headers = HEADERS;
}

void TextEdit::editTextLine( QString line )
{
    int size;

    if(headers==HEADERS){
        //First row wont be imported.
        //DB is created with standard headers of master csv file
        sql_db.createDatabase();
        sql_db.createTable( master_csv_table, master_csv_columns );
        sql_db.beginTransaction();
        headers = NO_HEADERS;
    }
    else{
        //import values into the created database
        QStringList line_split;
        if(line.contains(";")){
            line_split = line.split(';');
            line.replace(";", "', '");
        }
        else if(line.contains(",")){
            line_split = line.split(",");
            line.replace(",", "', '");
        }
        else{
            qDebug() << "Unknown Delimiter...";
            return;
        }
        size = line_split[0].size();
        createGroupId( size, &line );
        line.append("'");
        line.insert(0, "'");
        sql_db.insertIntoDatabase( master_csv_table, line );
    }
}

void TextEdit::createGroupId( int chipcode_length, QString *csv_line )
{
    if (chipcode_length==7){
        //do nothing
    }
    else if(chipcode_length==6){
        csv_line->insert(0, "0");
    }
    else if(chipcode_length==5){
        csv_line->insert(0,"00");
    }
    else if(chipcode_length==4){
        csv_line->insert(0,"000");
    }
    else if(chipcode_length==3){
        csv_line->insert(0,"0000");
    }
    else if(chipcode_length==2){
        csv_line->insert(0,"00000");
    }
    else {
        csv_line->insert(0,"000000");
    }
    csv_line->insert(2, "', '");
}
