/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/

#include "clang/AST/AST.h"
#include "llvm/IR/Function.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace clang;
using namespace llvm;

class Graph {

private:
  map<Value *, llvm::Function *> idToFuncMap;
  map<llvm::Function *, Value *> funcToIdMap;
  map<Value *, vector<Value *>> adjMap;
  bool isEdgeExist(Value *src, Value *desc);

public:
  void addEdge(Value *srcNode, Value *destNode);
  void addNode(llvm::Function *func);
  llvm::Function *getFunctionByNodeValue(Value *node);
  map<Value *, llvm::Function *> getValueToFuncMap();
  void printGraph();
  void displayBanner();
};