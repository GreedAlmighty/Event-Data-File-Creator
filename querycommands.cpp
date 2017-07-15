#include "querycommands.h"
#include <QString>

QueryCommands::QueryCommands()
{
    query_string = "";
}

QueryCommands::~QueryCommands()
{

}

void QueryCommands::addInsertToQuery( QString table, QString values )
{
    query_string.append( "INSERT INTO " + table +
                         " VALUES (" + values + ")");
}

void QueryCommands::clearQueryString()
{
    query_string.clear();
}

void QueryCommands::addDistinctToQuery( QString table, QString column )
{
    query_string.append( "SELECT DISTINCT " + column +
                                    " FROM " + table);
}

void QueryCommands::addOrderByToQuery( QString column )
{
    query_string.append( " ORDER BY " + column);
}

void QueryCommands::addWhereToQuery( QString condition )
{
    query_string.append( " WHERE " + condition );
}

void QueryCommands::addSelectToQuery( QString table, QString column )
{
    query_string.append( "SELECT " + column +
                         " FROM " + table );
}

QString QueryCommands::getQueryString()
{
    return query_string + ";";
}

