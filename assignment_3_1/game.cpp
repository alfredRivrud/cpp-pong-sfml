//
// Created by rivru on 13.02.2026.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include <iostream>

//Trengs for clamp
#include <algorithm>

//Trengs for å generere startPos
#include <random>

#include "game.h"
#include "ball.h"
#include "paddle.h"

#include "constants.h"


Game::Game()
//Oppretter vinduet
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pong"),
      //Initialiserer ball i midten av skjermen
      ball(10.f, {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}),
      //Initialiserer paddle
      leftPaddle({50.f, 200.f}, {0.f, 500.f}, 500.f),
      rightPaddle({50.f, 200.f}, {1450.f, 500.f}, 500.f),
      scoreText(font),
      hitSound(hitBuffer),
      winSound(winBuffer) {
    //Her setter vi lik hastighet for alle skjermer. Vi låser spillet til 60hz.
    window.setFramerateLimit(60);

    //Gir ball en tilfeldig startretning
    resetBall();

    //Tekst
    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Failed to load font\n";
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(48);
    scoreText.setFillColor(sf::Color::White);

    scoreText.setPosition({WINDOW_WIDTH / 2.f - 40.f, 20.f});

    if (!hitBuffer.loadFromFile("sound.wav")) {
        std::cout << "Failed to load sound.wav\n";
    }
    hitSound.setBuffer(hitBuffer);

    if (!winBuffer.loadFromFile("win.wav")) {
        std::cout << "Failed to load win.wav\n";
    }
    winSound.setBuffer(winBuffer);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

//Funksjon til å sette tilfeldig startretning
void Game::resetBall() {
    //Midten av skjermen:
    ball.setPositionManually();

    //Lager en tilfeldig-generator rng med generator mt og med seed random_device
    static std::mt19937 rng{std::random_device{}()};

    //Gir fordeling: enten 0 eller 1
    std::uniform_int_distribution<int> sideDist(0, 1);

    //Retningsvariabel, enten 0 eller 1. Hvis rng har gitt 0, sett retningsvariabel dirX til -1.f, hvis ikke sett til 1.f
    float dirX = (sideDist(rng) == 0) ? -1.f : 1.f;

    //Gir distribusjon for y, vinkel
    std::uniform_real_distribution<float> yDist(-0.7f, 0.7f);
    float y = yDist(rng);

    float speed = 300.f;

    // Lager en vektor med variablene ovenfor som brukes til setVelocity()
    sf::Vector2f v;
    v.x = dirX * speed;
    v.y = y * speed;

    ball.setVelocity(v);
}

void Game::processEvents() {
    //Close window: exit
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::update(float dt) {
    if (gameOver)
        return;


    //Score
    scoreText.setString(std::to_string(leftScore) + " : " + std::to_string(rightScore));

    //Left layer controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        leftPaddle.setDirection(-1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        leftPaddle.setDirection(1);
    else
        leftPaddle.setDirection(0);


    //Oppdater objektene
    leftPaddle.update(dt);
    ball.update(dt);


    //Initialiser variabler til bruk i kollisjonssteg
    sf::FloatRect ballBounds = ball.getBounds();
    sf::FloatRect leftPaddleBounds = leftPaddle.getBounds();
    sf::FloatRect rightPaddleBounds = rightPaddle.getBounds();

    //Oppdaterer AI
    rightPaddle.updateAI(dt, ballBounds);

    //Håndtere kollisjon av ball og venstre paddle
    if (ballBounds.findIntersection(leftPaddleBounds)) {
        hitSound.play();
        sf::Vector2f vel = ball.getVelocity();
        vel.x = -vel.x;

        //Vinkel skal også endres litt:

        //Først finner vi ball og paddle sentrum
        float ballCenterY = ballBounds.position.y + ballBounds.size.y * 0.5f;
        float paddleCenterY = leftPaddleBounds.position.y + leftPaddleBounds.size.y * 0.5f;

        //Avstand fra treff til senter. Clamp begrenser verdiene.
        float offset = (ballCenterY - paddleCenterY) / (leftPaddleBounds.size.y * 0.5f);
        offset = std::clamp(offset, -1.f, 1.f);

        //Y-hastighet gis basert på treffpunkt. Lenger fra senter gir mer vinkel
        float maxY = 300.f;
        vel.y = offset * maxY;

        //Øke farten litt
        vel.x *= 1.15f;
        vel.y *= 1.15f;

        ball.setVelocity(vel);
    }

    //Håndtere kollisjon av ball og høyre paddle
    else if (ballBounds.findIntersection(rightPaddleBounds)) {
        sf::Vector2f vel = ball.getVelocity();
        vel.x = -vel.x;
        hitSound.play();

        float ballCenterY = ballBounds.position.y + ballBounds.size.y * 0.5f;
        float paddleCenterY = rightPaddleBounds.position.y + rightPaddleBounds.size.y * 0.5f;

        float offset = (ballCenterY - paddleCenterY) / (rightPaddleBounds.size.y * 0.5f);
        offset = std::clamp(offset, -1.f, 1.f);

        float maxY = 300.f;
        vel.y = offset * maxY;

        vel.x *= 1.15f;
        vel.y *= 1.15f;

        ball.setVelocity(vel);
    }

    //Håndtere ball ut på venstre og høyre side
    if (ballBounds.position.x < 0.f) {
        rightScore++;

        if (rightScore == WINNING_SCORE) {
            winSound.play();
            gameOver = true;
            scoreText.setString("Right player won!");
            centerText(scoreText);
        } else {
            resetBall();
        }
    } else if (ballBounds.position.x + ballBounds.size.x > WINDOW_WIDTH) {
        leftScore++;
        if (leftScore == WINNING_SCORE) {
            winSound.play();
            gameOver = true;
            scoreText.setString("Left player won!");
            centerText(scoreText);
        } else {
            resetBall();
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    //Låser hz til 60.
    window.setFramerateLimit(60);

    ball.draw(window);
    leftPaddle.draw(window);
    rightPaddle.draw(window);
    window.draw(scoreText);

    //Tegner på vindu.
    window.display();
}

//Funksjon for å sentrere tekst
void Game::centerText(sf::Text &text) {
    sf::FloatRect bounds = text.getLocalBounds();

    float x = (WINDOW_WIDTH / 2.f) - (bounds.size.x / 2.f);
    float y = text.getPosition().y; // behold samme høyde

    text.setPosition({x, y});
}
