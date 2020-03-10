#include "command/led_set_rate_command.h"
#include <QException>
#include <QRegularExpression>

LedSetRateCommand::LedSetRateCommand(QSharedPointer<Led> LedGet): mLed(LedGet)
{
}

void LedSetRateCommand::Execute(QString& param, QString& /*answer*/)
{
    QRegularExpression reg("\\d+$");
    auto res = reg.match(param);
    if( !res.hasMatch() )
        throw QException();

    const int rate = param.toInt();

    if(rate < 0 || rate > 5)
    {
        throw QException();
    }
    else
    {
        mLed->SetLedRate(rate);
    }
}
