#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include "mainwindow.h"
#include "filecommands.h"
#include "textedits.h"

TextEdit text_edit;
QString file_name;

FileCommands::FileCommands()
{

}

FileCommands::~FileCommands()
{
    text_edit.~TextEdit();
}

void FileCommands::connectFile( QThread &thread)
{
    connect(&thread, SIGNAL(started()), this, SLOT(ReadFile()));
}

void FileCommands::setImportFile( QString selected_file )
{
    file_name = selected_file;
}

void FileCommands::ReadFile()
{
    QFile read_file(file_name);

    if(!read_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    emit totalFileSize(read_file.size());
    int i = 0;

    QTextStream in(&read_file);
    while(!in.atEnd()){
        QString line = in.readLine();
        text_edit.editTextLine( line );
        if(i==20000)
        {
            emit currentImportPos(read_file.pos());
            i = 0;
        }
        i++;
    }

    qDebug() << "Done importing file!";

    emit finishedImporting(read_file.size());
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

    qDebug() << FileData.size();

    foreach (QString str, FileData) {
        out << str << endl;
        //emit outputWrittenSize( str.size() );
    }
    write_file.flush();
    write_file.close();
    return true;
}
