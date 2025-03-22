#include "latexpp/latex.hpp"

int main(int argc, char* argv[])
{

        if(argc != 3){
                throw std::invalid_argument("Wrong number of arguements");
        }
        Latex latex;
        latex.to_png(argv[1], argv[2]);

        return 0;
}
