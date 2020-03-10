#include "command/led_set_state_command.h"
#include <QException>

LedSetStateCommand::LedSetStateCommand(QSharedPointer<Led> LedGet): mLed(LedGet)
{
}

void LedSetStateCommand::Execute(QString& param, QString &/*answer*/)
{
    if(param == "on")
        mLed->SetState(true);
    else if(param == "off")
        mLed->SetState(false);
    else
        throw QException();
}
