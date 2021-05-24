#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H
#include <SFML/Graphics.hpp>
#include "pocisk.h"

using namespace sf;
using namespace std;


class Przeciwnik:public::Sprite
{
public:
    Przeciwnik(Vector2f size);
    void set_position(Vector2f new_position);


    void set_speed(float speed);
    void setBounds(float l,float r);
    void set_kierunek_ruchu();
    void animate(const Time &elapsed);

    void set_lives(int l);
    bool is_alive();

    void shoot();

    void setFacing(bool f);
    bool getFacing();
    bool wrogi_wystrzelony=false;
    Clock shot_cooldown;
    float right_borderline;
    float left_borderline;
private:

    float speed_x;
    bool kierunek_ruchu=false;
    bool facing=true;
    int lives=3;

};

#endif // PRZECIWNIK_H
