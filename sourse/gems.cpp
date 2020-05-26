#include "gems.h"

Gem::Gem(int i, int j, QWidget *parent) : QPushButton(parent), m_i(i), m_j(j) {
    if (all_types.size() == 0) {
        loadImages();
    }
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFixedSize(G_WIDTH, G_HEIGHT);
    int type = rand() % GEMS_TYPE;
    m_type = all_types.at(type);
    m_color = type;
}

bool operator==(const Gem &gem1, const Gem &gem2) {
    return (gem1.m_type == gem2.m_type);
}

void Gem::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);
    QPainter p(this);
    p.setBrush(QBrush(this->m_color, Qt::SolidPattern));
    p.drawImage(2, 2, m_type);
    return;
}

void Gem::changeGem() {
    int type = rand() % GEMS_TYPE;
    m_type = all_types.at(type);
    m_color = type;
}

void Gem::removeGem() {
    m_color = -1;
    int size = all_types.size();
    m_type = all_types.at(size - 1);
}

void Gem::loadImages() {
    QImage tmp;
    tmp.load("img_gem1.png");
    all_types.append(tmp);
    tmp.load("img_gem2.png");
    all_types.append(tmp);
    tmp.load("img_gem3.png");
    all_types.append(tmp);
    tmp.load("img_gem4.png");
    all_types.append(tmp);
    tmp.load("img_gem5.png");
    all_types.append(tmp);
    tmp.load("img_delete.png");
    all_types.append(tmp);
}

Gem::~Gem() {};