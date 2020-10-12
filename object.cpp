#include "object.h"

Object::Object(qint16 xLeft, qint16 yOfTop): xLeft{xLeft},
                                             xRight(xLeft + BLOCKWIDTH),
                                             yOfTop{yOfTop},
                                             yOfBottom(yOfTop + BIRDHEIGHT * LEVEL1X)
{

}

Bird::Bird() : time{STIME}
{
    xLeft = START_X;
    xRight = xLeft + BIRDWIDTH;
    yOfTop = START_Y;
    yOfBottom = START_Y + BIRDHEIGHT;
}

qint16 Object::get_xLeft() const { return xLeft; }
qint16 Object::get_yOfTop() const { return yOfTop; }

Blocks::Blocks(qint16 xLeft, qint16 yOfTop) : Object(xLeft, yOfTop),
                                              skipped(false)
{

}

bool Blocks::outOfField() const
{
    return xRight < 0 ? true : false;
}

void Blocks::renew(std::uniform_int_distribution<qint16>& blockRandomY, std::uniform_int_distribution<qint16>& blockRandomX2)
{
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    *this = Blocks(blockRandomX2(rng), blockRandomY(rng));
}

bool collision(Object& bird, Object& block)
{
    return (bird.xLeft <= block.xRight &&
            bird.xRight >= block.xLeft &&
           (bird.yOfTop <= block.yOfTop || bird.yOfBottom >= block.yOfBottom)) ? true : false;
}

bool Blocks::passed()
{
    if(START_X > xRight && !skipped)
    {
        skipped = true;
        return true;
    }
    else
        return false;
}

void move(Blocks& block1, Blocks& block2, Blocks& block3)
{
    block1.xLeft -= BLOCKSTEP;
    block1.xRight -= BLOCKSTEP;
    block2.xLeft -= BLOCKSTEP;
    block2.xRight -= BLOCKSTEP;
    block3.xLeft -= BLOCKSTEP;
    block3.xRight -= BLOCKSTEP;
}

void Bird::down()
{   
    time += TIMERINTERVAL;
    yOfTop = yOfTop + (GRAVITY * time * time)/2000000;
    yOfBottom = yOfBottom + (GRAVITY * time * time)/2000000;
}

void Bird::up()
{
    time = STIME;
    yOfTop -= BIRDUPSTEP;
    yOfBottom -= BIRDUPSTEP;
}


