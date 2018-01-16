/*
 * Copyright (c) 2014-2015 Enrico M. Crisostomo
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "gettext_defs.h"
#include "path_utils.hpp"
#include "c/libfswatch_log.h"
#include <dirent.h>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <iostream>

using namespace std;

#ifdef HAVE_MSYS
#include <windows.h>
#include "realpath.h"
#include "c++/windows/win_strings.hpp"
#endif

namespace fsw
{
  vector<string> get_directory_children(const string& path)
  {

#ifdef HAVE_MSYS

      // for some reason opendir,readdir,FindFirstFileA,FindNextFileA are not good with unicode names on windows
      vector<string> children;
      WIN32_FIND_DATAW FindFileData;
      HANDLE hFind;
      wstring exp = win_strings::string_to_wstring(path + "\\*");
      hFind = FindFirstFileW(exp.c_str(), &FindFileData);
     if (hFind == INVALID_HANDLE_VALUE)
     {
        printf("FindFirstFile failed (%d)\n", GetLastError());
        return children;
     }
     else
     {
         wstring wchild = wstring(FindFileData.cFileName);
         string child = win_strings::wstring_to_string(wchild);
         children.push_back(child);
         while(FindNextFileW(hFind,&FindFileData) != 0) {
             wchild = wstring(FindFileData.cFileName);
             child = win_strings::wstring_to_string(wchild);
             children.push_back(child);
         }
        FindClose(hFind);
     }
     return children;

#else

    vector<string> children;
    DIR *dir = opendir(path.c_str());

    if (!dir)
    {
      if (errno == EMFILE || errno == ENFILE)
      {
        perror("opendir");
      }
      else
      {
        fsw_log_perror("opendir");
      }

      return children;
    }

    while (struct dirent *ent = readdir(dir))
    {
      children.push_back(ent->d_name);
    }

    closedir(dir);

    return children;

#endif
  }

  bool read_link_path(const string& path, string& link_path)
  {
    char *real_path = realpath(path.c_str(), nullptr);
    link_path = (real_path ? real_path : path);

    bool ret = (real_path != nullptr);
    free(real_path);

    return ret;
  }

  bool stat_path(const string& path, struct stat& fd_stat)
  {      
    if (stat(path.c_str(), &fd_stat) != 0)
    {
      fsw_logf_perror(_("Cannot stat %s"), path.c_str());

      return false;
    }

    return true;
  }

  bool lstat_path(const string& path, struct stat& fd_stat)
  {


#ifdef HAVE_MSYS

    wstring wpath = win_strings::string_to_wstring(path);

      if (wstat(wpath.c_str(), &fd_stat) != 0)
          {
            fsw_logf_perror(_("Cannot stat %s"), path.c_str());

            return false;
          }
      return true;
#else
      if (lstat(path.c_str(), &fd_stat) != 0)
      {
        fsw_logf_perror(_("Cannot lstat %s"), path.c_str());

        return false;
      }

      return true;
#endif
  }
}
