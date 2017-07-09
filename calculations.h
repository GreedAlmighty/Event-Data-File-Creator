#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QString>
#include <QStringList>

class calculations
{
public:
    void performCalculations( QString save_location );
    void clearTempFiles();
    calculations();
    ~calculations();

private:
    void retrieveAllLocations();
    int getAllTags();
    int getAllTagsForLocation( QString location );
    QList<QString> *getDetectionRates();
    QList<QString> *retrieveTagsDetectionPath();
};

#endif // CALCULATIONS_H
