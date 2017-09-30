///
/// \file       database_worker.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include <QDebug>
#include <QDirIterator>

#include "database_worker.h"
#include "picture/picture.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
DatabaseWorker::DatabaseWorker(Database *database,Settings* settings):
    mDatabase(database),
    mSettings(settings)
{
    connect(settings,SIGNAL(settingsChanged()),this,SLOT(settingsChanged()));
    connect(&mDirWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(changesInFileSystem(QString)));
    connect(&mDirWatcher,SIGNAL(fileChanged(QString)),this,SLOT(changesInFileSystem(QString)));

    mDirWatcher.addPaths(mSettings->value("settings/searchFolder").toStringList());
}

///
/// \brief      Start doing his work
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
void DatabaseWorker::startWatchingFiles()
{
    start();
}

///
/// \brief      Thread routine
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
void DatabaseWorker::run()
{
    for(auto folder:mDirWatcher.directories()){
        addImagesToDatabase(QDir(folder));
    }
}

///
/// \brief      Add images from the selected folder
///             to the database.
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
void DatabaseWorker::addImagesToDatabase(QDir directory)
{
    directory.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    QStringList qsl; qsl.append("*.jpg"); // I only want JPG files
    directory.setNameFilters(qsl);
    qDebug() <<"Root:" << directory;
    // Add recursiv
    QDirIterator it(directory, QDirIterator::Subdirectories);
    while(it.hasNext()) {
        it.next();
        QFileInfo info = it.fileInfo();
        addImageToDatabase(info);
    }
}

///
/// \brief      Add image to database
/// \author     Joachim Danmayr
/// \date       2017-08-18
/// \param[in]	file    File which should be added
///
void DatabaseWorker::addImageToDatabase(QFileInfo& file)
{
    Picture* newPicture = new Picture(mDatabase,file.baseName(), file.filePath(),file.filePath());
    if(newPicture->AddToDatabase()){
        newPictureAdded(file.baseName());
        newPicture->LoadAndCreateThumbnail(false);
        qDebug() <<"Added:" << file.baseName()<< "   " << file.filePath();
    }
}

///
/// \brief      Is called when settings have been changed
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
void DatabaseWorker::settingsChanged()
{
    mDirWatcher.addPaths(mSettings->value("settings/searchFolder").toStringList());
    startWatchingFiles();
}

///
/// \brief      Is called if there were changs in the filesystem
/// \author     Joachim Danmayr
/// \date       2017-08-17
/// \param[in]	file    File which has been changed
///
void DatabaseWorker::changesInFileSystem(QString file)
{
    startWatchingFiles();
}
