#pragma once

#define BIRDWIDTH 50
#define BIRDHEIGHT 35
#define BLOCKWIDTH 75
#define LEVEL1X 4
#define START_Y 350
#define START_X 110

//#define BLOCK1_Y 200
//#define BLOCK1_X 480
//#define BLOCK2_Y 300
//#define BLOCK2_X 780
//#define BLOCK3_Y 250
//#define BLOCK3_X 1080

#include <random>
#include <chrono>

class Object
{
public:
    Object(){}
    Object(int xLeft, int yOfTop);
    friend bool collision(Object&, Object&);
    int get_xLeft();
    int get_yOfTop();

protected:
    int xLeft;
    int xRight;
    int yOfTop;
    int yOfBottom;
};


class Blocks : public Object
{
public:
    Blocks(){}
    Blocks(int xLeft, int yOfTop);
    bool outOfField();
    void renew();
    bool passed();
    friend void move(Blocks&, Blocks&, Blocks&);

private:
    bool skipped;
};

class Bird : public Object
{
 public:
    Bird();
    void up();
    void down();
};

