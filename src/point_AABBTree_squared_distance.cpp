#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include "point_box_squared_distance.h"
#include "CloudPoint.h"
#include "MeshTriangle.h"

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
    // min priority queue
    // By default a max heap is created ordered
    // by first element of pair.
    // using std::greater<T> would cause the smallest element to appear as the top().
    std::priority_queue<std::pair<double, std::shared_ptr<Object>>, \
            std::vector<std::pair<double, std::shared_ptr<Object>>>, \
                    std::greater<std::pair<double, std::shared_ptr<Object>>>> priorityQueue;

    // initialization
    double min_dis = std::numeric_limits<double>::infinity();

    // distance to root box/left
    double d_r = point_box_squared_distance(query, root->box);
    // distance to right box
    double d_l;

    //distance from query to subtree's bounding box
    double d_s;
    std::pair<double, std::shared_ptr<Object>> cur_pair;

    // Q insert pair of d_r and root
    priorityQueue.push(std::make_pair(d_r, root));


    std::shared_ptr<AABBTree> tree_node;
    std::shared_ptr<CloudPoint> cloud_p;

    // while Q not empty:
    while (!priorityQueue.empty()){

        cur_pair = priorityQueue.top();
        priorityQueue.pop();
        d_s = cur_pair.first;

        if(d_s < min_dis){

                cloud_p = std::dynamic_pointer_cast<CloudPoint>(cur_pair.second);
            //if sub tree is a leave:
            if (cloud_p){
                    descendant = cloud_p;
                    min_dis = d_s;
            }
            else{
                tree_node = std::dynamic_pointer_cast<AABBTree>(cur_pair.second);

                d_l = point_box_squared_distance(query, tree_node->left->box);
                priorityQueue.push(std::make_pair(d_l, tree_node->left));

                d_r = point_box_squared_distance(query, tree_node->right->box);
                priorityQueue.push(std::make_pair(d_r, tree_node->right));
            }
        }
    }

    sqrd = min_dis;
    return(min_dis >= min_sqrd && min_dis <= max_sqrd);

}
