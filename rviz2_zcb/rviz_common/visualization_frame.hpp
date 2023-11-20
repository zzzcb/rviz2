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

class RenderPanel;



class VisualizationFrame : public QMainWindow
{
Q_OBJECT

public:
    explicit VisualizationFrame(QWidget * parent = nullptr);
    ~VisualizationFrame();

    void initialize();

signals:
    void statusUpdate(const QString & message);

private:

    /// Actual panel where the main 3D scene is rendered.
    RenderPanel * render_panel_;
    

};

}  // namespace rviz_common

#endif  // RVIZ_COMMON__VISUALIZATION_FRAME_HPP_
