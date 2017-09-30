///
/// \file       dialog_geo_location.h
/// \author     Joachim Danmayr
/// \date       2017-09-03
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef DIALOG_GEO_LOCATION_H
#define DIALOG_GEO_LOCATION_H

#include <QDialog>
#include <QGeoLocation>
#include <QtWidgets/QVBoxLayout>



class DialogGeoLocation : public QDialog
{
    Q_OBJECT

public:
    DialogGeoLocation();
    QGeoLocation showDialog(QGeoLocation location);

private:



private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    QVBoxLayout *verticalLayout;
    QGeoLocation mLocation;

};

#endif // DIALOG_GEO_LOCATION_H
