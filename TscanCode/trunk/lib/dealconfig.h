/*
* Tencent is pleased to support the open source community by making TscanCode available.
* Copyright (C) 2015 THL A29 Limited, a Tencent company. All rights reserved.
* Licensed under the GNU General Public License as published by the Free Software Foundation, version 3 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
* http://www.gnu.org/licenses/gpl.html
* TscanCode is free software: you can redistribute it and/or modify it under the terms of License.    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR * A PARTICULAR PURPOSE.  See the GNU General Public License for more details. 
*/

#ifndef DEALCONFIG_H
#define DEALCONFIG_H
#pragma once
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string> 
#include <vector>
#include "tinyxml.h"
#include <map>
#include <list>

using namespace std;

// TSC:from TSC 20140918  add ExitProcess(win32)
//#define JUMPSTR "return|abort|exit|continue|break|goto|ExitProcess|throw"
static std::string JUMPSTR="return|abort|exit|continue|break|goto|ExitProcess|throw";

#define MAXERRORCNT 20
#define AUTOFILTER_SUBID "FuncPossibleRetNULL|FuncRetNULL|dereferenceAfterCheck|dereferenceBeforeCheck|possibleNullDereferenced|nullpointerarg|nullpointerclass"
struct CUSTOMNULLPOINTER
{
	string functionname;
	int var;
};
// TSC:from TSC 20131029
struct  CANNOTBENULL
{
	string functionname;
	int var;
};

// by TSC 20140912
// identify one method
struct SFuncSignature
{
	std::string classname;
	std::string functionname;
	std::vector<std::string> params;

	bool operator<(const SFuncSignature& funcSign) const
	{
		if (classname < funcSign.classname)
		{
			return true;
		}
		else if (classname == funcSign.classname)
		{
			if (functionname < funcSign.functionname)
			{
				return true;
			}
			else if (functionname == funcSign.functionname)
			{
				//bool bLess = false;
				if (params.size() != funcSign.params.size())
				{
					return params.size() < funcSign.params.size();
				}
				int paramCount = params.size();
				for (int i = 0; i<paramCount; i++)
				{
					if (params[i] < funcSign.params[i])
					{
						return true;
					}
					else if (params[i] == funcSign.params[i])
					{
						continue;
					}
					else
					{
						return false;
					}
				}
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
};
//add by TSC
void trim(string& str);
//string& trimall(string &str, string::size_type pos = 0);
void TrimLeft(string &str);
void TrimRight(string &str);
void TrimAll(string &str);
//int splitString(const string & strSrc, const std::string& strDelims, vector<string>& strDest);
class dealconfig {
public:
	static dealconfig* instance()
	{
		return &s_instance;
	}
	static void SetConfigDir(const char* szDir)
	{
		if (NULL != szDir)
		{
			s_strDir = szDir;
		}
		
		// init from files
		s_instance.readxmlconf();
		s_instance.readConfig();
		//s_instance.readCustomNullPointerList();
		//s_instance.readCustomNullPointerList2();
		//s_instance.readCustomNullPointerList2_overload();
		//s_instance.readJumpMacros();
		s_instance.isinit = true;
	}

private:
	static std::string s_strDir;
	static dealconfig s_instance;
public:
	bool isinit;

	bool writelog;

	bool showfuncinfo;
	bool Suspicious;
	bool compute;

	bool nullpointer;
	bool bufoverrun;
	bool logic;
	bool memleak;
	bool autovar;
	bool unsafeFun;
	bool portability64;

	bool explicitNullDereferenced;
	bool possibleNullDereferenced;
	bool dereferenceIfNull;
	bool nullPointerLinkedList;
	bool dereferenceAfterCheck;
	bool dereferenceBeforeCheck;
	bool FuncPossibleRetNULL;
	bool FuncRetNULL;
	bool nullpointer_arg;
	bool nullpointer_class;

	bool UnconditionalBreakinLoop;
	bool NoFirstCase;
	bool PreciseComparison;
	bool AssignAndCompute;
	bool SuspiciousPriority;
	bool RecursiveFunc;

	bool uninitvar;
	//checkclass�࣬this���ڼ�������ı��ʽ���磺�ֶ���this->д����this-x
	bool thisSubtraction;
	//checkAssinif�࣬��ƥ��ĸ�ֵ��Ƚϣ����½����ԶΪ����
	bool assignIf;
	//checkAssinif�࣬�Ⱥ��������߲�ƥ��
	bool comparison;
	//checkAssinif�࣬ƥ��if��else if �����ʽ����false����Ϊelse ifƥ��ǰһ������
	bool multiCondition;
	//if�ж������ظ����磺if (a) { b = 1; } else if (a) { b = 2; }
	bool DuplicateIf;
	//checkstl invalidIterator
	bool invalidIterator;
	/*
	//checkstl,���ɵ��жϣ���std::set<int> s;  if (s.find(12)) { };��ȷд��std::set<int> s; if (s.find(12) != s.end()) { }
	bool iffind;
	//��ͬ�����ĵ�����������һ��ʹ�ã��ܿ�����д����������д���ˡ��磺std::find(foo.begin(), bar.end(), x)
	bool mismatchingContainers;
	//ͨ��iteratorɾ��������Ԫ�س���
	bool eraseDereference;
	*/
	//��֧�����ظ�
	bool DuplicateBranch;;
	//���ʽ�ظ���if (a && a)��if( a>a)��
	bool DuplicateExpression;
	//�������������λ�����У���a && bд����a & b
	bool clarifyCondition;
	//switch���ظ���ֵ��������ȱ��break
	bool RedundantAssignmentInSwitch;
	//������Ϊ��������ʱ����������sizeof���㣬�õ�����ָ��Ĵ�С�����������С���ܿ�������õ������д�С����д���ˣ���sizeof������void f( int a[]) std::cout << sizeof(a) / sizeof(int) << std::endl��ʵ������sizeof(a)��Զ��4��ָ��ռ4���ֽڣ��������int a[10];cout<<sizeof(a)/sizeof(int)<<endl;������ȷ�ģ�����aû��Ϊ������sizeof(a)=40
	bool SizeofForArrayParameter;
	//��һ�����ֳ���ʹ��sizeof��������̲�����ô�ã����п���д���ˡ�
	bool SizeofForNumericParameter;
	//��ָ��ʹ����sizeof���õ��Ĳ���ʵ�����ݵĴ�С������ָ���С��4�ֽڣ�
	bool SizeofForPointerSize;
	///sizeofsizeof���ܿ������ֶ��ิ����һ������  int i = sizeof sizeof char;
	bool sizeofsizeof;
	//������ֵ��int����ֵ���бȽϣ���:if(!x==4)����֪��Ϊɶrun�����У�Simplifiedrun�л���
	bool ComparisonOfBoolExpressionWithInt;
	//���ɵķֺ�ʹ�ã���if/for/while����ֱ�Ӹ��ֺš���while(a==2);{a=b;}��for(i=0;i<5;i++);{cout<<i;}
	bool SuspiciousSemicolon;
	//�ַ������ַ�������ӣ�һ��Ϊ����ʹ�õ����š��ַ������ַ�������ӣ��൱���ַ���ָ��ƫ��N��NΪ�ַ�������ASC��ֵ��char�൱���������磺const char *p = "/usr" + '/';
	bool strPlusChar;
	//�����ͱ������ֱ����з��ź��޷������ͣ��ܿ��������Ͷ�����ˡ�int ivar = -2; unsigned int uvar = 2;return ivar / uvar;�������Ԥ�ڵ�-1������Division with signed and unsigned operators. The result might be wrong
	bool UnsignedDivision;
	//�ڶ����жԱ������и�ֵ�������д��λ���ˡ�������ֻ��debug����Ч�ĺ꣩
	bool AssignmentInAssert;
	//�෴���ڲ����������´��벻�ɴ�ܿ����������ж�д���ˡ�����:if(a==b){if(a!=b)cout<<a;}
	bool oppositeInnerCondition;
	//ȡģ��������ֵС�ڱ�ȡģ��ֵ�����±��ʽ����������Ǽ١���if(var%4==4)��һ�����ֶ��ѱ߽�ֵд����
	bool ModuloAlwaysTrueFalse;
	//����Ϊ0
	bool ZeroDivision;
	//����ֵ������λ������
	bool BitwiseOnBoolean;
	//������߼����㣬�磺�����棬�����Ǽ�
	bool IncorrectLogicOperator;
	//������ֵ��int����ֵ���бȽϣ���:if(!x==4)
	bool ComparisonOfBoolWithInt;
	//bool���ͱ�����ıȽϣ���������ֵ��bool������ȴ�Ը��ຯ��ʹ�ù�ϵ�����<,>,<=,>=.����  bool b = compare2(6);bool a = compare1(4); if(b > a){}
	bool ComparisonOfBoolWithBool;
	//switch ȱ��break �� default��ǿ�Ƽ��
	bool SwitchNoBreak;
	//switch default��ǿ�Ƽ��
	bool SwitchNoDefault;
	// check break UP
	bool SwitchNoBreakUP;
	//�Ը����Ҳ���������λ�����㣬�磺a=5;a<<-1
	bool NegativeBitwiseShift;
	//��bool����ʹ������������bool������ֵ���ܲ�����Ԥ�ڡ��磺bool bValue = true;bValue++;
	bool IncrementBoolean;
	//��boolֵ��ֵ��ָ�룬�п�����bool��������ʱ����˸�*����void foo(bool *p) {p = false;}
	bool AssignBoolToPointer;
	//����memset������ֻ���0�ֽڣ�һ���ǵ�2��3������д���ˡ��磺memset(p, sizeof(p), 0)����ȷд����memset(p,0,sizeof(p))
	bool MemsetZeroBytes;
	bool IfCondition;
	bool FuncReturn;
	//���ɳ����forѭ��
	bool suspiciousfor;
	bool wrongvarinfor;

	bool suspiciousArrayIndex;
	//TSC:from TSC 20140726
	bool formatbufoverrun;
	//��Ա����δ��ʼ��
	bool uninitMemberVar;
	//end TSC
	bool nestedloop;
	//�޷�����С��0
	bool Unsignedlessthanzero;
	//bool���������˷�boolֵ
	bool BoolFuncReturn;
	// add by TSC, 20014-08-27
	// Validate the methods which have variable parameters 
	bool InvalidVarArgs;

	//std::string JumpMacrosConf;
    vector<CUSTOMNULLPOINTER> m_CustomPointerlList;
	// TSC:from  20131029
	vector<CANNOTBENULL> f_CustomPointerlList;
	// TSC:from  20140903
	vector<SFuncSignature> func_CustomPointerlList;
	
	dealconfig();
	~dealconfig();
	//from TSC init checks
	void init_true();
	void init_false();
	//from TSC handle checklist.xml and CustomNullPointerList.ini
	bool isOpen(const char* str);
	bool readxmlconf();
	void readCustomNullPointerList();
	void readCustomNullPointerList2();
	void readCustomNullPointerList2_overload();
	//from TSC 20141112 handle JumpMacros.ini
	void readJumpMacros();
	SFuncSignature parseFuncInfo(string funcinfo);

	void readConfig();

	void DumpCfg();

};


class IniParser
{
public:
	struct SPair
	{
		std::string sKey;
		std::string sValue;
	};
public:
	bool Parse(const std::string& iniPath);
	bool GetSection(const std::string& sName, std::list<SPair>*& pMapKeyValue);
private:
	std::map<std::string, std::list<SPair> > m_ini;
};

#endif // DEALCONFIG_H