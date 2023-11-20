#ifndef RVIZ_COMMON__LOAD_RESOURCE_HPP_
#define RVIZ_COMMON__LOAD_RESOURCE_HPP_

#include <QPixmap>
#include <QCursor>
#include <QString>

namespace rviz_common
{

// Helper functions to load resources based on their resource url,
// e.g. "package://rviz/icons/package.png",
// or "file:///home/user/.ros/config.yaml".

/// Try to load the pixmap url from disk or the cache.
/**
 * In case of a failure, the result will be an empty QPixmap.
 * If fill_cache is set to true (default), the image will be stored in the
 * cache after loading it from disk.
 */

QPixmap loadPixmap(QString url, bool fill_cache = true);

/// Load the default cursor: an arrow.
/**
 * The fill_cache parameter is ignored.
 */

QCursor getDefaultCursor(bool fill_cache = true);

/// Create a cursor using a shape in a file/url.
/**
 * In case of a failure, the result will be the default arrow cursor.
 * If fill_cache is set to true (default), the image will be stored in the
 * cache after loading it from disk.
 */

QCursor makeIconCursor(QString icon_url, bool fill_cache = true);

/// Create a cursor using the shape in the icon QPixmap.
/**
 * If fill_cache is set to true (default), the image will be stored in the
 * cache using cache_key.
 */

QCursor makeIconCursor(QPixmap icon, QString cache_key = "", bool fill_cache = true);

}  // namespace rviz_common

#endif  // RVIZ_COMMON__LOAD_RESOURCE_HPP_
