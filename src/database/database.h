///
/// \file   database.h
/// \author Joachim Danmayr
/// \date   2017-07-23
///
/// This program is licensed under the European Union Public
/// License 1.1 - Copyright 2017 by Joachim Danmayr.
/// All rights reserved!
///


#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDir>
#include "sqlite/sqlite3.h"


class PicturelistEntry;

///
/// \brief The database class to organize images
///
class Database  : public QObject
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////
    Database();
    Database(Database& db);
    ~Database();

    void Open();
    void Close();
    void Create();

    void AddTags(PicturelistEntry &picture);
    bool AddPicture(PicturelistEntry &picture);


    void UpdatePicture(PicturelistEntry &picture);

    void SearchPicture(const QString &text);
    void SearchAlbum(const QString &text);
    void SearchTags(const QString &text);
    void openFolder(const QStringList folderPathList);

    void SelectPicturesFromAlbum(const QString &album);
    void SelectPicturesFromTaggroup(const QString &tagname);
    void SelectPicturesFromFolder(const QString &foldername);

    void RemovePicture(PicturelistEntry &picture);
    void RemoveTags(PicturelistEntry &picture, QStringList tagsToRemove);

    PicturelistEntry* at(int idx){return mPictureList.at(idx);}
    int size(){return mPictureList.size();}

    QList<PicturelistEntry*>* data(){return &mPictureList;}
    QStringList SelectTags();
    QStringList SelectAlbums();

signals:
    void dataChanged();

private:
    void ClearList();

    ///////////////////////////////////////////////////////////////////////
    QStringList SelectTagsFromPicture(QString& picturePath);
    static const QString mDatabasePath;
    static QSqlDatabase mDatabase;

    QList<PicturelistEntry*> mPictureList;
    QList<PicturelistEntry*> mPictureListCopy;

};

#endif // DATABASE_H
