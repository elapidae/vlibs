#ifndef BINARYDATAJOINER_H
#define BINARYDATAJOINER_H


#include "vbytearray.h"
#include "net_core.h"
#include <unordered_map>
#include <set>

//=======================================================================================
namespace ii
{
    //===================================================================================
    //  NB! фрагменты нумеруются с единицы!
    class BinaryDataJoiner
    {
    public:
        explicit BinaryDataJoiner( int fragments_count );

        // Возвращает кол-во без одного уже присланных пакетов с таким же номером.
        // Если пакет будет обозначен большим номером, чем fragments, или меньшим нуля,
        // то вернет fragments + 1.
        int push( int fragment, const VByteArray &data );

        int  remained() const;
        bool is_ready() const;

        VByteArray join() const;

        steady_clock_t last_usage() const;
        int fragments_count()       const;

    private:
        std::unordered_map<int,int> _count;
        std::unordered_map<int,VByteArray> _data;
        std::set<int>  _waiting_frags;
        steady_clock_t _last_usage;
        int _fragments;
    };
    //===================================================================================
} // namespace ii
//=======================================================================================



#endif // BINARYDATAJOINER_H
