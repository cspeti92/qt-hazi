#ifndef LOGDATA_H
#define LOGDATA_H

#include <QObject>

class LogData : public QObject
{
    Q_OBJECT
public:
    LogData(float x,float y, float z,float temp,bool buttonpressed);
    LogData();
    /** Gyorsulás x irányban (m/s2) */
    Q_PROPERTY(float x READ x WRITE setX MEMBER _x NOTIFY xChanged)
    float x() const { return _x; }
    void setX(float x) { _x = x; }

    /** Gyorsulás y irányban (m/s2) */
    Q_PROPERTY(float y READ y WRITE setY MEMBER _y NOTIFY yChanged)
    float y() const { return _y; }
    void setY(float y) { _y= y; }

    /** Gyorsulás z irányban (m/s2) */
    Q_PROPERTY(float z READ z WRITE setZ MEMBER _z NOTIFY zChanged)
    float z() const { return _z; }
    void setZ(float z) { _z= z; }

    /** Nyomógomb értéke  */
    Q_PROPERTY(bool button READ button WRITE setButton MEMBER _button NOTIFY buttonChanged)
    bool button() const { return _button; }
    void setButton(bool button) { _button= button; }


    Q_PROPERTY(float temp READ temp WRITE setTemp MEMBER _temp NOTIFY tempChanged)
    float temp() const { return _temp; }
    void setTemp(float temp) { _temp= temp; }

    void updateCurrentLogData(float x,float y, float z,float temp,bool buttonpressed);
    void resetCurrentLogData();

signals:
    void xChanged();
    void yChanged();
    void zChanged();
    void buttonChanged();
    void tempChanged();
public slots:

private:
    float _x;   /** Gyorsulás (m/s2) x irányban*/
    float _y;   /** Gyorsulás (m/s2) y irányban*/
    float _z;   /** Gyorsulás (m/s2) z irányban*/
    float _temp; /** A hőmérséklet C fokban */
    bool _button; /** A nyomógomb értéke */

};

#endif // LOGDATA_H
