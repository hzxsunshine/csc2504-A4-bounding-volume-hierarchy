#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
    double x_min = box.min_corner[0];
    double y_min = box.min_corner[1];
    double z_min = box.min_corner[2];
    double x_max = box.max_corner[0];
    double y_max = box.max_corner[1];
    double z_max = box.max_corner[2];

    double a_x = 1 / ray.direction[0];
    double a_y = 1 / ray.direction[1];
    double a_z = 1 / ray.direction[2];

    double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;
    if(a_x >= 0){
        tx_min = a_x * (x_min - ray.origin[0]);
        tx_max = a_x * (x_max - ray.origin[0]);
    }
    else{
        tx_min = a_x * (x_max - ray.origin[0]);
        tx_max = a_x * (x_min - ray.origin[0]);
    }


    if(a_y >= 0){
        ty_min = a_y * (y_min - ray.origin[1]);
        ty_max = a_y * (y_max - ray.origin[1]);
    }
    else{
        ty_min = a_y * (y_max - ray.origin[1]);
        ty_max = a_y * (y_min - ray.origin[1]);
    }

    if(a_z >= 0){
        tz_min = a_z * (z_min - ray.origin[2]);
        tz_max = a_z * (z_max - ray.origin[2]);
    }
    else{
        tz_min = a_z * (z_max - ray.origin[2]);
        tz_max = a_z * (z_min - ray.origin[2]);
    }

    double t_max = std::min({tx_max, ty_max, tz_max});
    double t_min = std::max({tx_min, ty_min, tz_min});

    if (t_max < t_min) return false;

    // How to check a ray or min_t inside a box?
    return !((max_t < t_min) || (min_t > t_max));

}
