/*
===========================================================================
Copyright (C) 2024 the OpenMoHAA team

This file is part of OpenMoHAA source code.

OpenMoHAA source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

OpenMoHAA source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenMoHAA source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

// main.cpp: Windows implementation of the launcher

#include "launch.h"

#include <cstring>

#include <proto/dos.h>

std::filesystem::path GetProgramLocation()
{
    char path[FILENAME_MAX];

    BPTR lock = IDOS->GetProgramDir();
    if (lock)
    {
	    (void)IDOS->NameFromLock(lock,path,FILENAME_MAX);
    }

    return std::filesystem::path(std::string(path));
}

void LaunchProgram(const std::filesystem::path& path, const std::vector<std::string>& argumentList)
{
    std::string pathString = path.string();
    char commandLine[256]; /* 256 will do; nothing can go wrong! */
    int status;

    commandLine[0] = '\0';
    strcat(commandLine, pathString.c_str());

    for (size_t i = 0; i < argumentList.size(); i++) {
	    strcat(commandLine, " ");
	    strcat(commandLine, argumentList[i].c_str());
    }

    IDOS->System(commandLine, NULL);
}
