#include "gems.h"
#include <QMessageBox>
#include <QApplication>
#include "warning.h"

Gem::Gem(int i, int j, QWidget *parent) : QPushButton(parent), m_i(i), m_j(j) {
    if (all_types.size() == 0) {
        loadImages();
    }
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFixedSize(G_WIDTH, G_HEIGHT);
    int type = rand() % GEMS_TYPE;
    m_type = all_types.at(type);
    m_bonusType = type;
}

bool operator==(const Gem &gem1, const Gem &gem2) {
    return (gem1.m_type == gem2.m_type);
}

void Gem::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);
    QPainter p(this);
    p.setBrush(QBrush(this->m_bonusType, Qt::SolidPattern));
    p.drawImage(2, 2, m_type);
    return;
}

void Gem::changeGem() {
    int type = rand() % GEMS_TYPE;
    m_type = all_types.at(type);
    m_bonusType = type;
}

void Gem::removeGem() {
    m_bonusType = -1;
    int size = all_types.size();
    m_type = all_types.at(size - 1);
}

void Gem::loadImages() {
    QImage tmp;
    tmp.load("img\\img_gem1.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
    tmp.load("img\\img_gem2.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
    tmp.load("img\\img_gem3.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
    tmp.load("img\\img_gem4.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
    tmp.load("img\\img_gem5.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
    tmp.load("img\\img_delete.png");
    if (tmp.isNull()) {
        img_error();
    }
    all_types.append(tmp);
}

void Gem::img_error() {   
    static int count = 0;
    if (count == 0) {
        int n = QMessageBox::warning(0, "File not found", "Unfortunately the image was not found, please make sure that the folder with images exists");
        count++;
    }
}

Gem::~Gem() {};