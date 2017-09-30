///
/// \file       database_worker.h
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef DATABASE_WORKER_H
#define DATABASE_WORKER_H

#include <QFileSystemWatcher>
#include "database/settings.h"
#include <QThread>
#include <QDir>
#include "database.h"

///
/// \class      DatabaseWorker
/// \author     Joachim Danmayr
/// \date       2017-08-17
/// \brief      Thread which does things in the background
///             - Adding images
///             - Hold database clean
///
class DatabaseWorker : public QThread
{
    Q_OBJECT

public:
    DatabaseWorker(Database* database, Settings* settings);
    void startWatchingFiles();
    virtual void run() override;

signals:
    void newPictureAdded(QString path);

public slots:
    void settingsChanged();
    void changesInFileSystem(QString);

private:
    void addImageToDatabase(QFileInfo& file);
    void addImagesToDatabase(QDir directory);
    void lookForNotExistingImages();

    QFileSystemWatcher mDirWatcher;
    Database* mDatabase;
    Settings* mSettings;
};

#endif // DATABASE_WORKER_H
