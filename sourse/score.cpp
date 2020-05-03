#include "score.h"

void Score::updateScore(int points) {
    m_score += points;
    display(m_score);
}

Score::Score(QWidget *parent):QLCDNumber(parent), m_score(0) {
    if (str) {
        str->clear();
        delete str;
    }
    if (label) delete label;

    this->setStyleSheet("QLCDNumber { background-color: black }");
    setSegmentStyle(Outline);
  
    str = new QString();
    str->clear();
    str->append("YOUR SCORE:");
    display(m_score);
    label = new QLabel(*str, this);
    vbox = new QVBoxLayout();  
    vbox->addWidget(label,Qt::AlignTop);
    vbox->addWidget(this);
    vbox->addSpacing(10);
}

Score::~Score() {
    if (str) delete str;
}