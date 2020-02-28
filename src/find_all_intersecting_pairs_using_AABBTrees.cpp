#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>
#include "MeshTriangle.h"

void find_all_intersecting_pairs_using_AABBTrees(
        const std::shared_ptr<AABBTree> & rootA,
        const std::shared_ptr<AABBTree> & rootB,
        std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > &
        leaf_pairs)
{
    leaf_pairs = {};
    std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > Queue;

    //if root_A.box intersects root_B.box
    if (box_box_intersect(rootA->box, rootB->box)){
        Queue.emplace_back(rootA, rootB);
    }

    std::shared_ptr<Object> ob_a, ob_b;
    std::shared_ptr<AABBTree> node_a, node_b;
    std::pair<std::shared_ptr<Object>,std::shared_ptr<Object>> cur_pair;

    while (!Queue.empty()){
        cur_pair = Queue.front();
        Queue.pop_front();

        ob_a = cur_pair.first;
        ob_b = cur_pair.second;

        node_a = std::dynamic_pointer_cast<AABBTree>(ob_a);
        node_b = std::dynamic_pointer_cast<AABBTree>(ob_b);


        //if nodeA and nodeB are leaves
        if(node_a == nullptr && node_b == nullptr){
            leaf_pairs.emplace_back(ob_a, ob_b);
        }
            //else if node_A is a leaf
        else if(node_a == nullptr){
            //if node_A.box intersects node_B.left.box
            if(box_box_intersect(ob_a->box, node_b->left->box)){
                Queue.emplace_back(ob_a, node_b->left);
            }
            //if node_A.box intersects node_B.right.box
            if(box_box_intersect(ob_a->box, node_b->right->box)){
                Queue.emplace_back(ob_a, node_b->right);
            }
        }
            //else if node_B is a leaf
        else if(node_b == nullptr){
            //if node_A.left.box intersects node_B.box
            if(box_box_intersect(node_a->left->box, ob_b->box)){
                Queue.emplace_back(node_a->left, ob_b);
            }
            //if node_A.right.box intersects node_B.box
            if(box_box_intersect(node_a->right->box, ob_b->box)){
                Queue.emplace_back(node_a->right, ob_b);
            }
        }
        else{
            //if node_A.left.box intersects node_B.left.box
            if(box_box_intersect(node_a->left->box, node_b->left->box)){
                Queue.emplace_back(node_a->left, node_b->left);
            }
            //if node_A.left.box intersects node_B.right.box
            if(box_box_intersect(node_a->left->box, node_b->right->box)){
                Queue.emplace_back(node_a->left, node_b->right);
            }
            //if node_A.right.box intersects node_B.right.box
            if(box_box_intersect(node_a->right->box, node_b->right->box)){
                Queue.emplace_back(node_a->right, node_b->right);
            }
            //if node_A.right.box intersects node_B.left.box
            if(box_box_intersect(node_a->right->box, node_b->left->box)){
                Queue.emplace_back(node_a->right, node_b->left);
            }

        }

    }


}