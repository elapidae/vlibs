#include <iostream>

#include <algorithm>
#include <vector>
#include "vlog.h"
#include "vcat_containers.h"

using namespace std;
// ========================================================================
int main()
{
    vector<int> v { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 9, 8 };
    const vector<int> & cv = v;

    // const OK!
    auto it = partition_point( cv.begin(), cv.end(), [](int i) {return i > 6;} );
    vdeb << v;
    vdeb << *it;

    // const ERROR!!!1
    //it = partition( cv.begin(), cv.end(), [](int i) {return i > 6;} );

    it = partition( v.begin(), v.end(), [](int i) {return i > 6;} );
    vdeb << v;
    vdeb << *it;

    cout << "Hello World!" << endl;
    return 0;
}
