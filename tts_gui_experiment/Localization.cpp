#include "Localization.h"
#include "asa047.hpp" // Nelder-Mead algo.

#include <QDateTime>
#include <QDebug>


//Magnet magnet;
//QVector<Sensor*> sensors;

//static double localizationErrorFunction(double x[5]) {

//    Magnet testMagnet(magnet);
//    testMagnet.position(CImg<double>().assign(1,3).fill(x[0],x[1],x[2]));
//    testMagnet.moment(x[3],x[4]);

//    double error = 0;
//    for(int i=0; i<NUM_OF_SENSORS; i++)
//    {
//        error += ( testMagnet.fields(sensors[i]->position()) - sensors[i]->m_extrapField ).magnitude();
//    }

//    return error;
//}


Localization::Localization(ReadSensors *rs, QVector<Sensor*> &sensors, Magnet &magnet, QObject *parent): QThread(parent)
{
    stop = false;
    this->rs = rs;
    this->sensors = sensors;
    this->magnet = magnet;   
}


void Localization::run()
{
    connect(rs, SIGNAL(packetSaved(MagData)), this, SLOT(computeLocalization(MagData)));
}


void Localization::computeLocalization(MagData magData)
{
    mutex.lock();
    qDebug() << "Data [ " << magData.at(0) << " " << magData.at(1) << " " << magData.at(2) ;
    mutex.unlock();


//    mutex.lock();
//    // Update sensor fields
//    for (int i = 0; i < NUM_OF_SENSORS; i++)
//    {
//        int x = magData->at(i*3);
//        int y = magData->at(i*3 + 1);
//        int z = magData->at(i*3 + 2);
//        sensors[i]->currentField(x, y, z);
////        sensors[i]->calibrate();
//    }

//    // Localize
//    magnet = localizer(magnet);

//    // Save localized magnet data
//    (*outputFile_stream) << magnet.m_position(0) << " "
//                         << magnet.m_position(1) << " "
//                         << magnet.m_position(2) << " "
//                         << magnet.m_theta       << " "
//                         << magnet.m_phi         << " "
//                         << QDateTime::currentDateTime().toMSecsSinceEpoch() << endl;

//    mutex.unlock();
}


Magnet Localization::localizer(Magnet &magnet)
{
    const int n = 5;
    double start[n] = {magnet.position()(0),magnet.position()(1),magnet.position()(2),magnet.theta(),magnet.phi()};
    double step[n] = {0.0001,0.0001,0.0001,PI/720.,PI/720.};
    double reqmin = 1.0E-10;
    double xmin[n];
    int konvge = 250;
    int kcount = 500;
    int icount;
    int ifault;
    int numres;
//    double ynewlo = localizationErrorFunction(start);

//    double (Localization::*errorFunc_ptr)(double[5]);
//    errorFunc_ptr = &Localization::localizationErrorFunction;

//    nelmin ( localizationErrorFunction, n, start, xmin, &ynewlo, reqmin, step, konvge, kcount, &icount, &numres, &ifault );
//    Magnet newMagnet(magnet);
//    newMagnet.position(CImg<double>().assign(1,3).fill(xmin[0],xmin[1],xmin[2])).moment(xmin[3],xmin[4]);
//    return newMagnet;
    Magnet newMagnet(magnet);
    return newMagnet;
}


/* Manage Saving localization data  */
void Localization::setFileLocation(QString filename)
{
    this->filename = filename;
}

void Localization::startSaving()
{
    mutex.lock();
    save = true;
    outputFile.setFileName(filename);
    outputFile_stream = new QTextStream(&outputFile);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    mutex.unlock();
}

void Localization::stopSaving()
{
    mutex.lock();

    disconnect(rs, SIGNAL(newPacketAvail(MagData)), this, SLOT(computeLocalization(MagData)));
    save = false;

    if(outputFile.isOpen()){
        outputFile.close();
    }

    mutex.unlock();
}


/* Stop Execution */
void Localization::Stop()
{
    stopSaving();
    stop = true;
}

Localization::~Localization()
{
    stop = true;
}



