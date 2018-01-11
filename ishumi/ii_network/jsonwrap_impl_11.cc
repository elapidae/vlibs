
//  json 11 implementation

#include "json11.h"


//=======================================================================================
namespace ii
{
//=======================================================================================


//=======================================================================================
//      Array
//=======================================================================================
class ii::JsonArray::Pimpl
{
public:
    Pimpl( const json11::Json::array & arr ) :a(arr) {}

private:
    json11::Json::array a;
};
//=======================================================================================
//      Array
//=======================================================================================



//=======================================================================================
//      Object
//=======================================================================================
class ii::JsonObject::Pimpl
{
public:
    Pimpl( const json11::Json::object & obj ) :o(obj) {}

private:
    json11::Json::object o;
};
//=======================================================================================
//      Object
//=======================================================================================


//=======================================================================================
//      Document
//=======================================================================================
class JsonDocument::Pimpl
{
    json11::Json j;
public:
    //===================================================================================
    static Pimpl *parse( const std::string &json, std::string *error )
    {
        auto res = new Pimpl;
        res->j = json11::Json::parse( json, *error );
        return res;
    }
    //===================================================================================
    std::string dump( DumpStyle style )
    {
        return j.dump();
        (void)style;
    }
    //===================================================================================
    bool is_object() const
    {
        return j.is_object();
    }
    JsonObject::Pimpl * get_object() const
    {
        return new ii::JsonObject::Pimpl( j.object_items() );
    }
    //===================================================================================
    bool is_array() const
    {
        return j.is_array();
    }
    JsonArray get_array() const
    {
        return new ii::JsonArray::Pimpl( j.array_items() );
    }
    //===================================================================================
};
//=======================================================================================
//      Document
//=======================================================================================





//=======================================================================================
} // ii namespace
//=======================================================================================
