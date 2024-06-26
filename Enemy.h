#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include <string>
#include "DynamicObject.h"
#include "Controllable.h"
#include "Gun.h"
#include "Sword.h"
#include "Spear.h"

class Enemy : public DynamicObject, public Controllable{
private:
    static Text ct_text;
    static int counter;
    int steps;
    int maxSteps;
public:
    Enemy(sf::Vector2f position_, sf::Vector2f size_, int hp_, float speed_, int maxSteps_);
    Enemy(const Enemy& other);
    Enemy& operator= (const Enemy& other);

    static void updateCounter(sf::RenderWindow& window);
    static int getCounter();

    void move() override;
    void addWeapon(Weapon& wpn_) override;
    void possibleAttack(DynamicObject& obj) override;
    void draw(sf::RenderWindow& window) override;

    ~Enemy() override;
};


#endif //OOP_ENEMY_H
