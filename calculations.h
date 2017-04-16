#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QString>

class calculations
{
public:
    void performCalculations();

private:
    void retrieveAllLocations();
    int getAllTags();
    int getAllTagsForLocation( QString location );
};

#endif // CALCULATIONS_H
