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


#include "separator.h"
#include "database/database.h"
#include <QDebug>

///
/// \brief Folder::Folder
/// \param db       Pointer to the picture database
/// \param title    Title of the album
///
Separator::Separator(Database *db):
    PicturelistEntry(db,"","")
{
    mThumbnail = new QPixmap(":icons/folder.png");
}

///
/// \brief Copy constructor
/// \param obj
///
Separator::Separator(const Separator &obj):
    PicturelistEntry(obj)
{

}

///
/// \brief Destructor
///
Separator::~Separator()
{

}

///
/// \brief          Opens an album
/// \param list     List where to save the pictures of the album
///
void Separator::open()
{

}


bool Separator::exsits()
{
    return true;
}


void Separator::rename(QString newPrimaryKey)
{
    Q_UNUSED(newPrimaryKey);
}


void Separator::remove()
{

}


QSize Separator::size(const QSize& parentSize)
{
    Q_UNUSED(parentSize);
    return QSize(WIDTH,HEIGHT);
}

void Separator::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index)
{
    Q_UNUSED(index);

    int imgX = option.rect.x();
    int imgY = option.rect.y();
    QBrush brush(Qt::gray);
    painter->fillRect(imgX, imgY+HEIGHT/2, 250,1,brush);
}
