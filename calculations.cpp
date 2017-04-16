#include "calculations.h"
#include "databasecommands.h"
#include "filecommands.h"
#include <QList>
#include <QMap>
#include <QString>
#include <QDebug>

QList<QString> location_list;

void calculations::performCalculations()
{
    QMap<QString, QString> location_detectionrate;
    QString detection_rate_str;
    double total_detection = getAllTags();
    retrieveAllLocations();
    foreach( QString str, location_list)
    {
        double detections_on_location = getAllTagsForLocation( str );
        double detection_rate_for_location = detections_on_location * 100 / total_detection;
        detection_rate_str = detection_rate_str.number( detection_rate_for_location );
        location_detectionrate.insert( str, detection_rate_str );
        qDebug() << "Calculating...";
    }

    qDebug() << "Finished Calculating...";
    QMapIterator<QString, QString> Iter(location_detectionrate);

    while(Iter.hasNext())
    {
        Iter.next();
        qDebug() << Iter.key() << ";" << Iter.value();
    }

    //Perform calculations to determine detection rate
    //Write calculation to file
}

void calculations::retrieveAllLocations()
{
    DBCommands db_command;
    location_list = db_command.retrieveListOfUniqueText("location");
    qDebug() << location_list;
}

int calculations::getAllTags()
{
    DBCommands db_command;
    return db_command.countAllDistinctValues("chipcode");
}

int calculations::getAllTagsForLocation( QString location )
{
    DBCommands db_command;
    return db_command.countDistinctValuesWithCondition( "chipcode", "location = '" + location + "'");
}

//1ST - calculate all detected tags and calculate the detection rate for each location
//2ND - create a list of all tags that were detected.
//3RD - show on which location the tag has been detected and on which it wasnt.
//4TH - show how many tags missed only one timeline.
//5TH - show how many tags missed multiple timelines.
