#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
    Eigen::RowVector3d point;
    for (int i = 0; i < 3; ++i) {
        if (query(i) > box.max_corner(i)){
            point(i) = box.max_corner(i);
        }
        else if (query(i) < box.min_corner(i)){
            point(i) = box.min_corner(i);
        }
        else{
            point(i) = query(i);
        }
    }
    return (point - query).squaredNorm();
}
