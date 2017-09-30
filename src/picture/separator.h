///
/// \file       separator.h
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef SEPARATOR_H
#define SEPARATOR_H

#include "picturelistentry.h"

///
/// \brief The Album class
///
class Separator : public PicturelistEntry
{   
public:
    /////////////////////////////////////////////////////////////
    Separator(Database *db);
    Separator(const Separator &obj);
    ~Separator();
    virtual void open() override;
    virtual QPixmap* GetThumbnail(int size) override{Q_UNUSED(size); return mThumbnail;}
    virtual bool exsits() override;
    virtual void rename(QString newPrimaryKey) override;
    virtual void remove() override;
    virtual QSize size(const QSize& parentSize) override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    virtual bool isEnabled()override{return false;}
    virtual bool isSelectable()override{return false;}


private:
    /////////////////////////////////////////////////////////////
    static const int HEIGHT = 10;
    static const int WIDTH = 99999999;

};

#endif // SEPARATOR_H
