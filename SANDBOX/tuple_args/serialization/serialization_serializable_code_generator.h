#ifndef SERIALIZATION_SERIALIZABLE_CODE_GENERATOR_H
#define SERIALIZATION_SERIALIZABLE_CODE_GENERATOR_H

#include "serialization/serialization_type_signature.h"


namespace serialization
{


//struct SomeType_Serializator_FULLHASH
//{
//    struct StoredType
//    //static SomeType
//};


struct CPP_Generator_Traits
{
    static std::vector<std::string> encoder_preambul()
    { return {}; }
    static std::vector<std::string> encoder_tail()
    { return {}; }
    static std::vector<std::string> decoder_preambul()
    { return {}; }
    static std::vector<std::string> decoder_tail()
    { return {}; }

    static std::string indent( uint count )
    {
        return std::string( ' ', count * 4 );
    }

    static std::string begin_encoder(std::string name)
    {
        return "class Encoder_" + name + "\n{\n";
    }
    static std::string end_encoder(std::string name)
    {
        (void) name;
        return "}/n/n";
    }
    static std::string begin_decoder(std::string name)
    {
        return "class Decoder_" + name + "\n{\n";
    }
    static std::string end_decoder(std::string name)
    {
        (void) name;
        return "";
    }

    static std::string encode_type(std::string name, std::string type)
    {
        (void) name;
        return "";
    }

};




template<typename T, typename GenTraits = CPP_Generator_Traits>
class Code_Generator
{
public:
    Code_Generator()
    {}

    std::vector<std::string> enc, dec;
};



} // namespace serialization



#endif // SERIALIZATION_SERIALIZABLE_CODE_GENERATOR_H
