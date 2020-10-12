#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QTime>
#include <QString>
#include "object.h"
#include <QFile>

constexpr qint16 FIELD_SIZE_Y_BOTTOM{540};
constexpr qint16 FIELD_SIZE_Y_TOP{35};
constexpr qint16 FIELD_SIZE_X{480};

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine();
    Q_INVOKABLE void but_click();
    Q_INVOKABLE void restart();
    Q_INVOKABLE QString get_highScore() const;
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
    std::uniform_int_distribution<qint16> blockRandomY;
    std::uniform_int_distribution<qint16> blockRandomX1;
    std::uniform_int_distribution<qint16> blockRandomX2;
    std::uniform_int_distribution<qint16> blockRandomX3;
    void die();
    void blocksToStartPosition();

signals:
    void sendToQml(qint16 birdY);
    void sendToQmlMove(qint16 pic1X, qint16 pic1Y, qint16 pic2X, qint16 pic2Y, qint16 pic3X, qint16 pic3Y);
    void gameOver(QString newHighscore);
    void splash();
    void newScore(QString new_score);
    void restartQml();

public slots:
    void updateTime();
};

