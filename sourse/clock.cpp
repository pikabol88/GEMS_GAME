#include "clock.h"

Clock::Clock(QWidget *parent)
    :QLCDNumber(parent), m_time(0, 0, 0) {
    setSegmentStyle(Flat);
    setStyleSheet("background - color:black");

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_tick()));
    m_timer->start(1000);

    display(m_time.toString("hh:mm:ss"));

    setFixedSize(200, 30);
}

void Clock::on_tick() {
    m_time = m_time.addSecs(1);
    display(m_time.toString("hh:mm:ss"));
}

void Clock::stop() { 
    m_timer->stop(); 
}

Clock::~Clock() {
    m_timer = nullptr;
}