#include "Graph.h"
#include "PointerAnalysis.h"
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
  PointerAnalysis pointerAnalysis;

  CallGraphPass() : ModulePass(ID) {}

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }

  virtual bool runOnModule(llvm::Module &M) {

    for (Function &Func : M) {

            callgraph.addNode(&Func);
        // Collect callsite from this function
     

      for (BasicBlock &BB : Func) {
        for (Instruction &Ins : BB) {


          
            if(isa<StoreInst>(Ins)){
                  StoreInst *storeInst = dyn_cast<StoreInst>(&Ins);
                 
                  Value* to = storeInst->getValueOperand()->stripPointerCasts();
                
	                Value* from = storeInst->getPointerOperand()->stripPointerCasts();
                  // Add Points-To 
                  pointerAnalysis.pointsTo(from,to);
                  // Add to Worklist
                  pointerAnalysis.addToWorkList(&Ins);
                  continue;      
              }
              if(isa<LoadInst>(Ins)){
                  LoadInst *loadInst = dyn_cast<LoadInst>(&Ins);

                  Value* to = loadInst->getPointerOperand()->stripPointerCasts();
	                Value* from = dyn_cast<Value>(loadInst);
                  
                  // Add Points-To 
                  pointerAnalysis.pointsTo(from,to);
                  // Add to Worklist
                  pointerAnalysis.addToWorkList(&Ins);
                  continue;      
              }
              

          else if(isa<CallInst>(Ins)){
              CallBase *callBase = dyn_cast<CallBase>(&Ins);
          
                if(!callBase)
                  { 
                    // Maybe Indirect Call
                    pointerAnalysis.addToWorkList(&Ins);
                    continue;
                  }
                
               // errs()<<*callInst;
                if(callBase->isIndirectCall()){

                  pointerAnalysis.addToWorkList(&Ins);
                  continue;
                }
                //Direct Call 
                Function *calleeFunc=callBase->getCalledFunction();

                callgraph.addNode(calleeFunc);
                callgraph.addEdge(&Func,calleeFunc);
                

          }


        }
      }
    }

    return true;
  }

  virtual bool doFinalization(llvm::Module &M){
     
    
     pointerAnalysis.printPointToSet();
     //pointerAnalysis.processWorkList();

      /* */
    while(!pointerAnalysis.workList.empty()){
        llvm::Instruction *inst = pointerAnalysis.workList.front();

         if(isa<CallInst>(inst)){
                
                CallInst *callInst = dyn_cast<CallInst>(inst);
                    
                       

                        //get Function Address.
                        Function*func=pointerAnalysis.getFunction(callInst->getCalledOperand()->stripPointerCasts(),callgraph.idToFuncMap);

                        if(func!=nullptr){
                          // Add Edge 
                          // from 
                          errs()<<"Hererererer\n";
                          callgraph.addEdge(callInst->getFunction(),func);
                    
                        }
                        else{
                          errs()<<*callInst;
                          errs()<<"NULL";
                        }

                    
                        
                    
             }



        pointerAnalysis.workList.pop_front();

    }





      /* */




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
