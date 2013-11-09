#ifndef BOOST_PP_IS_ITERATING

#ifndef _SERIALIZATION_UTILS_H
#define _SERIALIZATION_UTILS_H

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/comparison.hpp>
namespace Serialization
{
    template<typename T>
    T* SerializeCreate(const T& obj)
    {
        return new T();
    }

    template<typename T>
    T* SerializeCreate()
    {
        return new T();
    }

    #define m 4
    #define BOOST_PP_ITERATION_LIMITS   (1,m)
    #define BOOST_PP_FILENAME_1 "utils.h"
    #include BOOST_PP_ITERATE() 
    #undef m
}
#endif //_SERIALIZATION_UTILS_H

#else //BOOST_PP_IS_ITERATING

#define n BOOST_PP_ITERATION()
#define Insertor BOOST_PP_CAT(PlaceholderInsertor,n)
template<BOOST_PP_ENUM_PARAMS(n,typename T),template<BOOST_PP_ENUM_PARAMS(n,typename U)> class Seq>
struct Insertor
{
    typedef T0& type;

    static type Insert(Seq<BOOST_PP_ENUM_PARAMS(n,T)>& seq)
    {
        auto it = seq.insert(seq.end(),T0());
        return const_cast<type>(*it);
    }
};

#define SEP BOOST_PP_COMMA_IF(BOOST_PP_GREATER(n,1))
template<BOOST_PP_ENUM_PARAMS(n,typename T), template<BOOST_PP_ENUM_PARAMS(n,typename U)> class Seq>
struct Insertor<T0* SEP  BOOST_PP_ENUM_SHIFTED_PARAMS(n,T) SEP BOOST_PP_COMMA_IF(BOOST_PP_EQUAL(n,1)) Seq>
{
    typedef T0* type;

    static type Insert(Seq<T0* SEP BOOST_PP_ENUM_SHIFTED_PARAMS(n,T)>& seq)
    {
        auto it = seq.insert(seq.end(),SerializeCreate<T0>());
        return const_cast<type>(*it);
    }
};

template<BOOST_PP_ENUM_PARAMS(n,typename T),template<BOOST_PP_ENUM_PARAMS(n,typename U)> class Seq>
typename Insertor<BOOST_PP_ENUM_PARAMS(n,T),Seq>::type InsertPlaceholder(Seq<BOOST_PP_ENUM_PARAMS(n,T)>& seq)
{
    return Insertor<BOOST_PP_ENUM_PARAMS(n,T),Seq>::Insert(seq);
}
#undef SEP
#undef Insertor
#undef n
#endif//BOOST_PP_IS_ITERATING

