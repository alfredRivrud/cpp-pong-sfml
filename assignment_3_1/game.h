//
// Created by rivru on 13.02.2026.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "ball.h"
#include "paddle.h"


#ifndef ASSIGNMENT_3_1_GAME_H
#define ASSIGNMENT_3_1_GAME_H


//Her lager vi base-klassen game og deklarerer funksjoner
class Game {

    //Disse skal main og andre ha tilgang på
public:
    Game();
    void run();

    //Disse er interne for game
private:
    //Hver instans av klassen Game har sitt eget vindu:
    sf::RenderWindow window;

    Ball ball;

    Paddle leftPaddle;
    Paddle rightPaddle;

    int leftScore = 0;
    int rightScore = 0;

    //Tekst
    sf::Font font;
    sf::Text scoreText;

    //Lyd
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

    sf::SoundBuffer winBuffer;
    sf::Sound winSound;

    bool gameOver = false;

    void processEvents();
    void update(float dt);
    void render();
    void resetBall();
    void centerText(sf::Text& text);
};


#endif //ASSIGNMENT_3_1_GAME_H