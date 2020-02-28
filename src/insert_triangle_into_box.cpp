#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
    double min_x = std::min({a[0], b[0], c[0]});
    double min_y = std::min({a[1], b[1], c[1]});
    double min_z = std::min({a[2], b[2], c[2]});

    double max_x = std::max({a[0], b[0], c[0]});
    double max_y = std::max({a[1], b[1], c[1]});
    double max_z = std::max({a[2], b[2], c[2]});

    //for min_corner
    B.min_corner[0] = (B.min_corner[0] < min_x)? B.min_corner[0]:min_x;
    B.min_corner[1] = (B.min_corner[1] < min_y)? B.min_corner[1]:min_y;
    B.min_corner[2] = (B.min_corner[2] < min_z)? B.min_corner[2]:min_z;

    // for max_corner
    B.max_corner[0] = (B.max_corner[0] > max_x)? B.max_corner[0]:max_x;
    B.max_corner[1] = (B.max_corner[1] > max_y)? B.max_corner[1]:max_y;
    B.max_corner[2] = (B.max_corner[2] > max_z)? B.max_corner[2]:max_z;
}


