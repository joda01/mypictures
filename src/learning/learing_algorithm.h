///
/// \file       learing_algorithm.h
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef LEARING_ALGORITHM_H
#define LEARING_ALGORITHM_H

#include <QStringList>
#include <QProcess>
#include <QThread>


class LearingAlgorithm : public QObject
{
    Q_OBJECT

public:
    LearingAlgorithm();
    void execute(QString imgFile);

signals:
    void analyseFinished(QStringList foundTerms);

public slots:
    void slotProcessFinished(int);



private:
    QProcess mProcess;

};

#endif // LEARING_ALGORITHM_H
