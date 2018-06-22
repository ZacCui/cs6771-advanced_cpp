// test 4: tests data integrity 

#include "Graph.h"

int main() {
	
	gdwg::Graph<std::string,int> gCopy;
	
	// create some data to store as nodes.
	std::string s = "a";
	std::string t = "b";
	std::string u = "c";
	
	// add this data into the graph
	gCopy.addNode(s);
	gCopy.addNode(t);
	gCopy.addNode(u);
	
	gCopy.addEdge(u,t,1);
	gCopy.addEdge(u,t,2);
	
	std::cout << "Graph g before attempted change" << std::endl;
	gCopy.printNodes();
	// change the value of t and make sure that the graph still prints out the original value
	t = "d";
	std::cout << "Graph g after attempted change" << std::endl;
	gCopy.printNodes();
	
	gdwg::Graph<std::shared_ptr<std::string>,std::shared_ptr<int>> gPtr;
	std::shared_ptr<std::string> sPtr = std::make_shared<std::string>("a");
	std::shared_ptr<std::string> tPtr = std::make_shared<std::string>("b");
	std::shared_ptr<std::string> uPtr = std::make_shared<std::string>("c");
	gPtr.addNode(sPtr);
	gPtr.addNode(tPtr);
	gPtr.addNode(uPtr);
	
	// add an edge between u and t
	gPtr.addEdge(uPtr,tPtr,std::make_shared<int>(1));
	// add a second edge between u and t with a different weight
	gPtr.addEdge(uPtr,tPtr,std::make_shared<int>(2));
	
	// change the value of the data in the ptr
	*tPtr = "d";
	
	std::cout << "Confirming that data has changed if we are using ptrs" << std::endl;
	// this should have updated in the graph as well as it is a pointer. 
	// can confirm this using isNode
	std::cout << std::boolalpha << gCopy.isNode(t) << " " << gPtr.isNode(tPtr) << std::endl;
}
