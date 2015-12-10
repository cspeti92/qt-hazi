#include "logdata.h"

LogData::LogData(float x,float y, float z,float temp,bool buttonpressed):
    _x(x),_y(y), _z(z),_temp(temp),_button(buttonpressed)
{

}

LogData::LogData()
{

}

void LogData::updateCurrentLogData(float x,float y, float z,float temp,bool buttonpressed)
{
    setX(x);
    setY(y);
    setZ(z);
    setTemp(temp);
    setButton(buttonpressed);
}

void LogData::resetCurrentLogData()
{
    setX(0.0);
    setY(0.0);
    setZ(0.0);
    setTemp(0.0);
    setButton(0);
}
