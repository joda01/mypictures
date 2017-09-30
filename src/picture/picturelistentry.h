///
/// \file       database.cpp
/// \author     Joachim Danmayr
/// \date       2017-07-23
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef PICTURELISTENTRY_H
#define PICTURELISTENTRY_H

#include <QPixmap>
#include <QDebug>
#include "database/database.h"
#include <QStyleOptionViewItem>
#include <QPainter>

///
/// \brief Interface class for a picture
///        entry in the picturelist. This
///        could either be a picture, an
///        album, a collage...
///
class PicturelistEntry
{
public:
    //////////////////////////////////////////////
    PicturelistEntry(Database *db,QString displayText,QString primaryKey):mDb(db),mDisplayText(displayText),mPrimaryKey(primaryKey){}
    PicturelistEntry(const PicturelistEntry &obj){mDisplayText = obj.mDisplayText;if(obj.mThumbnail!=nullptr){mThumbnail=new QPixmap(*obj.mThumbnail);}}
    virtual ~PicturelistEntry(){if(nullptr!=mThumbnail){delete mThumbnail;mThumbnail=nullptr;}}
    virtual QPixmap* GetThumbnail(int size)=0;
    virtual QSize size(const QSize& parentSize)=0;
    void setThumbnailSize(int size){mThumbnailSize=size;}
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    QString displayText(){return mDisplayText;}
    QString primaryKey(){return mPrimaryKey;}
    virtual void open() = 0;
    virtual bool exsits() =0;
    virtual void rename(QString newPrimaryKey) = 0;
    virtual void remove() = 0;
    virtual bool isEnabled(){return true;}
    virtual bool isSelectable(){return true;}

protected:
    void setPrimaryKey(QString text){mPrimaryKey=text;}
    void setDisplayText(QString text){mDisplayText=text;}
    //////////////////////////////////////////////
    QPixmap*    mThumbnail=nullptr;
    Database*   mDb;
    int         mThumbnailSize = 100;

private:
    //////////////////////////////////////////////
    QString     mDisplayText;
    QString     mPrimaryKey;
};


#endif // PICTURELISTENTRY_H
