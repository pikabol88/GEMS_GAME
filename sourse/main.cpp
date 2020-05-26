#include <QVBoxLayout>

#include "meditator.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QVBoxLayout *layout = new QVBoxLayout;

    MainWindow window;
    Meditator *widget = new Meditator;
    window.m = QSharedPointer<Meditator>(widget);
    //window.m = widget;
    
    widget->setLayout(layout);
    window.setCentralWidget(widget);
    window.setWindowTitle("GEMS");
    window.setWindowIcon(QIcon("img_logo.png"));
    window.setFixedSize(widget->width(), widget->height()*1.1);
    window.show();
    return app.exec();
}
