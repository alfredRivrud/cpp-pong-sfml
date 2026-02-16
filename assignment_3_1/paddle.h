//
// Created by rivru on 13.02.2026.
//

#ifndef ASSIGNMENT_3_1_PADDLE_H
#define ASSIGNMENT_3_1_PADDLE_H

#include "entity.h"

class Paddle : public Entity{
    public:
    Paddle(sf::Vector2f size, sf::Vector2f startPos, float speed);

    void setDirection(float dir);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect getBounds() const override;


    void updateAI(float dt, sf::FloatRect ballPos);

    sf::Vector2f getPosition() const;
    float getCenterY() const;

    private:
    float speed;
    float direction;
    sf::RectangleShape shape;
};


#endif //ASSIGNMENT_3_1_PADDLE_H