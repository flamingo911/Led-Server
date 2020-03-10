#include "command/led_get_state_command.h"

LedGetStateCommand::LedGetStateCommand(QSharedPointer<Led> LedGet): mLed(LedGet)
{
}

void LedGetStateCommand::Execute(QString& /*param*/, QString &answer)
{
    if( mLed->GetState() )
        answer = "on";
    else
        answer = "off";
}
