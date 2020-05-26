#include"bonusGem.h"

BonusGem::BonusGem(bonus_t type, int i, int j, QWidget *parent) : Gem( i, j, parent),m_color(type) {}

BonusGem::BonusGem(Gem *gem):Gem(gem->m_i,gem->m_j, 0) {
    if (all_types.size() == 0) {
        loadImages();
    }
    m_i = gem->m_i;
    m_j = gem->m_j;
    int type = rand() % all_types.size();
    m_type = all_types.at(type);
    if (type == 1) {
        m_color = BOMB;
    } else
        m_color = LINE_EXPLOSION;    
}

void BonusGem::loadImages() {
    QImage tmp;
    tmp.load("img_mask.png");
    all_types.append(tmp);
    tmp.load("img_dez.png");
    all_types.append(tmp);
}

void BonusGem::setRandomType() {
    int size = all_types.size();
    int type = rand() % size;
    m_type = all_types.at(type);
    if (type == 1) {
        m_color = BOMB;
    } else
        m_color = LINE_EXPLOSION;
}

BonusGem::~BonusGem() {}