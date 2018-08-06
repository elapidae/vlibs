#include <iostream>

#include "voutfile.h"
#include <fstream>

using namespace std;

int main()
{
    std::string phrase = "Hello_world!";
    std::string fname  = "test.txt";

    {
        VOutFile f( fname );
        f.write( phrase );
    }

    ifstream rf( fname, ios_base::in );
    //cout << rf.good();
    std::string res;
    rf >> res;

    if ( res != phrase )
        throw std::runtime_error( "Phrase '" +phrase+ "' from file '"
                                  +fname+ "' not accepted. Res='" +res+ "'.");


    return 0;
}
