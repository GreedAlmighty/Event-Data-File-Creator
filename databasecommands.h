#ifndef DATABASECOMMANDS_H
#define DATABASECOMMANDS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "querycommands.h"

const QString master_csv_table = "master_csv";
const QString master_csv_columns = "group_id uint8_t, "
                                   "chipcode int, "
                                   "time time, "
                                   "file char, "
                                   "device char, "
                                   "location char, "
                                   "chip_type char, "
                                   "opt1 int, "
                                   "opt2 int, "
                                   "opt3 int, "
                                   "opt4 int, "
                                   "opt5 int";

const QString path_table = "path_list";

class DBCommands
{

public:
    DBCommands();
    ~DBCommands();
    void beginTransaction();
    void createTable( QString table_name, QString table_columns);
    void createDatabase();
    void deleteDatabase();
    void insertIntoDatabase(  QString table, QString values );
    void endTransaction();
    int countAllValues(QString table);
    int countAllDistinctValues( QString table, QString column );
    int countDistinctValuesWithCondition( QString table, QString column, QString condition);
    int countValuesWithCondition( QString table, QString column, QString statement );
    QList<QString> *retrieveListOfUniqueText( QString table, QString column );
    QList<QString> *performListofDetections( QString table, QString condition, QString order_by );
    QList<QString> *getListofDistinctTextWithCondition( QString table, QString column, QString condition);
    QList<int> *retrieveListOfUniqueNumbers( QString table, QString column );
};


#endif // DATABASECOMMANDS_H
