// File: StlExt.h
// Original Author: Connor Skennerton on 1/07/11
// --------------------------------------------------------------------
//
// OVERVIEW:
//
// Place to put all ya'll stl extensions
// 
// --------------------------------------------------------------------
//  Copyright  2011 Michael Imelfort and Connor Skennerton
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
// --------------------------------------------------------------------
//
//                        A
//                       A B
//                      A B R
//                     A B R A
//                    A B R A C
//                   A B R A C A
//                  A B R A C A D
//                 A B R A C A D A
//                A B R A C A D A B 
//               A B R A C A D A B R  
//              A B R A C A D A B R A 
//
// --------------------------------------------------------------------
#ifndef STLEXT_H
#define STLEXT_H 
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include <iterator>
#include <numeric>



template <class T1, class T2>
void addOrIncrement(std::map<T1, T2> &inMap, T1 &searchThing)
{
    
    if (inMap.find(searchThing) != inMap.end())
    {
        inMap[searchThing] += 1;
    }
    else
    {
        inMap[searchThing] = 1;
    }
}

template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <class T>
bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
{
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

template <class T1, class T2, class T3>
void mapToVector(std::map<T1, T2>& map, std::vector<T3>& vector) 
{
    
    typename std::map<T1, T2>::iterator iter = map.begin();
    while (iter != map.end()) 
    {
        vector.push_back(iter->first);
        iter++;
    }
}
#endif