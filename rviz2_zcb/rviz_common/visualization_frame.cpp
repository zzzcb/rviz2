#include "rviz_common/visualization_frame.hpp"

#include <QHBoxLayout>

namespace rviz_common
{

VisualizationFrame::VisualizationFrame(QWidget * parent)
  :QMainWindow(parent)
{
    QWidget * central_widget = new QWidget(this);
    QHBoxLayout * central_layout = new QHBoxLayout;
    central_layout->setSpacing(0);
    central_layout->setMargin(0);
}

VisualizationFrame::~VisualizationFrame()
{

}

}  // namespace rviz_common
