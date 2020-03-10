#ifndef LEDSETSTATECOMMAND_H
#define LEDSETSTATECOMMAND_H

#include "command.h"
#include "led.h"
#include "memory"
#include <QSharedPointer>

class LedSetStateCommand: public ICommand
{
public:
    LedSetStateCommand(QSharedPointer<Led> led);
    virtual void Execute(QString& param, QString& answer);

private:
    QSharedPointer<Led> mLed;
};

#endif // LEDSETSTATECOMMAND_H
