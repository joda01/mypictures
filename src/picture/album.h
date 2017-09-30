///
/// \file       album.h
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef ALBUM_H
#define ALBUM_H

#include "picturelistentry.h"

///
/// \brief The Album class
///
class Album : public PicturelistEntry
{
public:
    /////////////////////////////////////////////////////////////
    Album(Database *db,QString displayText,QString primaryKey);
    Album(const Album &obj);
    ~Album();
    virtual void open() override;
    virtual void remove() override;
    virtual QPixmap* GetThumbnail(int size) override{Q_UNUSED(size); return mThumbnail;}
    virtual bool exsits() override{return true;}
    virtual void rename(QString newPrimaryKey) override;
    virtual QSize size(const QSize& parentSize) override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) override;


private:
    /////////////////////////////////////////////////////////////
    static const int HEIGHT = 80;
    static const int WIDTH = 200;
};

#endif // ALBUM_H
