#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
    double min_d = std::numeric_limits<double>::infinity();
    I = -1;
    sqrD = 0;
    double d_s;
    for (int i = 0; i < points.rows(); ++i) {

        Eigen::RowVector3d point = points.row(i);

        d_s = (point - query).squaredNorm();

        if(d_s < min_d){
            min_d = d_s;
            I = i;
        }
    }
    sqrD = min_d;
}
