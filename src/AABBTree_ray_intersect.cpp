#include "AABBTree.h"
#include "MeshTriangle.h"
#include "CloudPoint.h"
#include <ray_intersect_box.h>
#include <ray_intersect_triangle.h>
#include <iostream>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
    if (ray_intersect_box(ray, this->box, min_t,max_t)){

        bool left_hit;
        bool right_hit;

        double left_t = std::numeric_limits<double>::infinity();
        double right_t = std::numeric_limits<double>::infinity();

        std::shared_ptr<Object> left_descendant;
        std::shared_ptr<Object> right_descendant;

        left_hit = this->left->ray_intersect(ray, min_t, max_t, left_t, left_descendant);
        right_hit = this->right->ray_intersect(ray, min_t, max_t, right_t, right_descendant);

        if(left_hit && right_hit){
            t = (left_t < right_t) ? left_t : right_t;
            descendant = (left_t < right_t) ? left_descendant : right_descendant;
        }
        else if(left_hit){
            t = left_t;
            descendant = left_descendant;
        }
        else if(right_hit){
            t = right_t;
            descendant = right_descendant;
        }
        else
            return false;


        //leaves should be mesh triangle or cloud point
        std::shared_ptr<MeshTriangle> mesh_t;
        std::shared_ptr<Object> cloud_p;
        if (t == left_t && left_hit){
            mesh_t = std::dynamic_pointer_cast<MeshTriangle>(this->left);
            cloud_p = std::dynamic_pointer_cast<CloudPoint>(this->left);
            if (mesh_t || cloud_p)
                descendant = this->left;
        }
        if(t == right_t && right_hit) {
            mesh_t = std::dynamic_pointer_cast<MeshTriangle>(this->right);
            cloud_p = std::dynamic_pointer_cast<CloudPoint>(this->left);
            if (mesh_t || cloud_p)
                descendant = this->right;
        }

        return true;
    }

    return false;

}

