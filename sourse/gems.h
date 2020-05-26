#ifndef GEMS_H
#define GEMS_H
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QPainter>

class Meditator;

class Gem : public QPushButton {

    Q_OBJECT

public:
    int m_i = 0;
    int m_j = 0;
    int m_color = 0;
   // bool m_isBonus;
    QImage m_type;

    Gem(int i, int j, QWidget *parent = 0);
    ~Gem();

    void removeGem();
    void changeGem();

    virtual void paintEvent(QPaintEvent *) override;
    friend bool operator==(const Gem &gem1, const Gem &gem2);    

protected:
    QVector<QImage> all_types;
    static const int GEMS_TYPE = 5;
    static const int G_WIDTH = 55;
    static const int G_HEIGHT = 55;

    virtual void loadImages();

    friend class Meditator;
};
#endif // !GEMS_H