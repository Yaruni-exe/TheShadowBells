#ifndef PLAYERCLASSONE_H
#define PLAYERCLASSONE_H



#include "PlayerBaseClass.h"
#include "Animations.h"
#include "RepeatAnimation.h"

class Player_Class_One : public Player_Base_Class
{
private:
    Vector2 size{20,32};


public:
    RepeatAnimation test_animation{size,"assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Front.png",7,7};
    Player_Class_One(Vector2 start_Position,Object_Manager& om);
    ~Player_Class_One();
    void Draw() override;

};


#endif //PLAYERCLASSONE_H