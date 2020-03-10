#ifndef LEDGETCOLORCOMMAND_H
#define LEDGETCOLORCOMMAND_H

#include "command.h"
#include "led.h"
#include "memory"
#include <QSharedPointer>

class LedGetColorCommand: public ICommand
{
public:
    LedGetColorCommand(QSharedPointer<Led> LedGet);
    virtual void Execute(QString& param, QString& answer);

private:
    QSharedPointer<Led> mLed;
};

#endif // LEDGETCOLORCOMMAND_H
