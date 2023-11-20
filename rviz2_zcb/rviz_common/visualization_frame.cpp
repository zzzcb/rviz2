#include "rviz_common/visualization_frame.hpp"

#include <QHBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QStatusBar>
#include <QDir>
#include <QApplication>
#include <QDebug>

#include "globalconfig.h"
#include "rviz_common/splash_screen.hpp"
// #include "rviz_common/render_panel.hpp"


namespace rviz_common
{
    VisualizationFrame::VisualizationFrame(QWidget * parent)
    :QMainWindow(parent)
    {
        auto * reset_button = new QToolButton();
        reset_button->setText("Reset");
        reset_button->setContentsMargins(0, 0, 0, 0);
        statusBar()->addPermanentWidget(reset_button, 0);
        // connect(reset_button, SIGNAL(clicked(bool)), this, SLOT(reset()));

        auto status_label_ = new QLabel("");
        statusBar()->addPermanentWidget(status_label_, 1);
        // connect(this, SIGNAL(statusUpdate(const QString&)), status_label_, SLOT(setText(const QString&)));

        auto fps_label_ = new QLabel("");
        fps_label_->setMinimumWidth(40);
        fps_label_->setAlignment(Qt::AlignRight);
        statusBar()->addPermanentWidget(fps_label_, 0);
        auto original_status_bar_ = statusBar();

        setWindowTitle("RViz[*]");
    }

    VisualizationFrame::~VisualizationFrame()
    {

    }

    void VisualizationFrame::initialize()
    {
        qApp->setWindowIcon(QIcon(QDir(GlobalConfig::resource_path).absoluteFilePath("icons/package.png")));

        auto splash_path = QDir(GlobalConfig::resource_path).absoluteFilePath("images/splash.png");
        QPixmap splash_image(splash_path);
        auto splash = new SplashScreen(splash_image);
        splash->show();
        connect(this, SIGNAL(statusUpdate(const QString&)), splash, SLOT(showMessage(const QString&)));
        emit statusUpdate("Initializing");

        // Periodically process events for the splash screen.
        // See: http://doc.qt.io/qt-5/qsplashscreen.html#details
        qApp->processEvents();

        QWidget * central_widget = new QWidget(this);
        QHBoxLayout * central_layout = new QHBoxLayout;
        central_layout->setSpacing(0);
        central_layout->setMargin(0); 

        // render_panel_ = new RenderPanel(central_widget);


        
        delete splash;
        splash = nullptr;
    }



} // namespace rviz_common
