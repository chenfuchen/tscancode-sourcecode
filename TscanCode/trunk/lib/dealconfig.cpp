/*
* Tencent is pleased to support the open source community by making TscanCode available.
* Copyright (C) 2015 THL A29 Limited, a Tencent company. All rights reserved.
* Licensed under the GNU General Public License as published by the Free Software Foundation, version 3 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
* http://www.gnu.org/licenses/gpl.html
* TscanCode is free software: you can redistribute it and/or modify it under the terms of License.    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR * A PARTICULAR PURPOSE.  See the GNU General Public License for more details. 
*/


#include "dealconfig.h"
#include "FileDepend.h"
#include "path.h"


dealconfig dealconfig::s_instance;
std::string dealconfig::s_strDir;

void dealconfig::init_true()
{
	Suspicious = true;
    compute = true;
    nullpointer = true;
    bufoverrun = true;
    logic = true;
    memleak = true;
    autovar = true;

	explicitNullDereferenced=true;
    dereferenceAfterCheck = true;
    dereferenceBeforeCheck = true;
	FuncRetNULL = true; 
	dereferenceIfNull = true;
	nullPointerLinkedList=true;
    UnconditionalBreakinLoop = true;
    NoFirstCase = true;
    AssignAndCompute = true;
    SuspiciousPriority = true;
    RecursiveFunc = true;

    uninitvar = true;
    //checkclass�࣬this���ڼ�������ı��ʽ���磺�ֶ���this->д����this-x
    thisSubtraction = true;
    //checkAssinif�࣬��ƥ��ĸ�ֵ��Ƚϣ����½����ԶΪ����
    assignIf = true;
    //checkAssinif�࣬�Ⱥ��������߲�ƥ��
    comparison = true;
    //checkAssinif�࣬ƥ��if��else if �����ʽ����false����Ϊelse ifƥ��ǰһ������
    multiCondition = true;
    //if�ж������ظ����磺if (a) { b = 1; } else if (a) { b = 2; }
    DuplicateIf = true;
   
	invalidIterator=true;

    //��֧�����ظ�
    DuplicateBranch = true;;
    //���ʽ�ظ���if (a && a)��if( a>a)��
    DuplicateExpression = true;
    //�������������λ�����У���a && bд����a & b
    clarifyCondition = true;
    //switch���ظ���ֵ��������ȱ��break
    RedundantAssignmentInSwitch = true;
    //������Ϊ��������ʱ����������sizeof���㣬�õ�����ָ��Ĵ�С�����������С���ܿ�������õ������д�С����д���ˣ���sizeof������void f( int a[]) std::cout << sizeof(a) / sizeof(int) << std::endl��ʵ������sizeof(a)��Զ��4��ָ��ռ4���ֽڣ��������int a[10];cout<<sizeof(a)/sizeof(int)<<endl;������ȷ�ģ�����aû��Ϊ������sizeof(a)=40
    SizeofForArrayParameter = true;
    //��һ�����ֳ���ʹ��sizeof��������̲�����ô�ã����п���д���ˡ�
    SizeofForNumericParameter = true;
    //��ָ��ʹ����sizeof���õ��Ĳ���ʵ�����ݵĴ�С������ָ���С��4�ֽڣ�
    SizeofForPointerSize = true;
    ///sizeofsizeof���ܿ������ֶ��ิ����һ������  int i = sizeof sizeof char;
    sizeofsizeof = true;
    //������ֵ��int����ֵ���бȽϣ���:if(!x==4)����֪��Ϊɶrun�����У�Simplifiedrun�л���
    ComparisonOfBoolExpressionWithInt = true;
    //���ɵķֺ�ʹ�ã���if/for/while����ֱ�Ӹ��ֺš���while(a==2);{a=b;}��for(i=0;i<5;i++);{cout<<i;}
    SuspiciousSemicolon = true;
    //�ַ������ַ�������ӣ�һ��Ϊ����ʹ�õ����š��ַ������ַ�������ӣ��൱���ַ���ָ��ƫ��N��NΪ�ַ�������ASC��ֵ��char�൱���������磺const char *p = "/usr" + '/';
    strPlusChar = true;
    //�����ͱ������ֱ����з��ź��޷������ͣ��ܿ��������Ͷ�����ˡ�int ivar = -2; unsigned int uvar = 2;return ivar / uvar;�������Ԥ�ڵ�-1������Division with signed and unsigned operators. The result might be wrong
    UnsignedDivision = true;
    //�ڶ����жԱ������и�ֵ�������д��λ���ˡ�������ֻ��debug����Ч�ĺ꣩
    AssignmentInAssert = true;
    //�෴���ڲ����������´��벻�ɴ�ܿ����������ж�д���ˡ�����:if(a==b){if(a!=b)cout<<a;}
    oppositeInnerCondition = true;
    //ȡģ��������ֵС�ڱ�ȡģ��ֵ�����±��ʽ����������Ǽ١���if(var%4==4)��һ�����ֶ��ѱ߽�ֵд����
    ModuloAlwaysTrueFalse = true;
    //����Ϊ0
    ZeroDivision = true;
    //����ֵ������λ������
    BitwiseOnBoolean = true;
    //������߼����㣬�磺�����棬�����Ǽ�
    IncorrectLogicOperator = true;
    //������ֵ��int����ֵ���бȽϣ���:if(!x==4)
    ComparisonOfBoolWithInt = true;
    //bool���ͱ�����ıȽϣ���������ֵ��bool������ȴ�Ը��ຯ��ʹ�ù�ϵ�����<,>,<=,>=.����  bool b = compare2(6);bool a = compare1(4); if(b > a){}
    ComparisonOfBoolWithBool = true;
    SwitchNoBreakUP = true;
    //�Ը����Ҳ���������λ�����㣬�磺a=5;a<<-1
    NegativeBitwiseShift = true;
    //��bool����ʹ������������bool������ֵ���ܲ�����Ԥ�ڡ��磺bool bValue = true;bValue++;
    IncrementBoolean = true;
    //��boolֵ��ֵ��ָ�룬�п�����bool��������ʱ����˸�*����void foo(bool *p) {p = false;}
    AssignBoolToPointer = true;
    //����memset������ֻ���0�ֽڣ�һ���ǵ�2��3������д���ˡ��磺memset(p, sizeof(p), 0)����ȷд����memset(p,0,sizeof(p))
    MemsetZeroBytes = true;
    IfCondition = true;
    suspiciousfor = true;
    wrongvarinfor = true;
    formatbufoverrun = true;  
   
    Unsignedlessthanzero = true;
    BoolFuncReturn = true;
	InvalidVarArgs = true;
}
void dealconfig::init_false()
{
	unsafeFun = false;
    portability64 = false;
	FuncPossibleRetNULL = false;
	possibleNullDereferenced=false;
	nullpointer_arg = false;
	nullpointer_class = false;

	suspiciousArrayIndex = false;
	PreciseComparison = false;
	SwitchNoBreak = false;
    SwitchNoDefault = false;
	nestedloop = false;
	FuncReturn = false;
	uninitMemberVar = false;
}
dealconfig::dealconfig()
{
	isinit=false;
	writelog=false;
    showfuncinfo = false;

	init_true();
	init_false();
    m_CustomPointerlList.clear();

}

void trim(string& str)
{
	str.erase(str.find_last_not_of(' ') + 1, string::npos);
	str.erase(0, str.find_first_not_of(' '));
}

void trim_2(string& str)
{
    str.erase(str.find_last_not_of(" \t\n\r") + 1, string::npos);
    str.erase(0, str.find_first_not_of(" \t\n\r"));
}

void TrimLeft(string &str)//ȥ��߿ո�
{
	size_t index;
	index = str.find_first_not_of(" \t\n");
	if (index != string::npos)
	{
		str.erase(0,index);
	}
}
void TrimRight(string &str)//ȥ�ұ߿ո�
{
	size_t index;
	index = str.find_last_not_of(" \t\n");
	if (index != string::npos)
	{
		str = str.substr(0,index+1);
	}
}
void TrimAll(string &str)//ȥ���пո�
{
	TrimLeft(str);
	TrimRight(str);
}

bool dealconfig::isOpen(const char* str)
{
	if(strcmp(str, "0") == 0){
		return false;
	}
	else{
	    return true;
	}
}
//from TSC read config file "checklist.xml";
bool dealconfig::readxmlconf()
{
    TiXmlDocument doc;

	std::string filePath = s_strDir + "checklist.xml";
    if (doc.LoadFile(filePath.c_str()))
    {
        TiXmlElement *node = doc.FirstChildElement();

        if(!node)
            return false;

        const char* ttt = node->Value();

        if(!ttt)
            return false;
		   //log
        TiXmlElement *log_conf = node->FirstChildElement("log");

        if(log_conf && log_conf->Attribute("isopen"))
        {
			const char* str=log_conf->Attribute("isopen");
            writelog = isOpen(str);
        }

        //showfuncinfo_conf
        TiXmlElement *showfuncinfo_conf = node->FirstChildElement("showfuncinfo");

        if(showfuncinfo_conf && showfuncinfo_conf->Attribute("isopen"))
        {
			const char* str=showfuncinfo_conf->Attribute("isopen");
            showfuncinfo = isOpen(str);
        }

        //	nullpointer_conf
        TiXmlElement *nullpointer_conf = node->FirstChildElement("nullpointer");

        if(nullpointer_conf && nullpointer_conf->Attribute("isopen"))
        {
			const char* str=nullpointer_conf->Attribute("isopen");
            nullpointer = isOpen(str);
        }
		TiXmlElement *sub=NULL;
		if(nullpointer_conf)
		{
			sub = nullpointer_conf->FirstChildElement("subid");

        for(; sub; sub = sub->NextSiblingElement())
        {
            ttt = sub->Attribute("name");

			if(strcmp(ttt, "possibleNullDereferenced") == 0  && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                possibleNullDereferenced = isOpen(str);
                continue;
            }

            if(strcmp(ttt, "explicitNullDereferenced") == 0 && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                explicitNullDereferenced = isOpen(str);
                continue;
            }
            if(strcmp(ttt, "dereferenceAfterCheck") == 0 && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                dereferenceAfterCheck = isOpen(str);
                continue;
            }

            if(strcmp(ttt, "dereferenceBeforeCheck") == 0 && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                dereferenceBeforeCheck = isOpen(str);
                continue;
            }

            if(strcmp(ttt, "FuncPossibleRetNULL") == 0 && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                FuncPossibleRetNULL = isOpen(str);
                continue;
            }

            if(strcmp(ttt, "FuncRetNULL") == 0 && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                FuncRetNULL = isOpen(str);
                continue;
            }


            if(strcmp(ttt, "nullpointerarg") == 0 && sub->Attribute("isopen") )
            {
				const char* str=sub->Attribute("isopen");
                nullpointer_arg = isOpen(str);
                continue;
            }

			if(strcmp(ttt, "nullpointerclass") == 0 && sub->Attribute("isopen") )
            {
				const char* str=sub->Attribute("isopen");
                nullpointer_class = isOpen(str);
                continue;
            }
			if(strcmp(ttt, "dereferenceIfNull") == 0 && sub->Attribute("isopen") )
            {
				const char* str=sub->Attribute("isopen");
                dereferenceIfNull = isOpen(str);
                continue;
            }
			if(strcmp(ttt, "nullPointerLinkedList") == 0 && sub->Attribute("isopen") )
			{
				const char* str=sub->Attribute("isopen");
				nullPointerLinkedList = isOpen(str);
				continue;
			}
        }
	}
        //	bufoverrun_conf
        TiXmlElement *bufoverrun_conf = node->FirstChildElement("bufoverrun");

        if(bufoverrun_conf && bufoverrun_conf->Attribute("isopen"))
        {
			const char* str=bufoverrun_conf->Attribute("isopen");
            bufoverrun = isOpen(str);
        }
		if(bufoverrun_conf)
		{
        //from TSC 20140726
        sub = bufoverrun_conf->FirstChildElement("subid");

        if(sub)
            ttt = sub->Value();

        for(; sub; sub = sub->NextSiblingElement())
        {
            ttt = sub->Attribute("name");

            if(strcmp(ttt, "formatbufoverrun") == 0 && sub->Attribute("isopen"))
            {
				const char* str=sub->Attribute("isopen");
                formatbufoverrun = isOpen(str);
                continue;
            }
        }
        //end bufoverrun_conf
		}
        //	memleak_conf
        TiXmlElement *memleak_conf = node->FirstChildElement("memleak");

        if(memleak_conf && memleak_conf->Attribute("isopen"))
        {
			const char* str=memleak_conf->Attribute("isopen");
            memleak = isOpen(str);
        }

        //	unsafeFun_conf
        TiXmlElement *unsafeFun_conf = node->FirstChildElement("unsafeFunc");

        if(unsafeFun_conf && unsafeFun_conf->Attribute("isopen"))
        {
			const char* str=unsafeFun_conf->Attribute("isopen");
            unsafeFun = isOpen(str);
        }

        //logic
        TiXmlElement *logic_conf = node->FirstChildElement("logic");

        if(logic_conf)
        {
            if(logic_conf->Attribute("isopen"))
            {
				const char* str=logic_conf->Attribute("isopen");
                logic = isOpen(str);
            }

            sub = logic_conf->FirstChildElement("subid");

            if(sub)
                ttt = sub->Value();

            for(; sub; sub = sub->NextSiblingElement())
            {
                ttt = sub->Attribute("name");

                if(strcmp(ttt, "uninitvar") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    uninitvar = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "assignIf") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    assignIf = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "NoFirstCase") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    NoFirstCase = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "RecursiveFunc") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    RecursiveFunc = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "comparison") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    comparison = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "DuplicateIf") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    DuplicateIf = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "DuplicateBranch") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    DuplicateBranch = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "DuplicateExpression") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    DuplicateExpression = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "clarifyCondition") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    clarifyCondition = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SwitchNoDefault") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    SwitchNoDefault = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SwitchNoBreakUP") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    SwitchNoBreakUP = isOpen(str);
                    continue;
                }
				if(strcmp(ttt, "ComparisonOfBoolWithInt") == 0 && sub->Attribute("isopen") )
				{
					const char* str=sub->Attribute("isopen");
					ComparisonOfBoolWithInt = isOpen(str);
					continue;
				}
				
                if(strcmp(ttt, "ComparisonOfBoolExpressionWithInt") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    ComparisonOfBoolExpressionWithInt = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "oppositeInnerCondition") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    oppositeInnerCondition = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "BitwiseOnBoolean") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    BitwiseOnBoolean = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "IncorrectLogicOperator") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    IncorrectLogicOperator = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "ComparisonOfBoolExpressionWithInt") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    ComparisonOfBoolExpressionWithInt = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "ComparisonOfBoolWithBool") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    ComparisonOfBoolWithBool = isOpen(str);
                    continue;
                }

                //from TSC 20140726
                if(strcmp(ttt, "uninitMemberVar") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    uninitMemberVar = isOpen(str);
                    continue;
                }

				if(strcmp(ttt, "InvalidVarArgs") == 0 && sub->Attribute("isopen") )
				{
					const char* str=sub->Attribute("isopen");
					InvalidVarArgs = isOpen(str);
					continue;
				}
            }
        }

        //Suspicious_conf
        TiXmlElement *Suspicious_conf = node->FirstChildElement("Suspicious");

        if(Suspicious_conf)
        {
            if(Suspicious_conf->Attribute("isopen"))
            {
				const char* str=Suspicious_conf->Attribute("isopen");
                Suspicious = isOpen(str);
            }

            sub = Suspicious_conf->FirstChildElement("subid");

            if(sub)
                ttt = sub->Value();

            for(; sub; sub = sub->NextSiblingElement())
            {
                ttt = sub->Attribute("name");
                if(strcmp(ttt, "suspiciousArrayIndex") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    suspiciousArrayIndex = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "thisSubtraction") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    thisSubtraction = isOpen(str);
                    continue;
                }
                if(strcmp(ttt, "UnconditionalBreakinLoop") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    UnconditionalBreakinLoop = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "AssignmentInAssert") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    AssignmentInAssert = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SuspiciousSemicolon") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    SuspiciousSemicolon = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "AssignBoolToPointer") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    AssignBoolToPointer = isOpen(str);
                    continue;
                }
                if(strcmp(ttt, "IfCondition") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    IfCondition = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "FuncReturn") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    FuncReturn = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "strPlusChar") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    strPlusChar = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "MemsetZeroBytes") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    MemsetZeroBytes = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SuspiciousPriority") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    SuspiciousPriority = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "suspiciousfor") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    suspiciousfor = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "nestedloop") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    nestedloop = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "wrongvarinfor") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    wrongvarinfor = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "autovar") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    autovar = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "portability64") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    portability64 = isOpen(str);
                    continue;
                }

				if(strcmp(ttt, "BoolFuncReturn") == 0 && sub->Attribute("isopen"))
				{
					const char* str=sub->Attribute("isopen");
					BoolFuncReturn = isOpen(str);
					continue;
				}
				if(strcmp(ttt, "invalidIterator") == 0 && sub->Attribute("isopen"))
				{
					const char* str=sub->Attribute("isopen");
					invalidIterator = isOpen(str);
					continue;
				}
            }
        }

        //compute_conf
        TiXmlElement *compute_conf = node->FirstChildElement("compute");

        if(compute_conf)
        {
            if(compute_conf->Attribute("isopen"))
            {
				const char* str=compute_conf->Attribute("isopen");
                compute = isOpen(str);
            }

            sub = compute_conf->FirstChildElement("subid");

            if(sub)
                ttt = sub->Value();

            for(; sub; sub = sub->NextSiblingElement())
            {
                ttt = sub->Attribute("name");

                if(strcmp(ttt, "AssignAndCompute") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    AssignAndCompute = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "PreciseComparison") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    PreciseComparison = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "UnsignedDivision") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    UnsignedDivision = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "UnsignedDivision") == 0 && strcmp(sub->Attribute("isopen"), "0") == 0)
                {
					const char* str=sub->Attribute("isopen");
                    UnsignedDivision = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "ModuloAlwaysTrueFalse") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    ModuloAlwaysTrueFalse = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "Unsignedlessthanzero") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    Unsignedlessthanzero = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "ZeroDivision") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    ZeroDivision = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "NegativeBitwiseShift") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    NegativeBitwiseShift = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "IncrementBoolean") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    IncrementBoolean = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SizeofForArrayParameter") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    SizeofForArrayParameter = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SizeofForNumericParameter") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    SizeofForNumericParameter = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "sizeofsizeof") == 0 && sub->Attribute("isopen") )
                {
					const char* str=sub->Attribute("isopen");
                    sizeofsizeof = isOpen(str);
                    continue;
                }

                if(strcmp(ttt, "SizeofForPointerSize") == 0 && sub->Attribute("isopen"))
                {
					const char* str=sub->Attribute("isopen");
                    SizeofForPointerSize = isOpen(str);
                    continue;
                }
            }
        }
		return true;
    }
    else
    {
        cout << "û���ҵ�checklist.xml�����ļ������������ļ��Ƿ���ڣ�" << endl;
        return false;
    }
}


dealconfig::~dealconfig()
{
}

void dealconfig::readCustomNullPointerList()
{
	std::string filePath = s_strDir + "CustomNullPointerCheckList.ini";
    fstream cfgFile(filePath.c_str());

    if(!cfgFile)
    {
        cout << "û���ҵ�CustomNullPointerCheckList.ini�����ļ������������ļ��Ƿ���ڣ�" << endl;
        return;
    }

    char tmp[1000] = {0};

    while(!cfgFile.eof())
    {
        cfgFile.getline(tmp, 1000); //ÿ�ж�ȡǰ1000���ַ���1000���㹻��
        //ȥ��ע��
        if(tmp[0] == '#' || tmp[0] < 0)
        {
            continue;
        }

        string line(tmp);

        //ȥ������
        if(line.length() == 0)
        {
            continue;
        }

        size_t pos = line.find('=');//�ҵ�ÿ�еġ�=����λ�ã�֮ǰ��key֮����value

        if(pos == string::npos)
        {
            continue ;
        }

        string tmpKey = line.substr(0, pos); //ȡ=��֮ǰ
        trim(tmpKey);
        string value;//��Ӧ����ֵ
        value = line.substr(pos + 1); //ȡ=��֮��
        CUSTOMNULLPOINTER temp;
        int i = atoi(value.c_str());

        if ( i != 0)
        {
            temp.functionname = tmpKey;
            temp.var = i;
            m_CustomPointerlList.push_back(temp);
        }
    }

    cfgFile.close();
}

void dealconfig::readCustomNullPointerList2()
{
	std::string filePath = s_strDir + "CustomNullPointerCheckList2.ini";
	fstream cfgFile(filePath.c_str());
    if(!cfgFile)
    {
        return;
    }

    char tmp[1000];

    while(!cfgFile.eof())
    {
        cfgFile.getline(tmp, 1000); //ÿ�ж�ȡǰ1000���ַ���1000���㹻��

        //ȥ��ע��
        if(tmp[0] == '#')
        {
            continue;
        }

        string line(tmp);

        //ȥ������
        if(line.length() == 0)
        {
            continue;
        }

        size_t pos = line.find('=');//�ҵ�ÿ�еġ�=����λ�ã�֮ǰ��key֮����value
        if (pos == string::npos)
        {
            continue;
        }
		string tmpKey = line.substr(0, pos); //ȡ=��֮ǰ
		trim(tmpKey);
        string value;//��Ӧ����ֵ
		value = line.substr(pos + 1); //ȡ=��֮��
        CANNOTBENULL temp;
        int i = atoi(value.c_str());

        if ( i != 0)
        {
            temp.functionname = tmpKey;
            temp.var = i;
            f_CustomPointerlList.push_back(temp);
        }
    }

    cfgFile.close();
}

void dealconfig::readCustomNullPointerList2_overload()
{
	std::string filePath = s_strDir + "CustomNullPointerCheckList2.ini";
	fstream cfgFile(filePath.c_str());

	if(!cfgFile)
	{
		//cout<<"û���ҵ�CustomNullPointerCheckList2.ini�����ļ������������ļ��Ƿ���ڣ�"<<endl;
		return;
	}

	char tmp[1000];

	while(!cfgFile.eof())
	{
		cfgFile.getline(tmp, 1000); //ÿ�ж�ȡǰ1000���ַ���1000���㹻��

		if(tmp[0] == '#')//ȥ��ע��
			continue;

		string line(tmp);

		if(line.length() == 0)//ȥ������
			continue;

		SFuncSignature temp;
		temp = parseFuncInfo(line);
		func_CustomPointerlList.push_back(temp);
	}

	cfgFile.close();
}

SFuncSignature dealconfig::parseFuncInfo(string funcinfo)
{
	string classname;
	string functionname;
	vector<string> params;
	SFuncSignature temp;

	string::size_type pos_class = 0;
	string::size_type pos_functionname = 0;

	if((pos_class=funcinfo.find("::"))!=string::npos)
	{
		classname  = funcinfo.substr(0,pos_class);
		trim(classname);
	}
	else
		pos_class = 0;

	if((pos_functionname=funcinfo.find('(',pos_class))!=string::npos)
	{
		string::size_type start = 0;
		if(pos_class)
			start=pos_class+2;
		else
			start=0;
		functionname  = funcinfo.substr(start,pos_functionname-start);
	}
	string::size_type pos_params_start = pos_functionname + 1;
	string params_line;
	if(funcinfo[pos_params_start]!=')')
		params_line = funcinfo.substr(pos_params_start,funcinfo.size()-pos_params_start-1);
	if(params_line!="")
	{
		string::size_type pos;
		string pattern(",");

		params_line+=pattern;	
		bool find_map = false;

		if((funcinfo.find("::",pos_class+1))!=string::npos)
			find_map = true;
		string::size_type size=params_line.size();
		for(string::size_type i=0; i<size; i++)
		{
			pos=params_line.find(pattern,i);
			if(pos<size)
			{
				int count = 0;
				if(find_map)
				{
					for(string::size_type i = pos;i<params_line.length();i++)
					{
						if(params_line[i]=='<')
							count++;
						else if(params_line[i]=='>')
							count--;
					}
				}
				if(count<0)
				{
					pos=params_line.find(pattern,pos+1);
					if(!(pos<size))
						continue;
				}
				string s=params_line.substr(i,pos-i);
				trim(s);
				string::size_type pos_param_name;
				if((pos_param_name=s.rfind(" "))!=string::npos)
				{
					char c2 = s[pos_param_name+1];
					s=s.substr(0,pos_param_name);
					trim(s);
					char c = s[s.length()-1];
					if(c2=='&'||c2=='*')
					{
						s+=c2;
					}
					else if(c=='&'||c=='*')
					{
						s = s.substr(0,s.length()-1);
						trim(s);
						s+=c;
					}

				}
				//add by TSC  20141010
				if(s=="anyTypeTSC")
				{
					s="";
				}
				params.push_back(s);
				i=pos;
			}
		}
	}
	temp.classname = classname;
	temp.functionname = functionname;
	temp.params = params;
	return temp;
}

//from TSC 20141112 handle JumpMacros.ini
void dealconfig::readJumpMacros()
{
	std::string filePath = s_strDir + "JumpMacros.ini";
    fstream cfgFile(filePath.c_str());

    if(!cfgFile)
    {
        return;
    }

    char tmp[1000] = {0};

    while(!cfgFile.eof())
    {
        cfgFile.getline(tmp, 1000); //ÿ�ж�ȡǰ1000���ַ���1000���㹻��
        //ȥ��ע��
        if(tmp[0] == '#' || tmp[0] < 0)
        {
            continue;
        }
        string line(tmp);
        //ȥ������
        if(line.length() == 0)
        {
            continue;
        }
        trim(line);
        JUMPSTR=JUMPSTR+"|"+line;
        
    }

    cfgFile.close();
}


void dealconfig::DumpCfg()
{
	std::ofstream ofs;
	std::string sPath = CFileDependTable::GetProgramDirectory();
	sPath += "log/cfg.log";
	CFileDependTable::CreateLogDirectory();
	ofs.open(Path::toNativeSeparators(sPath).c_str(), std::ios_base::trunc);

	ofs << "[CustomNullPointerCheckList]" << std::endl;

	std::vector<CUSTOMNULLPOINTER>::iterator iter = m_CustomPointerlList.begin();
	while(iter != m_CustomPointerlList.end())
	{
		ofs << iter->functionname << "=" <<iter->var << std::endl;
		++iter;
	}

	ofs << std::endl;

	ofs << "[CustomNullPointerCheckList2]" << std::endl;
	std::vector<CANNOTBENULL>::iterator iter2 = f_CustomPointerlList.begin();
	while(iter2 != f_CustomPointerlList.end())
	{
		ofs << iter2->functionname << "=" <<iter2->var << std::endl;
		++iter2;
	}

	std::vector<SFuncSignature>::iterator iter3 = func_CustomPointerlList.begin();
	while(iter3 != func_CustomPointerlList.end())
	{
		ofs << iter3->functionname << std::endl;
		++iter3;
	}

	ofs << std::endl;

	ofs << "[JumpMacros]" << std::endl;
	ofs << JUMPSTR << std::endl;
	
	ofs.close();
}

void dealconfig::readConfig()
{
	std::string filePath = s_strDir + "cfg.ini";
	IniParser parser;
	if (!parser.Parse(filePath))
	{
		std::cout<< "Parsing [cfg.ini] failed, please check whether cfg.ini exist or the format is valid." << std::endl;
		return;
	}
	std::list<IniParser::SPair>* pListPair = NULL;
	if (parser.GetSection("CustomNullPointerCheckList", pListPair))
	{
		std::list<IniParser::SPair>::iterator iter = pListPair->begin();
		for (;iter != pListPair->end(); ++iter)
		{
			CUSTOMNULLPOINTER temp;
			int i = atoi(iter->sValue.c_str());
			if ( i != 0)
			{
				temp.functionname = iter->sKey;
				temp.var = i;
				m_CustomPointerlList.push_back(temp);
			}
		}
	}

	if (parser.GetSection("CustomNullPointerCheckList2", pListPair))
	{
		std::list<IniParser::SPair>::iterator iter = pListPair->begin();
		for (;iter != pListPair->end(); ++iter)
		{
			CANNOTBENULL temp;
			int i = atoi(iter->sValue.c_str());
			if ( i != 0)
			{
				temp.functionname = iter->sKey;
				temp.var = i;
				f_CustomPointerlList.push_back(temp);
			}
			else
			{
				SFuncSignature temp2;
				temp2 = parseFuncInfo(iter->sKey);
				func_CustomPointerlList.push_back(temp2);
			}
		}
	}

	if (parser.GetSection("JumpMacros", pListPair))
	{
		std::list<IniParser::SPair>::iterator iter = pListPair->begin();
		for (;iter != pListPair->end(); ++iter)
		{
			JUMPSTR=JUMPSTR+"|"+iter->sKey;
		}
	}

	if (writelog)
	{
		DumpCfg();
	}
}

bool IniParser::Parse(const std::string& iniPath)
{
	fstream iniFile(iniPath.c_str());

	if(!iniFile)
	{
		return false;
	}

	m_ini.clear();

	char line_buf[1000] = {0};
	std::string curSection;
	std::list<IniParser::SPair> listPair;
	while(!iniFile.eof())
	{
		iniFile.getline(line_buf, 1000); //ÿ�ж�ȡǰ1000���ַ���1000���㹻��

		//ȥ��ע��
		if(line_buf[0] == '#' || line_buf[0] <= 0)
			continue;

		std::string sLine(line_buf);
		trim_2(sLine);

		//ȥ������
		if(sLine.length() == 0)
			continue;

		if (sLine[0] == '[' && *sLine.rbegin() == ']')
		{
			m_ini[curSection] = listPair;
			curSection = sLine.substr(1, sLine.length() - 2);
			listPair.clear();
		}
		else
		{
			
			size_t pos = sLine.find('=');//�ҵ�ÿ�еġ�=����λ�ã�֮ǰ��key֮����value
			if(pos == string::npos)
			{
				IniParser::SPair newPair = {sLine, ""};
				listPair.push_back(newPair);
			}
			else
			{
				std::string sKey = sLine.substr(0, pos); 
				trim_2(sKey);
				std::string sValue = sLine.substr(pos + 1); 
				trim_2(sValue);
				IniParser::SPair newPair = {sKey, sValue};
				listPair.push_back(newPair);
			}
		}
	}

	m_ini[curSection] = listPair;
	iniFile.close();

	return true;
}

bool IniParser::GetSection(const std::string& sName, std::list<SPair>*& pMapKeyValue)
{
	if (m_ini.count(sName))
	{
		pMapKeyValue = &m_ini[sName];
		return true;
	}
	return false;
}
