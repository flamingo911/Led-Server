#ifndef LEDGETSTATECOMMAND_H
#define LEDGETSTATECOMMAND_H

#include "command.h"
#include "led.h"
#include "memory"
#include <QSharedPointer>

class LedGetStateCommand: public ICommand
{
public:
    LedGetStateCommand(QSharedPointer<Led> LedGet);
    virtual void Execute(QString& param, QString& answer);

private:
    QSharedPointer<Led> mLed;
};

#endif // LEDGETSTATECOMMAND_H
