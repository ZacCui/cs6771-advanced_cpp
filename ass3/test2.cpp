// test 2: tests edge insertion and print ordering

#include "Graph.h"

int main() {
	
	// create 3 graphs
	gdwg::Graph<int,int> g;
	gdwg::Graph<std::string,double> g2{};
	gdwg::Graph<std::shared_ptr<int>,std::string> g3{};
	
	// add some nodes to each graph. 
	g.addNode(1);
	int i = 2;
	g.addNode(i);
	double d = 3.41;
	g.addNode(static_cast<int>(d));
	
	g2.addNode("Hello");
	std::string s = "world";
	g2.addNode(s);
	
	std::shared_ptr<int> sp = std::make_shared<int>(5);
	g3.addNode(sp);
	g3.addNode(std::make_shared<int>(6));
	
	// add some edges 
	g.addEdge(2,1,3);
	int j = 3;
	g.addEdge(i,j,1);
	
	g2.addEdge("Hello","world",d);
	
	g.printEdges(2);
	g2.printEdges("Hello");
	g2.printEdges("world");
	
	std::cout << "Printing nodes in graph g to check print order" << std::endl;
	g.printNodes();
}
