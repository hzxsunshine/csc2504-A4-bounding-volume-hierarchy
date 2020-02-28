#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
    Eigen::Vector3d t0, t1, normal;
    t0 = (B - A).transpose();
    t1 = (C - A).transpose();

    Eigen::Matrix3d M;
    M.col(0) = t1;
    M.col(1) = t0;
    M.col(2) = - ray.direction;

    //Eigen::Vector3d temp = ray.origin - A;
    //Eigen::Vector3d x = M.colPivHouseholderQr().solve(ray.origin- std::get<0>(corners));
    Eigen::Vector3d x = M.householderQr().solve(ray.origin - A.transpose());

    normal = t1.cross(t0);
    double a = x[0];
    double b = x[1];
    t = x[2];
    if ((t < min_t)||(t > max_t)) return false;

    if((a >= 0) && (b >= 0) && (a + b <= 1)){
        normal.normalize();
        return true;
    }else return false;
}

