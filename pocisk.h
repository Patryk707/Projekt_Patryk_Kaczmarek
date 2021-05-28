#ifndef POCISK_H
#define POCISK_H
#include <SFML/Graphics.hpp>
#include "przeciwnik.h"
#include <iostream>

using namespace sf;
using namespace std;

class Pocisk:public::CircleShape
{
public:
    Pocisk(Vector2f size, bool face);
    void set_speed(float speed);
    void set_position(sf::Vector2f new_position);
    bool check_collision(Sprite &przeciwnik);
    ~Pocisk(){       
    }

    float top();
    float bottom();
    float left();
    float right();

    bool getFacing();
    static vector<Pocisk> wystrzelone_pociski;
    static vector<Pocisk> wrogie_pociski;


private:
    const float promien_pocisku=4.0f;
    bool facing;


};

#endif // POCISK_H
