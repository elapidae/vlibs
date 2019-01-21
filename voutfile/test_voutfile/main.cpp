/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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
