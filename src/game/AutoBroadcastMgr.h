/*
* Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
*
* Wlk Wlezley 2010 <http://WoWResource.eu/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _ABRMGR_H
#define _ABRMGR_H

#include <unordered_map>
using namespace std;
struct AutoBroadcastData
{
    std::string msg;
    uint32 nextid;
};

typedef unordered_map<uint32, AutoBroadcastData> AutoBroadcastDataMap;

class AbrMgr
{
    friend struct AutoBroadcastData;

    // Constructors
public:
    AbrMgr();
    ~AbrMgr();

    // Accessors (const or static functions)
public:
    // AutoBroadcast get data
    AutoBroadcastData const* GetAutoBroadcastData(uint32 abr_id) const
    {
        AutoBroadcastDataMap::const_iterator itr = mAutoBroadcastData.find(abr_id);
        if (itr != mAutoBroadcastData.end())
            return &itr->second;
        return NULL;
    }

    static AbrMgr& Instance();
    void LoadAbrData();

private:
    AutoBroadcastDataMap mAutoBroadcastData;
};
#define sAbrMgr AbrMgr::Instance()
#endif