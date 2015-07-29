#include "kd_tree.h"

#include <vector>
#include <tr1/unordered_map>

void ANNkd_tree::TraverseByLevel(std::tr1::unordered_map<int, std::vector<int> > & leaf_point_indexes,
                                 std::tr1::unordered_map<int, std::vector<double> > & bound_boxes)
{
    int noud_count = 0;
    if(root != NULL)
    {
        std::vector<double> child_bound_boxes(6);
        root->travel_by_level(noud_count, leaf_point_indexes, bound_boxes, child_bound_boxes);
    }
}

void ANNkd_split::travel_by_level(int & node_count,
                                  std::tr1::unordered_map<int, std::vector<int> > & leaf_point_indexes,
                                  std::tr1::unordered_map<int, std::vector<double> > & bound_boxes,
                                  std::vector<double> const & child_bound_boxes)
{
    node_count++;
    ANNcoord low = cd_bnds[0];
    ANNcoord high = cd_bnds[1];

    std::vector<double> bnds0, bnds1;
    bnds0 = bnds1 = child_bound_boxes;

    bnds0[cut_dim] = low;
    bnds0[cut_dim + 3] = cut_val;

    bnds1[cut_dim] = cut_val;
    bnds1[cut_dim + 3] = high;

    child[ANN_LO]->travel_by_level(node_count, leaf_point_indexes, bound_boxes, bnds0);
    child[ANN_HI]->travel_by_level(node_count, leaf_point_indexes, bound_boxes, bnds1);
}

void ANNkd_leaf::travel_by_level(int & node_count,
                                 std::tr1::unordered_map<int, std::vector<int> > & leaf_point_indexes,
                                 std::tr1::unordered_map<int, std::vector<double> > & bound_boxes,
                                 std::vector<double> const & child_bound_boxes)
{
    node_count++;
    std::vector<int> point_indexes(n_pts);
    for(int i = 0; i < n_pts; i++)
    {
        point_indexes[i] = bkt[i];
    }

    leaf_point_indexes.insert(std::make_pair(node_count, point_indexes));
    bound_boxes.insert(std::make_pair(node_count, child_bound_boxes));
}

