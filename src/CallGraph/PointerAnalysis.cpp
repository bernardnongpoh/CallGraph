/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/

#include"PointerAnalysis.h"
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

void PointerAnalysis::addToWorkList(llvm::Instruction *inst){

        workList.push_back(inst);
        // Build Point to Graph.


}

void PointerAnalysis::pointsTo(llvm::Value *from,llvm::Value *to){

        pointToSet[from].insert(to); // Map from to to


}

int PointerAnalysis::getWorkListSize(){
    return workList.size();
} 

void PointerAnalysis::processWorkList(){

    while(!workList.empty()){
        llvm::Instruction *inst = workList.front();

         if(isa<CallInst>(inst)){
                
                CallInst *callInst = dyn_cast<CallInst>(inst);
                    
                       llvm::errs()<<"========\n"<<*callInst;
                       llvm::errs()<<callInst->getCalledOperand()->stripPointerCasts();

                        //get Function Address.

                    
                        
                    
             }



        workList.pop_front();

    }

}

void PointerAnalysis::printPointToSet(){
    
     std::string pointToFileName ="pointto.text";
     
    std::ofstream file;
    file.open(pointToFileName);
   

    for(auto const &set:pointToSet){
        file<<set.first<<":";
        for(auto const &addr:set.second){
            file<<addr<<", ";
        }
        file<<"\n";
    }

        file.close();
}

Function* PointerAnalysis::getFunction(Value * val,map<Value*,llvm::Function*> idToFunctionMap){

    if(idToFunctionMap[val]!=nullptr) return idToFunctionMap[val];
        
    set<Value*> values=pointToSet[val];
    for(Value* v:values){
        return getFunction(v,idToFunctionMap);
    }
    
    return nullptr;
}


