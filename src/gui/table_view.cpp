///
/// \file       table_view.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "table_view.h"
#include "table_model.h"
#include <QDebug>
#include <QHeaderView>
#include <QPainter>
#include <QColor>
#include <QBrush>
#include "picture/picturelistentry.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
TableView::TableView()
{
    ////////////////////////////////////////////////////////
    // horizontalHeader()->ga
    PictureItemDelegate* delgat = new PictureItemDelegate(this->viewport());

    setItemDelegate(delgat);
    setSelectionMode(SelectionMode::ExtendedSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    setFrameShape(QFrame::NoFrame);
    setMovement(QListView::Snap);
    setFlow(QListView::LeftToRight);
    setProperty("isWrapping", QVariant(true));
    setResizeMode(QListView::Adjust);
    setLayoutMode(QListView::SinglePass);
    setViewMode(QListView::IconMode);
    setModelColumn(0);
}

///
/// \brief      Current index has been changed
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void TableView::currentChanged(const QModelIndex & current, const QModelIndex & previous)
{
    QListView::currentChanged(current,previous);
    emit currentIndexChanged(current);
}

///
/// \brief      Resize event
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	event   Event information
///
void TableView::resizeEvent(QResizeEvent *event)
{
    QListView::resizeEvent(event);
}

///
/// \brief      Sets the thumbnail size
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	size    Size of the thumbnail
///
void TableView::setThumbnailSize(int thumbnailSize)
{
    mThumbnailSize = thumbnailSize;
    resizeEvent(new QResizeEvent(size(),size()));
    emit model()->layoutChanged();
}

///
/// \brief      Select the next element
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[out]	New selected element
///
QModelIndex TableView::selectNextElement()
{
    QModelIndex actIdx = currentIndex();

    int idx = actIdx.row();
    if(idx>=model()->rowCount()){return actIdx;}     // Stop if last element has been reached
    idx++;

    QModelIndex select2 = model()->index(idx,0);
    QAbstractItemView::SelectionMode mode = selectionMode();
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setCurrentIndex(select2);
    setSelectionMode(mode);
    return select2;
}

///
/// \brief      Select the prevoius element
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[out]	New selected element
///
QModelIndex TableView::selectPreviousElement()
{
    QModelIndex actIdx = currentIndex();
    int idx = actIdx.row();
    if(idx==0){return actIdx;}
    idx--;

    QModelIndex select2 = model()->index(idx,0);
    QAbstractItemView::SelectionMode mode = selectionMode();
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setCurrentIndex(select2);
    setSelectionMode(mode);
    return select2;
}



PictureItemDelegate::PictureItemDelegate(QWidget *parent):
    QItemDelegate(parent),
    mParent(parent),
    mPicSelect(":icons/checked_filled_blue_small.png")
{
}

///
/// \brief      Paint method of the item delegate
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
void PictureItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    PicturelistEntry* entry  = VPtr<PicturelistEntry>::asPtr(index.data());
    if(nullptr != entry){

        /////////////////////////////////////////////////////////
        // Draw selection state
        QBrush brush(Qt::white);
        if (option.state & QStyle::State_Selected){
            painter->fillRect(option.rect,brush);
        }

        /////////////////////////////////////////////////////////
        // Draw image
        entry->paint(painter,option,index);

        // Draw focus
        if (option.state & QStyle::State_HasFocus){
            QColor selectionColor(33,155,196);
            QPen pen(selectionColor, 3);
            QBrush brush(selectionColor);
            painter->setPen(pen);
            painter->drawRect(option.rect.x()+5,option.rect.y()+5,option.rect.width()-10,option.rect.height()-10);
        }

        /////////////////////////////////////////////////////////
        // Draw selection state
        if (option.state & QStyle::State_Selected){
            QPen pen(Qt::black, 1);
            QBrush brush(Qt::gray);
            painter->setPen(pen);
            painter->drawPixmap(option.rect.x(),option.rect.y(),32,32, mPicSelect);
        }

    }
}

QSize PictureItemDelegate::sizeHint( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    Q_UNUSED(option);
    PicturelistEntry* entry  = VPtr<PicturelistEntry>::asPtr(index.data());
    if(nullptr != entry){
        return entry->size(mParent->size());
    }
    return QSize(0,0);
}

