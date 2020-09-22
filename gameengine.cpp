#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) : QObject(parent),
                                          tmr(new QTimer()),
                                          score(0),
//                                          block1(BLOCK1_X, BLOCK1_Y),
//                                          block2(BLOCK2_X, BLOCK2_Y),
//                                          block3(BLOCK3_X, BLOCK3_Y),
                                          bird(),
                                          gameover(true),
                                          datafile("highscore.txt")
{
    tmr->setInterval(15);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    datafile.open(QIODevice::ReadOnly);
//    QString data = datafile.readLine();
    highscore = datafile.readLine().toInt();
    datafile.close();
    blocksToStartPosition();
//    this->start();
}

GameEngine::~GameEngine()
{
    delete tmr;
    datafile.close();
}

void pause(qint32 ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameEngine::blocksToStartPosition()
{
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<int> uidx1(480, 500);
    std::uniform_int_distribution<int> uidy(70, 330);
    block1 = Blocks(uidx1(rng), uidy(rng));

    std::uniform_int_distribution<int> uidx2(780, 800);
    block2 = Blocks(uidx2(rng), uidy(rng));

    std::uniform_int_distribution<int> uidx3(1080, 1100);
    block3 = Blocks(uidx3(rng), uidy(rng));
}

void GameEngine::die()
{
    gameover = true;
    tmr->stop();
    emit splash();
    pause(200);
    emit splash();
    while (bird.get_yOfTop() <= FIELD_SIZE_Y_BOTTOM)
    {
        bird.down();
        emit sendToQml(bird.get_yOfTop());
        pause(5);
    }
    pause(200);
    QString newHighscore{""};
    if (score > highscore)
    {
        highscore = score;
        datafile.open(QIODevice::WriteOnly | QIODevice::Text);
        datafile.write(QString::number(score).toUtf8());
        datafile.close();
        newHighscore = " NEW!";
        emit gameOver(" NEW!");
    }
    emit gameOver(newHighscore);
}

void GameEngine::start()
{
    score = 0;
    gameover = false;
    emit newScore(QString::number(score));
    tmr->start();
}

void GameEngine::restart()
{
//    block1 = Blocks(BLOCK1_X, BLOCK1_Y);
//    block2 = Blocks(BLOCK2_X, BLOCK2_Y);
//    block3 = Blocks(BLOCK3_X, BLOCK3_Y);
    blocksToStartPosition();
    bird = Bird();
    emit sendToQml(bird.get_yOfTop());
    emit sendToQmlMove(block1.get_xLeft(), block1.get_yOfTop(), block2.get_xLeft(), block2.get_yOfTop(), block3.get_xLeft(), block3.get_yOfTop());
    emit restartQml();
//    this->start();
}

QString GameEngine::get_highScore()
{
    return QString::number(highscore);
}

void GameEngine::updateTime()
{
    if (collision(bird, block1) || collision(bird, block2) || collision(bird, block3) || bird.get_yOfTop() >= FIELD_SIZE_Y_BOTTOM || bird.get_yOfTop() <= FIELD_SIZE_Y_TOP)
    {
        die();
    }
    else
    {
        bird.down();
        move(block1, block2, block3);
        emit sendToQml(bird.get_yOfTop());
        emit sendToQmlMove(block1.get_xLeft(), block1.get_yOfTop(), block2.get_xLeft(), block2.get_yOfTop(), block3.get_xLeft(), block3.get_yOfTop());
    }
    if (block1.passed() || block2.passed() || block3.passed())
    {
        score++;
        emit newScore(QString::number(score));
    }
    if (block1.outOfField())
        block1.renew();
    else if (block2.outOfField())
        block2.renew();
    else if (block3.outOfField())
        block3.renew();
}

void GameEngine::but_click()
{
    if (/*bird.get_yOfTop() > FIELD_SIZE_Y_TOP && */!gameover)
    {
        bird.up();
        emit sendToQml(bird.get_yOfTop());
    }
}
