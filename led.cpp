#include "led.h"

Led::Led(): mEnabled(false), mLedRate(0), mColor(RED)
{
}

bool Led::GetState() const
{
    return mEnabled;
}

void Led::SetState(const bool state)
{
    mEnabled = state;
}

int Led::GetLedRate() const
{
    return mLedRate;
}

void Led::SetLedRate(const int rate)
{
    if(rate < 0)
        mLedRate = 0;
    else if(rate > 5)
        mLedRate = 5;
    else
        mLedRate = rate;
}

Color Led::GetLedColor() const
{
    return mColor;
}

void Led::SetLedColor(const Color color)
{
    mColor = color;
}

LedInfoMap Led::GetLedInfo() const
{
    LedInfoMap led_info;
    if( this->GetState() )
        led_info["state"] = "on";
    else
        led_info["state"] = "off";

    led_info["color"] = this->GetLedColorStr();
    led_info["rate"] = QString::number(this->GetLedRate());

    return led_info;
}

QString Led::GetLedColorStr() const
{
    switch(this->GetLedColor())
    {
        case RED:
            return "red";
            break;
        case GREEN:
            return "green";
            break;
        case BLUE:
            return "blue";
            break;
    }
}
