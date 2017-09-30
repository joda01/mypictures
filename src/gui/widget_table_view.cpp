///
/// \file       widget_table_view.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include <QMessageBox>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QAbstractButton>
#include <QPushButton>

#include "widget_table_view.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]  parent  Pointer to the parent class
///
WidgetTableView::WidgetTableView(Settings* settings, WidgetTopMenu* widgetTopMenu,  WidgetMenuPicture* widgetMenuPic, Database *database, QWidget *parent) : QWidget(parent),
    mWidgetTopMenu(widgetTopMenu),
    mWidgetMenuPicture(widgetMenuPic),
    mSettings(settings),
    mDatabase(database)
{
    ////////////////////////////////////////////////////////
    mTableModel = new TableModel(database,mTableView.viewport());
    mTableView.setModel(mTableModel);

    ////////////////////////////////////////////////////////
    /// Layout settings
    QVBoxLayout* gridLayout = new QVBoxLayout();
    setLayout(gridLayout);

    /// TopMenu
    connect(mWidgetTopMenu,SIGNAL(searchTextChanged(QString)),this,SLOT(startSearch(QString)));
    connect(mWidgetMenuPicture,SIGNAL(nextPicPressed()),this,SLOT(nextPicture()));
    connect(mWidgetMenuPicture,SIGNAL(prevPicPressed()),this,SLOT(prevPicture()));
    connect(mWidgetTopMenu,SIGNAL(buttonBackPressed()),this,SLOT(slotBackButtonPressed()));
    connect(mWidgetTopMenu,SIGNAL(signalViewChanged(WidgetTopMenu::View)),this,SLOT(slotViewChanged(WidgetTopMenu::View)));

    /// Table
    gridLayout->addWidget(&mTableView);
    connect(&mTableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(openSelectedTableElement(QModelIndex)));
    connect(&mTableView,SIGNAL(currentIndexChanged(QModelIndex)),this,SLOT(slotCurrentIndexChanged(QModelIndex)));
    // connect(&mTableView.selectionModel(),SIGNAL)

    /// Slider
    mSlider = new QSlider(Qt::Horizontal,this);
    mSlider->setMinimum(100);
    mSlider->setMaximum(500);
    connect(mSlider,SIGNAL(valueChanged(int)),this,SLOT(setThumbnailSize(int)));
    gridLayout->addWidget(mSlider);

    ////////////////////////////////////////////////////////
    setThumbnailSize(100);
}

///
/// \brief      Is called when slider value has been changed
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	value   New slider value
///
void WidgetTableView::setThumbnailSize(int value)
{
    for( auto elem:*mDatabase->data()){
        elem->setThumbnailSize(value);
    }
    mTableView.setThumbnailSize(value);
}

///
/// \brief      Start a search process
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	text    String to search
///
void WidgetTableView::startSearch(QString text)
{
    mActSearchText = text;

    switch(mActView){
    case WidgetTopMenu::View::Pictures:
        mDatabase->SearchPicture(text);
        break;

    case WidgetTopMenu::View::Albums:
        mDatabase->SearchAlbum(text);
        break;

    case WidgetTopMenu::View::Tags:
        mDatabase->SearchTags(text);
        break;

    case WidgetTopMenu::View::Folders:
        mDatabase->openFolder(mSettings->value("settings/searchFolder").toStringList());
        break;
    }
    setThumbnailSize(mSlider->value());
}

///
/// \brief      Open the selected elements in the table
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	index   Index of the selected element
///
void WidgetTableView::openSelectedTableElement(QModelIndex index)
{
    PicturelistEntry* entry  = VPtr<PicturelistEntry>::asPtr(index.data());
    if(nullptr != entry){
        if(false == entry->exsits()){
            QMessageBox msgBox;
            msgBox.setText(tr("Remove or search?"));
            QAbstractButton* pButtonYes = msgBox.addButton(tr("Search!"), QMessageBox::YesRole);
            msgBox.addButton(tr("Remove"), QMessageBox::NoRole);

            msgBox.exec();
            if (msgBox.clickedButton()==pButtonYes) {
                QString dirString = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
                entry->rename(dirString);
            }
            else{
                entry->remove();
            }
        }
        else{
            Picture*pic = dynamic_cast<Picture*>(entry);
            if(pic){
              //  mTableView.selectionModel()->clearSelection();
                signalOpenNewPicture((Picture&)*entry);
            }
            else{

                entry->open();
                setThumbnailSize(mSlider->value());
            }

        }
    }
}

///
/// \brief      Returns the selected elements
/// \author     Joachim Danmayr
/// \date       2017-08-19
///
QModelIndexList WidgetTableView::selectedElements()
{
    return mTableView.selectionModel()->selectedIndexes();
}

///
/// \brief      Loads the next picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WidgetTableView::nextPicture()
{
    openSelectedTableElement(mTableView.selectNextElement());
}

///
/// \brief      Loads the previous picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WidgetTableView::prevPicture()
{
    openSelectedTableElement(mTableView.selectPreviousElement());
}

///
/// \brief      Current index in table has changed
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	index Current index
///
void WidgetTableView::slotCurrentIndexChanged(QModelIndex index)
{
    Picture* entry  = dynamic_cast<Picture*>(VPtr<PicturelistEntry>::asPtr(index.data()));
    if(nullptr != entry){
        emit signalPictureSelected((Picture&)*entry);
    }
}

///
/// \brief      Adds tags to the selected elements
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	tags    List with tags
///
void WidgetTableView::slotSetTagsToSelectedelements(QStringList tags)
{
    QModelIndexList selectedList = mTableView.selectionModel()->selectedIndexes();
    for(auto idx:selectedList){
        Picture* entry  = dynamic_cast<Picture*>(VPtr<PicturelistEntry>::asPtr(idx.data()));
        if(nullptr != entry){
            ((Picture&)*entry).SetTags(tags);
        }
    }
}

///
/// \brief      Back button has been pressed
/// \author     Joachim Danmayr
/// \date       2017-08-19
///
void WidgetTableView::slotBackButtonPressed()
{

}

void WidgetTableView::slotViewChanged(WidgetTopMenu::View view)
{
    mActView = view;
    startSearch(mActSearchText);
}
