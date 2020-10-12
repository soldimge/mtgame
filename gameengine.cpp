#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) : QObject{parent},
                                          tmr{new QTimer()},
                                          score{0},
                                          bird{},
                                          gameover{true},
                                          datafile{"highscore.txt"},
                                          blockRandomY{BLOCK_MIN_Y, BLOCK_MAX_Y},
                                          blockRandomX1{FIELD_SIZE_X, FIELD_SIZE_X + DELTA},
                                          blockRandomX2{FIELD_SIZE_X + DISTANCE_BETWEEN_BLOCKS, FIELD_SIZE_X + DISTANCE_BETWEEN_BLOCKS + DELTA},
                                          blockRandomX3{FIELD_SIZE_X + 2 * DISTANCE_BETWEEN_BLOCKS, FIELD_SIZE_X + 2 * DISTANCE_BETWEEN_BLOCKS + DELTA}
{
    tmr->setInterval(TIMERINTERVAL);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    datafile.open(QIODevice::ReadOnly | QIODevice::Text);
    highscore = datafile.readLine().toInt();
    datafile.close();
    blocksToStartPosition();
}

GameEngine::~GameEngine()
{
    delete tmr;
    datafile.close();
}

void pause(qint32 ms)
{
    QTime pauseEnd = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < pauseEnd)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameEngine::blocksToStartPosition()
{
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    block1 = Blocks(blockRandomX1(rng), blockRandomY(rng));
    block2 = Blocks(blockRandomX2(rng), blockRandomY(rng));
    block3 = Blocks(blockRandomX3(rng), blockRandomY(rng));
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
    blocksToStartPosition();
    bird = Bird();
    emit sendToQml(bird.get_yOfTop());
    emit sendToQmlMove(block1.get_xLeft(), block1.get_yOfTop(), block2.get_xLeft(), block2.get_yOfTop(), block3.get_xLeft(), block3.get_yOfTop());
    emit restartQml();
}

QString GameEngine::get_highScore() const
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
        block1.renew(blockRandomY, blockRandomX2);
    else if (block2.outOfField())
        block2.renew(blockRandomY, blockRandomX2);
    else if (block3.outOfField())
        block3.renew(blockRandomY, blockRandomX2);
}

void GameEngine::but_click()
{
    if (!gameover)
    {
        bird.up();
        emit sendToQml(bird.get_yOfTop());
    }
}
