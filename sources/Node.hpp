#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <list>
#include <stdexcept>
#include <memory>
#include <map>

namespace ariel
{

    class Node
    {
        using NodeRef = std::shared_ptr<Node>;
        public:
            /* just defulats */
            Node() : parent(nullptr), level(0){}
            // Node(const Node&) = default;
            // Node(const Node&&) = default;
            Node(std::string& word) : level(0){content = word;}
            // Node(Node& n) : parent(n.parent), all_childs(n.all_childs), content(n.content){}
            ~Node() = default;

            Node (Node&) = default;
            Node(Node && ) = default;
            Node& operator =( Node const &) = default;
            Node& operator=( Node&&) = default;

            /* getters-setters */
            NodeRef get_parent(){return parent;}
            void set_parent(NodeRef p){parent = std::move(p);}
            
            std::string get_val(){return content;}
            void set_val(std::string& val){content = val;}

            std::list<NodeRef> get_childs(){return all_childs;}
            void add_child(NodeRef const & n){all_childs.push_back(n);}

            int get_level() const {return level;}
            void set_level(int k){level = k;}

        private:
            NodeRef parent; // the origin node which come before this.
            std::list<NodeRef> all_childs; // all nodes that this -> points to. 
            std::string content; // the value of the node
            int level;
    };
    using NodeRef = std::shared_ptr<Node>;
    NodeRef search_node(NodeRef curr, std::string& val); // check if val is related as sun to curr, if yes, return its node

}