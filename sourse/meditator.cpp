#include "meditator.h"

Meditator::Meditator()
    : m_field(0), m_time(0),m_score(0) {
    m_layout = new QGridLayout;
    setLayout(m_layout);
    on_gameReset();
}

void Meditator::on_gameReset() {
    if (m_field) { 
        for (int i = 0;i < m_field->M_GEM_COUNT;i++) {
            for (int j = 0;j < m_field->M_GEM_COUNT;j++) {
                delete m_field->m_field[i][j];
            }
        }        
        if (m_field->m_bonusGem) delete m_field->m_bonusGem;
        delete m_field;
    }
    if (m_time) delete m_time;
    for (int i = 0;i < m_layout->count();i++) {
        delete m_layout->takeAt(i);
    }
 
    m_time = new Clock(this);
    m_field = new Field(this);
    m_score = QSharedPointer<Score>(m_field->points);
    connect(m_field, SIGNAL(finished()), m_time, SLOT(stop()));
    this->setWindîwSize();
    m_layout->addWidget(m_time, 0, 0, 1, 1, Qt::AlignLeft); 
    m_layout->addLayout(m_score->vbox, 0, 0, 1, 1, Qt::AlignRight);
    m_layout->addWidget(m_field, 1, 0, 1, 1, Qt::AlignLeft);
    this->setFixedSize(m_windîw_size,m_windîw_size+50);
}

void Meditator::setWindîwSize() {
    m_windîw_size = m_field->M_GEM_COUNT * 55 + (m_field->M_GEM_COUNT - 1)*3;
}

void Meditator::changeColor(QString back, QString pick) {
    QString background = "background-color:";
    QString picked_background = "background-color:";
    background.append(back);
    picked_background.append(pick);
    this->m_field->m_background.clear();
    this->m_field->m_picked_background.clear();
    this->m_field->m_background.append(background);
    this->m_field->m_picked_background.append(picked_background);
    this->m_field->setStyleSheet(background);
    this->m_field->repaintField();
}

Meditator::~Meditator() {
    if (m_field) {
        for (int i = 0;i < m_field->M_GEM_COUNT;i++) {
            for (int j = 0;j < m_field->M_GEM_COUNT;j++) {
                delete m_field->m_field[i][j];
            }
        }
        if (m_field->m_bonusGem) delete m_field->m_bonusGem;
        delete m_field;
    }
}