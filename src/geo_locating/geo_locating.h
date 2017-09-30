#ifndef GEO_LOCATING_H
#define GEO_LOCATING_H

#include <QThread>

#include <QGeoCoordinate>
#include <QApplication>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QDebug>

#include <QGeoLocation>
#include <QGeoServiceProvider>

class GeoLocating
{

public:
    GeoLocating();

    static void coordinatesToAddress(QGeoCoordinate coord);

public slots:
    static void locationFound();

private:


    //static QGeoCodingManager *pQGeoCoder;
    static QGeoCodeReply *pQGeoCode;
    static QGeoCoordinate coordinates;
    static GeoLocating*loc;



};

#endif // GEO_LOCATING_H
