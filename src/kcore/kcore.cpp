#include "kcore.hpp"

namespace kcore {
std::vector<count_t> bucket, vert, pos;

std::vector<count_t> k_core_decomposition(Graph &g)
{
    auto start_time = std::chrono::system_clock::now();
    g.k_core = g.degree;
    for(auto i = 0u; i < bucket.size()-1; i++)
    {
        for(auto j = bucket[i]; j < bucket[i+1]; j++)
        {
            auto u = vert[j];
            for(auto k = g.num_edges[u]; k != g.num_edges[u + 1]; k++)
            {
                auto v = g.adj[k];
                if(bucket[g.k_core[v]] > bucket[g.k_core[u]])
                {
                    auto firstValConBucketInd = bucket[g.k_core[v]];
                    auto firstValConBucket = vert[firstValConBucketInd];
                    if(firstValConBucket != v)
                    {
                        auto con_pos = pos[v];
                        pos[v] = firstValConBucketInd;
                        pos[firstValConBucket] = con_pos;
                        vert[firstValConBucketInd] = v;
                        vert[con_pos] = firstValConBucket;
                    }
                    bucket[g.k_core[v]]++;
                    g.k_core[v]--;
                }
            }
        }
    }

    auto end_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>( end_time - start_time );
    std::cout << "BZ algorithm: " << elapsed_time.count() << " ms" << std::endl;

    return g.k_core;
}

void bucket_sort(Graph &g)
{
    auto start_time = std::chrono::system_clock::now();
    auto md = 0u;

    // find the maximum degree
    //#pragma omp parallel for reduction(max:md)
    //    for(eid_t i = 0; i<g.m; i++)
    //        md = std::max(md, g.support[i]);
    md = *std::max_element(g.degree.cbegin(), g.degree.cend());

    // incrementing maximum degree by 1 to include the max index in the bucket
    md = md + 1;

    // calculating the size of each bucket
    bucket = std::vector<count_t>(md + 1, 0);
    for(auto i = 0u; i < g.n; i++) {
        bucket[g.degree[i]]++;
    }

    std::vector<count_t> temp_bucket(md + 1);
    temp_bucket[0] = 0;
    //partial sum of bucket size, denotes the starting index of each bucket
    //    uint32_t cursum = 0;
    //    for(auto i=0u; i<md; i++)
    //    {
    //        cursum += bucket[i];
    //        bucket[i] = cursum - bucket[i];
    //    }
    std::partial_sum(bucket.begin(), bucket.end()-1, temp_bucket.begin()+1);
    std::copy(temp_bucket.cbegin(), temp_bucket.cend(), bucket.begin());

    //sorting using bucket sort and keeping the position in pos array
    vert = std::vector<count_t>(g.n);
    pos = std::vector<count_t>(g.n);

    //#pragma omp parallel for
    for(auto i=0u; i<g.n; i++)
    {
        pos[i] = temp_bucket[g.degree[i]]++;
        vert[pos[i]] = i;
    }

    auto end_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>( end_time - start_time );
    std::cout << "Bucket sort: " << elapsed_time.count() << " ms" << std::endl;
}

std::vector<count_t> find_kcore(Graph &g){
    bucket_sort(g);
    return k_core_decomposition(g);
}
}
