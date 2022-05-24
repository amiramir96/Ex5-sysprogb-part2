#pragma once
#include <iostream>
#include <memory>
#include <list>

namespace ariel
{
    constexpr int EMPTY_I = -1;
    constexpr int PRE_ORDER = 1;
    constexpr int LEVEL_ORDER = 2;
    constexpr int REVERSE_LEVEL_ORDER = 3;

    class Node;
    class OrgChart;

    class MyIter
    {
        using NodeRef = std::shared_ptr<Node>;
        public:
            MyIter(): iter_mc(0), my_org(nullptr){}
            MyIter(OrgChart&, int);
            MyIter(OrgChart& org, std::list<NodeRef> plist);
            ~MyIter() = default;
            MyIter (MyIter&) = default;
            MyIter(MyIter && ) = default;
            MyIter& operator =( MyIter const &) = default;
            MyIter& operator=( MyIter&&) = default;

            // forward to next item
            MyIter& operator++();
            MyIter operator++(int);
            
            // bool iter
            // the compare is via adress of nodes and NOT via the string notent
            bool operator==(const MyIter&) const;
            bool operator!=(const MyIter&) const;
            
            // get instantly the value of the curr node 
            std::string operator*(); 
            std::string* operator->();

        private:
            // this three functions is the options to add in diff order the components of my_org to oredered_nodes 
            //      and then we will be able to start iterate
            void preOrderTraversal(NodeRef const &);
            void levelOrderTraversal(NodeRef const &);
            void reverseLevelOrderTraversal(NodeRef const &);
            
            int iter_mc; // awareness if my_org editted
            OrgChart* my_org; 

            std::list<NodeRef> ordered_nodes; // all nodes ordered after traversal sort there and we can iterate linear
            NodeRef curr; // head
    };
}
