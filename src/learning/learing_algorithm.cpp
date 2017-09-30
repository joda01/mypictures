///
/// \file       learing_algorithm.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "learing_algorithm.h"
#include <QDebug>

#include <QFile>


LearingAlgorithm::LearingAlgorithm()
{
    connect(&mProcess,SIGNAL(finished(int)),this,SLOT(slotProcessFinished(int)));
}


void LearingAlgorithm::execute(QString imgFile)
{
    QFile file("../src/learning/python/classify_image.py");
    qDebug() << "Start analyse algorithm" << file.exists();

    QStringList params;
    params << "../src/learning/python/classify_image.py" << "--model_dir" << "../src/learning/python/" << "--image_file" << imgFile;
    //mProcess.moveToThread(&mThread);
    mProcess.start("python", params);
    //mThread.start();

}

void LearingAlgorithm::slotProcessFinished(int)
{
    QString p_stdout = mProcess.readAll();
    QStringList outputList = p_stdout.split("\n");
    QStringList returnList;
    for(auto en:outputList){
        en = en.replace("\"","");
        en = en.replace(")","");
        en = en.replace("(score = ",";");
        en = en.replace(" ","");

        returnList.append(en);
        qDebug() << en;
    }

    analyseFinished(returnList);
}
