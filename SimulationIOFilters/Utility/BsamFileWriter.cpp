#include "BsamFileWriter.h"

#include <QtCore/QDir>
#include <QtCore/QTextStream>

bool BsamFileWriter::write(const QString& outputPath, const QString& filePrefix, int32_t numClusters)
{
  QString masterFilePath = outputPath + QDir::separator() + filePrefix + ".in";

  QFile masterFile(masterFilePath);
  if(!masterFile.open(QIODevice::OpenModeFlag::WriteOnly))
  {
    QString ss = QObject::tr("BSAM file can not be created: %1").arg(masterFilePath);
    return false;
  }

  QTextStream masterStream(&masterFile);

  masterStream << "***********************************************\n";
  masterStream << "**** BSAM INPUT FILE  generated by DREAM.3D ***\n";
  masterStream << "***********************************************\n";
  masterStream << "\n";

  for(int32_t i = 0; i < numClusters; i++)
  {
    QString inputFilePath = outputPath + QDir::separator() + filePrefix + QString("_Cluster") + QString::number(i + 1) + ".ele";

    QFile inputFile(inputFilePath);

    if(!inputFile.open(QIODevice::OpenModeFlag::ReadOnly))
    {
      QString ss = QObject::tr("BSAM Input file could not be opened: %1").arg(inputFilePath);
      return false;
    }

    QTextStream inputStream(&inputFile);

    masterStream << "***********************************************\n";

    while(!inputStream.atEnd())
    {
      masterStream << inputStream.readLine();
    }

    masterStream << "\n";
  }

  return true;
}
