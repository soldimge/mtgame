#include "blocks.h"

Object::Object(int xLeft, int yOfTop): xLeft(xLeft),
                                       xRight(xLeft + BLOCKWIDTH),
                                       yOfTop(yOfTop),
                                       yOfBottom(yOfTop + BIRDHEIGHT * LEVEL1X)
{

}

Bird::Bird()
{
    xLeft = START_X;
    xRight = xLeft + BIRDWIDTH;
    yOfTop = START_Y;
    yOfBottom = START_Y + BIRDHEIGHT;
}

int Object::get_xLeft(){ return xLeft; }
int Object::get_yOfTop(){ return yOfTop; }

Blocks::Blocks(int xLeft, int yOfTop) : Object(xLeft, yOfTop),
                                        skipped(false)
{

}

bool Blocks::outOfField()
{
    return xRight < 0 ? true : false;
}

void Blocks::renew()
{
//    std::random_device rd;
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> uidx(780, 800);
    std::uniform_int_distribution<int> uidy(70, 330);
    *this = Blocks(uidx(rng), uidy(rng));
}

bool collision(Object& bird, Object& block)
{
    return (bird.xLeft <= block.xRight &&
            bird.xRight >= block.xLeft &&
           (bird.yOfTop <= block.yOfTop || bird.yOfBottom >= block.yOfBottom)) ? true : false;
}

bool Blocks::passed(/*Object& bird, Blocks& block*/)
{
    if(START_X > /*block.*/xRight && !/*block.*/skipped /*&& !block.skipped*/)
    {
        /*block.*/skipped = true;
        return true;
    }
    else
        return false;
}

void move(Blocks& block1, Blocks& block2, Blocks& block3)
{
    block1.xLeft -= 2;
    block1.xRight -= 2;
    block2.xLeft -= 2;
    block2.xRight -= 2;
    block3.xLeft -= 2;
    block3.xRight -= 2;
}

void Bird::down()
{
    yOfTop += 2;
    yOfBottom += 2;
}

void Bird::up()
{
    yOfTop -= 60;
    yOfBottom -= 60;
}


