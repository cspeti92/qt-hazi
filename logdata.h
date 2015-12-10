#ifndef LOGDATA_H
#define LOGDATA_H

#include <QObject>

/**
 * @brief Tároló osztály, melynek egy példányát használja mindig a Logger.
 * A Logger ebből egy, az aktuális állapotot jelző objektummal rendelkezik.
 * A QML oldallal összeköttetésben áll, az aktuális státuszt jelző résszel.
 * A grafikonok is az ő információi alapján frissülnek vagy reszetelődnek.
 */

class LogData : public QObject
{
    Q_OBJECT
public:
    /** Konstruktor
     * @param x x irányú gyorsulás m/s^2-ben
     * @param y y irányú gyorsulás m/s^2-ben
     * @param z z irányú gyorsulás m/s^2-ben
     * @param temp hőmérséklet °C-ban
     * @param buttonpressed A nyomógomb állapota
     */
    LogData(float x,float y, float z,float temp,bool buttonpressed);
    /** Konstruktor paraméterek nélkül
     */
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

    /**
      Frissíti az aktuális állapotleírást a beadott paraméterek alapján.
     * @param x
     * @param y
     * @param z
     * @param temp
     * @param buttonpressed
     */
    void updateCurrentLogData(float x,float y, float z,float temp,bool buttonpressed);
    /**
     * Reszeteli az aktuális állapotleírást. A szimuláció leállításánál használjuk.
     */
    void resetCurrentLogData();

signals:
    // Ezeket a szignalokat most nem használjuk */
    void xChanged();
    void yChanged();
    void zChanged();
    void buttonChanged();
    void tempChanged();
public slots:

private:
     /** Gyorsulás (m/s2) x irányban*/
    float _x;
     /** Gyorsulás (m/s2) y irányban*/
    float _y;
    /** Gyorsulás (m/s2) z irányban*/
    float _z;
     /** A hőmérséklet C fokban */
    float _temp;
    /** A nyomógomb értéke */
    bool _button;

};

#endif // LOGDATA_H
