#ifndef COMMON_GRAPH_HPP
#define COMMON_GRAPH_HPP

#include "settings.hpp"

struct Graph
{
    count_t n;
    count_t m;

    std::vector<vid_t> adj;
    std::vector<count_t> num_edges;
    std::vector<count_t> degree;
    std::vector<count_t> k_core;

    void populate_from_file( const std::filesystem::path& fs );
    void populate_from_list( const std::vector<vid_t>&src, const std::vector<vid_t>&dst );
};

#endif // COMMON_GRAPH_HPP
