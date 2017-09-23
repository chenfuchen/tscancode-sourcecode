/*
* Tencent is pleased to support the open source community by making TscanCode available.
* Copyright (C) 2015 THL A29 Limited, a Tencent company. All rights reserved.
* Licensed under the GNU General Public License as published by the Free Software Foundation, version 3 (the "License"); you may not use this file except in compliance with the License. You may obtain a * copy of the License at
* http://www.gnu.org/licenses/gpl.html
* TscanCode is free software: you can redistribute it and/or modify it under the terms of License.    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/


#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>


typedef unsigned long long UINT64;
typedef bool (*fp_fileFilter)(const std::string &filename);
class CFileBase;
class CFolder;
class CCodeFile;

class CFileDependTable
{

public:
	CFileDependTable();
	~CFileDependTable();
	// ��������·���������ļ�������
	bool Create(
		const std::vector<std::string>& paths, 
		const std::vector<std::string>& excludesPaths, 
		const std::vector<std::string>& includePaths);

	CCodeFile* GetFirstFile();
	CFileBase* FindFile(const std::string& filePath);
	void DumpFileDependResults();

	static std::string GetProgramDirectory();
	static void CreateLogDirectory();
private:
	bool CreateFileDependTree(const std::vector<std::string> &paths, const std::vector<std::string> &includePaths, const std::vector<std::string>& excludesPaths);

	bool BuildFileDependTree(std::string &sPath, fp_fileFilter fp);

	void UpdateIncludes(const std::vector<std::string>& includePaths);
	bool BuildTable(CFolder* pRoot, const std::string& sPath, fp_fileFilter fp);
	void ReleaseTable();

	static unsigned char ReadChar(std::istream &istr, unsigned int bom);

	void GetIncludes(const std::string &fileName, std::vector<std::string> &strIncludes);
	void ParseIncludes(CCodeFile* pCode);
	CCodeFile* FindMatchedFile(CCodeFile* pFile, std::string sInclude);
	CCodeFile* FindShortestPath(const std::vector<CCodeFile*>& vecFiles, CCodeFile* pFile);
	std::size_t GetFileSize(const std::string& sPath);


	std::string getAbsolutePath(const std::string& path);
	
private:
	// �ļ��ṹ���ĸ��ڵ�
	CFolder* m_pRoot;
	CCodeFile* m_begin;
	CCodeFile* m_flag;
	// �ַ������ļ��ڵ��ӳ�䣬���ܴ���һ�Զ��������ļ�������
	std::multimap<std::string, CCodeFile*> m_fileDict;
	std::vector<CFolder*> m_includePaths;

};

enum EFileType { FT_NONE, FT_FOLDER, FT_CODE };

// �ļ��ڵ����
class CFileBase
{
public:
	void SetParent(CFolder* pParent);
	EFileType GetFileType();
	const std::string& GetName();
	CFolder* GetParent();
	std::string GetFullPath();
	virtual ~CFileBase();
protected:
	CFileBase();

	// ÿһ���ļ���Ӧ��Ψһ���
	unsigned int m_uID;
	// �ļ��л����ļ�����
	std::string m_name;
	// ���ڵ�ָ��
	CFolder* m_parent;
	EFileType m_fileType;
private:
	static unsigned int s_id;
};

// �ļ�����
class CFolder : public CFileBase
{
public:
	CFolder(const char* szName);
	virtual ~CFolder();

	void AddFile(CFileBase* pFile);
	void RemoveFile(const std::string& sName);
	CCodeFile*  AddCodeFile(const std::string& sName, std::size_t uSize, bool& bNew);
	CFolder* AddFolder(const std::string& sName, bool& bNew);
	CFileBase* FindFile(const std::string& fileName);
	void Release();
	const std::vector<CFileBase*>& GetSubs();
	
private:
	// �ӽڵ�ָ�뼯��
	std::vector<CFileBase*> m_subs;
};

// �����ļ���
class CCodeFile : public CFileBase
{
public:
	CCodeFile(const char* szName, std::size_t size);
	virtual ~CCodeFile();

	void SetNext(CCodeFile* next);
	CCodeFile* GetNext();
	;
	std::size_t GetSize();

	void AddDependFile(CCodeFile* pFile);
	std::vector<CCodeFile*>& GetDepends();

	
	std::list<CCodeFile*>& GetAllDepends();
private:
	void FillAllDepends();
	static void ExpandIncludes(CCodeFile* pCodeFile, std::list<CCodeFile*>& allDepends, std::set<CCodeFile*>& included);
private:
	// �ļ���С
	std::size_t m_size;
	// �����ļ��������ļ��б�
	std::vector<CCodeFile*> m_depends;
	// �����ļ����������ļ��б�
	std::vector<CCodeFile*> m_beDepends;

	std::list<CCodeFile*> m_allDepends;

	CCodeFile* m_next;
};