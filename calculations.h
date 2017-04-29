#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QString>
#include <QStringList>

class calculations
{
public:
    void performCalculations( QString save_location );

private:
    void retrieveAllLocations();
    int getAllTags();
    int getAllTagsForLocation( QString location );
    QStringList getDetectionRates();
    QStringList retrieveTagsDetectionPath();
};

#endif // CALCULATIONS_H
