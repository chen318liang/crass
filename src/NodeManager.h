// File: NodeManager.h
// Original Author: Michael Imelfort 2011
// --------------------------------------------------------------------
//
// OVERVIEW:
// 
// Class to handle all the lists of nodes and class instances.
// Each cannonical form of direct repeat gets it's "own" NodeManager
// Thus a cannonical DR is a crispr is a NodeManager
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

#ifndef NodeManager_h
    #define NodeManager_h

// system includes
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

// local includes
#include "NodeManager.h"
#include "crassDefines.h"
#include "CrisprNode.h"
#include "SpacerInstance.h"
#include "libcrispr.h"
#include "StringCheck.h"
#include "ReadHolder.h"
#include "GraphDrawingDefines.h"
#include "Rainbow.h"

// typedefs
typedef std::map<StringToken, CrisprNode *> NodeList;
typedef std::map<StringToken, CrisprNode *>::iterator NodeListIterator;
typedef std::map<SpacerKey, SpacerInstance *> SpacerList;
typedef std::map<SpacerKey, SpacerInstance *>::iterator SpacerListIterator;

typedef std::vector<CrisprNode *> NodeVector;
typedef std::pair<CrisprNode * , CrisprNode *> CrisprNodePair;

class WalkingManager {
    CrisprNodePair WM_WalkingElem;
    bool WM_Direction;
    EDGE_TYPE WM_Wanted_Edge_Type;
    
public:

    WalkingManager(CrisprNode * firstNode, CrisprNode * secondNode, EDGE_TYPE incommingEdge)
    {
        WM_WalkingElem.first = firstNode;
        WM_WalkingElem.second = secondNode;
        WM_Wanted_Edge_Type = incommingEdge;
    }
    WalkingManager(void){}
    ~WalkingManager(void){}


    CrisprNode * getFirstNode(void)
    {
        return WM_WalkingElem.first;
    }
    CrisprNode * getSecondNode(void)
    {
        return WM_WalkingElem.second;
    }
    CrisprNodePair getWalkingElem(void)
    {
        return WM_WalkingElem;
    }
    EDGE_TYPE getEdgeType(void)
    {
        return WM_Wanted_Edge_Type;
    }
    void setFirstNode(CrisprNode * fn)
    {
        WM_WalkingElem.first = fn;
    }
    void setSecontNode(CrisprNode * sn)
    {
        WM_WalkingElem.second = sn;
    }
    void setWalkingElem(CrisprNodePair np)
    {
        WM_WalkingElem = np;
    }
    void setWantedEdge(EDGE_TYPE e)
    {
        WM_Wanted_Edge_Type = e;
    }
};



class NodeManager {
    public:

        NodeManager(std::string drSeq, const options * userOpts);
        ~NodeManager(void);



    inline int getMaxCoverage(void){ return NM_MaxCoverage;}
    inline int getMinCoverage(void){ return NM_MinCoverage;}
    inline void setMaxCoverage(int i){ NM_MaxCoverage = i;}
    inline void setMinCoverage(int i){ NM_MinCoverage = i;}



        bool addReadHolder(ReadHolder * RH);


        NodeListIterator nodeBegin(void)
        {
            return NM_Nodes.begin();
        }
        
        NodeListIterator nodeEnd(void)
        {
            return NM_Nodes.end();
        }
    
    // Walking


    void walk(void);
    bool getEdge(WalkingManager * walkElem, CrisprNode * node, EDGE_TYPE * et);
    bool stepForType(WalkingManager * walkElem, EDGE_TYPE * et, CrisprNode ** detatchDelay);
    void findCapNodes(NodeVector * capNodes);                               // go through all the node and get a list of pointers to the nodes that have only one edge
    void countEdgesForType(int * count, CrisprNode * currNode, EDGE_TYPE edgeType);
    // Cleaning


        void cleanGraph(void);


    // Making purdy colours
        void setColourLimits(void);


    // Printing / IO
        void printGraph(std::ostream &dataOut, std::string title, bool showDetached, bool printBackEdges);         // Print a graphviz style graph of the DRs and spacers
    void printNodeAttributes(std::ostream& dataOut, CrisprNode * currCrisprNode, std::string colourCode);
    void printEdgeAttributes(std::ostream& dataOut);
    
    private:
        bool splitReadHolder(ReadHolder * RH);
        void addCrisprNodes(CrisprNode ** prevNode, std::string& workingString);
        void addSecondCrisprNode(CrisprNode ** prevNode, std::string& workingString);
        void addFirstCrisprNode(CrisprNode ** prevNode, std::string& workingString);
        void setUpperAndLowerCoverage(void);
        // members
        std::string NM_DirectRepeatSequence;  // the sequence of this managers direct repeat
        NodeList NM_Nodes;                    // list of CrisprNodes this manager manages
        SpacerList NM_Spacers;                // list of all the spacers
        ReadList NM_ReadList;                 // list of readholders
        StringCheck NM_StringCheck;           // string check object for unique strings 
        Rainbow NM_Rainbow;                   // the Rainbow class for making colours
        int NM_MaxCoverage;                   // The maximum coverage of any of the CrisprNodes managed 
        int NM_MinCoverage;                   // The minimum coverage of any of the CrisprNodes managed
        const options * NM_opts;              // pointer to the user options structure
};


#endif // NodeManager_h
