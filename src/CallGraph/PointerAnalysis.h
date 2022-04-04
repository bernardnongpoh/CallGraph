/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/

#include "Graph.h"
#include "clang/AST/AST.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace clang;

using namespace llvm;

class PointerAnalysis {

private:
  list<llvm::Instruction *> workList;
  map<Value *, set<Function *>> valueToFunctionMap;
  map<llvm::Value *, set<llvm::Value *>> pointToSet;
  Function *resolvePointsTo(Value *val,
                            map<Value *, llvm::Function *> idToFunctionMap,
                            set<Function *> &functionSet);
  set<Function *>
  getPointsToFunctions(Value *val,
                       map<Value *, llvm::Function *> idToFunctionMap);

public:
  void pointsTo(llvm::Value *from, llvm::Value *to);
  void addToWorkList(llvm::Instruction *inst);
  void processWorkList(Graph *graph);
  int getWorkListSize();
  void printPointToSet();
};