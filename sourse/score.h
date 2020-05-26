#ifndef SCORE_H
#define SCORE_H
#pragma once
#include <QLCDNumber>
#include <QLabel>
#include <QVBoxLayout>

//! класс отображения цифровых часов
class Score :public QLCDNumber {

    Q_OBJECT

public:
    Score(QWidget *parent = 0);
    ~Score();
    int m_score = 0;
    QVBoxLayout *vbox = nullptr;
    QLabel *label = nullptr;
    QString *str = nullptr;

public slots:
    void updateScore(int points);
};
#endif // !SCORE_H