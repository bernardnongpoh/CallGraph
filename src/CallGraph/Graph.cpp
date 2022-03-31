/*
@Author: Bernard Nongpoh
@Email: bernard.nongpoh@cea.fr
*/

#include"Graph.h"

void Graph::addEdge(int src, int dest){
      adjMap[src].push_back(dest);
      
}




int Graph::size(){
    return adjMap.size();
}



int Graph::addNode(llvm::Function *func){
    int ID = func->getGUID();  //One Way mapping is sufficient, if GUID is globally unique.
    idToFuncMap[ID]=func;
    funcToIdMap[func]=ID;
    return ID;
}

llvm::Function* Graph::getFunctionByNodeId(int nodeId){
    return idToFuncMap[nodeId];
}
  
int Graph::getNodeIdByFunction(llvm::Function *func){
    return funcToIdMap[func];
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
                
                graphDot<<getFunctionByNodeId(node.first)->getName().str()<<node.first<<"->"<<getFunctionByNodeId(calleeNodeId)->getName().str()<<calleeNodeId<<";\n";
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

