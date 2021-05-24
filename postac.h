#ifndef POSTAC_H
#define POSTAC_H
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class Postac:public::Sprite
{
public:
    Postac(Vector2f &position);
    void setSpeed(float x,float y);
    void animate(const Time &elapsed);
    void setBounds(float l,float r, float t, float b);
    void bounce();
    const int groundHeight=1340;
    //const int gravityspeed=50;
    const int acceleration=30;
    bool is_jumping=false;
    bool check_collision(const vector<unique_ptr<Sprite>> &walls );
    void collision(const vector<unique_ptr<Sprite>> &walls , const Time &elapsed);
    float speed_x=0;
    float speed_y=0;
    float actual_position_x;
    float actual_position_y;
private:
    float right_borderline;
    float left_borderline;
    float top_borderline;
    float bottom_borderline;

    float gravity_speed=0;

};

#endif // POSTAC_H
