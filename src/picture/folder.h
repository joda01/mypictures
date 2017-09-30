///
/// \file       folder.h
/// \author     Joachim Danmayr
/// \date       2017-08-05
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef FOLDER_H
#define FOLDER_H

#include "picturelistentry.h"

///
/// \brief The Album class
///
class Folder : public PicturelistEntry
{   
public:
    /////////////////////////////////////////////////////////////
    Folder(Database *db, QString displayText, QString primaryKey);
    Folder(const Folder &obj);
    ~Folder();
    virtual void open() override;
    virtual QPixmap* GetThumbnail(int size) override{Q_UNUSED(size); return mThumbnail;}
    virtual bool exsits() override;
    virtual void rename(QString newPrimaryKey) override;
    virtual void remove() override;
    virtual QSize size(const QSize& parentSize) override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    virtual bool isSelectable()override{return false;}


private:
    /////////////////////////////////////////////////////////////
    static const int HEIGHT = 90;
    static const int WIDTH = 250;

};

#endif // FOLDER_H
