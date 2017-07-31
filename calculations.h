#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QThread>
#include "databasecommands.h"

class calculations : public QObject
{
    Q_OBJECT

public:
    void setSaveLocation( QString selected_save_location);
    void clearTempFiles();
    void connectCalc(QThread &thread);
    calculations();
    ~calculations();

signals:
    void nowProcessing( QString );
    void finishedCalculating();

public slots:
    void performCalculations();

private:
    void retrieveAllLocations();
    void createPathTable( QStringList lines );
    int getAllTags();
    int getAllTagsForLocation( QString location );
    QList<QString> *getDetectionRates();
    QList<QString> *retrieveTagsDetectionPath();
    QList<QString> *calcLocationSpecifics();
};

#endif // CALCULATIONS_H
