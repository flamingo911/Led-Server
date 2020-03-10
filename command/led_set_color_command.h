#ifndef LEDSETCOLORCOMMAND_H
#define LEDSETCOLORCOMMAND_H

#include "command.h"
#include "led.h"
#include "memory"
#include <QSharedPointer>

class LedSetColorCommand: public ICommand
{
public:
    LedSetColorCommand(QSharedPointer<Led> LedGet);
    virtual void Execute(QString& param, QString& answer);

private:
    QSharedPointer<Led> mLed;
};

#endif // LEDSETCOLORCOMMAND_H
