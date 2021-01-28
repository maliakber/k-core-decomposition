#include "graph.hpp"

void Graph::populate_from_file( const std::filesystem::path& filename )
{
    FILE *infp = fopen(filename.string().c_str(), "r");
    if (infp == NULL) {
        std::cerr << "Error: could not open input file: " << filename << ".\n Exiting ...\n";
        exit(1);
    }

    vid_t u, v;
    std::vector<vid_t> src, dst;
    std::cout << "Reading input file: " << filename << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    while( fscanf(infp, "%u %u\n", &u, &v) != EOF ) {
        src.push_back(u);
        dst.push_back(v);
    }
    fclose( infp );

    populate_from_list(src, dst);

    auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time);
    std::cout << "Reading input file took time: " << end_time.count() << " ms " << std::endl;
}


void Graph::populate_from_list(const std::vector<vid_t> &src, const std::vector<vid_t> &dst)
{
    // find the number of nodes
    n = std::max(*std::max_element(src.cbegin(), src.cend()), *std::max_element(dst.cbegin(), dst.cend()));
    n++; // indices start from zero
    m = src.size(); // assuming no duplicate entry

    std::cout << "N (nodes#): " << n << ", M (edges#): " << m << std::endl;

    //Allocate space to the list holding degrees, initialized with zeros
    num_edges = std::vector<count_t>(n + 1, 0);
    degree = std::vector<count_t>(n + 1, 0);
#pragma omp parallel for
    for (auto i = 0lu; i < src.size(); i++) {
        vid_t u = src[i], v = dst[i];
        if (u == v)
            continue;
        __sync_fetch_and_add( &(num_edges[u]), 1);
        __sync_fetch_and_add( &(num_edges[v]), 1);
    }

    count_t edges_read = 0;
    std::vector<count_t> temp_num_edges(n + 1);
    temp_num_edges[0] = 0;

    for (auto i = 0llu; i < n; ++i) {
        edges_read += num_edges[i];
        temp_num_edges[i + 1] = edges_read;
    }

    std::copy(temp_num_edges.cbegin(), temp_num_edges.cend(), num_edges.begin());

    //Allocate space for adj
    adj = std::vector<vid_t>(edges_read);

#pragma omp parallel for
    for (auto i = 0lu; i < src.size(); i++) {
        vid_t u = src[i], v = dst[i];
        if (u == v)
            continue;
        auto const ind1 = __sync_fetch_and_add( &(temp_num_edges[u]), 1);
        auto const ind2 = __sync_fetch_and_add( &(temp_num_edges[v]), 1);
        adj[ ind1 ] = v;
        adj[ ind2 ] = u;
    }

    //Sort the adjacency lists
    auto start = std::begin( adj );
    temp_num_edges[0] = 0;

    for( auto i = 0u; i < n; ++i )
    {
        std::sort( adj.begin() + num_edges[ i ], adj.begin() + num_edges[ i + 1 ] );

        for( auto j = num_edges[ i ], ne = num_edges[ i + 1 ]; j < ne; ++j )
        {
            if( j == num_edges[ i ] || adj[ j ] != adj[ j - 1 ] )
            {
                *start++ = adj[ j ];
            }
        }
        temp_num_edges[i + 1] = start - adj.begin();
        degree[i] = temp_num_edges[i + 1] - temp_num_edges[i];
    }

    std::copy(temp_num_edges.cbegin(), temp_num_edges.cend(), num_edges.begin());

    m = num_edges[n];
    std::cout << "Number of \"sanitised\" edges: " << m << std::endl;
}
