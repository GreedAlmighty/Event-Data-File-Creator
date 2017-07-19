#ifndef FILECOMMANDS_H
#define FILECOMMANDS_H

#include <QString>
#include "textedits.h"

class FileCommands
{

public:
    FileCommands();
    ~FileCommands();
    void ReadFile( QString FileName);
    void DeleteFile( QString FileName );
    bool WriteFile( QString FileName, QStringList FileData);

private:
};

#endif // FILECOMMANDS_H
