#ifndef _PLUGIN_H_
#define _PLUGIN_H_
//=============================================================================
//
//   File : plugin.h
//   Creation date : Wed Apr 11 04 2007 00:54:00 GMT+1 by TheXception
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2007 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc. ,59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//=============================================================================

#include "kvi_module.h"
#include "kvi_dict.h"

#define MAX_RETURN_BUFFER 512

typedef int (*plugin_function)(int argc, char* argv[], char ** buffer);
typedef int (*plugin_unload)();
typedef int (*plugin_load)();
typedef int (*plugin_free)(char * pBuffer);

class KviPlugin
{
protected:
	// You have to create plugin instance by calling KviPlugin::load()
	KviPlugin(kvi_library_t pLib, const QString& name);
public:
	~KviPlugin();
private:
	// shared
	// internal
	kvi_library_t m_Plugin;
	QString m_szName;
public:
	static KviPlugin* load(const QString& szFileName);
	bool pfree(char * pBuffer);
	bool unload(bool forced);
	int call(const QString& szFunctionName, int argc, char * argv[], char ** pBuffer);
	QString name();
	void setName(const QString& szName);
protected:
};

class KviPluginManager
{
	public:
		KviPluginManager();
		~KviPluginManager();
	private:
		// shared
		bool m_bCanUnload;
		// internal
		KviDict<KviPlugin> * m_pPluginDict;
	public:
		bool pluginCall(KviKvsModuleFunctionCall *c);
		bool checkUnload();
		void unloadAll(bool forced);
	protected:
		bool findPlugin(QString& szName);
		bool isPluginLoaded(const QString& szFileNameOrPathToLoad);
		bool loadPlugin(const QString& szPluginPath);
		KviPlugin * getPlugin(const QString& szPluginPath);
};

#endif //_PLUGIN_H_