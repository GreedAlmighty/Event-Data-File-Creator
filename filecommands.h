#ifndef FILECOMMANDS_H
#define FILECOMMANDS_H

#include <QString>

class FileCommands
{

public:
    void ReadFile( QString FileName);
    bool WriteFile( QString FileName, QStringList FileData);

private:
};

#endif // FILECOMMANDS_H
