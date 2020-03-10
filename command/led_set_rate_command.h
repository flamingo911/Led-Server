#ifndef LEDSETRATECOMMAND_H
#define LEDSETRATECOMMAND_H

#include "command.h"
#include "led.h"
#include "memory"
#include <QSharedPointer>

class LedSetRateCommand: public ICommand
{
public:
    LedSetRateCommand(QSharedPointer<Led> LedGet);
    virtual void Execute(QString& param, QString& answer);

private:
    QSharedPointer<Led> mLed;
};

#endif // LEDSETRATECOMMAND_H
