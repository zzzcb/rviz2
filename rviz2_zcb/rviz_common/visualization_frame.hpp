#ifndef RVIZ_COMMON__VISUALIZATION_FRAME_HPP_
#define RVIZ_COMMON__VISUALIZATION_FRAME_HPP_

#include <chrono>
#include <deque>
#include <map>
#include <string>

#include <QList>  
#include <QMainWindow> 
#include <QString>  
#include <Qt>  

namespace rviz_common
{

class VisualizationFrame : public QMainWindow
{
Q_OBJECT

public:
    explicit VisualizationFrame(QWidget * parent = nullptr);
    ~VisualizationFrame();

};

}  // namespace rviz_common

#endif  // RVIZ_COMMON__VISUALIZATION_FRAME_HPP_
