//
// Created by rivru on 13.02.2026.
//

#ifndef ASSIGNMENT_3_1_BALL_H
#define ASSIGNMENT_3_1_BALL_H
#include "entity.h"
#include "constants.h"


class Ball : public Entity{
    public:
    Ball(float radius, sf::Vector2f startPos);

    //Ball sin implementasjon av Entity::upate
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect getBounds() const override;

    void setVelocity(sf::Vector2f vel);
    sf::Vector2f getVelocity() const;

    void setPositionManually();

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};


#endif //ASSIGNMENT_3_1_BALL_H