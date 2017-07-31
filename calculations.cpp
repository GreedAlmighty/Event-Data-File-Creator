#include "calculations.h"
#include "databasecommands.h"
#include "filecommands.h"
#include <QList>
#include <QString>
#include <QDebug>

QList<QString> location_list;
DBCommands db_command;
QString save_location;

void calculations::connectCalc(QThread &thread)
{
    connect(&thread, SIGNAL(started()),this,SLOT(performCalculations()));
}

void calculations::clearTempFiles()
{
    db_command.deleteDatabase();
}

void calculations::performCalculations()
{
    FileCommands data_file;

    qDebug() << "Start receiving data";
    emit nowProcessing( "calculating data" );

    retrieveAllLocations();
    qDebug() << "Start Calculating Detection Rates";
    QList<QString> *detection_rate_list = getDetectionRates();
    qDebug() << "Start Calculating Detection Location per Chip";
    QList<QString> *detection_path_list = retrieveTagsDetectionPath();
    qDebug() << "Start Calculating Missed Detection On One Location Only";
    createPathTable((*detection_path_list));
    QList<QString> *location_numbers = calcLocationSpecifics();
    qDebug() << "Done calculating everything";
    emit nowProcessing( "done calculating, Writing data to files");

    data_file.WriteFile( save_location + "/detection_rates.csv", (*detection_rate_list));
    qDebug() << "Detection Rates calculated and written";
    data_file.WriteFile( save_location + "/tags_detected_on_location.csv", (*detection_path_list));
    qDebug() << "Detection Location per Chip calculated and written";
    data_file.WriteFile( save_location + "/tags_missed_only_on_location.csv", (*location_numbers));
    qDebug() << "Missed Detection On One Location Only calculated and written";

    emit nowProcessing( "Finished Writing and Calculating Files");
    emit finishedCalculating();
    qDebug() << "Done Creating Files...";
}

calculations::calculations()
{

}

calculations::~calculations()
{

}

void calculations::setSaveLocation( QString selected_save_location)
{
    save_location = selected_save_location;
}

void calculations::createPathTable(QStringList lines)
{
    QString str, column_headers;
    bool first_line = true;

    foreach( str, lines){
        if(first_line){
            first_line = false;
            str.replace(" ", "_");
            str.replace("(", "");
            str.replace(")", "");
            str.replace(",_", " char DEFAULT NULL, ");
            column_headers = str;
            column_headers.resize( column_headers.size()-2);
            db_command.createTable(path_table, column_headers);
            db_command.beginTransaction();
        }
        else{
            str.prepend("'");
            str.replace(",", "', '");
            str.resize( str.size()-3);
            db_command.insertIntoDatabase(path_table, str);
        }
    }
    db_command.endTransaction();
}

QList<QString> *calculations::calcLocationSpecifics()
{
    QString qry;
    QString calc_location;
    QString condition_query;
    QString number;
    QList<QString> *data_list;
    data_list = new QList<QString>;

    data_list->append( "Location,Number of Tags that only missed specified location," );

    foreach (calc_location, location_list) {
        calc_location = calc_location.replace(" ", "_");
        calc_location.replace(" ", "_");
        calc_location.replace("(", "");
        calc_location.replace(")", "");
        condition_query = calc_location + "=\"\"";
        foreach(qry, location_list){
            qry.replace(" ", "_");
            qry.replace("(", "");
            qry.replace(")", "");
            if(qry!=calc_location){
                condition_query.append(" AND " + qry + "=\"x\"");
            }
        }
        number = number.number( db_command.countDistinctValuesWithCondition(path_table, "Chipcode", condition_query ) );
        data_list->append( calc_location + "," + number +",");
    }
    return data_list;
}

QList<QString> *calculations::retrieveTagsDetectionPath()
{
    QList<QString> *data_list;
    data_list = new QList<QString>;
    QList<QString> *detection_path_list;
    detection_path_list = new QList<QString>;
    QString detection_string = "GroupID, Chipcode, ";
    QString group_id_prev = "";
    QString chipcode_prev = "";
    int location_indicator = 0;
    int data_indicator = 0;
    int list_size = 0;
    int location_compensator = 0;

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
            while(location_compensator!=0){
                detection_string.append(",");
                location_compensator--;
            }
            location_indicator=0;
            location_compensator = location_list.size();
            detection_path_list->append(detection_string);
            detection_string.clear();
            detection_string.append((*data_list)[0+(3*data_indicator)] + "," +
                                    (*data_list)[1+(3*data_indicator)] + ",");
            group_id_prev = (*data_list)[0+(3*data_indicator)];
            chipcode_prev = (*data_list)[1+(3*data_indicator)];
        }
        while((*data_list)[2+(3*data_indicator)]!=location_list[location_indicator]){
            detection_string.append(",");
            location_indicator++;
            location_compensator--;
        }
        detection_string.append("x,");
        location_indicator++;
        location_compensator--;
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
