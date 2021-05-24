#ifndef POSTAC_H
#define POSTAC_H
#include <SFML/Graphics.hpp>
#include<cmath>

using namespace sf;
using namespace std;


class Bohater:public::Sprite
{
public:
    Bohater(Vector2f &position);
    void setSpeed(float x,float y);
    void setFacing(bool f);
    bool getFacing();

    void animate(const Time &elapsed);
    void setBounds(float l,float r, float t, float b);
    void bounce();

    void shoot();

    bool check_collision(const vector<unique_ptr<Sprite>> &walls );
    void collision(const vector<unique_ptr<Sprite>> &walls , const Time &elapsed);

    const int groundHeight=1340;
    //const int gravityspeed=50;
    const int acceleration=30;
    bool is_jumping=false;

    void set_lives(int l);
    bool is_alive();


private:
    float right_borderline;
    float left_borderline;
    float top_borderline;
    float bottom_borderline;

    float speed_x;
    float speed_y;
    float previous_position_x;
    float previous_position_y;
    float current_position_x;
    float current_position_y;

    int lives=3;

    float gravity_speed=0;
    bool facing=true;

};

#endif // POSTAC_H



