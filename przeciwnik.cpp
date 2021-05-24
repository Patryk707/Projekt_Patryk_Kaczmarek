#include "przeciwnik.h"

Przeciwnik::Przeciwnik(Vector2f size)
{   this->setScale(size);
}
void Przeciwnik::set_position(Vector2f new_position){
    this->setPosition(new_position);
}


void Przeciwnik::set_speed(float speed){
    this->speed_x=speed;
}
void Przeciwnik::animate(const Time &elapsed){
    float sec = elapsed.asSeconds();
    set_speed(100);
    set_kierunek_ruchu();
    float droga=speed_x*sec;
    if(!kierunek_ruchu){
        move(-std::abs(droga),0);
        setFacing(false);
    }
    else{
        move(std::abs(droga),0);
        setFacing(true);
    }
}
void Przeciwnik::setBounds(float left, float right){
    left_borderline=left;
    right_borderline=right;
}
void Przeciwnik::set_kierunek_ruchu(){
    if(getGlobalBounds().left<=left_borderline){
        kierunek_ruchu=true;
        setScale(0.4,0.4);
    }
    if(getGlobalBounds().left+getGlobalBounds().width>=right_borderline){
        kierunek_ruchu=false;
        setScale(-0.4,0.4);
    }
}


void Przeciwnik::set_lives(int l){
    lives+=l;
}
bool Przeciwnik::is_alive(){
    if(lives<=0){
        return false;
    }
    return true;
}
void Przeciwnik::setFacing(bool f) {
    facing = f;
}

bool Przeciwnik::getFacing() {
    return facing;
}

void Przeciwnik::shoot(){
    Pocisk nowy_pocisk(Vector2f(20, 20), getFacing());
    nowy_pocisk.set_position(Vector2f(getPosition().x, getPosition().y));
    Pocisk::wrogie_pociski.emplace_back(nowy_pocisk);
}



