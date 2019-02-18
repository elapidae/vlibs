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


#ifndef VTRANSFORMATION_H
#define VTRANSFORMATION_H

#include <string>


/**
 * @brief The TransformationUtils class
 * реализует функции для пересчета координат точек
 * при вращении объекта в пространстве
 * сдвиги относительно осей координат
 *
 * Вращение вокруг осей описывается матрицами вращения
 *
 *         | cos(A)   0   sin(A) |
 * Mx(A) = |   0      1     0    |
 *         | -sin(A)  0   cos(A) |
 *
 *         | 1    0        0     |
 * My(A) = | 0  cos(A)  -sin(A)  |
 *         | 0  sin(A)   cos(A)  |
 *
 *         | cos(A)  -sin(A)  0 |
 * Mz(Z) = | sin(A)   cos(A)  0 |
 *         |   0        0     1 |
 *
 * Углы поворота задаются в градусах.
 * Положительный угол - поворот против часовой стрелки.
 * Отрицательный угол - поворот по часвой стрелке.
 */
class TransformationUtils
{
public:

    TransformationUtils( float sh_x, float sh_y, float sh_z,
                         float route_angle_y, float route_angle_z );

    void route_angle_z(float *new_x, float *new_y);
    void route_angle_y(float *new_x, float *new_z);

    void shift(float *x, float *y, float *z);
    void shift(float *x, float *y);

private:

    float _sh_x;
    float _sh_y;
    float _sh_z;
    float _route_angle_y;
    float _route_angle_z;
};

#endif /* VTRANSFORMATION_H */
