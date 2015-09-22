#include "kd_tree.h"
#include "kd_util.h"

#include <vector>

void ANNkd_tree::TraverseByLevel(std::vector<int> & leaf_indexes,
                                 std::vector<std::vector<int> > & leaf_point_indexes,
                                 std::vector<double> & spread_sizes)
{
    int noud_count = 0;
    if(root != NULL)
    {
        root->travel_by_level(pts, noud_count, leaf_indexes, leaf_point_indexes, spread_sizes);
    }
}

void ANNkd_split::travel_by_level(ANNpointArray pts,
                                  int & node_count,
                                  std::vector<int> & leaf_indexes,
                                  std::vector<std::vector<int> > & leaf_point_indexes,
                                  std::vector<double> & bound_boxes)
{
    node_count++;
    child[ANN_LO]->travel_by_level(pts, node_count, leaf_indexes, leaf_point_indexes, bound_boxes);
    child[ANN_HI]->travel_by_level(pts, node_count, leaf_indexes, leaf_point_indexes, bound_boxes);
}

void ANNkd_leaf::travel_by_level(ANNpointArray pts,
                                 int & node_count,
                                 std::vector<int> & leaf_indexes,
                                 std::vector<std::vector<int> > & leaf_point_indexes,
                                 std::vector<double> & bound_boxes)
{
    node_count++;
    std::vector<int> point_indexes(n_pts);
    for(int i = 0; i < n_pts; i++)
    {
        point_indexes[i] = bkt[i];
    }

    if(point_indexes.size() == 0)
    {
        return;
    }

    leaf_indexes.push_back(node_count);
    leaf_point_indexes.push_back(point_indexes);
    double spread_size = annSpread(pts, bkt, n_pts, 3);
    bound_boxes.push_back(spread_size);
}

