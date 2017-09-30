///
/// \file       widget_top_menu.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "widget_top_menu.h"

#include <QHBoxLayout>
#include <QToolButton>

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	parent  Pointer to the parent widget
///
WidgetTopMenu::WidgetTopMenu(QWidget *parent) : QWidget(parent)
{
    setObjectName("WidgetTopMenu");
    ////////////////////////////////////////////////////////
    /// Layout settings
    QHBoxLayout* layout = new QHBoxLayout();
    setLayout(layout);

    /// Buttons on the left side
    buttonBack = new QToolButton();
    buttonBack->setIcon(QIcon(":icons/long_arrow_left_filled.png"));
    buttonBack->setCursor(Qt::PointingHandCursor);
    connect(buttonBack,SIGNAL(pressed()),this,SLOT(slotButtonBackPressed()));
    layout->addWidget(buttonBack);

    // Menu to select what should be shown (Pictures, Albums, Folder...)
    layout->addWidget(createRadioButtons());

    layout->addStretch(0);

    /// Searchtext
    mTextSearch = new QLineEdit(this);
    mTextSearch->setObjectName("TextSearch");
    mTextSearch->setPlaceholderText(tr("Search..."));
    connect(mTextSearch,SIGNAL(editingFinished()) ,this,SLOT(slotTextEditFinished()));
    layout->addWidget(mTextSearch);

    /// Buttons on the right side


    pictureInfo = new QToolButton();
    QIcon icon2;
    icon2.addFile(QStringLiteral(":icons/menu_2.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon2.addFile(QStringLiteral(":icons/menu_2_filled.png"), QSize(), QIcon::Active, QIcon::On);
    pictureInfo->setIcon(icon2);
    pictureInfo->setCursor(Qt::PointingHandCursor);
    pictureInfo->setCheckable(true);
    connect(pictureInfo,SIGNAL(toggled(bool)),this,SLOT(slotPictureInfo(bool)));
    layout->addWidget(pictureInfo);


    buttonSettings = new QToolButton();

    buttonSettings->setIcon(QIcon(":icons/settings.png"));
    buttonSettings->setCursor(Qt::PointingHandCursor);
    connect(buttonSettings,SIGNAL(pressed()),this,SLOT(slotButtonSettingsPressed()));
    layout->addWidget(buttonSettings);

    setMinimumHeight(60);

}

QWidget *WidgetTopMenu::createRadioButtons()
{

    mWidgetButtonsView = new QWidget();

    QToolButton *buttonPictures = new QToolButton();
    buttonPictures->setText(tr("&Pictures"));
    buttonPictures->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":icons/picture.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon1.addFile(QStringLiteral(":icons/picture_blue.png"), QSize(), QIcon::Active, QIcon::On);
    buttonPictures->setIcon(icon1);
    buttonPictures->setCheckable(true);
    buttonPictures->setAutoExclusive(true);

    QToolButton *buttonAlbums = new QToolButton();
    buttonAlbums->setText(tr("&Albums"));
    buttonAlbums->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QIcon icon2;
    icon2.addFile(QStringLiteral(":icons/stack_of_photos.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon2.addFile(QStringLiteral(":icons/stack_of_photos_blue.png"), QSize(), QIcon::Active, QIcon::On);
    buttonAlbums->setIcon(icon2);
    buttonAlbums->setCheckable(true);
    buttonAlbums->setAutoExclusive(true);

    QToolButton *buttonTags = new QToolButton();
    buttonTags->setText(tr("&Tags"));
    buttonTags->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QIcon icon3;
    icon3.addFile(QStringLiteral(":icons/tags.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon3.addFile(QStringLiteral(":icons/tags_blue.png"), QSize(), QIcon::Active, QIcon::On);
    buttonTags->setIcon(icon3);
    buttonTags->setCheckable(true);
    buttonTags->setAutoExclusive(true);


    QToolButton *buttonFolder = new QToolButton();
    buttonFolder->setText(tr("&Folder"));
    buttonFolder->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QIcon icon4;
    icon4.addFile(QStringLiteral(":icons/pictures_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon4.addFile(QStringLiteral(":icons/pictures_folder_blue.png"), QSize(), QIcon::Active, QIcon::On);
    buttonFolder->setIcon(icon4);
    buttonFolder->setCheckable(true);
    buttonFolder->setAutoExclusive(true);

    connect(buttonPictures,SIGNAL(pressed()),this,SLOT(slotButtonShowPictures()));
    connect(buttonAlbums,SIGNAL(pressed()),this,SLOT(slotButtonshowAlbums()));
    connect(buttonTags,SIGNAL(pressed()),this,SLOT(slotButtonShowTags()));
    connect(buttonFolder,SIGNAL(pressed()),this,SLOT(slotButtonShowFolder()));


    buttonPictures->setChecked(true);

    QHBoxLayout *vbox = new QHBoxLayout;

    vbox->addWidget(buttonPictures);
    vbox->addWidget(buttonAlbums);
    vbox->addWidget(buttonTags);
    vbox->addWidget(buttonFolder);
    vbox->addStretch(1);

    mWidgetButtonsView->setLayout(vbox);
    return mWidgetButtonsView;
}

void WidgetTopMenu::setBlackStyle(bool bigPictureMenu)
{
    if(true == bigPictureMenu){
        setViewButtonsVisible(false);

        setAutoFillBackground(true);

        buttonBack->setIcon(QIcon(":icons/long_arrow_left_filled_white.png"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":icons/menu_2_white.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":icons/menu_2_filled_white.png"), QSize(), QIcon::Active, QIcon::On);
        pictureInfo->setIcon(icon2);

    }else{
        buttonBack->setIcon(QIcon(":icons/long_arrow_left_filled.png"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":icons/menu_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":icons/menu_2_filled.png"), QSize(), QIcon::Active, QIcon::On);
        pictureInfo->setIcon(icon2);


        setViewButtonsVisible(true);
    }
}

///
/// \brief      Make view buttons visible or not
/// \author     Joachim Danmayr
/// \date       2017-09-10
/// \param[in]	visble  true to show view buttons else false
///
void WidgetTopMenu::setViewButtonsVisible(bool visble)
{
    buttonBack->setVisible(!visble);
    mTextSearch->setVisible(visble);
    buttonSettings->setVisible(visble);
    mWidgetButtonsView->setVisible(visble);
}


///
/// \brief      Text in the search field has been changed
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	text New text in the search field
///
void WidgetTopMenu::slotTextEditFinished()
{
    emit searchTextChanged(mTextSearch->text());
}


void WidgetTopMenu::slotButtonBackPressed()
{
    emit buttonBackPressed();
}

void WidgetTopMenu::slotButtonSettingsPressed()
{
    emit buttonSettingsPressed();
}

void WidgetTopMenu::slotButtonShowPictures()
{
    emit signalViewChanged(View::Pictures);
}

void WidgetTopMenu::slotButtonshowAlbums()
{
    emit signalViewChanged(View::Albums);
}
void WidgetTopMenu::slotButtonShowTags()
{
    emit signalViewChanged(View::Tags);
}
void WidgetTopMenu::slotButtonShowFolder()
{
    emit signalViewChanged(View::Folders);
}

void WidgetTopMenu::slotPictureInfo(bool active)
{
    emit signalPictureInfoPressed(active);
}
