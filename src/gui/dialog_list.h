///
/// \file       dialog_list.h
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///m

#ifndef DIALOG_LIST_H
#define DIALOG_LIST_H

#include <QDialog>

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>


///
/// \class      DialogList
/// \author     Joachim Danmayr
/// \date       2017-08-23
/// \brief      List dialog which allows to choose
///             elements. Use the function showDialof to
///             open the dialog
///
class DialogList : public QDialog
{
    Q_OBJECT

public:
    DialogList();
    QStringList showDialog(QStringList elements, bool allowMulitSelection=true, bool allowAdd=true);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void filter(QString searchText);
    void add_new_field();

private:
    QVBoxLayout *verticalLayout;
    QLineEdit* textSearch;
    QLineEdit* textNew;
    QListWidget *listWidget;
    QStringList mSelection;


    void hideAll();

};

#endif // DIALOG_LIST_H
