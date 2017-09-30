///
/// \file       folder.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///


#include "folder.h"
#include "database/database.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

///
/// \brief Folder::Folder
/// \param db       Pointer to the picture database
/// \param title    Title of the album
///
Folder::Folder(Database *db, QString title,QString primaryKey):
    PicturelistEntry(db,title,primaryKey)
{
    mThumbnail = new QPixmap(":icons/folder.png");
}

///
/// \brief Copy constructor
/// \param obj
///
Folder::Folder(const Folder &obj):
    PicturelistEntry(obj)
{

}

///
/// \brief Destructor
///
Folder::~Folder()
{

}

///
/// \brief          Opens an album
/// \param list     List where to save the pictures of the album
///
void Folder::open()
{
    mDb->openFolder(QStringList(primaryKey()));
}


bool Folder::exsits()
{
    QDir dir(primaryKey());
    return dir.exists();
}


void Folder::rename(QString newPrimaryKey)
{
   // bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE pictures set path = :newPath, filepath = REPLACE(filepath, '"+primaryKey()+"', '"+newPrimaryKey+"') WHERE path = :path");
    query.bindValue(":newPath",newPrimaryKey);
    query.bindValue(":path", primaryKey());
    if(query.exec()){
      //  success = true;
    }
    else{
     //   qDebug() << "Folder::rename:: " << query.lastError();
    }

    emit mDb->dataChanged();
}


void Folder::remove()
{
  //  bool success = false;
    QSqlQuery query;
    query.prepare("DELETE FROM pictures WHERE path = :path");
    query.bindValue(":path", primaryKey());
    if(query.exec()){
    //    success = true;
    }
    else{
     //   qDebug() << "Folder::remove:: " << query.lastError();
    }
    emit mDb->dataChanged();
}


QSize Folder::size(const QSize& parentSize)
{
    Q_UNUSED(parentSize);
    return QSize(WIDTH,HEIGHT);
}

void Folder::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index)
{
    Q_UNUSED(index);
    int margin = 10;
    int thumbnailSize = mThumbnailSize;
    int imgWidth = option.rect.width();
    int imgHeight = option.rect.height();
    int imgX = option.rect.x();
    int imgY = option.rect.y();

    QPixmap* thumbNail = GetThumbnail(thumbnailSize);
    //if(thumbNail)
    {
        //QImage img = thumbNail->toImage();
        //painter->drawImage(imgX+margin, imgY+margin,img,0,0, imgWidth-margin,imgHeight-25-margin);
        QBrush brush(QColor::fromRgb(119 ,	136 ,	153 	));
        painter->fillRect(imgX+margin, imgY+margin, imgWidth-margin*2,imgHeight-40-margin,brush);
    }

    // Shrink folder name size to fit to rectangle
    painter->setFont(QFont("Open Sans",12,50,false));
    QString text = displayText();
    int width = painter->fontMetrics().width(text);
    while(width>(imgWidth-margin*2)){
        QFontMetrics fm = painter->fontMetrics();
        width = fm.width(text);
        int middle = text.length()/2-4;
        text.replace(middle,8,".....");
    }
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    painter->drawText(imgX+5+margin,imgY+imgHeight-8-margin,text);
    painter->drawRect(imgX+margin, imgY+margin, imgWidth-margin*2,imgHeight-margin*2);
}
