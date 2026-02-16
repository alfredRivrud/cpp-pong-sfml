//
// Created by rivru on 13.02.2026.
//

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "constants.h"

Ball::Ball(float radius, sf::Vector2f startPos)
    : shape(radius), velocity(200.f, 200.f) {
    shape.setPosition(startPos);
    shape.setFillColor(sf::Color::White);
}

void Ball::update(float dt) {
    shape.move(velocity * dt);

    //Hindre bevegelse utenfor vindu
    sf::FloatRect bounds = shape.getGlobalBounds();

    if (bounds.position.y < 0.f)
        velocity.y = -velocity.y;
    else if (bounds.position.y + bounds.size.y > WINDOW_HEIGHT)
        velocity.y = -velocity.y;

}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::setVelocity(sf::Vector2f vel) {
velocity = vel;
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

void Ball::setPositionManually() {
    shape.setPosition({WINDOW_WIDTH/ 2.f, WINDOW_HEIGHT/2.f});
}