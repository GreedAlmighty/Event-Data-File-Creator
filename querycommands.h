#ifndef QUERYCOMMANDS_H
#define QUERYCOMMANDS_H

#include <QString>

class QueryCommands
{
public:
    QueryCommands();
    ~QueryCommands();
    void addInsertToQuery( QString table, QString values );
    void clearQueryString();
    void addDistinctToQuery( QString table, QString column );
    void addOrderByToQuery( QString column );
    void addWhereToQuery( QString condition );
    void addSelectToQuery( QString table, QString column );

    QString getQueryString();

private:
    QString query_string;
};

#endif // QUERYCOMMANDS_H
