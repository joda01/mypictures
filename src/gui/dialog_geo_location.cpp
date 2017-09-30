///
/// \file       dialog_geo_location.cpp
/// \author     Joachim Danmayr
/// \date       2017-09-03
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "dialog_geo_location.h"
#include <QPushButton>
#include <QDialogButtonBox>

DialogGeoLocation::DialogGeoLocation()
{

    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

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
QGeoLocation DialogGeoLocation::showDialog(QGeoLocation location)
{
    exec();
    return mLocation;
}


///
/// \brief      Ok button pressed
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void DialogGeoLocation::on_buttonBox_accepted()
{

    close();
}

///
/// \brief      Cancle button pressed
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void DialogGeoLocation::on_buttonBox_rejected()
{
    close();
}
