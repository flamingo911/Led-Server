#include "command/led_get_rate_command.h"

LedGetRateCommand::LedGetRateCommand(QSharedPointer<Led> LedGet): mLed(LedGet)
{
}

void LedGetRateCommand::Execute(QString& /*param*/, QString &answer)
{
    answer = QString::number( mLed->GetLedRate() );
}
