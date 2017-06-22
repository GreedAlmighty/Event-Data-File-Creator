#ifndef FILECOMMANDS_H
#define FILECOMMANDS_H

#include <QString>

class FileCommands
{

public:
    void ReadFile( QString FileName);
    void DeleteFile( QString FileName );
    bool WriteFile( QString FileName, QStringList FileData);

private:
    QString createGroupId( int chipcode_length, QString csv_line );
};

#endif // FILECOMMANDS_H
