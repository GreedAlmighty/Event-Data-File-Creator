#include "calculations.h"
#include "databasecommands.h"
#include "filecommands.h"
#include <QList>
#include <QString>
#include <QDebug>

QList<QString> location_list;
DBCommands db_command;

void calculations::clearTempFiles()
{
    db_command.deleteDatabase();
}

void calculations::performCalculations( QString save_location )
{
    FileCommands data_file;

    retrieveAllLocations();

    QList<QString> *detection_rate_list = getDetectionRates();
    QList<QString> *detection_path_list = retrieveTagsDetectionPath();

    data_file.WriteFile( save_location + "/detection_rates.csv", (*detection_rate_list));
    data_file.WriteFile( save_location + "/tags_detected_on_location.csv", (*detection_path_list));

    qDebug() << "Done Creating Files...";
}

calculations::calculations()
{

}

calculations::~calculations()
{

}

QList<QString> *calculations::retrieveTagsDetectionPath()
{
    QList<QString> *data_list;
    data_list = new QList<QString>;
    QList<QString> *detection_path_list;
    detection_path_list = new QList<QString>;
    QString detection_string = "GroupID:, Chipcode:, ";
    QString group_id_prev = "";
    QString chipcode_prev = "";
    int location_indicator = 0;
    int data_indicator = 0;
    int list_size = 0;

    foreach (QString str, location_list) {
        detection_string.append( str + ", ");
    }

    data_list = db_command.performListofDetections( master_csv_table,
                                                    "group_id, chipcode, location",
                                                    "group_id, chipcode, location");
    list_size = data_list->size() / 3;


    while(list_size!=0)
    {
        if(group_id_prev==(*data_list)[0+(3*data_indicator)] &&
           chipcode_prev==(*data_list)[1+(3*data_indicator)]){

        }
        else{
            detection_path_list->append(detection_string);
            detection_string.clear();
            location_indicator=0;
            detection_string.append((*data_list)[0+(3*data_indicator)] + "," +
                                    (*data_list)[1+(3*data_indicator)] + ",");
            group_id_prev = (*data_list)[0+(3*data_indicator)];
            chipcode_prev = (*data_list)[1+(3*data_indicator)];
        }
        while((*data_list)[2+(3*data_indicator)]!=location_list[location_indicator]){
            detection_string.append(",");
            location_indicator++;
        }
        detection_string.append("x,");
        location_indicator++;
        data_indicator++;
        list_size--;
    }

    return detection_path_list;
}

QList<QString> *calculations::getDetectionRates()
{
    QString detection_rate_str;
    QString detection_number_str;
    QList<QString> *detection_rate_list;
    detection_rate_list = new QList<QString>;

    double total_detection = getAllTags();
    detection_rate_list->append("Location,Number Detected,Detection Rate");

    foreach( QString str, location_list)
    {
        double detections_on_location = getAllTagsForLocation( str );
        double detection_rate_for_location = detections_on_location * 100 / total_detection;
        detection_rate_str = detection_rate_str.number( detection_rate_for_location, 'g', 5);
        detection_number_str = detection_number_str.number(detections_on_location);
        detection_rate_list->append(str + "," + detection_number_str + "," + detection_rate_str + ",");
    }

    detection_number_str = detection_rate_str.number(total_detection);
    detection_rate_list->append("Total," + detection_number_str + ",100");

    return detection_rate_list;
}

void calculations::retrieveAllLocations()
{
    location_list = (*db_command.retrieveListOfUniqueText(master_csv_table, "location"));
}

int calculations::getAllTags()
{
    return db_command.countAllDistinctValues(master_csv_table, "chipcode");
}

int calculations::getAllTagsForLocation( QString location )
{
    return db_command.countDistinctValuesWithCondition( master_csv_table, "chipcode", "location = '" + location + "'");
}
