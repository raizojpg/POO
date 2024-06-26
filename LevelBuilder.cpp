#include "LevelBuilder.h"

std::vector<std::shared_ptr<Text>> LevelBuilder::init_instructions() {
    std::vector<std::shared_ptr<Text>> instructions;
    std::shared_ptr<Text> text_ptr;
    text_ptr = std::make_shared<Text>(Text{"Move with WASD", {400,-50}});
    instructions.push_back(text_ptr);
    text_ptr = std::make_shared<Text>(Text{"Press E to attack (punch) ",{350,80}});
    instructions.push_back(text_ptr);
    text_ptr = std::make_shared<Text>(Text{"140 years old kung fu master ",{-400,1250}});
    instructions.push_back(text_ptr);
    return instructions;
}

std::vector<std::shared_ptr<Platform>> LevelBuilder::init_platforms(unsigned int durability) {
    std::vector<std::shared_ptr<Platform>> platforms;
    std::shared_ptr<Platform> ptr;

    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{100, 400}, {200, 50}, durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{300, 400}, {200, 50}, durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{500, 20}, {200, 50}, durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{100, 150}, {200, 50}, durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{200, 600}, {200, 50}, durability});
    platforms.push_back(ptr);

    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{-500,-500},{5000,20},10*durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{1500,-500},{20,5000},10*durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{1500,1500},{5000,20},10*durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<StaticPlatform>(StaticPlatform{{-500,1500},{20,5000},10*durability});
    platforms.push_back(ptr);

    ptr = std::make_shared<MovingPlatform>(MovingPlatform{{1200, 500}, {20, 700}, durability, 1, 400, true});
    platforms.push_back(ptr);
    ptr = std::make_shared<MovingPlatform>(MovingPlatform{{950, 700}, {800, 20}, durability, 1, 400, false});
    platforms.push_back(ptr);
    ptr = std::make_shared<MovingPlatform>(MovingPlatform{{1200, 1000}, {20, 700}, durability, 1, 400, true});
    platforms.push_back(ptr);
    ptr = std::make_shared<MovingPlatform>(MovingPlatform{{950, 1000}, {800, 20}, durability, 1, 400, false});
    platforms.push_back(ptr);

    ptr = std::make_shared<RotatingPlatform>(RotatingPlatform{{-200,290},{150,150},durability});
    platforms.push_back(ptr);
    ptr = std::make_shared<RotatingPlatform>(RotatingPlatform{{-200,530},{150,150},durability});
    platforms.push_back(ptr);

    return platforms;
}

std::vector<std::shared_ptr<Object>> LevelBuilder::init_objects(int hp) {
    std::vector<std::shared_ptr<Object>> dynamicObjects;
    std::shared_ptr<Object> ptr;
    ptr = std::make_shared<DynamicObject>(DynamicObject{{100,300},{100,100},hp,5});
    dynamicObjects.push_back(ptr);
    ptr = std::make_shared<DynamicObject>(DynamicObject{{100,500},{100,100},hp,5});
    dynamicObjects.push_back(ptr);
    ptr = std::make_shared<DynamicObject>(DynamicObject{{400,300},{100,100},hp,5});
    dynamicObjects.push_back(ptr);
    ptr = std::make_shared<DynamicObject>(DynamicObject{{300,500},{100,100},hp,5});
    dynamicObjects.push_back(ptr);

    return dynamicObjects;
}

std::vector<std::shared_ptr<Enemy>> LevelBuilder::init_enemy(int hp) {
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Enemy> enemy_ptr;
    Sword swd = Sword{25,100};
    Gun gun = Gun{100,100};
    Spear spr = Spear{100,100};

    enemy_ptr = std::make_shared<Enemy>(Enemy{{500,400},{120,120},hp,1,400});
    enemies.push_back(enemy_ptr);
    enemy_ptr = std::make_shared<Enemy>(Enemy{{500,700},{120,120},hp,1,400});
    enemies.push_back(enemy_ptr);

    Enemy e1 = Enemy{{800,400},{100,100},hp,1,800};
    e1.addWeapon(gun);
    enemy_ptr = std::make_shared<Enemy>(e1);
    enemies.push_back(enemy_ptr);

    Enemy e2 = Enemy{{800,700},{100,100},hp,1,800};
    e2.addWeapon(gun);
    enemy_ptr = std::make_shared<Enemy>(e2);
    enemies.push_back(enemy_ptr);

    Enemy e3 = Enemy{{900,900},{100,100},hp,2,400};
    e3.addWeapon(swd);
    enemy_ptr = std::make_shared<Enemy>(e3);
    enemies.push_back(enemy_ptr);

    Enemy e4 = Enemy{{600,1000},{100,100},hp,2,400};
    e4.addWeapon(swd);
    enemy_ptr = std::make_shared<Enemy>(e4);
    enemies.push_back(enemy_ptr);

    Enemy e5 = Enemy{{-450,1450},{100,100},2*hp,1,0};
    e5.addWeapon(spr);
    enemy_ptr = std::make_shared<Enemy>(e5);
    enemies.push_back(enemy_ptr);

    return enemies;
}

LevelBuilder::LevelBuilder() : level() {
    std::cout<<"Building level\n";
}

LevelBuilder &LevelBuilder::add_player(Player *player) {
    level.setPlayer(player);
    return *this;
}

LevelBuilder &LevelBuilder::build_instructions() {
    level.setInstructions(init_instructions());
    return *this;
}

LevelBuilder &LevelBuilder::build_platforms(unsigned int durability) {
    level.setPlatforms(init_platforms(durability));
    return *this;
}

LevelBuilder &LevelBuilder::build_objects(int hp) {
    level.setDynamicObjects(init_objects(hp));
    return *this;
}

LevelBuilder &LevelBuilder::build_enemy(int hp) {
    level.setEnemies(init_enemy(hp));
    return *this;
}

Level LevelBuilder::build() {
    checkPlayer(level.getPlayer());
    checkCollection(level.getPlatforms(),"Platform");
    checkCollection(level.getDynamicObjects(),"Object");
    checkCollection(level.getEnemies(),"Enemy");
    return level;
}

void LevelBuilder::checkPlayer(const Player *player) {
    if(player==nullptr){
        throw LevelError("Can't build the level without a player !\n");
    }
}

void LevelBuilder::checkCollection(const auto &collection, const std::string &name) {
    if(collection.size()==0){
        std::string msg = name + "Collection Incomplete\n";
        throw LevelError(msg);
    }
}

