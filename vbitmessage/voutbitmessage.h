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


#ifndef VOUTBITMESSAGE_H
#define VOUTBITMESSAGE_H

#include <string>
#include <vector>


//=======================================================================================
/*  VOutBitMessage -- составление коротких сообщений из бит.
 *
 *      - В конструктор надо передать количество бит сообщения, притом кратное 8!
*/
//=======================================================================================


//=======================================================================================
class VOutBitMessage
{
public:
    explicit VOutBitMessage(uint bits );

    void set( uint from, uint to, uint32_t val );

    std::string result() const;

    // Выводит результат побитово.
    std::string str_as_bits() const;

private:
    std::vector<uint8_t> _data;
};
//=======================================================================================




#endif // VOUTBITMESSAGE_H
