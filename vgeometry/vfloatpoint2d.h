#ifndef VFLOATPOINT2D_H
#define VFLOATPOINT2D_H

#include "vbytearray.h"


//=======================================================================================
//class [[deprecated]] VFloatPoint2D
//{
//public:
//    class Vector;

//    static VFloatPoint2D from_back_LE( VByteArray *buf );
//    void to_back_LE( VByteArray *buf ) const;

//    VFloatPoint2D();
//    VFloatPoint2D( float xx, float yy );

//    bool is_valid() const;

//    float x;
//    float y;

//    bool operator == ( const VFloatPoint2D &rhs ) const;
//    bool operator != ( const VFloatPoint2D &rhs ) const;

//    float distance_to( const VFloatPoint2D &rhs ) const;
//    float vector_len() const                               { return distance_to({0,0}); }

//    template<typename T>
//    T convert() const { return {x,y}; }
//};
//=======================================================================================
//  Класс введен, чтобы было поудобнее работать с группами точек.
//  После формирования группы можно вызвать recalc(), который посчитает параметры
//  группы, например, весовой центр, плотность, линейность и пр.
//class VFloatPoint2D::Vector : public std::vector<VFloatPoint2D>
//{
//public:

//    VFloatPoint2D center() const        { return _center; }

//    void recalc()
//    {
//        _clear_calcs();

//        double xsum = 0;
//        double ysum = 0;
//        for ( const auto & p: *this )
//        {
//            xsum += p.x;
//            ysum += p.y;
//        }
//        if (!empty())
//        {
//            _center.x = xsum / size();
//            _center.y = ysum / size();
//        }
//    }

//private:
//    VFloatPoint2D _center;

//    void _clear_calcs()
//    {
//        _center = VFloatPoint2D();
//    }
//};
//=======================================================================================



#endif // VFLOATPOINT2D_H
