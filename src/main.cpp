#include "gui/windowmain.h"
#include <QApplication>
#include "database/settings.h"


#include "database/database.h"
#include "database/database_worker.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QPalette p = QApplication::palette();
    p.setColor( QPalette::Background, Qt::white );
    p.setColor( QPalette::Base, Qt::white );
    p.setColor( QPalette::Light, Qt::white );
    p.setColor( QPalette::Midlight, Qt::white );
    p.setColor( QPalette::Dark, Qt::white );
    p.setColor( QPalette::Mid, Qt::white );
    p.setColor( QPalette::Shadow, Qt::white );
    p.setColor( QPalette::AlternateBase, Qt::white );
    p.setColor( QPalette::Window, Qt::white );
    p.setColor( QPalette::Shadow, Qt::white );



    QApplication::setPalette( p );

    // Load an application style
    QFile styleFile( ":/style.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    a.setStyleSheet(style);

    QString path(QDir::homePath());
    path.append("/.mypictures/my_pictures.ini");

    Settings settings(path, Settings::IniFormat);
    Database database;database.Open();
    DatabaseWorker databaseWorker(&database,&settings);databaseWorker.startWatchingFiles();

    WindowMain w(&settings,&database,&databaseWorker);
    w.show();
    a.exec();
    database.Close();
    return 0;
}
