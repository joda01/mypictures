#include "geo_locating.h"



#include <iostream>
#include <string>

using namespace std;



//QGeoCodingManager * GeoLocating::pQGeoCoder=nullptr;
QGeoCodeReply * GeoLocating::pQGeoCode;
QGeoCoordinate GeoLocating::coordinates;
GeoLocating* GeoLocating::loc=nullptr;

GeoLocating::GeoLocating()
{

}
bool running = false;
QGeoCodingManager * pQGeoCoder=nullptr;
QGeoServiceProvider *qGeoService;

void GeoLocating::coordinatesToAddress(QGeoCoordinate coord)
{
    if(true == running){return;}
    running = true;
    coordinates = coord;
    // check for available services
    QStringList qGeoSrvList = QGeoServiceProvider::availableServiceProviders();
    for (QString entry : qGeoSrvList) {
        // choose provider
        qGeoService = new QGeoServiceProvider(entry);
        pQGeoCoder = qGeoService->geocodingManager();
        if (!pQGeoCoder) {
            // Provider not available
            continue;
        }
        QLocale qLocaleC(QLocale::C, QLocale::AnyCountry);
        pQGeoCoder->setLocale(qLocaleC);

        QGeoShape shape;
        pQGeoCode = pQGeoCoder->reverseGeocode(coordinates,shape);
        if (!pQGeoCode) {
            // "GeoCoding totally failed!";
            return;
        }
        cout << "Searching..." << endl;
        QObject::connect(pQGeoCode,&QGeoCodeReply::finished,locationFound);
        break;
    }



}

void GeoLocating::locationFound()
{
    qDebug() << "Finished...";
    switch (pQGeoCode->error()) {
    case QGeoCodeReply::NoError:
        break;
    default:
        break;
    }
    if (pQGeoCode->error() != QGeoCodeReply::NoError){
        return;
    }
    QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();

    qDebug() << qGeoLocs.size() << " location(s) returned.";
    for (QGeoLocation &qGeoLoc : qGeoLocs) {
        qGeoLoc.setCoordinate(coordinates);
        QGeoCoordinate qGeoCoord = qGeoLoc.coordinate();
        qDebug()
                << "Lat.:  " << qGeoCoord.latitude() << "\n"
                << "Long.: " << qGeoCoord.longitude() << "\n"
                << "Alt.:  " << qGeoCoord.altitude() << "\n"
                << "City: "    << qGeoLoc.address().city() << "\n"
                << "CTR: "    << qGeoLoc.address().country() << "\n"
                << "CTR: "    << qGeoLoc.address().street() << "\n"
                << "CTR: "    << qGeoLoc.address().countryCode() << "\n"
                << "CTR: "    << qGeoLoc.address().district() << "\n";
    }
    qDebug() << "Ended...";

}


/*
void addressToCoordinates(int argc, char *argv[])
{
    cout << "Qt Version: " << QT_VERSION_STR << endl;
    // main application
#undef qApp // undef macro qApp out of the way
    QCoreApplication qApp(argc, argv);
    // check for available services
    QStringList qGeoSrvList
            = QGeoServiceProvider::availableServiceProviders();
    for (QString entry : qGeoSrvList) {
        cout << "Try service: " << entry.toStdString() << endl;
        // choose provider
        QGeoServiceProvider qGeoService(entry);
        QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
        if (!pQGeoCoder) {
            cerr
                    << "GeoCodingManager '" << entry.toStdString()
                    << "' not available!" << endl;
            continue;
        }
        QLocale qLocaleC(QLocale::C, QLocale::AnyCountry);
        pQGeoCoder->setLocale(qLocaleC);
        // build address
        QGeoAddress qGeoAddr;
        //qGeoAddr.setCountry(QString::fromUtf8("Germany"));
        //qGeoAddr.setPostalCode(QString::fromUtf8("88250"));
        //qGeoAddr.setCity(QString::fromUtf8("Weingarten"));
        // qGeoAddr.setStreet(QString::fromUtf8("Heinrich-Hertz-Str. 6"));


        //QGeoCodeReply *pQGeoCode = pQGeoCoder->geocode(qGeoAddr);



        QGeoCoordinate coord(48.224941,16.377885);
        QGeoShape shape;

        QGeoCodeReply *pQGeoCode = pQGeoCoder->reverseGeocode(coord,shape);


        if (!pQGeoCode) {
            cerr << "GeoCoding totally failed!" << endl;
            continue;
        }
        cout << "Searching..." << endl;
        QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
                         [&qApp, &coord, pQGeoCode](){
            cout << "Reply: " << pQGeoCode->errorString().toStdString() << endl;
            switch (pQGeoCode->error()) {
#define CASE(ERROR) \
            case QGeoCodeReply::ERROR: cerr << #ERROR << endl; break
            CASE(NoError);
            CASE(EngineNotSetError);
            CASE(CommunicationError);
            CASE(ParseError);
            CASE(UnsupportedOptionError);
            CASE(CombinationError);
            CASE(UnknownError);
#undef CASE
            default: cerr << "Undocumented error!" << endl;
            }
            if (pQGeoCode->error() != QGeoCodeReply::NoError) return;
            // eval. result
            QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
            cout << qGeoLocs.size() << " location(s) returned." << endl;
            for (QGeoLocation &qGeoLoc : qGeoLocs) {
                //qGeoLoc.setAddress(qGeoAddr);
                qGeoLoc.setCoordinate(coord);
                QGeoCoordinate qGeoCoord = qGeoLoc.coordinate();
                cout
                        << "Lat.:  " << qGeoCoord.latitude() << endl
                        << "Long.: " << qGeoCoord.longitude() << endl
                        << "Alt.:  " << qGeoCoord.altitude() << endl
                        << "City: "    << qGeoLoc.address().city().toStdString() << endl
                        << "CTR: "    << qGeoLoc.address().country().toStdString() << endl
                        << "CTR: "    << qGeoLoc.address().street().toStdString() << endl
                        << "CTR: "    << qGeoLoc.address().countryCode().toStdString() << endl
                        << "CTR: "    << qGeoLoc.address().district().toStdString() << endl;
            }
            qApp.exit(0);
        });
        qApp.exec();
        return;
    }
    return;
}
*/
