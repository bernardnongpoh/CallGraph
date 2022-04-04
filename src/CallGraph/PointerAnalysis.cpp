/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/

#include "PointerAnalysis.h"

void PointerAnalysis::addToWorkList(llvm::Instruction *inst) {

  workList.push_back(inst);
  // Build Point to Graph.
}

void PointerAnalysis::pointsTo(llvm::Value *from, llvm::Value *to) {

  pointToSet[from].insert(to); // Map from to to
}

int PointerAnalysis::getWorkListSize() { return workList.size(); }

void PointerAnalysis::printPointToSet() {

  std::string pointToFileName = "pointto.text";

  std::ofstream file;
  file.open(pointToFileName);

  for (auto const &set : pointToSet) {
    file << set.first << ":";
    for (auto const &addr : set.second) {
      file << addr << ", ";
    }
    file << "\n";
  }

  file.close();
}

set<Function *> PointerAnalysis::getPointsToFunctions(
    Value *val, map<Value *, llvm::Function *> idToFunctionMap) {
  set<Function *> funcSet;
  resolvePointsTo(val, idToFunctionMap, funcSet);
  return funcSet;
}

Function *
PointerAnalysis::resolvePointsTo(Value *val,
                                 map<Value *, llvm::Function *> idToFunctionMap,
                                 set<Function *> &functionSet) {

  // Collect the Function.
  if (idToFunctionMap[val] != nullptr) {
    return idToFunctionMap[val];
  }

  set<Value *> values = pointToSet[val];
  for (Value *v : values) {
    Function *func = resolvePointsTo(v, idToFunctionMap, functionSet);
    if (func != nullptr) {
      functionSet.insert(func);
    }
  }
  return nullptr;
}

void PointerAnalysis::processWorkList(Graph *callgraph) {
  /* */
  while (!workList.empty()) {
    llvm::Instruction *inst = workList.front();

    if (isa<CallInst>(inst)) {

      CallInst *callInst = dyn_cast<CallInst>(inst);

      set<Function *> funcSet = getPointsToFunctions(
          callInst->getCalledOperand()->stripPointerCasts(),
          callgraph->getValueToFuncMap());

      for (auto f : funcSet) {
        callgraph->addEdge(callInst->getFunction(), f);
      }
    }

    workList.pop_front();
  }
}
