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


#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFileInfo>
#include <QDirIterator>
#include <QSqlError>
#include <typeinfo>
#include "database.h"
#include "picture/picture.h"
#include "picture/album.h"
#include "picture/folder.h"
#include "picture/taggroup.h"
#include "picture/picturelistentry.h"
#include "picture/separator.h"

const QString Database::mDatabasePath = QDir::homePath() + "/.mypictures/mypicturesdb.db";
QSqlDatabase Database::mDatabase;

///
/// \brief Constructor
///
Database::Database()
{

}

Database::~Database()
{
    for(int n=0;n<mPictureList.size();n++){
        delete mPictureList.at(n);
    }
}

///
/// \brief Open the database connection
///
void Database::Open()
{

    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(mDatabasePath);

    if (!mDatabase.open()){
        qDebug() << "Error: connection with database fail";
    }
    else{
        qDebug() << "Database: connection ok";
        Create();
    }
}


void Database::Close()
{

}

///
/// \brief Create database
///
void Database::Create()
{
    QSqlQuery query;

    bool ok = query.exec("CREATE TABLE IF NOT EXISTS pictures (filepath VARCHAR(4096) NOT NULL,path VARCHAR(4096) NOT NULL,title VARCHAR(255),album VARCHAR(255), date VARCHAR(255), time TIME,  country VARCHAR(255),city VARCHAR(255),PRIMARY KEY(filepath));");
    ok |= query.exec("CREATE TABLE IF NOT EXISTS tags( name VARCHAR(255) NOT NULL,PRIMARY KEY(name)); ");
    ok |= query.exec("CREATE TABLE IF NOT EXISTS pictures_has_tags(pictures_filepath VARCHAR(4096) NOT NULL,tags_name VARCHAR(255) NOT NULL,PRIMARY KEY(pictures_filepath, tags_name) FOREIGN KEY(pictures_filepath) REFERENCES pictures(filepath) ON DELETE CASCADE ON UPDATE CASCADE,FOREIGN KEY(tags_name) REFERENCES tags(name) ON DELETE SET NULL ON UPDATE CASCADE);");                                        \


    if(true == ok){
        qDebug() << "Create OK" << query.lastError();
    }else{
        qDebug() << "Create Error" << query.lastError();
    }

}

///
/// \brief Sets the directory from which the files should be shown
/// \param directory
///
//void PictureList::LoadDirectory(QDir directory)
//{
//    ClearList();
//    QStringList namefilter;
//    namefilter <<"*.jpg";
//    QFileInfoList fileList = directory.entryInfoList(namefilter,QDir::Files);
//
//    for(int n=0;n<fileList.size();n++){
//        Picture* newPicture = new Picture(mDatabase,fileList.at(n).baseName(), fileList.at(n).absoluteFilePath());
//        newPicture->AddToDatabase();
//        mPictures.append(newPicture);
//    }
//    emit dataChanged();
//}



///
/// \brief Is loking for pictures with the given keyword
/// \param text[in]         Searchtext
/// \param pictureList[out] Reference to the list where the pictures should be saved
///
void Database::SearchPicture(const QString &text)
{
    ClearList();
    // Select Picture
    {
        QString sqlStatement("SELECT filepath,title,album FROM pictures LEFT JOIN pictures_has_tags on pictures.filepath = pictures_has_tags.pictures_filepath  WHERE UPPER(title) LIKE '%"+text+"%' OR UPPER(album) LIKE '%"+text+"%' OR UPPER(pictures_has_tags.tags_name) LIKE'%"+text+"%' GROUP BY(filepath) ORDER BY title;");
        QSqlQuery query(sqlStatement);
        int fieldNoPath = query.record().indexOf("filepath");
        int fieldNoTitle = query.record().indexOf("title");
        int fieldNoAlbum = query.record().indexOf("album");

        while (query.next()) {
            QString path = query.value(fieldNoPath).toString();
            QString title = query.value(fieldNoTitle).toString();
            QString album = query.value(fieldNoAlbum).toString();
            QStringList tags =SelectTagsFromPicture(path);
            Picture* newPicture = new Picture(this,title,path,path,album,tags);
            mPictureList.append(newPicture);
        }
    }
    emit dataChanged();
}

///
/// \brief      Select all tags from the given picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	picturePath Picture path as primary key
///
QStringList Database::SelectTagsFromPicture(QString& picturePath)
{
    QStringList tags;
    QString sqlStatement("SELECT tags_name FROM pictures_has_tags WHERE pictures_filepath = '"+picturePath+"';");
    QSqlQuery query(sqlStatement);
    int fieldTag = query.record().indexOf("tags_name");

    while (query.next()) {
        QString tagName = query.value(fieldTag).toString();
        tags << tagName;
    }
    return tags;
}

///
/// \brief      Select all Tags from the database
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
QStringList Database::SelectTags()
{
    QStringList tags;
    QString sqlStatement("SELECT * FROM tags;");
    QSqlQuery query(sqlStatement);
    int fieldTag = query.record().indexOf("name");

    while (query.next()) {
        QString tagName = query.value(fieldTag).toString();
        tags << tagName;
    }
    return tags;
}

///
/// \brief      Select all albums from the database
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
QStringList Database::SelectAlbums()
{
    QStringList tags;
    QString sqlStatement("SELECT album FROM pictures WHERE album not null GROUP BY album;");
    QSqlQuery query(sqlStatement);
    int fieldTag = query.record().indexOf("album");

    while (query.next()) {
        QString tagName = query.value(fieldTag).toString();
        tags << tagName;
    }
    return tags;
}

///
/// \brief Is loking for pictures with the given keyword
/// \param text[in]         Album name
/// \param pictureList[out] Reference to the list where the pictures should be saved
///
void Database::SelectPicturesFromAlbum(const QString &album)
{
    ClearList();
    QString sqlStatement("SELECT * FROM pictures WHERE album = '"+album+"' ORDER BY filepath;");
    QSqlQuery query(sqlStatement);
    int fieldNoPath = query.record().indexOf("filepath");
    int fieldNoTitle = query.record().indexOf("title");
    int fieldNoAlbum = query.record().indexOf("album");

    while (query.next()) {
        QString path = query.value(fieldNoPath).toString();
        QString title = query.value(fieldNoTitle).toString();
        QString album = query.value(fieldNoAlbum).toString();
        QStringList tags =SelectTagsFromPicture(path);
        Picture* newPicture = new Picture(this,title,path,path,album,tags);
        mPictureList.append(newPicture);
    }
    emit dataChanged();
}

///
/// \brief Is loking for pictures with the given keyword
/// \param text[in]         Searchtext
/// \param pictureList[out] Reference to the list where the pictures should be saved
///
void Database::SearchAlbum(const QString &text)
{
    ClearList();
    QString sqlStatement("SELECT album,filepath FROM pictures WHERE album not null AND UPPER(album) LIKE '%" +text+"%' GROUP BY album;");
    QSqlQuery query(sqlStatement);
    int fieldNoAlbum = query.record().indexOf("album");
    int fieldNoPath= query.record().indexOf("filepath");

    while (query.next()) {
        QString album = query.value(fieldNoAlbum).toString();
        QString path = query.value(fieldNoPath).toString();
        Album* newPicture = new Album(this,album,album);
        mPictureList.append(newPicture);
    }
    emit dataChanged();
}

///
/// \brief Adds a picture to the database
/// \param picture
///
bool Database::AddPicture(PicturelistEntry &picture)
{
    bool success = false;
    try{
        Picture& p1 = dynamic_cast<Picture&>(picture);
        QSqlQuery query;
        query.prepare("INSERT INTO pictures (filepath,path, title) VALUES (:filepath,:path, :title)");
        query.bindValue(":filepath", p1.absoluteFilePath());
        query.bindValue(":path", p1.absolutePath());
        query.bindValue(":title", p1.displayText());
        if(query.exec()){
            success = true;
        }
        else{
            //qDebug() << "addPerson error:  " << query.lastError();
        }
    }
    catch(std::bad_cast exp){

    }
    return success;
}

///
/// \brief Removes a picture
/// \param picture
///
void Database::RemovePicture(PicturelistEntry &picture)
{
    try{
        Picture& p1 = dynamic_cast<Picture&>(picture);
        QSqlQuery query;
        query.prepare("DELETE FROM pictures WHERE filepath = :filepath");
        query.bindValue(":filepath", p1.absoluteFilePath());
        if(query.exec()){
            //success = true;
        }
        else{
            //qDebug() << "Database::RemovePicture: " << query.lastError();
        }
    }
    catch(std::bad_cast exp){
        //qDebug() << "Database::RemovePictureBasCast: ";
    }

    mPictureList.removeAll(&picture);
    emit dataChanged();
}

///
/// \brief Updates a picture in the database
/// \param picture
///
void Database::UpdatePicture(PicturelistEntry &picture)
{
    try{
        Picture& p1 = dynamic_cast<Picture&>(picture);
        QSqlQuery query;
        query.prepare("UPDATE pictures SET title=:title, album=:album WHERE filepath=:filepath");
        query.bindValue(":title", p1.displayText());
        query.bindValue(":album", p1.album());
        query.bindValue(":filepath", p1.absoluteFilePath());
        if(query.exec()){
           // success = true;
        }
        else{
            //qDebug() << "update error:  " << query.lastError();
        }
    }
    catch(std::bad_cast exp){

    }
}

///
/// \brief      Add tags to the given pictures
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	picture Reference to the pictures which should be tagged
///
void Database::AddTags(PicturelistEntry &picture)
{
    try{
        Picture& p1 = dynamic_cast<Picture&>(picture);
        for(auto tagName:p1.tags()){
            QSqlQuery query;
            //----- Insert tags into the tag table
            query.prepare("INSERT INTO tags (name) VALUES (:name)");
            query.bindValue(":name", tagName);
            query.exec();
            qDebug() << "insert into tags  " << query.lastError();
            //----- Link tag with picture
            query.clear();

            query.prepare("INSERT INTO pictures_has_tags (pictures_filepath,tags_name) VALUES (:filepath, :name);");
            query.bindValue(":filepath", p1.absoluteFilePath());
            query.bindValue(":name", tagName);
            query.exec();
            qDebug() << "uinsert into tag has picture  " << query.lastError();
        }
    }
    catch(std::bad_cast exp){

    }
}

///
/// \brief      Remove tags to the given pictures
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	picture Reference to the pictures which should be tagged
///
void Database::RemoveTags(PicturelistEntry &picture, QStringList tagsToRemove)
{
    try{
        Picture& p1 = dynamic_cast<Picture&>(picture);

        for(auto tagName:tagsToRemove){
            QSqlQuery query;
            query.prepare("DELETE FROM pictures_has_tags WHERE pictures_filepath = :path AND tags_name = :tagName");
            query.bindValue(":path", p1.absoluteFilePath());
            query.bindValue(":tagName", tagName);
            if(query.exec()){
               // success = true;
               // qDebug() << "Database::Removed OK: " << tagName;
            }
            else{
              //  qDebug() << "Database::RemoveTags NOT Ok: " << query.lastError();
            }
        }
    }
    catch(std::bad_cast exp){
        //qDebug() << "Database::RemoveTags::BadCast";
    }
}


///
/// \brief Is loking for pictures with the given keyword
/// \param text[in]         Searchtext
/// \param pictureList[out] Reference to the list where the pictures should be saved
///
void Database::SearchTags(const QString &text)
{
    ClearList();
    QString sqlStatement("SELECT name, COUNT(*) FROM tags JOIN pictures_has_tags on pictures_has_tags.tags_name = tags.name WHERE UPPER(name) LIKE '%" +text+"%' GROUP BY name HAVING count(*) >= 1 ORDER BY name;");
    QSqlQuery query(sqlStatement);
    int fieldNoTagName = query.record().indexOf("name");
    while (query.next()) {
        QString tagName = query.value(fieldNoTagName).toString();
        Taggroup* newPicture = new Taggroup(this,tagName,tagName);
        mPictureList.append(newPicture);
    }
    emit dataChanged();
}


///
/// \brief Is loking for pictures with the given keyword
/// \param text[in]         Album name
/// \param pictureList[out] Reference to the list where the pictures should be saved
///
void Database::SelectPicturesFromTaggroup(const QString &tagname)
{
    ClearList();
    QString sqlStatement("SELECT filepath,title,album FROM pictures JOIN pictures_has_tags on pictures.filepath = pictures_has_tags.pictures_filepath  WHERE pictures_has_tags.tags_name = '"+tagname+"' ORDER BY title;");
    QSqlQuery query(sqlStatement);
    int fieldNoPath = query.record().indexOf("filepath");
    int fieldNoTitle = query.record().indexOf("title");
    int fieldNoAlbum = query.record().indexOf("album");
    while (query.next()) {
        QString path = query.value(fieldNoPath).toString();
        QString title = query.value(fieldNoTitle).toString();
        QString album = query.value(fieldNoAlbum).toString();
        QStringList tags =SelectTagsFromPicture(path);
        Picture* newPicture = new Picture(this,title,path,path,album,tags);
        mPictureList.append(newPicture);
    }
    emit dataChanged();
}

///
/// \brief      Open the folder with the given path
/// \author     Joachim Danmayr
/// \date       2017-08-27
/// \param[in]	folderPath  Path which should be opened
///
void Database::openFolder(const QStringList folderPathList)
{
    ClearList();

    for(auto folderPath:folderPathList){
        if(folderPath.size() <=0){
            continue;
        }

        QDir directory(folderPath);
        QDir directoryParent(folderPath);
        directoryParent.cd("..");

        directory.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
        QStringList qsl; //qsl.append("*.jpg"); // I only want JPG files
        directory.setNameFilters(qsl);
        directory.setSorting(QDir::SortFlag::DirsFirst);
        // Add recursiv,

        QString fullPath = directoryParent.absolutePath();
        Folder* newPicture = new Folder(this,"..",fullPath);
        mPictureList.append(newPicture);

        QFileInfoList list = directory.entryInfoList();
        bool addingDirs = true;
        for(auto info : list) {
            if(info.isDir()){
                QString fullPath = info.absoluteFilePath();
                QString displayText = fullPath.mid(fullPath.lastIndexOf("/")+1,fullPath.length()-fullPath.lastIndexOf("/"));
                Folder* newPicture = new Folder(this,displayText,fullPath);
                mPictureList.append(newPicture);
            }else if(info.absoluteFilePath().endsWith(".jpg",Qt::CaseInsensitive)){
                if(true==addingDirs){
                    addingDirs = false;
                    mPictureList.append(new Separator(this));
                }
                /// \todo Get picture information from database
                QString path = info.absoluteFilePath();
                QString title = info.absoluteFilePath();
                QString album = "";
                QStringList tags;
                Picture* newPicture = new Picture(this,title,path,path,album,tags);
                mPictureList.append(newPicture);
            }
        }
        mPictureList.append(new Separator(this));
    }
    emit dataChanged();
    return;


//    ClearList();
//    QString sqlStatement("SELECT path, COUNT(*) FROM pictures WHERE UPPER(path) LIKE '%" +folderPath+"%' GROUP BY path HAVING count(*) >= 1 ORDER BY path;");
//    QSqlQuery query(sqlStatement);
//    int fieldNoTagName = query.record().indexOf("path");
//    while (query.next()) {
//        QString fullPath = query.value(fieldNoTagName).toString();
//        QString displayText = fullPath.mid(fullPath.lastIndexOf("/")+1,fullPath.length()-fullPath.lastIndexOf("/"));

//        Folder* newPicture = new Folder(this,displayText,fullPath);
//        mPictureList.append(newPicture);
//    }
//    emit dataChanged();
}

void Database::SelectPicturesFromFolder(const QString &foldername)
{
    ClearList();
    QString sqlStatement("SELECT * FROM pictures WHERE path = '"+foldername+"' ORDER BY filepath;");
    qDebug() << sqlStatement;
    QSqlQuery query(sqlStatement);
    int fieldNoPath = query.record().indexOf("filepath");
    int fieldNoTitle = query.record().indexOf("title");
    int fieldNoAlbum = query.record().indexOf("album");
    while (query.next()) {
        QString path = query.value(fieldNoPath).toString();
        QString title = query.value(fieldNoTitle).toString();
        QString album = query.value(fieldNoAlbum).toString();
        QStringList tags =SelectTagsFromPicture(path);
        Picture* newPicture = new Picture(this,title,path,path,album,tags);
        mPictureList.append(newPicture);
    }
    emit dataChanged();
}


void Database::ClearList()
{
    for(int n=0;n<mPictureList.size();n++){
        delete mPictureList.at(n);
    }
    mPictureList.clear();
}
