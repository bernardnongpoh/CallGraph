/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@gmail.com
*/

#include"Graph.h"

void Graph::addEdge(Value *src, Value* dest){
      adjMap[src].push_back(dest);
      
}

int Graph::size(){
    return adjMap.size();
}

Value* Graph::addNode(llvm::Function *func){
  //  int ID = func->getGUID();  //One Way mapping is sufficient, if GUID is globally unique.
    idToFuncMap[func]=func;
    //funcToIdMap[func]=func;
    return func;
}

llvm::Function* Graph::getFunctionByNodeId(Value *nodeId){
    return idToFuncMap[nodeId];
}
  




void Graph::printGraph(){


    std::string graphFileName ="graph.text";
     std::string graphFileNameDot ="graph.dot";
    std::ofstream graphFile,graphDot;
    graphFile.open(graphFileName);
    graphDot.open(graphFileNameDot);
    graphDot<<"digraph G {"<<"\n";

     for (auto const& node : adjMap)
            {
                 graphFile<<"["<< getFunctionByNodeId(node.first)->getName().str()<<"]:";  
                 
                 unsigned int count=0;
                 for(auto const calleeNodeId: node.second){
                
                graphDot<<getFunctionByNodeId(node.first)->getName().str()<<"->"<<getFunctionByNodeId(calleeNodeId)->getName().str()<<";\n";
                          // Formatting Comma only
                    if(count!=node.second.size()-1)
                     {
                         graphFile<<"["<< getFunctionByNodeId(calleeNodeId)->getName().str()<<"],";
                     
                           }
                    else
                   { 
                       graphFile<<"["<< getFunctionByNodeId(calleeNodeId)->getName().str()<<"]"; 
                 }
                    count++;
                
                 } 
                  graphFile<<"\n";

            }
           

 graphDot<<"}";


  graphFile.close();
  graphDot.close();
 


   

    }

