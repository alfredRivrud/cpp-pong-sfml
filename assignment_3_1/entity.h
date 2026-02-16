//
// Created by rivru on 13.02.2026.
//

#ifndef ASSIGNMENT_3_1_ENTITY_H
#define ASSIGNMENT_3_1_ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
    public:
    //Destruktør
    virtual ~Entity() = default;

    //Setter 3 abstrakte funksjoner til 0, de skal bare arves
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
};

#endif //ASSIGNMENT_3_1_ENTITY_H