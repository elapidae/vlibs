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


#ifndef VCOMPILER_H
#define VCOMPILER_H


//=======================================================================================
#ifdef __GNUC__
    //===================================================================================
    #define V_GNUC_COMPILER_VERSION ( (__GNUC__            * 0x10000) + \
                                      (__GNUC_MINOR__      *   0x100) + \
                                      (__GNUC_PATCHLEVEL__          )   \
                                    )
    //===================================================================================
#else
    //===================================================================================
    #error "Unknown compiler"
    //===================================================================================
#endif // __GNUC__
//=======================================================================================


//=======================================================================================
// V_NOEXCEPT_SIGNATURE_WARNING_ENABLED -- выставляется когда версия компилятора
//  достаточно высока, чтобы выдать такое сообщение: "<надо еще получить :(>"
//  NB! С версией не уверен.
#define V_NOEXCEPT_SIGNATURE_WARNING_ENABLED (V_GNUC_COMPILER_VERSION > 0x040703)
//=======================================================================================


//=======================================================================================
// V_NORETURN_ENABLED -- выставляется когда компилятор в состоянии опознать [[noreturn]].
//  NB! С версией не уверен.
//  Use V_NORETURN macro instead of real [[noreturn]] :((
#define V_NORETURN_ENABLED (V_GNUC_COMPILER_VERSION > 0x040703)
#if V_NORETURN_ENABLED
    #define V_NORETURN [[noreturn]]
#else
    #define V_NORETURN
#endif
//=======================================================================================


//=======================================================================================
// V_CONTAINERS_HAS_EMPLACE -- выставляется когда контейнеры стандартной библиотеки,
//  такие как map, set, unordered_map etc обучены emplace().
//  NB! С версией не уверен.
#define V_CONTAINERS_HAS_EMPLACE (V_GNUC_COMPILER_VERSION > 0x040703)
//=======================================================================================


//=======================================================================================
// V_CAN_VARIADIC_TEMPLATES_IN_LAMBDAS -- может работать с variadic templates с лямбдами.
//  См. vapplication/vinvoke_iface
//  NB! С версией не уверен.
#define V_CAN_VARIADIC_TEMPLATES_IN_LAMBDAS (V_GNUC_COMPILER_VERSION > 0x040804)
//=======================================================================================


//=======================================================================================
// V_COMPILER_KNOWS_THREAD_LOCAL -- знает keyword thread_local.
//  См. vapplication/vpoll
//  NB! С версией не уверен.
#define V_COMPILER_KNOWS_THREAD_LOCAL (V_GNUC_COMPILER_VERSION > 0x040703)
//=======================================================================================


#endif // VCOMPILER_H
