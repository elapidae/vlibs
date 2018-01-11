#ifndef JSONWRAP_H
#define JSONWRAP_H

#include <memory>

//=======================================================================================
namespace ii
{
    //===================================================================================
    class JsonArray;
    class JsonObject;
    //===================================================================================

    //===================================================================================
    class JsonArray
    {
    public:

        int count() const;
        bool empty() const;

        double d() const;
        JsonObject o() const;
        std::string s() const;
        bool b() const;


    private:
        class Pimpl; std::shared_ptr<Pimpl> p;
        friend class JsonDocument; JsonArray( Pimpl *pp );
    };
    //===================================================================================
    class JsonObject
    {
    public:

    private:
        class Pimpl; std::shared_ptr<Pimpl> p;
        friend class JsonDocument; JsonObject( Pimpl *pp );
    };
    //===================================================================================
    class JsonDocument
    {
    public:
        enum DumpStyle { Pretty, Compact };

        static JsonDocument parse( const std::string &json, std::string *error );
        std::string dump( DumpStyle style = Compact ) const;

        bool is_array() const;
        JsonArray get_array() const;

        bool is_object() const;
        JsonObject get_object() const;

    private:
        class Pimpl; std::shared_ptr<Pimpl> p;
        JsonDocument( Pimpl *pp );
    };
    //===================================================================================

}
//=======================================================================================




#endif // JSONWRAP_H
