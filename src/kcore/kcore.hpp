#ifndef KCORE_KCORE_HPP
#define KCORE_KCORE_HPP

#include "../common/graph.hpp"

namespace kcore {
std::vector<count_t> find_kcore(Graph &g);
}

#endif // KCORE_KCORE_HPP
