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

    void set(uint from, uint to, uint32_t val );

    std::string result() const;

    // Выводит результат побитово.
    std::string str_as_bits() const;

private:
    std::vector<uint8_t> _data;
};
//=======================================================================================




#endif // VOUTBITMESSAGE_H
