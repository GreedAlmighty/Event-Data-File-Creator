#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include "filecommands.h"
#include "textedits.h"

TextEdit text_edit;

FileCommands::FileCommands()
{

}

FileCommands::~FileCommands()
{
    text_edit.~TextEdit();
}

void FileCommands::ReadFile( QString FileName )
{
    QFile read_file(FileName);

    if(!read_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream in(&read_file);

    while(!in.atEnd()){
        QString line = in.readLine();
        text_edit.editTextLine( line );
    }
    qDebug() << "Done importing file...";
}

void FileCommands::DeleteFile( QString FileName )
{
    QFile remove_file(FileName);

    if(remove_file.remove()){
        qDebug() << "Removed File: " + FileName;
    }
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
