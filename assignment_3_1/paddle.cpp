//
// Created by rivru on 13.02.2026.
//

#include <SFML/Graphics.hpp>

//For clamp
#include <algorithm>

#include "paddle.h"
#include "constants.h"

Paddle::Paddle(sf::Vector2f size, sf::Vector2f startPos, float speed)
    : shape(size), speed(speed), direction(0.f)
{
    shape.setPosition(startPos);
    shape.setFillColor(sf::Color::White);
}

void Paddle::setDirection(float dir) {
direction = dir;
}

void Paddle::update(float dt) {
    //Beveger seg kun i Y. Move tar inn 1 parameter, så setter en vektor.
    shape.move(sf::Vector2f(0.f, direction * speed * dt));

    //Stopp bevegelse ut av skjermen
    sf::FloatRect bounds = shape.getGlobalBounds();

    if (bounds.position.y < 0.f)
        shape.setPosition({bounds.position.x, 0.f});
    else if (bounds.position.y + bounds.size.y > WINDOW_HEIGHT)
        shape.setPosition({bounds.position.x, WINDOW_HEIGHT - bounds.size.y});
}

//Funksjon for AI motstander
void Paddle::updateAI(float dt, sf::FloatRect ballPos) {
    sf::FloatRect bounds = shape.getGlobalBounds();

    // Finn sentrene
    sf::FloatRect padB = shape.getGlobalBounds();
    float paddleCenterY = padB.position.y + padB.size.y * 0.5f;
    float ballCenterY   = ballPos.position.y + ballPos.size.y * 0.5f;

    // Hvor mye vi "ønsker" å flytte denne framen
    float diff = ballCenterY - paddleCenterY;

    // Maks flytt per frame (AI-hastighet)
    float aiSpeed = 100.f;              // juster for vanskelighetsgrad
    float maxStep = aiSpeed * dt;

    // Begrens bevegelsen per frame
    float step = std::clamp(diff, -maxStep, +maxStep);

    //Stopp bevegelse ut av skjermen
    if (bounds.position.y <= 0.f && step < 0.f)
step = 0.f;
    else if (bounds.position.y + bounds.size.y >= WINDOW_HEIGHT && step >0.f )
step = 0.f;

    shape.move({0.f, step});
}


void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

//Får midten. Høyde delt på 2.
float Paddle::getCenterY() const {
    return shape.getPosition().y + shape.getSize().y * 0.5f;
}
