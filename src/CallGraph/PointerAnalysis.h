/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/


#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/AST/AST.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace clang;

using namespace llvm;

class PointerAnalysis{
    
    public:
        
        list<llvm::Instruction*> workList;
        map<llvm::Value*,set<llvm::Value*>> pointToSet;
        void pointsTo(llvm::Value *from,llvm::Value *to);
        void addToWorkList(llvm::Instruction *inst);
        void processWorkList();
        int getWorkListSize();
        void printPointToSet();
        Function *getFunction(Value * val,map<Value*,llvm::Function*> idToFunctionMap);
};