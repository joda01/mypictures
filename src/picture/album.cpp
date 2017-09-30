///
/// \file       album.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///


#include "album.h"
#include "database/database.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

///
/// \brief Album::Album
/// \param db       Pointer to the picture database
/// \param title    Title of the album
///
Album::Album(Database *db, QString title, QString primaryKey):
    PicturelistEntry(db,title,primaryKey)
{

}

///
/// \brief Copy constructor
/// \param obj
///
Album::Album(const Album &obj):
    PicturelistEntry(obj)
{

}

///
/// \brief Destructor
///
Album::~Album()
{

}

///
/// \brief          Opens an album
/// \param list     List where to save the pictures of the album
///
void Album::open()
{
    mDb->SelectPicturesFromAlbum(primaryKey());
}


///
/// \brief      Removes the album
/// \author     Joachim Danmayr
/// \date       2017-08-19
///
void Album::remove()
{
    QSqlQuery query;
    query.prepare("UPDATE pictures set album = null WHERE album = :album");
    query.bindValue(":album", primaryKey());
    if(query.exec()){
        //success = true;
    }
    else{
       // qDebug() << "Album::remove:: " << query.lastError();
    }

    emit mDb->dataChanged();
}

///
/// \brief      Renames the album
/// \author     Joachim Danmayr
/// \date       2017-08-19
/// \param[in]	newPrimaryKey   New album name
///
void Album::rename(QString newPrimaryKey)
{
    QSqlQuery query;
    query.prepare("UPDATE pictures set album = :newName WHERE album = :album");
    query.bindValue(":newName",newPrimaryKey);
    query.bindValue(":album", primaryKey());
    if(query.exec()){
       // success = true;
    }
    else{
       // qDebug() << "Album::rename:: " << query.lastError();
    }

    emit mDb->dataChanged();
}

QSize Album::size(const QSize& parentSize)
{
    Q_UNUSED(parentSize);
    return QSize(WIDTH,HEIGHT);
}

void Album::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index)
{
    Q_UNUSED(index);

    int margin = 10;
    int thumbnailSize = mThumbnailSize;
    int imgWidth = option.rect.width();
    int imgHeight = option.rect.height();
    int imgX = option.rect.x();
    int imgY = option.rect.y();

    QPixmap* thumbNail = GetThumbnail(thumbnailSize);
    if(thumbNail){
        QImage img = thumbNail->toImage();
        //painter->drawImage(imgX+margin, imgY+margin,img,0,0, imgWidth-margin,imgHeight-25-margin);
    }
    QBrush brush(QColor::fromRgb(153,255,153));
    painter->fillRect(imgX+margin, imgY+margin, imgWidth-margin*2,imgHeight-30-margin,brush);


    painter->drawText(imgX+5+margin,imgY+imgHeight-5-margin, displayText());
    painter->drawRect(imgX+margin, imgY+margin, imgWidth-margin*2,imgHeight-margin*2);
}
