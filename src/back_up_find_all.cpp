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
    //leaf_pairs ← {}
    leaf_pairs = {};

    std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > Queue;

    //if root_A.box intersects root_B.box
    if (box_box_intersect(rootA->box, rootB->box)){
        Queue.emplace_back(rootA, rootB);
    }

    std::shared_ptr<Object> mesh_t_a, mesh_t_b;

    while (!Queue.empty()){
        std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > cur_pair = Queue.front();
        Queue.pop_front();

        std::shared_ptr<AABBTree> node_a = std::dynamic_pointer_cast<AABBTree>(cur_pair.first);
        std::shared_ptr<AABBTree> node_b = std::dynamic_pointer_cast<AABBTree>(cur_pair.second);


        mesh_t_a = std::dynamic_pointer_cast<MeshTriangle>(node_a);
        mesh_t_b = std::dynamic_pointer_cast<MeshTriangle>(node_b);

        //if nodeA and nodeB are leaves
        if(mesh_t_a && mesh_t_b){
            leaf_pairs.emplace_back(mesh_t_a, mesh_t_b);
        }
            //else if node_A is a leaf
        else if(mesh_t_a){
            //if node_A.box intersects node_B.left.box
            if(box_box_intersect(node_a->box, node_b->left->box)){
                Queue.emplace_back(node_a, node_b->left);
            }
            //if node_A.box intersects node_B.right.box
            if(box_box_intersect(node_a->box, node_b->right->box)){
                Queue.emplace_back(node_a, node_b->right);
            }
        }
            //else if node_B is a leaf
        else if(mesh_t_b){
            //if node_A.left.box intersects node_B.box
            if(box_box_intersect(node_a->left->box, node_b->box)){
                Queue.emplace_back(node_a->left, node_b);
            }
            //if node_A.right.box intersects node_B.box
            if(box_box_intersect(node_a->right->box, node_b->box)){
                Queue.emplace_back(node_a->right, node_b);
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
    //leaf_pairs ← {}
    leaf_pairs = {};

    std::list<std::pair<std::shared_ptr<AABBTree>,std::shared_ptr<AABBTree> > > Queue;

    //if root_A.box intersects root_B.box
    if (box_box_intersect(rootA->box, rootB->box)){
        Queue.emplace_back(rootA, rootB);
    }

    std::shared_ptr<MeshTriangle> mesh_t_a, mesh_t_b;

    while (!Queue.empty()){
        std::pair<std::shared_ptr<AABBTree>,std::shared_ptr<AABBTree> > cur_pair = Queue.front();
        Queue.pop_front();

        std::shared_ptr<AABBTree> node_a = cur_pair.first;
        std::shared_ptr<AABBTree> node_b = cur_pair.second;


        mesh_t_a = std::dynamic_pointer_cast<MeshTriangle>(node_a);
        mesh_t_b = std::dynamic_pointer_cast<MeshTriangle>(node_b);

        //if nodeA and nodeB are leaves
        if(mesh_t_a && mesh_t_b){
            leaf_pairs.emplace_back(mesh_t_a, mesh_t_b);
        }
            //else if node_A is a leaf
        else if(mesh_t_a){
            //if node_A.box intersects node_B.left.box
            if(box_box_intersect(node_a->box, node_b->left->box)){
                Queue.emplace_back(node_a, std::dynamic_pointer_cast<AABBTree>(node_b->left));
            }
            //if node_A.box intersects node_B.right.box
            if(box_box_intersect(node_a->box, node_b->right->box)){
                Queue.emplace_back(node_a, std::dynamic_pointer_cast<AABBTree>(node_b->right));
            }
        }
            //else if node_B is a leaf
        else if(mesh_t_b){
            //if node_A.left.box intersects node_B.box
            if(box_box_intersect(node_a->left->box, node_b->box)){
                Queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_a->left), node_b);
            }
            //if node_A.right.box intersects node_B.box
            if(box_box_intersect(node_a->right->box, node_b->box)){
                Queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_a->right), node_b);
            }
        }
        else{
            //if node_A.left.box intersects node_B.left.box
            if(box_box_intersect(node_a->left->box, node_b->left->box)){
                Queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_a->left), std::dynamic_pointer_cast<AABBTree>(node_b->left));
            }
            //if node_A.left.box intersects node_B.right.box
            if(box_box_intersect(node_a->left->box, node_b->right->box)){
                Queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_a->left), std::dynamic_pointer_cast<AABBTree>(node_b->right));
            }
            //if node_A.right.box intersects node_B.right.box
            if(box_box_intersect(node_a->right->box, node_b->right->box)){
                Queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_a->right), std::dynamic_pointer_cast<AABBTree>(node_b->right));
            }
            //if node_A.right.box intersects node_B.left.box
            if(box_box_intersect(node_a->right->box, node_b->left->box)){
                Queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_a->right), std::dynamic_pointer_cast<AABBTree>(node_b->left));
            }

        }

    }


}

