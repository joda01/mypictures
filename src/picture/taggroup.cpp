///
/// \file       Taggroup.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///


#include "taggroup.h"
#include "database/database.h"
#include <QDebug>

///
/// \brief Taggroup::Taggroup
/// \param db       Pointer to the picture database
/// \param title    Title of the Taggroup
///
Taggroup::Taggroup(Database *db, QString title,QString primaryKey):
    PicturelistEntry(db,title,primaryKey)
{

}

///
/// \brief Copy constructor
/// \param obj
///
Taggroup::Taggroup(const Taggroup &obj):
    PicturelistEntry(obj)
{

}

///
/// \brief Destructor
///
Taggroup::~Taggroup()
{

}

///
/// \brief          Opens an Taggroup
/// \param list     List where to save the pictures of the Taggroup
///
void Taggroup::open()
{
    mDb->SelectPicturesFromTaggroup(primaryKey());
}


///
/// \brief Removes this Taggroup
///
void Taggroup::remove()
{
    //mDb->RemoveTags(*this);
}

void Taggroup::rename(QString newPrimaryKey)
{

}

QSize Taggroup::size(const QSize& parentSize)
{
    Q_UNUSED(parentSize);
    return QSize(WIDTH,HEIGHT);
}

void Taggroup::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index)
{
    Q_UNUSED(index);
    int margin = 10;
    int imgWidth = option.rect.width();
    int imgHeight = option.rect.height();
    int imgX = option.rect.x();
    int imgY = option.rect.y();

   // QPixmap* thumbNail = GetThumbnail(thumbnailSize);
   // if(thumbNail){
      //  QImage img = thumbNail->toImage();
        //painter->drawImage(imgX+margin, imgY+margin,img,0,0, imgWidth-margin,imgHeight-25-margin);
        QBrush brush(QColor::fromRgb(204,229,255));
        painter->fillRect(imgX+margin, imgY+margin, imgWidth-margin*2,imgHeight-30-margin,brush);
  //  }
    painter->drawText(imgX+5+margin,imgY+imgHeight-5-margin, displayText());
    painter->drawRect(imgX+margin, imgY+margin, imgWidth-margin*2,imgHeight-margin*2);
}
