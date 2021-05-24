#include "postac.h"

Postac::Postac(Vector2f &position)
{
    this->setPosition(position);


}
void Postac::setSpeed(float x,float y){
    speed_x=x;
    speed_y=y;
}
void Postac::setBounds(float left, float right, float top, float bottom){
    left_borderline=left;
    right_borderline=right;
    top_borderline=top;
    bottom_borderline=bottom;
}
void Postac::bounce(){
    if(this->getGlobalBounds().top<=top_borderline){
        this->speed_y=std::abs(this->speed_y);
    }
    else if(this->getGlobalBounds().top+this->getGlobalBounds().height>=bottom_borderline){
        this->speed_y=-std::abs(this->speed_y);
    }
    else if(this->getGlobalBounds().left<=left_borderline){
        this->speed_x=std::abs(this->speed_x);
    }
    else if(this->getGlobalBounds().left+this->getGlobalBounds().width>=right_borderline){
        this->speed_x=-std::abs(this->speed_x);
    }
}
void Postac::animate(const Time &elapsed){
    float sec = elapsed.asSeconds();
    bounce();
    float droga_x=sec*speed_x;
    gravity_speed=acceleration*sec;
    float grawitacja=(sec*speed_y)-(acceleration*sec*sec/2);
    float droga_y=sec*speed_y;
    if(Keyboard::isKeyPressed(Keyboard::Key::Left)&& this->getGlobalBounds().left>left_borderline){
        this->move(-std::abs(droga_x),0);
    }
     if(Keyboard::isKeyPressed(Keyboard::Key::Right) && this->getGlobalBounds().left+this->getGlobalBounds().width<right_borderline){
       this->move(std::abs(droga_x),0);
    }
     if(Keyboard::isKeyPressed(Keyboard::Key::Up)&& this->getGlobalBounds().top>top_borderline){
        //speed_y=gravityspeed;
        this->move(0,-std::abs(droga_y));
        is_jumping=true;
    }
     if(Keyboard::isKeyPressed(Keyboard::Key::Down) && this->getGlobalBounds().top+this->getGlobalBounds().height<bottom_borderline){
        this->move(0,std::abs(droga_y));
    }
    else{
        this->move(0,0);

    }

    // gravity
    //if(Keyboard::isKeyPressed(Keyboard::Key::Up)==false && this->getGlobalBounds().top+this->getGlobalBounds().height<bottom_borderline){
     //   this->move(0,std::abs(grawitacja));
    //    is_jumping=false;
    //}
}
bool Postac::check_collision(const vector<unique_ptr<Sprite>> &walls ){
    for(auto &el:walls){
        Sprite *cast=dynamic_cast<Sprite *>(el.get());
        if(this->getGlobalBounds().intersects(cast->getGlobalBounds())){
            return true;
        }
    }
    return false;
}
void Postac::collision(const vector<unique_ptr<Sprite>> &walls, const Time &elapsed){
    float sec = elapsed.asSeconds();
    float droga_x=sec*speed_x;
    float droga_y=sec*speed_y;
    this->setSpeed(0,0);
    if(!check_collision(walls)){
        this->setSpeed(200,200);
        animate(elapsed);
    }

    else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Left)){
        //this->setPosition(getPosition().x+1,getPosition().y);
        this->move(std::abs(droga_x),0);
        //this->move(0,0);

    }
    else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Right)){
        //this->setPosition(getPosition().x-1,getPosition().y);
        this->move(-std::abs(droga_x),0);

    }
    else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Up)){

        this->move(0,std::abs(droga_y));
        //this->setPosition(getPosition().x,getPosition().y+1);



    }
    else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Down)){
        //this->setPosition(getPosition().x,getPosition().y-1);
        this->move(0,-std::abs(droga_y));


    }
}
