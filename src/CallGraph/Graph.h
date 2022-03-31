/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/


#include "llvm/IR/Function.h"
#include "clang/AST/AST.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace clang;



class Graph{
    
    public:
        map<int,llvm::Function*> idToFuncMap;
        map<llvm::Function*,int> funcToIdMap;
      

   
    map<int,vector<int>> adjMap;
       
    void addEdge(int srcNodeId, int destNodeId);
    int getRootId();
    int size();
    int addNode(llvm::Function *func);
    int getNodeId(llvm::Function *func);
    llvm::Function *getFunctionByNodeId(int nodeId);
    int getNodeIdByFunction(llvm::Function *func);
    void printGraph();
   
    


};