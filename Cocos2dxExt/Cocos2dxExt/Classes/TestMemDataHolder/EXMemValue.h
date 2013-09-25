//
//  EXMemValue.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-8-8.
//
//

#ifndef __Cocos2dxExt__EXMemValue__
#define __Cocos2dxExt__EXMemValue__

#include "cocos2d.h"
USING_NS_CC;

template<class T>
class EXMemValue
{
public:
	EXMemValue()
    : m_value(0)
	{
	}
	~EXMemValue()
	{
	}
    
	T getValue()
	{
		return m_value ^ m_memKey;
	}
    
	void setValue(T value)
	{
		m_value = value;
		m_memKey = arc4random();
		m_value ^= m_memKey;
	}
    
	void offset(T value)
	{
		setValue(getValue() + value);
	}
    
public:
	T m_value;
	int m_memKey;
};

typedef EXMemValue<int> DynamicValueInt;
typedef EXMemValue<float> DynamicValueFloat;
typedef EXMemValue<bool> DynamicValueBool;

#endif /* defined(__Cocos2dxExt__EXMemValue__) */
