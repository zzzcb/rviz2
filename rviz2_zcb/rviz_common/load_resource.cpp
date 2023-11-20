#include "rviz_common/load_resource.hpp"

#include <string>

#include <QDir>
#include <QFile>  // NOLINT: cpplint cannot handle the include order here
#include <QPainter>  // NOLINT: cpplint cannot handle the include order here
#include <QPixmapCache>  // NOLINT: cpplint cannot handle the include order here

// #include "ament_index_cpp/get_package_share_directory.hpp"
// #include "ament_index_cpp/get_package_prefix.hpp"
#include "mesh_loader/retriever.h"

// #include "rviz_common/logging.hpp"
#include <iostream>

#include "globalconfig.h"

namespace rviz_common
{

resource_retriever::MemoryResource getResource(const std::string & resource_path)
{
  resource_retriever::Retriever retriever;
  resource_retriever::MemoryResource res;
  try {
    res = retriever.get(resource_path);
  } catch (resource_retriever::Exception & e) {
    std::cout << e.what() << std::endl;
    return resource_retriever::MemoryResource();
  }

  return res;
}

QPixmap loadPixmap(QString url, bool fill_cache)
{
  QPixmap pixmap;

  // if it's in the cache, no need to locate
  if (QPixmapCache::find(url, &pixmap)) {
    return pixmap;
  }

  auto image = getResource(url.toStdString());
  if (image.size != 0) {
    if (!pixmap.loadFromData(image.data.get(), static_cast<uint32_t>(image.size))) {
        std::cout << "Could not load pixmap " + url.toStdString() << std::endl;
    }
  }

  if (fill_cache) {
    QPixmapCache::insert(url, pixmap);
  }

  return pixmap;
}

QCursor getDefaultCursor(bool fill_cache)
{
  Q_UNUSED(fill_cache);
  return QCursor(Qt::ArrowCursor);
}

QCursor makeIconCursor(QString url, bool fill_cache)
{
  QPixmap icon = loadPixmap(url, fill_cache);
  if (icon.width() == 0 || icon.height() == 0) {
    std::cout <<
      "Could not load pixmap " << url.toStdString() << " -- "
        "using default cursor instead." << std::endl;
    return getDefaultCursor();
  }
  QString cache_key = url + ".cursor";
  return makeIconCursor(icon, cache_key, fill_cache);
}

QCursor makeIconCursor(QPixmap icon, QString cache_key, bool fill_cache)
{
  // if it's in the cache, no need to locate
  QPixmap cursor_img;
  if (QPixmapCache::find(cache_key, &cursor_img) ) {
    return QCursor(cursor_img, 0, 0);
  }

  QPixmap base_cursor = loadPixmap(QDir(GlobalConfig::resource_path).absoluteFilePath("icons/cursor.svg"), fill_cache);

  const int cursor_size = 32;

  cursor_img = QPixmap(cursor_size, cursor_size);
  cursor_img.fill(QColor(0, 0, 0, 0) );

  // copy base cursor & icon into one image
  QPainter painter(&cursor_img);

  int draw_x = 12;
  int draw_y = 16;

  // if the icon is too large, move it to the left
  if (draw_x + icon.width() > cursor_size) {
    draw_x = cursor_size - icon.width();
  }
  if (draw_y + icon.height() > cursor_size) {
    draw_y = cursor_size - icon.height();
  }

  painter.drawPixmap(0, 0, base_cursor);
  painter.drawPixmap(draw_x, draw_y, icon);

  if (fill_cache) {
    QPixmapCache::insert(cache_key, cursor_img);
  }

  return QCursor(cursor_img, 1, 1);
}

}  // namespace rviz_common
