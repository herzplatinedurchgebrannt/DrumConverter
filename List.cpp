#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

int main()
{
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