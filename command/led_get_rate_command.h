#ifndef LEDGETRATECOMMAND_H
#define LEDGETRATECOMMAND_H

#include "command.h"
#include "led.h"
#include "memory"
#include <QSharedPointer>

class LedGetRateCommand: public ICommand
{
public:
    LedGetRateCommand(QSharedPointer<Led> LedGet);
    virtual void Execute(QString& param, QString& answer);

private:
    QSharedPointer<Led> mLed;
};

#endif // LEDGETRATECOMMAND_H
