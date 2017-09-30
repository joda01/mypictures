///
/// \file       widget_settings.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>
#include "database/database_worker.h"
#include <QFileDialog>
#include <QLabel>
#include "database/settings.h"

#include "widget_settings.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]  parent  Pointer to the parent class
///
WidgetSettings::WidgetSettings(WidgetTopMenu* widgetTopMenu, Settings* settings,QWidget *parent) : QWidget(parent),
    mWidgetTopMenu(widgetTopMenu),
    mSettings(settings)
{

    ////////////////////////////////////////////////////////
    /// Layout settings
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel(tr("Settings"));
    title->setFont(QFont("Open Sans",20,200,false));
    layout->addWidget(title);


    /// Paths textfield
    mPaths = new QListWidget();
    mPaths->setFrameStyle(0);
    mPaths->setFont(QFont("Open Sans",12,50,false));
    layout->addWidget(mPaths);
    mPaths->addItems(mSettings->value("settings/searchFolder").toStringList());

    /// Button
    QHBoxLayout* buttonBox = new QHBoxLayout();
    QPushButton* add = new QPushButton("Add folder");
    add->setIcon(QIcon(":icons/add.png"));
    connect(add,SIGNAL(pressed()),this,SLOT(slotAddFolderPressed()));
    buttonBox->addWidget(add);

    QPushButton* remove = new QPushButton("Remove folder");
    remove->setIcon(QIcon(":icons/minus.png"));
    connect(remove,SIGNAL(pressed()),this,SLOT(slotRemoveFolderPressed()));
    buttonBox->addWidget(remove);

    layout->addItem(buttonBox);

    setLayout(layout);
}


///
/// \brief      Add a folder to the list
/// \author     Joachim Danmayr
/// \date       2017-09-10
///
void WidgetSettings::slotAddFolderPressed()
{
    QString dirString = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(dirString.length()>0){

        mPaths->addItem(dirString);
        savePathsToSettings();
    }
}

///
/// \brief      Remove selected folder from the list
/// \author     Joachim Danmayr
/// \date       2017-09-10
///
void WidgetSettings::slotRemoveFolderPressed()
{
    for(auto item:mPaths->selectedItems()){
        mPaths->takeItem(mPaths->row(item));
    }
    savePathsToSettings();
}

///
/// \brief      Save the ListWidget entry to the settings file
/// \author     Joachim Danmayr
/// \date       2017-09-10
///
void WidgetSettings::savePathsToSettings()
{
    QStringList items;
    for(int i = 0; i < mPaths->count(); ++i){
        items.append(mPaths->item(i)->data(Qt::DisplayRole).toString());
    }
    mSettings->setValue("settings/searchFolder", items);
    mSettings->sync();
}
