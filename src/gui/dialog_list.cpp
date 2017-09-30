///
/// \file       dialog_list.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "dialog_list.h"
#include <QDebug>
#include <QPushButton>


///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
DialogList::DialogList()
{
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    /// Textfield to search in the list
    textSearch = new QLineEdit();
    textSearch->setPlaceholderText(tr("Search text..."));
    textSearch->setFrame(false);
    connect(textSearch,SIGNAL(textChanged(QString)),this,SLOT(filter(QString)));
    verticalLayout->addWidget(textSearch);

    /// List widget
    listWidget = new QListWidget();
    listWidget->setFrameShape(QFrame::NoFrame);
    listWidget->setObjectName(QStringLiteral("listWidget"));
    listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    verticalLayout->addWidget(listWidget);

    /// Textfield to add a new element
    textNew = new QLineEdit();
    textNew->setPlaceholderText(tr("Add new..."));
    textNew->setFrame(false);
    connect(textNew,SIGNAL(returnPressed()),this,SLOT(add_new_field()));
    verticalLayout->addWidget(textNew);

    /// DialogButton box with Ok and cancle button
    QDialogButtonBox* bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply);
    QPushButton* okBtn = bb->button(QDialogButtonBox::Ok);
    okBtn->setAutoDefault(false);
    okBtn->setDefault(false);
    QPushButton* caBtn = bb->button(QDialogButtonBox::Cancel);
    caBtn->setAutoDefault(false);
    caBtn->setDefault(false);
    QPushButton* caApply = bb->button(QDialogButtonBox::Apply);
    caApply->setAutoDefault(true);
    caApply->setDefault(true);
    caApply->setHidden(true);
    caApply->setMaximumWidth(0);
    verticalLayout->addWidget(bb);
    connect(okBtn,SIGNAL(pressed()),this,SLOT(on_buttonBox_accepted()));
    connect(caBtn,SIGNAL(pressed()),this,SLOT(on_buttonBox_rejected()));

    /// Add lacout
    this->setLayout(verticalLayout);

}

///
/// \brief      Shows the dialog and returns a list
///             with the selected elements
/// \author     Joachim Danmayr
/// \date       2017-08-23
/// \param[in]	elements    Elements which should be shown in the List
/// \param[in]  allowMulitSelection true to alow multiple selections in the list
/// \param[in]  allowAdd    Allow to add new elements to the list
///
QStringList DialogList::showDialog(QStringList elements, bool allowMulitSelection, bool allowAdd)
{
    if(false == allowMulitSelection){
        listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    }

    if(false==allowAdd){
        textNew->setVisible(false);
    }

    listWidget->addItems(elements);
    exec();
    return mSelection;
}

///
/// \brief      Ok button pressed
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void DialogList::on_buttonBox_accepted()
{
    mSelection.clear();
    for(auto item:listWidget->selectedItems()){
        mSelection.append(item->data(Qt::DisplayRole).toString());
    }
    close();
}

///
/// \brief      Cancle button pressed
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void DialogList::on_buttonBox_rejected()
{
    mSelection.clear();
    close();
}

///
/// \brief      Filter for the list
/// \author     Joachim Danmayr
/// \date       2017-08-23
/// \param[in]	searchText  Text to filter
///
void DialogList::filter(QString searchText)
{
    hideAll();
    QList<QListWidgetItem*> matches ( listWidget->findItems(searchText, Qt::MatchFlag::MatchContains) );
    for(QListWidgetItem* item : matches)
        item->setHidden(false);
}

///
/// \brief      Hide all elements in the list
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void DialogList::hideAll()
{
    for(int row(0); row < listWidget->count(); row++ )
        listWidget->item(row)->setHidden(true);
}

///
/// \brief      Adds a new element to the list
///             Text is taken from the textNew line edit
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void DialogList::add_new_field()
{
    listWidget->addItem(textNew->text());
    listWidget->item(listWidget->count()-1)->setSelected(true);
    textNew->setText("");
}
