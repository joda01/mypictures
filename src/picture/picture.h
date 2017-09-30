///
/// \file       database.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-01
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef PICTURE_H
#define PICTURE_H

#include <QPixmap>
#include <QFileInfo>
#include <QStringList>
#include <QDateTime>
#include <QGeoLocation>
#include <QGeoCoordinate>
#include <QGeoAddress>

#include "picturelistentry.h"
#include "database/database.h"


class Picture : public PicturelistEntry
{
public:
    ///////////////////////////////////////////////////////////
    Picture(Database *db, QString displayText, QString primaryKey, QString path, QString album, QStringList tags);
    Picture(Database *db,QString displayText,QString primaryKey,QString path);
    Picture(const Picture &obj);
    virtual ~Picture();
    virtual QPixmap* GetThumbnail(int size) override;
    void SetAlbum(const QString &albumName);
    void AddTags(const QStringList& tags);
    void RemoveTags(const QStringList& tags);
    void SetTags(const QStringList& tags);
    QString album(){return mAlbum;}
    QStringList tags(){return mTags;}
    QString absoluteFilePath(){return mPath.absoluteFilePath();}
    QString absolutePath(){return mPath.absolutePath();}
    virtual QSize size(const QSize& parentSize) override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    bool AddToDatabase();
    virtual void remove() override;
    virtual bool exsits() override;
    virtual void open() override{}
    virtual void rename(QString newPrimaryKey) override;
    void LoadAndCreateThumbnail(bool overrideExisting=false);
    void readExif();
    QDateTime datePhotographing(){return mDatePhotographing;}
    QString cameraModel(){return mCameraModel;}
    QString aperture(){return mAperture;}
    QString exposure(){return mExposure;}
    QString iso(){return mISO;}
    QGeoLocation geoLocation(){return mGeoLocation;}

private:

    void getCityFromCoordinates();

    ///////////////////////////////////////////////////////////
    QFileInfo   mPath;

    QString     mAlbum;
    QStringList mTags;
    QDateTime   mDatePhotographing;
    QString     mCameraModel;
    QString     mAperture;
    QString     mExposure;
    QString     mISO;
    QGeoLocation mGeoLocation;

    QPixmap     mThumbnailScaled;
};

#endif // PICTURE_H
