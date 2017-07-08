#ifndef FILECOMMANDS_H
#define FILECOMMANDS_H

#include <QString>

class FileCommands
{

public:
    FileCommands();
    ~FileCommands();
    void ReadFile( QString FileName);
    void DeleteFile( QString FileName );
    bool WriteFile( QString FileName, QStringList FileData);

};

#endif // FILECOMMANDS_H
