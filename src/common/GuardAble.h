#ifndef _GUARDABLE_H
#define _GUARDABLE_H

template<typename T>
struct GuardAble:T
{
    GuardAble():mFlag(true){}

    GuardAble(typename T::type& u)
	:T(u)
	,mFlag(true)
    {}

    GuardAble(typename T::type & u,const std::string& expr)
	:T(u,expr)
	,mFlag(true)
    {}

    operator bool ()
    {
        bool prev = mFlag; 
        mFlag = false; 
        return prev;
    }
private:
    bool mFlag;
};

#define GUARD(T,expr) for(GuardAble<T> __guard__(expr);__guard__;)
#endif

