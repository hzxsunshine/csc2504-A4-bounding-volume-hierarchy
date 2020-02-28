#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
    int size = objects.size();

    if(size <= 1) throw;
    else{
        for (const auto & object : objects) {
            insert_box_into_box(object->box, this->box);
        }
    }

    double x_len = abs(this->box.max_corner.x() - this->box.min_corner.x());
    double x_mid = this->box.center().x();

    double y_len = abs(this->box.max_corner.y() - this->box.min_corner.y());
    double y_mid = this->box.center().y();

    double z_len = abs(this->box.max_corner.z() - this->box.min_corner.z());
    double z_mid = this->box.center().z();

    assert(!(isinf(x_len)) && "x len error");
    assert(!(isinf(y_len)) && "y len error");
    assert(!(isinf(z_len)) && "z len error");

    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;


    for (const auto & object : objects) {
        // x_axis is the longest axis:
        if(x_len > y_len && x_len > z_len){
            if(object->box.center().x() < x_mid){
                left_objects.push_back(object);
            }else{
                right_objects.push_back(object);
            }
        }
        // y_axis is the longest axis:
        else if (y_len > z_len){
            if(object->box.center().y() < y_mid){
                left_objects.push_back(object);
            }else{
                right_objects.push_back(object);
            }
        }
        // z_axis is the longest axis:
        else{
            if(object->box.center().z() < z_mid){
                left_objects.push_back(object);
            }else{
                right_objects.push_back(object);
            }
        }
    }

    if (left_objects.size() == objects.size()){
        for(int i = (int) (left_objects.size() / 2); i < left_objects.size(); i++)
            right_objects.push_back(left_objects[i]);
        left_objects.erase(left_objects.begin() + (int)(left_objects.size() / 2), left_objects.end());
    }
    else if (right_objects.size() == objects.size()){
        for(int i = (int) (right_objects.size() / 2); i < right_objects.size(); i++)
            left_objects.push_back(right_objects[i]);
        right_objects.erase(right_objects.begin() + (int)(right_objects.size() / 2), right_objects.end());
    }


    if(left_objects.empty()){
        printf("left_object is 0");
        throw;
    }
    else if(left_objects.size() == 1){
        this->left = left_objects[0];
    }else{
        this->left = std::make_shared<AABBTree>(left_objects, a_depth + 1);
    }

    if(right_objects.empty()){
        printf("right_object is 0");
        throw;
    }
    else if (right_objects.size() == 1){
        this->right = right_objects[0];
    }else{
        this->right = std::make_shared<AABBTree>(right_objects, a_depth + 1);
    }

}
