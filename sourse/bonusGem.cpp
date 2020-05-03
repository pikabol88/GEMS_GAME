#include"bonusGem.h"
#include <QMessageBox>
#include "warning.h"

BonusGem::BonusGem(bonus_t type, int i, int j, QWidget *parent) : Gem( i, j, parent),m_bonusType(type) {}

BonusGem::BonusGem(Gem *gem):Gem(gem->m_i,gem->m_j, 0) {
    if (all_types.size() == 0) {
        loadImages();
    }
    m_i = gem->m_i;
    m_j = gem->m_j;
    int type = rand() % all_types.size();
    m_type = all_types.at(type);
    if (type == 1) {
        m_bonusType = BOMB;
    } else
        m_bonusType = LINE_EXPLOSION;    
}

void BonusGem::loadImages() {
    QImage tmp;
    tmp.load("img\\img_mask.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
    tmp.load("img\\img_dez.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
}

void BonusGem::setRandomType() {
    int size = all_types.size();
    int type = rand() % size;
    m_type = all_types.at(type);
    if (type == 1) {
        m_bonusType = BOMB;
    } else
        m_bonusType = LINE_EXPLOSION;
}

BonusGem::~BonusGem() {}