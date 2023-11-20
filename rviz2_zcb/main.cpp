#include <QApplication>

#include "rviz_common/visualization_frame.hpp"
#include "globalconfig.h"

#include <QCommandLineParser>
#include <QDir>
#include <QDebug>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("3D visualization tool for zcb");
    parser.addHelpOption();

    QCommandLineOption resource_path_option(
        QStringList() << "p" << "path",
        "Resource path to images and icons",
        "path");    ///< 最后一个必须要有,但是好像没啥用,命名也无所谓
    parser.addOption(resource_path_option);

    parser.process(app);    ///< 必须!

    // 解析resource_path并将其存储到g_resource_path，最终为绝对路径
    if(parser.isSet(resource_path_option))
    {
        GlobalConfig::resource_path = parser.value(resource_path_option);
    }
    else 
    {
        GlobalConfig::resource_path = "..";
    }
    if(!QDir(GlobalConfig::resource_path).isAbsolute())
    {
        QDir dir(app.applicationDirPath());
        dir.cd(GlobalConfig::resource_path);
        GlobalConfig::resource_path = dir.absolutePath();
    }


    rviz_common::VisualizationFrame mw(nullptr);
    mw.initialize();
    mw.show();

    return app.exec();
}


