#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
    // reference: https://stackoverflow.com/questions/7113344/find-whether-two-triangles-intersect-or-not
    Ray ray(Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(0, 0, 0));

    double min_t, max_t, t;
    min_t = 0;

    ray.origin = A0;
    ray.direction = A1 - A0;
    max_t = ray.direction.norm();
    if (ray_intersect_triangle(ray, B0, B1, B2, min_t, max_t ,t))
        return true;

    ray.origin = A0;
    ray.direction = A2 - A0;
    max_t = ray.direction.norm();
    min_t = - max_t;
    if (ray_intersect_triangle(ray, B0, B1, B2, min_t, max_t ,t))
        return true;

    ray.origin = A2;
    ray.direction = A1 - A2;
    max_t = ray.direction.norm();
    if (ray_intersect_triangle(ray, B0, B1, B2, min_t, max_t ,t))
        return true;

    ray.origin = B0;
    ray.direction = B1 - B0;
    max_t = ray.direction.norm();
    if (ray_intersect_triangle(ray, A0, A1, A2, min_t, max_t ,t))
        return true;

    ray.origin = B0;
    ray.direction = B2 - B0;
    max_t = ray.direction.norm();
    if (ray_intersect_triangle(ray, A0, A1, A2, min_t, max_t ,t))
        return true;

    ray.origin = B2;
    ray.direction = B1 - B2;
    max_t = ray.direction.norm();
    return ray_intersect_triangle(ray, A0, A1, A2, min_t, max_t, t);

}
