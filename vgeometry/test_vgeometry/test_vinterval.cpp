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


#include "gtest/gtest.h"

#include "vinterval.h"
#include "vlog_pretty.h"

//=======================================================================================

class VInterval_Test: public testing::Test
{
protected:
//    const float eps = 0.00001;
};

//=======================================================================================

TEST_F(VInterval_Test, simples)
{
    VIntervalD id{ {1,0}, {2,1} };
    EXPECT_TRUE( id.angle_degrees() == 45.f );

    EXPECT_TRUE( !id.is_normal( {1,2.01} )  );
    EXPECT_TRUE( id.is_normal( {1,2} )      );
    EXPECT_TRUE( id.is_normal( {0,1} )      );
    EXPECT_TRUE( !id.is_normal( {0,0.99} )  );
}

//=======================================================================================

// TODO: More and more tests!
