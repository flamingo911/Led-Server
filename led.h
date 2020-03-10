#pragma once

#ifndef LED_H
#define LED_H

#include <map>
#include <QString>

enum Color
{
    RED,
    GREEN,
    BLUE
};

typedef std::map<QString, QString> LedInfoMap;

class Led
{
public:
    Led();
    ~Led() {};

    bool GetState() const;
    void SetState(const bool state);

    int GetLedRate() const;
    void SetLedRate(const int rate);

    Color GetLedColor() const;
    void SetLedColor(const Color color);

    LedInfoMap GetLedInfo() const;

private:
    QString GetLedColorStr() const;

private:
    bool  mEnabled;
    int   mLedRate;
    Color mColor;
};

#endif // LED_H
