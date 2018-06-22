#pragma once


#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <exception>
#include <map>
#include <list>

namespace gdwg{
    template <typename N, typename E> 
    class Graph
    {
        class Node;
        class Edge;
    public:
        Graph();
        Graph(const Graph&);
        Graph(Graph&&);
        ~Graph();
        Graph<N,E>& operator=(const Graph &); 
        Graph<N,E>& operator=(Graph &&); 
        bool addNode(const N& val);
        bool addEdge(const N& src, const N& dst, const E& w);
        bool replace(const N& oldData, const N& newData);
        void mergeReplace(const N& oldData, const N& newData); 
        void deleteNode(const N&) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isNode(const N& val) const;
        bool isConnected(const N& src, const N& dst) const;
        void printNodes() const;
        void printEdges(const N& val) const;
        void begin() const;
        bool end() const;
        void next() const;
        const N& value() const;

    private:
        class Node
        {
        public:
            Node(const N&);
            bool link(const std::shared_ptr<Node> & dst, const E& w);
            N& getNode() const;
            const int getEdgeNum() const;
            bool Connected(const std::shared_ptr<Node> & dst) const;
            void printEdge() const;
            const E& getWeight(const std::shared_ptr<Node> & dst) const;
            bool setNode(const N & val);
            void setWeight(const std::shared_ptr<Node> & old);
            void changeEdge(const std::shared_ptr<Node> & old,const std::shared_ptr<Node> & New);
            void mergeEdge(const std::shared_ptr<Node> & old);
            void deleteEdge(const std::shared_ptr<Node> & to, const E &w);
            void deleteEdge(const std::shared_ptr<Node> & to);
            void clear() noexcept;
            const auto& getWeight() const;
            ~Node();
        private:
            std::shared_ptr<N> node;
            mutable std::list<std::pair<std::weak_ptr<Node>,E>> weight;
        };

        std::map<N, std::shared_ptr<Node>> nodes;

        mutable typename std::map<N, std::shared_ptr<Node>>::const_iterator MyIterator;

    };

    #include "Graph.tem"
}