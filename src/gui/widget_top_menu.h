///
/// \file       widget_top_menu.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WIDGET_TOP_MENU_H
#define WIDGET_TOP_MENU_H

#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>


///
/// \class      WidgetTopMenu
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      Top menu widget. Contains buttons
///             for different views and a search bar.
///
class WidgetTopMenu : public QWidget
{
    Q_OBJECT
public:
    enum class View{Pictures, Albums, Tags, Folders};
    explicit WidgetTopMenu(QWidget *parent = nullptr);
    void setBlackStyle(bool);
    void setViewButtonsVisible(bool);

signals:
    void searchTextChanged(QString text);
    void buttonSettingsPressed();
    void buttonBackPressed();
    void signalViewChanged(WidgetTopMenu::View view);
    void signalPictureInfoPressed(bool active);


public slots:
    void slotTextEditFinished();
    void slotButtonBackPressed();
    void slotButtonSettingsPressed();
    void slotButtonShowPictures();
    void slotButtonshowAlbums();
    void slotButtonShowTags();
    void slotButtonShowFolder();
    void slotPictureInfo(bool);



private:
    QWidget* createRadioButtons();
    QToolButton* buttonBack;
    QToolButton* pictureInfo;
    QToolButton* buttonSettings;
    QLineEdit* mTextSearch;
    QWidget *mWidgetButtonsView;


};

#endif // WIDGET_TOP_MENU_H
