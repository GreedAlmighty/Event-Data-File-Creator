#ifndef DATABASECOMMANDS_H
#define DATABASECOMMANDS_H

#include <QString>

const QString create_table_query = "create table mastercsv "
                                   "(chipcode int, "
                                   "time datetime, "
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

private:
};


#endif // DATABASECOMMANDS_H
