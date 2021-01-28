#include "kcore/kcore.hpp"

#define CATCH_CONFIG_MAIN       // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"     // This includes the catch header, which defines the entire library

SCENARIO( "Testing kore value of a graph", "[k-core]" ) {
    GIVEN( "a set of of nodes and their connections(edges)" ) {
        Graph g;
        std::vector<vid_t> src, dst;

        WHEN( "custom graph - connected with a bridge node" ) {
            src = {0, 0, 0, 0, 1, 3, 3, 4};
            dst = {1, 2, 3, 4, 2, 4, 5, 5};
            g.populate_from_list(src, dst);

            THEN( "all the nodes will have core value 2" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 2, 2, 2, 2, 2, 2, 0 } );
            }
        }

        WHEN( "custom graph - connected with a bridge node" ) {
            src = {0, 0, 0, 0, 1, 3};
            dst = {1, 2, 3, 4, 2, 4};
            g.populate_from_list(src, dst);

            THEN( "all the nodes will have core value 2" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 2, 2, 2, 2, 2, 0 } );
            }
        }

        WHEN( "custom graph - two disconnected 2-core" ) {
            src = {0, 0, 1, 3, 3, 4};
            dst = {1, 2, 2, 4, 5, 5};
            g.populate_from_list(src, dst);

            THEN( "all the nodes will have core value 2" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 2, 2, 2, 2, 2, 2, 0 } );
            }
        }

        WHEN( "sample graph - from skyline community paper" ) {
            src = {1, 1, 2, 2, 2, 3, 3, 4, 4, 5};
            dst = {2, 3, 3, 4, 5, 5, 6, 5, 6, 6};
            g.populate_from_list(src, dst);

            THEN( "following output" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 0, 2, 3, 3, 3, 3, 3, 0 } );
            }
        }

        WHEN( "custom graph - rectangle with a center node" ) {
            src = {0, 0, 0, 0, 1, 1, 2, 3};
            dst = {1, 2, 3, 4, 2, 3, 4, 4};
            g.populate_from_list(src, dst);

            THEN( "all of them will have core value 3" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{3, 3, 3, 3, 3, 0} );
            }
        }

        WHEN( "one common edge with two and rest of them has one triangle" ) {
            src = {0, 0, 1, 1, 2};
            dst = {1, 2, 2, 3, 3};
            g.populate_from_list(src, dst);

            THEN( "one triangle will be removed from the common edge truss value" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 2, 2, 2, 2, 0 } );
            }
        }

        WHEN( "two edges with one, one common edge with three and rest of them has two triangles" ) {
            src = {0, 0, 1, 1, 1, 2, 2, 3};
            dst = {1, 2, 2, 3, 4, 3, 4, 4};
            g.populate_from_list(src, dst);

            THEN( "one triangle will be removed from the common edge truss value" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 2, 3, 3, 3, 3, 0 } );
            }
        }

        WHEN( "graph from shaden paper, one common edge and one edge without triangle" ) {
            src = {1, 2, 2, 3, 4, 4, 5, 5, 5, 6, 6, 7};
            dst = {2, 3, 4, 4, 5, 6, 6, 7, 8, 7, 8, 8};
            g.populate_from_list(src, dst);

            THEN( "truss value will be 2 for no triangle edge and common edge truss value will be one less" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 0, 1, 2, 2, 2, 3, 3, 3, 3, 0 } );
            }
        }

        WHEN( "custom graph by Ali, have all the variations(edge with no triangle, common edges etc.)" ) {
            src = {0, 0, 0, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6};
            dst = {1, 2, 3, 2, 6, 3, 4, 4, 5, 7, 5, 6, 7, 7, 7};
            g.populate_from_list(src, dst);

            THEN( "truss value will be 2 for no triangle edge and common edges truss value will be one less" ) {
                REQUIRE( kcore::find_kcore(g) == std::vector<count_t>{ 3, 3, 3, 3, 3, 3, 3, 3, 0 } );
            }
        }
    }
}