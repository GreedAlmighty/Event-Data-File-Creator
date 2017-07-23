#ifndef FILECOMMANDS_H
#define FILECOMMANDS_H

#include <QString>
#include <QThread>
#include <QObject>

class FileCommands : public QObject
{
    Q_OBJECT

public:
    FileCommands();
    ~FileCommands();
    void connectFile( QThread &thread);
    void setImportFile( QString selected_file );
    void DeleteFile( QString FileName );
    bool WriteFile( QString FileName, QStringList FileData);

signals:
    void finishedImporting(int);
    void currentImportPos(int);
    void totalFileSize(int);

public slots:
    void ReadFile();
};

#endif // FILECOMMANDS_H
