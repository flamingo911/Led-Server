#include "command/led_get_color_command.h"
#include <QException>

LedGetColorCommand::LedGetColorCommand(QSharedPointer<Led> LedGet): mLed(LedGet)
{
}

void LedGetColorCommand::Execute(QString& /*param*/, QString& answer)
{
    switch( mLed->GetLedColor() )
    {
    case RED:
        answer = "red";
        break;
    case GREEN:
        answer = "green";
        break;
    case BLUE:
        answer = "blue";
        break;

    default:
        throw QException();
    }

}
