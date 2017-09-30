#include "table_model.h"
#include <QSize>
#include <QImageReader>
#include <QPainter>
#include <QIcon>
#include <QWidget>
#include <QApplication>
#include "picture/picturelistentry.h"


TableModel::TableModel(Database* database, QWidget* viewportParetn,QObject *parent) :
    QAbstractListModel(parent),
    mViewPortParent(viewportParetn),
    mDatabase(database)
{
    QPalette p = QApplication::palette();
    connect(mDatabase,SIGNAL(dataChanged()),this,SLOT(PictureListDataChanged()));
}

///
/// \brief Sets the directory from which the files should be shown
/// \param directory
///
void TableModel::PictureListDataChanged()
{
    beginResetModel();
    endResetModel();
}


///
/// \brief TableModel::rowCount
/// \param parent
/// \return
///
int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(nullptr == mDatabase){
        return 0;
    }
    return mDatabase->size();
}

///
/// \brief TableModel::data
/// \param index
/// \param role
/// \return
///
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }

    if(nullptr==mDatabase){
        return QVariant();
    }
    int idx = index.row();
    if (role == Qt::DisplayRole){
        if(idx < mDatabase->size()){
            return VPtr<PicturelistEntry>::asQVariant(mDatabase->at(idx));
        }else{
            return QVariant();
        }
    }
    else if(role ==Qt::DecorationRole){
        return QVariant();
    }
    else if (role == Qt::BackgroundColorRole) {
        return QColor(Qt::green);
    }
    else if(role == Qt::TextColorRole){
        return QVariant();
    }
    else if(role == Qt::SizeHintRole && idx < mDatabase->size()){
        return mDatabase->at(idx)->size(mViewPortParent->size());
    }
    else{
        return QVariant();
    }
}

PicturelistEntry* TableModel::data(int idx)
{
    if(idx < mDatabase->size()){
        return mDatabase->at(idx);
    }else{
        return nullptr;
    }
}

///
/// \brief TableModel::headerData
/// \param section
/// \param orientation
/// \param role
/// \return
///
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Groesse bestimmen
    if(role == Qt::SizeHintRole && orientation == Qt::Horizontal)
    {
        // Groesse
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        switch(section){
        default:
            return QString(tr("."));

        }
    }
    return QVariant();
}


///
/// \brief TableModel::flags
/// \param index
/// \return
///
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    if(nullptr!=mDatabase){
        int idx = index.row();
        if(idx < mDatabase->size()){
            if(false == mDatabase->at(idx)->isEnabled())
                flags &= (~Qt::ItemIsEnabled);

            if(false == mDatabase->at(idx)->isSelectable())
                flags &= (~Qt::ItemIsSelectable);
        }
    }

    flags &= ~Qt::ItemIsEditable;

    return flags;
}

