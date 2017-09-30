///
/// \file       settings.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "settings.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-17
/// \param[in]	path    Path where to store the settings
/// \param[in]  format  Settings format
///
Settings::Settings(QString path, Format format):
    QSettings(path, format)
{

}

///
/// \brief      Sync the settings and throw a signal
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
void Settings::sync()
{
    QSettings::sync();
    emit settingsChanged();
}
