#ifndef OOP_DYNAMICOBJECT_H
#define OOP_DYNAMICOBJECT_H

#include "Object.h"
#include "Text.h"

class DynamicObject : public Object {
protected:
    Text hp_text;
    unsigned int hp;
    float speed;

    void print(std::ostream& os) const override;

public:
    DynamicObject();
    DynamicObject(sf::Vector2f position_, sf::Vector2f size_, unsigned int hp_, float speed_);
    DynamicObject(const DynamicObject& other);
    DynamicObject& operator= (const DynamicObject& other);

    void showHP(sf::RenderWindow* window);

    unsigned int getHp() const;
    void setHp(unsigned int hp_);
    //float getSpeed() const {return speed;}
    //void setSpeed(float speed_) {speed = speed_;}

    bool checkHP() const;

    ~DynamicObject() override;
};

#endif //OOP_DYNAMICOBJECT_H
