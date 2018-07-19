#include <iostream>
#include <map>

typedef std::map<int, int> arraypair;

void unio(arraypair& a, const arraypair& b)
{
    auto in1 = a.begin();
    auto in2 = b.begin();
    
    while(in1 != a.end() || in2 != b.end())
    {
        if( in2 == b.end() || (
               in1 != a.end() &&
               in1->first < in2->first
        ))
        {
            a.emplace(in1->first, in1->second);
            ++in1;
        }
        else 
        if( in1 == a.end() || (
                in2 != b.end() &&
                in2->first < in1->first
        ))
        {
            a.emplace(in2->first, in2->second);
            ++in2;
        }
        else //in1->first == in2->first
        {
            a.emplace(in1->first, in1->second);
            ++in1;
            ++in2;
        }
    }
}

int main()
{
    arraypair map = {
        {1, 1},
        {2, 2},
        {4, 4},
        {6, 6},
        {7, 7}
    };

    arraypair merge_with = {
        {3, 3},
        {5, 5},
        {8, 8}
    };

    unio(map, merge_with);

    std::cout << "Printing result:\n";
    for(auto it = map.begin(); it != map.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
}