#ifndef FILECOMMANDS_H
#define FILECOMMANDS_H

#include <QString>
#include <QThread>
#include <QObject>
#include "textedits.h"

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

public slots:
    void ReadFile();

private:
};

#endif // FILECOMMANDS_H
