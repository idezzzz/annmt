#include "kd_tree.h"

#include <vector>
#include <tr1/unordered_map>

void ANNkd_tree::TraverseByLevel(
        std::vector<std::vector<int> > & level_nodes,
        std::vector<std::pair<int, int> > & child_nodes,
        std::tr1::unordered_map<int, std::vector<int> > & leaf_point_indexes)
{
    if(root != NULL)
    {
        root->traver_by_level(0, level_nodes, child_nodes, leaf_point_indexes);
    }
}

void ANNkd_split::traver_by_level(
        int level,
        std::vector<std::vector<int> > & level_nodes,
        std::vector<std::pair<int, int> > & child_nodes,
        std::tr1::unordered_map<int, std::vector<int> > & leaf_point_indexes)
{
    int node_index = (int)child_nodes.size();
    int num_levels = (int)level_nodes.size();
    if(level >= num_levels)
    {
        std::vector<int> nodes;
        nodes.push_back(node_index);
        level_nodes.push_back(nodes);
    }
    else {
        std::vector<int> & nodes = level_nodes[level];
        nodes.push_back(node_index);
    }
    child_nodes.push_back(std::pair<int, int>());

    child[ANN_LO]->traver_by_level(level + 1, level_nodes, child_nodes, leaf_point_indexes);

    int left_child_index = node_index + 1;
    int right_child_index = child_nodes.size();
    std::pair<int, int> child_node(left_child_index, right_child_index);
    child_nodes[node_index] = child_node;

    child[ANN_HI]->traver_by_level(level + 1, level_nodes, child_nodes, leaf_point_indexes);
}

void ANNkd_leaf::traver_by_level(int level,
        std::vector<std::vector<int> > & level_nodes,
        std::vector<std::pair<int, int> > & child_nodes,
        std::tr1::unordered_map<int, std::vector<int> > & leaf_point_indexes)
{
    int node_index = (int)child_nodes.size();
    int num_levels = (int)level_nodes.size();
    if(num_levels <= level)
    {
        std::vector<int> nodes;
        nodes.push_back(node_index);
        level_nodes.push_back(nodes);
    }
    else {
        std::vector<int> & nodes = level_nodes[level];
        nodes.push_back(node_index);
    }

    int left_child_index = -1;
    int right_child_index = -1;
    std::pair<int, int> child_node(left_child_index, right_child_index);
    child_nodes.push_back(child_node);

    std::vector<int> point_indexes(n_pts);
    for(int i = 0; i < n_pts; i++)
    {
        point_indexes[i] = bkt[i];
    }

    leaf_point_indexes.insert(std::make_pair(node_index, point_indexes));
}

