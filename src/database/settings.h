///
/// \file       settings.h
/// \author     Joachim Danmayr
/// \date       2017-08-17
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

///
/// \class      Settings
/// \author     Joachim Danmayr
/// \date       2017-08-17
/// \brief      Settings class
///
class Settings : public QSettings
{
    Q_OBJECT

public:
    Settings(QString path, Format format);
    virtual void sync();

signals:
    void settingsChanged();
};

#endif // SETTINGS_H
