#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <filesystem>


#include <experimental/filesystem>

// for brevity
namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) 
{

    std::cout << "Current path: " << fs::current_path() << std::endl;



    std::cout << argv[1] << std::endl;


    std::list<int> missedNotes = {2,4,6,8};

    for (int n : missedNotes){
        std::cout << n << std::endl;
    }

    std::vector<int> v;

    std::cout << v.size() << std::endl; 


    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v.at(i) << std::endl;
        std::cout << "drin";
    }
}