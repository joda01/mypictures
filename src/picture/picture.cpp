///
/// \file       picture.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "picture.h"
#include <QDir>
#include <QImageReader>
#include <QGeoCodingManagerEngine>
#include <QGeoCodingManager>
#include "easyexif/exif.h"
#include <QGeoServiceProvider>
#include "geo_locating/geo_locating.h"

Picture::Picture(Database *db, QString title,QString primaryKey, QString path, QString album, QStringList tags):
    PicturelistEntry(db,title,primaryKey),
    mPath(path),
    mAlbum(album),
    mTags(tags)
{

}


Picture::Picture(Database *db, QString title, QString primaryKey, QString path):
    Picture(db,title,primaryKey,path,"",QStringList())
{

}

///
/// \brief Copy constructor
/// \param obj
///
Picture::Picture(const Picture &obj):
    PicturelistEntry(obj)
{
    mDb = obj.mDb;
    mPath = obj.mPath;
    mAlbum = obj.mAlbum;
}


Picture::~Picture()
{

}

///
/// \brief Picture::AddToDatabase
///
bool Picture::AddToDatabase()
{
    return mDb->AddPicture(*this);
}

///
/// \brief Removes picture from database
///
void Picture::remove(){
    mDb->RemovePicture(*this);
}

///
/// \brief Assign an album to the picture
/// \param[in] albumName    Albumname
///
void Picture::SetAlbum(const QString& albumName)
{
    mAlbum=albumName;
    mDb->UpdatePicture(*this);
}

///
/// \brief Add tags to the picture
/// \param tags
///
void Picture::AddTags(const QStringList& tags)
{
    for(auto tag:tags){
        mTags.append(tag);
    }
    mTags.removeDuplicates();
    mDb->AddTags(*this);
}

///
/// \brief Remove tags from the picture
/// \param tags
///
void Picture::RemoveTags(const QStringList& tags)
{
    mDb->RemoveTags(*this,tags);
    for(auto tag:tags){
        mTags.removeAll(tag);
    }
}

///
/// \brief      Removes all old tags and set the new tags
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	tags    List of tags which should be set
///
void Picture::SetTags(const QStringList& tags)
{
    RemoveTags(mTags);
    AddTags(tags);
}

///
/// \brief      Returns false if the picture
///             does not exist.
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
bool Picture::exsits()
{
    return mPath.exists();
}

///
/// \brief Scales the thumbnail to the given size
///        and returns the thumbnail. A thumbnail
///        will be generated if no one is available.
/// \param size Wanted size
/// \return Pointer to the scaled thumbnail
///
QPixmap *Picture::GetThumbnail(int size)
{
    if(false==mPath.exists()){
        return nullptr;
    }

    if(nullptr==mThumbnail){
        LoadAndCreateThumbnail();
    }
    if(nullptr != mThumbnail && mThumbnail->isNull()==false){
        float ratio = (float)mThumbnail->size().width()/(float)mThumbnail->size().height();
        int imgWidth;
        int imgHeight;
        if(ratio < 1){
            imgWidth = size;
            imgHeight = (int)((float)size*(float)ratio);
        }else{
            imgHeight = size;
            imgWidth = (int)((float)size*(float)ratio);
        }
        mThumbnailScaled = mThumbnail->scaled(imgWidth,imgHeight);
        return &mThumbnailScaled;
    }
    return nullptr;
}

///
/// \brief Load the thumbnail of the picture.
///        If no thumbnail is available, a
///        thumbnail of the original picture
///        will be created.
///
void Picture::LoadAndCreateThumbnail(bool overrideExisting)
{
    if(nullptr==mThumbnail){
        // Saves a thumbnail picture
        QString filePathOriginal = mPath.absoluteFilePath();
        QString thumbPath = mPath.absolutePath().append("/");


        QString path(QDir::homePath());
        path.append("/.mypictures/thumbnails/");
        thumbPath.insert(0,path);


        QString thumbFile(thumbPath);
        thumbFile.append(mPath.fileName());
        QDir dir(thumbPath);
        if(false == dir.exists()){
            dir.mkpath(thumbPath);
        }
        QFile file(thumbFile);

        // If thumbnail still exists but should be overridden, remove the old one
        if(true == file.exists() && true == overrideExisting){
            file.remove();
        }

        if(false == file.exists()){
            QImageReader reader(filePathOriginal);
            reader.setFormat("jpg");
            reader.setQuality(2);
            float ratio = (float)reader.size().width()/(float)reader.size().height();
            if(ratio > 1){
                reader.setScaledSize(QSize((int)((float)400*(float)ratio),400));
            }else{
                reader.setScaledSize(QSize(400,(int)((float)400*(float)ratio)));
            }
            QImage image = reader.read();
            if(image.save(thumbFile,"jpg",60)){
                mThumbnail = new QPixmap(QPixmap::fromImage(image));
            }else{
                // Load original picture if thumbnail load faileds
                //qDebug() << "Picture::LoadThumbnail:: Image save error!";
                mThumbnail = new QPixmap(mPath.absoluteFilePath());
            }
        }
        else{
            mThumbnail = new QPixmap(thumbFile);
        }
    }
}

void Picture::rename(QString newPrimaryKey)
{

}

QSize Picture::size(const QSize& parentSize)
{
    int columnCount = (parentSize.width()-10)/mThumbnailSize;
    if(columnCount<1){columnCount=1;}
    int columnSize  = (parentSize.width()-10)/columnCount;

    return QSize(columnSize,columnSize);
}

void Picture::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(index);

    int thumbnailSize = mThumbnailSize;
    int whiteSpace = option.rect.height()-mThumbnailSize;
    int imgWidth = option.rect.width()-whiteSpace;
    int imgHeight = option.rect.height();
    int imgX = option.rect.x()+whiteSpace/2;
    int imgY = option.rect.y()+whiteSpace/2;

    QPixmap* thumbNail = GetThumbnail(thumbnailSize);
    if(thumbNail){
        QImage img = thumbNail->toImage();
        if(false == img.isNull()){
            painter->drawImage(imgX,imgY,img,0,0,imgWidth,imgHeight);
        }
    }
}

///
/// \brief      Read the EXIF data from the picture
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void Picture::readExif()
{
    // Read the JPEG file into a buffer
    FILE *fp = fopen(absoluteFilePath().toStdString().c_str(), "rb");
    if (!fp) {
        // printf("Can't open file.\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        // printf("Can't read file.\n");
        delete[] buf;
        return;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code) {
        // printf("Error parsing EXIF: code %d\n", code);
        return;
    }


    mCameraModel=QString("%1\n%2\n%3").arg(result.Make.c_str()).arg(result.Model.c_str()).arg(result.Software.c_str());
    //QString a=QString("%1\n%2\n%3").arg(result.DateTime.c_str()).arg(result.DateTimeOriginal.c_str()).arg(result.DateTimeDigitized.c_str());
    QString dateTimeTemp = QString(result.DateTime.c_str());
    mDatePhotographing = QDateTime::fromString(dateTimeTemp,"yyyy:MM:dd hh:mm:ss");

    mAperture = QString("f 1 / %1").arg(result.FNumber);
    mExposure = QString("EV 1 / %1 s").arg(1/result.ExposureTime);
    mISO = QString("ISO %1").arg(result.ISOSpeedRatings);

    QGeoCoordinate coordinate;
    coordinate.setAltitude(result.GeoLocation.Altitude);    // height
    coordinate.setLatitude(result.GeoLocation.Latitude);
    coordinate.setLongitude(result.GeoLocation.Longitude);
    mGeoLocation.setCoordinate(coordinate);

    QGeoAddress address;
    //address.setCity("Nussbach");
    //address.setStreet("Bergstrasse 16");

    mGeoLocation.setAddress(address);

    if(result.GeoLocation.Latitude > 0){
        GeoLocating::coordinatesToAddress(coordinate);

    }

    // Dump EXIF information

    // QString a4=QString("Bits per sample      : %1").arg(result.BitsPerSample);
    // QString a5=QString("Image width          : %1").arg(result.ImageWidth);
    // QString a6=QString("Image height         : %1").arg(result.ImageHeight);
    // QString a7=QString("Image description    : %1").arg(result.ImageDescription.c_str());
    // QString a8=QString("Image orientation    : %1").arg(result.Orientation);
    // QString a9=QString("Image copyright      : %1").arg(result.Copyright.c_str());
    //
    // QString a16 = QString("Exposure program     : %1"     ).arg(result.ExposureProgram);
    // QString a17 = QString("ISO speed            : %1"     ).arg(result.ISOSpeedRatings);
    // QString a18 = QString("Subject distance     : %1 m"   ).arg(result.SubjectDistance);
    // QString a19 = QString("Exposure bias        : %1 EV"  ).arg(result.ExposureBiasValue);
    // QString a20 = QString("Flash used?          : %1"     ).arg(result.Flash);
    // QString a21 = QString("Flash returned light : %1"     ).arg(result.FlashReturnedLight);
    // QString a22 = QString("Flash mode           : %1"     ).arg(result.FlashMode);
    // QString a23 = QString("Metering mode        : %1"     ).arg(result.MeteringMode);
    // QString a24 = QString("Lens focal length    : %1 mm"  ).arg(result.FocalLength);
    // QString a25 = QString("35mm focal length    : %1 mm"  ).arg(result.FocalLengthIn35mm);
    //QString a66 = QString("GPS Latitude         : %f deg (%f deg, %f min, %f sec %c)",
    //       result.GeoLocation.Latitude, result.GeoLocation.LatComponents.degrees,
    //       result.GeoLocation.LatComponents.minutes,
    //       result.GeoLocation.LatComponents.seconds,
    //       result.GeoLocation.LatComponents.direction);
    //printf("GPS Longitude        : %f deg (%f deg, %f min, %f sec %c)",
    //       result.GeoLocation.Longitude, result.GeoLocation.LonComponents.degrees,
    //       result.GeoLocation.LonComponents.minutes,
    //       result.GeoLocation.LonComponents.seconds,
    //       result.GeoLocation.LonComponents.direction);
    //printf("GPS Precision (DOP)  : %f\n", result.GeoLocation.DOP);
    //printf("Lens min focal length: %f mm\n", result.LensInfo.FocalLengthMin);
    //printf("Lens max focal length: %f mm\n", result.LensInfo.FocalLengthMax);
    //printf("Lens f-stop min      : f/%.1f\n", result.LensInfo.FStopMin);
    //printf("Lens f-stop max      : f/%.1f\n", result.LensInfo.FStopMax);
    //printf("Lens make            : %s\n", result.LensInfo.Make.c_str());
    //printf("Lens model           : %s\n", result.LensInfo.Model.c_str());
    //printf("Focal plane XRes     : %f\n", result.LensInfo.FocalPlaneXResolution);
    //printf("Focal plane YRes     : %f\n", result.LensInfo.FocalPlaneYResolution);

}


