#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bohater.h"
#include "przeciwnik.h"
#include "pocisk.h"
#include <vector>

using namespace std;
using namespace sf;

vector<Pocisk> Pocisk::wystrzelone_pociski;
vector<Pocisk> Pocisk::wrogie_pociski;

Texture loadtexture(const string &filename_with_path){
    Texture texture;
    if(!texture.loadFromFile(filename_with_path)){
        cerr<<"Could not load texture"<<endl;
    }
    return texture;
}



int main()
{
    RenderWindow window(VideoMode(1600,900 ),"Projekt");
    window.setFramerateLimit(60);
    Event event;



    //Texture platformy_tekstura=loadtexture("./../Projekt_proba1/Environment/ground_grass_small.png");
    //platformy_tekstura.setRepeated(true);
    Texture bohater_tekstura=loadtexture("./../Projekt_proba2/Players/bunny1_walk2.png");
    Texture sciana_tekstura=loadtexture("./../Projekt_proba2/wall.png");
    Texture przeciwnik_tekstura=loadtexture("./../Projekt_proba2/Players/bunny2_walk2.png");
    sciana_tekstura.setRepeated(true);

    vector<unique_ptr<Sprite>> otoczenie;

    //auto platforma1=make_unique<Sprite>();
    //platforma1->setTexture(platformy_tekstura);
    //platforma1->setPosition(0,1240);
    //platforma1->setTextureRect(IntRect(0,1240,1500,100));
    //otoczenie.emplace_back(move(platforma1));

    //auto platforma2=make_unique<Sprite>();
    //platforma2->setTexture(platformy_tekstura);
    //platforma2->setPosition(0,940);
    //platforma2->setTextureRect(IntRect(0,940,1500,50));
    //otoczenie.emplace_back(move(platforma2));

    //auto platforma3=make_unique<Sprite>();
    //platforma3->setTexture(platformy_tekstura);
    //platforma3->setPosition(0,640);
    //platforma3->setTextureRect(IntRect(0,640,1500,50));
    //otoczenie.emplace_back(move(platforma3));

    //walls
    auto wall1=make_unique<Sprite>();
    wall1->setTexture(sciana_tekstura);
    wall1->setPosition(0,1240);
    wall1->setTextureRect(IntRect(0,1240,1500,100));
    otoczenie.emplace_back(move(wall1));

    auto wall2=make_unique<Sprite>();
    wall2->setTexture(sciana_tekstura);
    wall2->setPosition(0,940);
    wall2->setTextureRect(IntRect(0,940,1500,50));
    otoczenie.emplace_back(move(wall2));

    auto wall3=make_unique<Sprite>();
    wall3->setTexture(sciana_tekstura);
    wall3->setPosition(0,640);
    wall3->setTextureRect(IntRect(0,640,1500,50));
    otoczenie.emplace_back(move(wall3));

    auto wall4=make_unique<Sprite>();
    wall4->setTexture(sciana_tekstura);
    wall4->setPosition(900,300);
    wall4->setTextureRect(IntRect(0,640,1500,50));
    otoczenie.emplace_back(move(wall4));

    //postac
    Vector2f position(100, 100);
    Bohater postac(position);
    postac.setScale(0.4, 0.4);
    postac.setOrigin(float(bohater_tekstura.getSize().x) / 2, float(bohater_tekstura.getSize().y) / 2);
    postac.setTexture(bohater_tekstura);
    postac.setBounds(0, window.getSize().x, 0, window.getSize().y);
    postac.setSpeed(200, 200);
    //przeciwnik
    //vector<unique_ptr<Sprite>> przeciwnicy;
    //auto przeciwnik1=make_unique<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik1->setTexture(przeciwnik_tekstura);
    //przeciwnik1->set_position(Vector2f(1000,500));
    //przeciwnicy.emplace_back(move(przeciwnik1));

    //auto przeciwnik2=make_unique<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik2->setTexture(przeciwnik_tekstura);
    //przeciwnik2->set_position(Vector2f(500,500));
    //przeciwnicy.emplace_back(move(przeciwnik2));

   // auto przeciwnik3=make_unique<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik3->setTexture(przeciwnik_tekstura);
    //przeciwnik3->set_position(Vector2f(800,500));
    //przeciwnicy.emplace_back(move(przeciwnik3));


    //----------------
    vector<Przeciwnik> enemies;
    Przeciwnik enemy1(Vector2f(0.4,0.4));
    enemy1.setTexture(przeciwnik_tekstura);
    enemy1.set_position(Vector2f(100,200));
    enemy1.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    enemy1.shot_cooldown.restart();
    enemy1.setBounds(0,1600);
    enemies.emplace_back(enemy1);

    Przeciwnik enemy2(Vector2f(0.4,0.4));
    enemy2.setTexture(przeciwnik_tekstura);
    enemy2.set_position(Vector2f(500,500));
    enemy2.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    enemy2.shot_cooldown.restart();
    enemy2.setBounds(400,800);
    enemies.emplace_back(enemy2);

    //pocisk       
    bool wystrzelony=false;




    Clock clock;
    Clock shot_cooldown;    
    shot_cooldown.restart();   
        srand(time(NULL));
    while(window.isOpen()){
        Time elapsed = clock.restart();
        window.clear(Color::Black);
        window.pollEvent(event);
        if(event.type==Event::Closed){
            window.close();
            break;
        }
        if(Event::KeyReleased){
            postac.is_jumping=false;
        }
        //wystrzeliwanie pociskow
        if (!wystrzelony and Keyboard::isKeyPressed(Keyboard::Space)
            and shot_cooldown.getElapsedTime().asSeconds() >= 1) {
            postac.shoot();           
            shot_cooldown.restart();
            wystrzelony = true;
        } else if (wystrzelony and !Keyboard::isKeyPressed(Keyboard::Space)) {
            wystrzelony = false;
        }
       // for(auto &enemy : enemies){
       // if (!enemy.wrogi_wystrzelony and enemy.shot_cooldown.getElapsedTime().asSeconds() >= 1) {
       //     enemy.shoot();
       //     enemy.shot_cooldown.restart();
       //     enemy.wrogi_wystrzelony = true;
       // } else if (enemy.wrogi_wystrzelony) {
       //     enemy.wrogi_wystrzelony = false;
       // }
        //}
        //wystrzeliwanie pociskow
        for (auto& wystrzelony_pocisk : Pocisk::wystrzelone_pociski) {
            window.draw(wystrzelony_pocisk);
            wystrzelony_pocisk.set_speed(wystrzelony_pocisk.getFacing() ? 3 : -3);
        }
        for (auto& wrogi_pocisk : Pocisk::wrogie_pociski) {
            window.draw(wrogi_pocisk);
            wrogi_pocisk.set_speed(wrogi_pocisk.getFacing() ? 3 : -3);
        }


        //przeciwnik a pocisk
        for(auto &wystrzelony_pocisk : Pocisk::wystrzelone_pociski){
            for(auto i=0; i<enemies.size(); i++){
                if(wystrzelony_pocisk.check_collision(enemies[i])){
                    //wystrzelony_pocisk.Pocisk::~Pocisk();
                   wystrzelony_pocisk.set_position(Vector2f(10000,10000));
                   enemies[i].set_lives(-1);
                   if(!enemies[i].is_alive()){
                        enemies[i].set_position(Vector2f(10000,10000));
                   }
            }
            }
        }
        //bohater a pocisk
        for(auto &wystrzelony_pocisk : Pocisk::wrogie_pociski){
                if(wystrzelony_pocisk.check_collision(postac)){
                    wystrzelony_pocisk.set_position(Vector2f(10000,10000));
                    postac.set_lives(-1);
                    if(!postac.is_alive()){
                        postac.move(10000,10000);
                    }
                }
        }





        //enemy animation

        for(auto &enemy : enemies){
            if(postac.getGlobalBounds().left>enemy.left_borderline and
                    postac.getGlobalBounds().left+postac.getGlobalBounds().width<enemy.right_borderline and
                    postac.getGlobalBounds().top>enemy.getGlobalBounds().top-enemy.getGlobalBounds().height and
                    postac.getGlobalBounds().top+postac.getGlobalBounds().height<enemy.getGlobalBounds().top+2*enemy.getGlobalBounds().height){
                if(postac.getGlobalBounds().left<enemy.getGlobalBounds().left){
                    enemy.setScale(-0.4,0.4);
                    enemy.setFacing(false);
                }
                if(postac.getGlobalBounds().left>enemy.getGlobalBounds().left){
                    enemy.setScale(0.4,0.4);
                    enemy.setFacing(true);
                }

                if (!enemy.wrogi_wystrzelony and enemy.shot_cooldown.getElapsedTime().asSeconds() >= 1) {
                    enemy.shoot();
                    enemy.shot_cooldown.restart();
                    enemy.wrogi_wystrzelony = true;
                } else if (enemy.wrogi_wystrzelony) {
                    enemy.wrogi_wystrzelony = false;
                }
            }
            else{
            enemy.animate(elapsed);
            }
        }


        //collision postac
        postac.collision(otoczenie,elapsed);


        //if(postac.check_collision(otoczenie)){
            //cout<<"Kolizja!";
            //cout<<postac.getGlobalBounds().left;
            //cout<<postac.getGlobalBounds().top;
        //}


        //drawing
        for(const auto &ksztalty:otoczenie){
            window.draw(*ksztalty);
        }
        //for(const auto &przeciwnik:przeciwnicy){
        //    window.draw(*przeciwnik);
        //}
        for(auto &enemy : enemies){
            window.draw(enemy);
        }
        //window.draw(enemy1);
        window.draw(postac);


        window.display();
       }
    return 0;
}
