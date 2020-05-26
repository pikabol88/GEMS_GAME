#ifndef BONUSGEM_H
#define BONUSGEM_H
#pragma once
#include "gems.h"

class BonusGem :public Gem {

    Q_OBJECT

private:

    typedef enum bonus_t {
        LINE_EXPLOSION = 1,
        BOMB = 2,
        VOID = 3
    } bonus_t;

    void loadImages() override;
    QList<bonus_t>all_bones = { LINE_EXPLOSION,BOMB,VOID };
   

public:
    QVector<QImage> all_types;
    BonusGem(bonus_t type, int i, int j, QWidget *parent);
    BonusGem(Gem *gem);
    ~BonusGem();
    bonus_t m_color;    

    void setRandomType();
};

#endif // !BONUSGEM_H
