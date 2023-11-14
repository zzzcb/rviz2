#include <QApplication>

#include "rviz_common/visualization_frame.hpp"

#include <QDebug>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    rviz_common::VisualizationFrame mw(nullptr);
    mw.show();

    return app.exec();
}


