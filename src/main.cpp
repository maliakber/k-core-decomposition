#include "kcore/kcore.hpp"
#include <unistd.h>

int main( int argc, char ** argv )
{
    if ( argc < 2 ) {
        std::cout << "Please provide file path: " << " <Graph file>" << std::endl;
        std::cout << "example : -f /home/aliakber/Desktop/projects/dataset/soc-slashdot.txt" << std::endl;
        exit( 1 );
    }

    std::string input_filename = argv[1];
    Graph g;
    int32_t c;
    while ( (c = getopt( argc, argv, "f:" )) != -1 ) {
        switch ( c ) {
        case 'f':
            input_filename = std::string( optarg );
            break;
        default:
            if ( isprint( optopt ) )
                fprintf(stderr, "Unknown option `-%c'.\n", optopt );
            return 0;
        }
    }

    std::filesystem::path infile(input_filename);
    if(infile.extension().string() == ".txt") 
    {
        g.populate_from_file( infile );
    }
    else
    {
        std::cout << "Please provide a .txt graph file" << std::endl;
        return 0;
    }

    std::cout << "\033[32mComputing k-core decomposition... " << std::endl;
    kcore::find_kcore(g);
    std::cout << "\033[32mk-core decomposition done " << std::endl;

    auto max_core = *std::max_element(g.k_core.cbegin(), g.k_core.cend());
    std::cout<<"Maximum k-core: " << max_core << "\n";

    return 0;
}
