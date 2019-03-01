#ifndef VTYPE_TRAITS_H
#define VTYPE_TRAITS_H

#include <type_traits>
#include <stddef.h>

#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

//===== std::array ======================================================================
//template<typename T> struct _v_is_array : std::false_type {};
//template<typename T> struct _v_is_array<std::array<T>> : std::true_type {};
//template<typename T> static constexpr
//bool v_is_array()  { return _v_is_array<T>::value; }


//===== std::vector =====================================================================
template<typename T> struct _v_is_vector : std::false_type {};
template<typename T> struct _v_is_vector<std::vector<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_vector()  { return _v_is_vector<T>::value; }

//===== std::list =======================================================================
template<typename T> struct _v_is_list : std::false_type {};
template<typename T> struct _v_is_list<std::list<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_list() { return _v_is_list<T>::value; }

//===== std::forward_list ===============================================================
template<typename T> struct _v_is_forward_list : std::false_type {};
template<typename T> struct _v_is_forward_list<std::forward_list<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_forward_list() { return _v_is_forward_list<T>::value; }

//===== std::deque ======================================================================
template<typename T> struct _v_is_deque : std::false_type {};
template<typename T> struct _v_is_deque<std::deque<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_deque() { return _v_is_deque<T>::value; }

//===== std::stack ======================================================================
template<typename T> struct _v_is_stack : std::false_type {};
template<typename T> struct _v_is_stack<std::stack<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_stack() { return _v_is_stack<T>::value; }

//===== std::queue ======================================================================
template<typename T> struct _v_is_queue : std::false_type {};
template<typename T> struct _v_is_queue<std::queue<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_queue() { return _v_is_queue<T>::value; }


//===== std::set ======================================================================
template<typename T> struct _v_is_set : std::false_type {};
template<typename T> struct _v_is_set<std::set<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_set() { return _v_is_set<T>::value; }

//===== std::multiset ===================================================================
template<typename T> struct _v_is_multiset : std::false_type {};
template<typename T> struct _v_is_multiset<std::multiset<T>> : std::true_type {};
template<typename T> static constexpr
bool v_is_multiset() { return _v_is_multiset<T>::value; }

//===== std::unordered_set ==============================================================
template<typename T> struct _v_is_unordered_set : std::false_type {};
template<typename T> struct _v_is_unordered_set<std::unordered_set<T>>: std::true_type{};
template<typename T> static constexpr
bool v_is_unordered_set() { return _v_is_unordered_set<T>::value; }

//===== std::unordered_multiset =========================================================
template<typename T> struct _v_is_unordered_multiset : std::false_type {};
template<typename T> struct _v_is_unordered_multiset<std::unordered_multiset<T>>
                            : std::true_type {};
template<typename T> static constexpr
bool v_is_unordered_multiset() { return _v_is_unordered_multiset<T>::value; }


//=======================================================================================
//template<typename T> static constexpr
//bool v_is_container()
//{
//    return  v_is_deque<T>()                 ||
//            v_is_forward_list<T>()          ||
//            v_is_list<T>()                  ||
//            v_is_multiset<T>()              ||
//            v_is_queue<T>()                 ||
//            v_is_set<T>()                   ||
//            v_is_stack<T>()                 ||
//            v_is_unordered_multiset<T>()    ||
//            v_is_unordered_set<T>()         ||
//            v_is_vector<T>();
//}
//=======================================================================================
//template<typename T> static constexpr
//const char* v_container_signature()
//{
//    static_assert ( v_is_container<T>(), "Not a declared container" );

//    return  v_is_deque<T>()                 ? "std::deque"  :
//            v_is_forward_list<T>()          ? "forward_list" :
//            v_is_list<T>()                  ? "list" :
//            v_is_multiset<T>()              ? "multiset" :
//            v_is_queue<T>()                 ? "queue" :
//            v_is_set<T>()                   ? "set" :
//            v_is_stack<T>()                 ||
//            v_is_unordered_multiset<T>()    ||
//            v_is_unordered_set<T>()         ||
//            v_is_vector<T>();
//}
//=======================================================================================


//===== std::map ========================================================================
//template<typename T,typename U> struct _v_is_map : std::false_type {};
//template<typename T,typename U> struct _v_is_map<std::map<T,U>> : std::true_type {};
//template<typename T,typename U> static constexpr
//bool v_is_map() { return _v_is_map<T,U>::value; }

////===== std::multimap ======================================================================
//template<typename T> struct _v_is_multimap : std::false_type {};
//template<typename T> struct _v_is_multimap<std::multimap<T>> : std::true_type {};
//template<typename T> static constexpr
//bool v_is_multimap() { return _v_is_multimap<T>::value; }

////===== std::unordered_map ======================================================================
//template<typename T> struct _v_is_unordered_map : std::false_type {};
//template<typename T> struct _v_is_unordered_map<std::unordered_map<T>> : std::true_type {};
//template<typename T> static constexpr
//bool v_is_unordered_map() { return _v_is_unordered_map<T>::value; }

////===== std::unordered_multimap ======================================================================
//template<typename T> struct _v_is_unordered_multimap : std::false_type {};
//template<typename T> struct _v_is_unordered_multimap<std::unordered_multimap<T>> : std::true_type {};
//template<typename T> static constexpr
//bool v_is_unordered_multimap() { return _v_is_unordered_multimap<T>::value; }






//=======================================================================================

//template<typename T, typename U = void>
//struct _v_has_value_type: std::false_type {};

//template<typename T>
//struct _v_has_value_type<T, typename T::value_type>: std::true_type {};

//template<typename T>
//static constexpr bool v_has_value_type =
//        _v_has_value_type<T,typename T::value_type>::value;

////=======================================================================================

//template<typename T>
//using _v_begin_iterator_type = decltype( T().begin() );
//template<typename T>
//using _v_end_iterator_type = decltype( T().end() );
//template<typename T>
//using _v_size_type = decltype( T().size() );


//template<typename T, typename = void>
//struct _v_correct_container: std::false_type {};

//template<typename T>
//struct _v_correct_container< T,
//        typename std::enable_if<(std::is_same<_v_begin_iterator_type<T>,
//                                              _v_end_iterator_type<T>>::value &&
//                                 std::is_same<_v_size_type<T>,size_t>::value),
//                            void>::type>
//    : std::true_type
//{};

//template<typename T>
//static constexpr auto v_correct_container = _v_correct_container<T>::value &&
//                                            v_has_value_type<T>;

//=======================================================================================



#endif // VTYPE_TRAITS_H
