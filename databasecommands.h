#ifndef DATABASECOMMANDS_H
#define DATABASECOMMANDS_H

#include <QString>
#include <QList>

const QString create_table_query = "create table mastercsv "
                                   "(chipcode int, "
                                   "time time, "
                                   "file char, "
                                   "device char, "
                                   "location char, "
                                   "chip_type char, "
                                   "opt1 int, "
                                   "opt2 int, "
                                   "opt3 int, "
                                   "opt4 int, "
                                   "opt5 int)";

class DBCommands
{

public:
    void createDatabase();
    void insertIntoDatabase( QString values );
    void endTransaction();
    QList<QString> retrieveListOfUniqueText( QString column );
    QList<int> retrieveListOfUniqueNumbers( QString column );

private:
};


#endif // DATABASECOMMANDS_H
