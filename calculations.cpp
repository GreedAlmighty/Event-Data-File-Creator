#include "calculations.h"
#include "databasecommands.h"
#include "filecommands.h"
#include <QList>
#include <QString>
#include <QDebug>

QList<QString> location_list;

void calculations::performCalculations( QString save_location )
{
    FileCommands data_file;

    retrieveAllLocations();

    QStringList detection_rate_list = getDetectionRates();
    QStringList detection_path_list = retrieveTagsDetectionPath();

    data_file.WriteFile( save_location + "/detection_rates.csv", detection_rate_list);
    data_file.WriteFile( save_location + "/tags_detected_on_location.csv", detection_path_list);

    qDebug() << "Done Creating Files...";
}

QStringList calculations::retrieveTagsDetectionPath()
{
    DBCommands db_command;
    QStringList data_list;
    QStringList detection_path_list;
    QString detection_string = "GroupID:; Chipcode:; ";
    QString group_id_prev = "";
    QString chipcode_prev = "";
    int location_indicator = 0;
    int data_indicator = 0;
    int list_size = 0;

    foreach (QString str, location_list) {
        detection_string.append( str + "; ");
    }

    data_list = db_command.performListofDetections( "group_id, chipcode, location",
                                                    "group_id, chipcode, location");
    list_size = data_list.size() / 3;


    while(list_size!=0)
    {
        if(group_id_prev==data_list[0+(3*data_indicator)] &&
           chipcode_prev==data_list[1+(3*data_indicator)]){

        }
        else{
            detection_path_list.append(detection_string);
            detection_string.clear();
            location_indicator=0;
            detection_string.append(data_list[0+(3*data_indicator)] + ";" +
                                    data_list[1+(3*data_indicator)] + ";");
            group_id_prev = data_list[0+(3*data_indicator)];
            chipcode_prev = data_list[1+(3*data_indicator)];
        }
        while(data_list[2+(3*data_indicator)]!=location_list[location_indicator]){
            detection_string.append(";");
            location_indicator++;
        }
        detection_string.append("x;");
        location_indicator++;
        data_indicator++;
        list_size--;
    }

    return detection_path_list;
}

QStringList calculations::getDetectionRates()
{
    QString detection_rate_str;
    QStringList detection_rate_list;

    double total_detection = getAllTags();
    detection_rate_list.append("Location;Detection Rate");

    foreach( QString str, location_list)
    {
        double detections_on_location = getAllTagsForLocation( str );
        double detection_rate_for_location = detections_on_location * 100 / total_detection;
        detection_rate_str = detection_rate_str.number( detection_rate_for_location, 'g', 5);
        detection_rate_list.append(str + ";" + detection_rate_str + ";");
    }
    return detection_rate_list;
}

void calculations::retrieveAllLocations()
{
    DBCommands db_command;
    location_list = db_command.retrieveListOfUniqueText("location");
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

//4TH - show how many tags missed only one timeline.
//5TH - show how many tags missed multiple timelines.
