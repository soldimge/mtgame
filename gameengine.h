#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QTime>
#include <QString>
#include "blocks.h"
#include <QFile>
//#include <QTextCodec>
//#include <QTextStream>

#define FIELD_SIZE_Y_BOTTOM 540
#define FIELD_SIZE_Y_TOP 35

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();
    Q_INVOKABLE void but_click();
    Q_INVOKABLE void restart();
    Q_INVOKABLE QString get_highScore();
    Q_INVOKABLE void start();

private:
    QTimer* tmr;
    qint32 score;
    Blocks block1;
    Blocks block2;
    Blocks block3;
    Bird bird;
    bool gameover;
    qint32 highscore;
    QFile datafile;
    void die();
    void blocksToStartPosition();

signals:
    void sendToQml(qint32 birdY);
    void sendToQmlMove(qint32 pic1X, qint32 pic1Y, qint32 pic2X, qint32 pic2Y, qint32 pic3X, qint32 pic3Y);
    void gameOver(QString newHighscore);
    void splash();
    void newScore(QString new_score);
    void restartQml();

public slots:
    void updateTime();
};

