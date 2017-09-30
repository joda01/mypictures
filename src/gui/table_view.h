///
/// \file       table_view.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QListView>
#include <QResizeEvent>
#include <QItemDelegate>

///
/// \class      TableView
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      Table view
///
class TableView : public QListView
{
    Q_OBJECT

public:
    TableView();
    void setThumbnailSize(int thumbnailSize);
    QModelIndex selectNextElement();
    QModelIndex selectPreviousElement();

signals:
    void currentIndexChanged(QModelIndex current);

private:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void currentChanged(const QModelIndex & current, const QModelIndex & previous) override;
    int mThumbnailSize=100;
};

class PictureItemDelegate : public QItemDelegate{

public:
    explicit PictureItemDelegate(QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const override;
    QSize sizeHint( const QStyleOptionViewItem & option, const QModelIndex & index ) const override;

private:
    const QWidget* mParent;
    const QPixmap mPicSelect;

};


#endif // TABLE_VIEW_H
