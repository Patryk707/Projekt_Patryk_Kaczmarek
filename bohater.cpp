#include "bohater.h"
#include "pocisk.h"

Bohater::Bohater(Vector2f &position)
{
    this->setPosition(position);
    current_position_x=position.x;
    current_position_y=position.y;
}


void Bohater::setSpeed(float x,float y){
    speed_x=x;
    speed_y=y;
}

void Bohater::setFacing(bool f) {
    facing = f;
}

bool Bohater::getFacing() {
    return facing;
}



void Bohater::setBounds(float left, float right, float top, float bottom){
    left_borderline=left;
    right_borderline=right;
    top_borderline=top;
    bottom_borderline=bottom;
}
void Bohater::bounce(){
    if(getGlobalBounds().top<=top_borderline){
        speed_y=abs(speed_y);
    }
    else if(getGlobalBounds().top+getGlobalBounds().height>=bottom_borderline){
        speed_y=-abs(speed_y);
    }
    else if(getGlobalBounds().left<=left_borderline){
        speed_x=abs(speed_x);
    }
    else if(this->getGlobalBounds().left+getGlobalBounds().width>=right_borderline){
        speed_x=-abs(speed_x);
    }
}

void Bohater::shoot() {
    Pocisk nowy_pocisk(Vector2f(20, 20), getFacing());
    nowy_pocisk.set_position(Vector2f(getPosition().x, getPosition().y));
    Pocisk::wystrzelone_pociski.emplace_back(nowy_pocisk);
}

void Bohater::animate(const Time &elapsed){
    float sec = elapsed.asSeconds();
    bounce();
    gravity_speed=acceleration*sec;
    float grawitacja=(sec*speed_y)-(acceleration*sec*sec/2);

    current_position_x = getPosition().x;
    current_position_y = getPosition().y;

    previous_position_x = current_position_x;
    previous_position_y = current_position_y;

    if(Keyboard::isKeyPressed(Keyboard::Key::Left)&& this->getGlobalBounds().left>left_borderline){
        setSpeed(-200,0);
        current_position_x=speed_x*sec;
        current_position_y=speed_y*sec;
        setScale(-0.4,0.4);
        setFacing(false);
        //this->setPosition(potential_position_x,potential_position_y);


        move(current_position_x,current_position_y);
        //if(check_collision(walls)){
        //    this->setSpeed(0,speed_y);
        //    this->setPosition(getPosition().x-1,getPosition().y);
        //}

    }
     if(Keyboard::isKeyPressed(Keyboard::Key::Right) && this->getGlobalBounds().left+this->getGlobalBounds().width<right_borderline){
         setSpeed(200, 0);
         current_position_x = speed_x * sec;
         current_position_y = speed_y * sec;
         setScale(0.4f, 0.4f);
         setFacing(true);
         move(current_position_x, current_position_y);

    }
     if(Keyboard::isKeyPressed(Keyboard::Key::Up)&& this->getGlobalBounds().top>top_borderline){
        //speed_y=gravityspeed;
         setSpeed(0, -200);
         current_position_x = speed_x * sec;
         current_position_y = speed_y * sec;
         move(current_position_x, current_position_y);
        is_jumping=true;
    }
     if(Keyboard::isKeyPressed(Keyboard::Key::Down) && this->getGlobalBounds().top+this->getGlobalBounds().height<bottom_borderline){
        setSpeed(0,200);
        current_position_x = speed_x * sec;
        current_position_y = speed_y * sec;
        move(current_position_x, current_position_y);

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

bool Bohater::check_collision(const vector<unique_ptr<Sprite>> &walls ){
    for(auto &el:walls){
        Sprite *cast=dynamic_cast<Sprite *>(el.get());
        if(this->getGlobalBounds().intersects(cast->getGlobalBounds())){
            return true;
        }
    }
    return false;
}
void Bohater::collision(const vector<unique_ptr<Sprite>> &walls, const Time &elapsed){
    float sec = elapsed.asSeconds();
    //float droga_x=sec*speed_x;
    //float droga_y=sec*speed_y;
    this->setSpeed(0,0);
    if(!check_collision(walls)){
        this->setSpeed(200,200);
        animate(elapsed);
    }else {
        setPosition(previous_position_x, previous_position_y);
    }

   // else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Left)){
        //this->setPosition(getPosition().x+1,getPosition().y);
   //     this->move(abs(droga_x),0);
        //this->move(0,0);
    //}
    //else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Right)){
        //this->setPosition(getPosition().x-1,getPosition().y);
    //    this->move(-abs(droga_x),0);
    //}
    //else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Up)){
    //    this->move(0,abs(droga_y));
        //this->setPosition(getPosition().x,getPosition().y+1);
    //}
    //else if(check_collision(walls) && Keyboard::isKeyPressed(Keyboard::Key::Down)){
        //this->setPosition(getPosition().x,getPosition().y-1);
     //   this->move(0,-abs(droga_y));
    //}
}
void Bohater::set_lives(int l){
    lives+=l;
}
bool Bohater::is_alive(){
    if(lives<=0){
        return false;
    }
    return true;
}
