#pragma once
#include <QtGlobal>
#include <random>
#include <chrono>

constexpr qint16 BIRDWIDTH{50};
constexpr qint16 BIRDHEIGHT{35};
constexpr qint16 BLOCKWIDTH{75};
constexpr qint16 LEVEL1X{4};
constexpr qint16 START_Y{350};
constexpr qint16 START_X{110};
constexpr qint16 DISTANCE_BETWEEN_BLOCKS{300};
constexpr qint16 DELTA{20};
constexpr qint16 BLOCK_MIN_Y{70};
constexpr qint16 BLOCK_MAX_Y{330};

class Object
{
public:
    Object(){}
    Object(qint16 xLeft, qint16 yOfTop);
    friend bool collision(Object&, Object&);
    qint16 get_xLeft();
    qint16 get_yOfTop();

protected:
    qint16 xLeft;
    qint16 xRight;
    qint16 yOfTop;
    qint16 yOfBottom;
};

class Blocks : public Object
{
public:
    Blocks(){}
    Blocks(qint16 xLeft, qint16 yOfTop);
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

