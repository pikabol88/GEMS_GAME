#ifndef THREAD_H
#define THREAD_H
#pragma once

#include <QThread>

class thread_hack : public QThread {
public:
    using QThread::sleep;
    using QThread::msleep;
    using QThread::usleep;
};

#endif // !THREAD_H
