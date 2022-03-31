#include "Graph.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct CallGraphPass : public ModulePass {
  static char ID;

  Graph callgraph;

  CallGraphPass() : ModulePass(ID) {}

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }

  virtual bool runOnModule(llvm::Module &M) {

    for (Function &Func : M) {

            int callerId=callgraph.addNode(&Func);
        // Collect callsite from this function
     
      for (BasicBlock &BB : Func) {
        for (Instruction &Ins : BB) {
           
          if(isa<CallInst>(Ins)){
              
                CallInst *callInst = dyn_cast<CallInst>(&Ins);
                Function *func=callInst->getCalledFunction();
                int calleeId = callgraph.addNode(func);
                callgraph.addEdge(callerId,calleeId);
                

          }


        }
      }
    }

    return true;
  }

  virtual bool doFinalization(llvm::Module &M){
     
      callgraph.printGraph();
      return true;
  }
};
} // namespace

char CallGraphPass::ID = 0;

static RegisterPass<CallGraphPass> X("callgraph", "CallGraph Generation");

// Automatically enable the pass for Clang .
// http://adriansampson.net/blog/clangpass.html
static void registerPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new CallGraphPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerPass);
