#pragma once

#ifndef COMMAND_H
#define COMMAND_H

#endif // COMMAND_H

#include <QString>

class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void Execute(QString& param, QString& answer) = 0;
};
