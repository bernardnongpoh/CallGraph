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
using namespace llvm;


class Graph{
    
    public:
        map<Value*,llvm::Function*> idToFuncMap;
        map<llvm::Function*,Value*> funcToIdMap;
      

   
    map<Value*,vector<Value*>> adjMap;
       
    void addEdge(Value* srcNode, Value* destNode);
    int getRootId();
    int size();
    Value* addNode(llvm::Function *func);
    Value* getNodeId(llvm::Function *func);
    llvm::Function *getFunctionByNodeId(Value *node);
   
    void printGraph();
   
    


};