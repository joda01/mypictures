#ifndef TABLE_MODEL_H_
#define TABLE_MODEL_H_

#include <QAbstractListModel>
#include <QColor>
#include <QDir>
#include <QPixmap>
#include <QThread>
#include <QDebug>

#include "database/database.h"


template <class T> class VPtr
{
public:
    static T* asPtr(QVariant v)
    {
    return  (T *) v.value<void *>();
    }

    static QVariant asQVariant(T* ptr)
    {
    return qVariantFromValue((void *) ptr);
    }
};


class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TableModel(Database *database, QWidget *viewportParetn, QObject *parent = 0);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Database* dataList(){return mDatabase;}
    PicturelistEntry* data(int idx);

private slots:
    void PictureListDataChanged();

private:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QWidget* mViewPortParent;

    /////////////////////////////////////////////////////////////////////
    Database* mDatabase=nullptr;
};






#endif
