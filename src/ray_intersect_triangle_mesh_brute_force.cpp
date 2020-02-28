#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
    hit_f = -1;

    int f_rows = F.rows();
    double best_t = std::numeric_limits<double>::infinity();

    Eigen::RowVector3d a, b, c; // vertices of triangle
    for (int i = 0; i < f_rows; i++){
        a = V.row(F(i, 0));
        b = V.row(F(i, 1));
        c = V.row(F(i, 2));
        if (ray_intersect_triangle(ray, a, b, c, min_t, max_t, hit_t)){
            if (hit_t < best_t){
                best_t = hit_t;
                hit_f = i;
            }
        }
    }
    hit_t = best_t;
    return (!isinf(best_t));
}
