#include "command/led_set_color_command.h"
#include <QException>

LedSetColorCommand::LedSetColorCommand(QSharedPointer<Led> LedGet): mLed(LedGet)
{
}

void LedSetColorCommand::Execute(QString& param, QString& /*answer*/)
{
    if(param == "red")
        mLed->SetLedColor(RED);
    else if(param == "green")
        mLed->SetLedColor(GREEN);
    else if(param == "blue")
        mLed->SetLedColor(BLUE);
    else
    {
        throw QException();
    }
}
