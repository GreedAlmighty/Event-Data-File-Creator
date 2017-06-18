#ifndef DATABASECOMMANDS_H
#define DATABASECOMMANDS_H

#include <QString>
#include <QList>

const QString create_table_query = "create table mastercsv "
                                   "(group_id uint8_t, "
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
                                   "opt5 int)";

class DBCommands
{

public:
    void createDatabase();
    void insertIntoDatabase( QString values );
    void endTransaction();
    int countAllValues();
    int countAllDistinctValues( QString column );
    int countDistinctValuesWithCondition( QString column, QString condition);
    int countValuesWithCondition( QString column, QString statement );
    QList<QString> retrieveListOfUniqueText( QString column );
    QList<QString> performListofDetections( QString condition, QString order_by );
    QList<QString> getListofDistinctTextWithCondition( QString column, QString condition);
    QList<int> retrieveListOfUniqueNumbers( QString column );

private:
};


#endif // DATABASECOMMANDS_H
