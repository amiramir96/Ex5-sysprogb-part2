#include "OrgChart.hpp"
#include "stack"

namespace ariel
{

    OrgChart OrgChart::add_root(std::string name)
    { /* no matter what is the root, replace it with another root */
        if (this->root == NULL)
        {
            this->root = std::make_shared<Node>(name);

        }
        else 
        {
            this->root.get()->set_val(name);

        }
        // this->mc++; not used in the tests
        this->root.get()->set_level(0);
        return *this;
    }

    OrgChart OrgChart::add_sub(std::string superior, std::string subject)
    { /* throw logic_error  if the superior isnt exist in the ORGCHART obj itself */
        if (this->root == NULL)
        {
            throw std::runtime_error("cannot add sub to NULL root\n");
        }

        NodeRef superv = search_node(this->root, superior);
        if (superv == NULL)
        {
            throw std::logic_error("cannot set subject to inexist superior\n");
        } 
        
        // set the supervizer and its sub as parent <-> child
        superv->add_child(std::make_shared<Node>(subject));
        search_node(superv, subject).get()->set_parent(superv);
        search_node(superv, subject).get()->set_level(superv.get()->get_level()+1);

        this->mc++;
        return *this;
    }

    ostream& operator<<(ostream &out, const OrgChart& obj)
    { /* prints the OrgChart via preorder xD (eziest no time sorry) */
        std::string res;

        // root level
        if (obj.get_root() == nullptr){return out;}
        res.append(obj.get_root().get()->get_val());
        res.append("\n");

        std::stack<NodeRef> helper;
        // initialize stack with all the root childs
        for (NodeRef const & n : obj.get_root().get()->get_childs())
        {
            helper.push(n);
        }

        // start traversal on all the tree via preorder
        while (!helper.empty())
        {   
            NodeRef temp = helper.top();
            helper.pop();
            for (int j = temp.get()->get_level(); j > 0; j--) // level decides amount of tabs \t
            {
                res.append("\t");

            }
            res.append(temp.get()->get_val());
            res.append("\n");

            for (NodeRef const & n : temp.get()->get_childs())
            {
                helper.push(n);
            }

        }

        out << res;
        return out;
    }
    
    MyIter OrgChart::begin_preorder() {return MyIter(*this, PRE_ORDER);} // return the iterator for preorder traversal
 
    MyIter OrgChart::end_preorder() {return MyIter(*this, EMPTY_I);} // return empty iterator

    MyIter OrgChart::begin() {return MyIter(*this, LEVEL_ORDER);} // return the iterator for level_order traversal
 
    MyIter OrgChart::end() {return MyIter(*this, EMPTY_I);} // return empty iterator

    MyIter OrgChart::begin_level_order() {return MyIter(*this, LEVEL_ORDER);} // return the iterator for level_order traversal
 
    MyIter OrgChart::end_level_order() {return MyIter(*this, EMPTY_I);} // return empty iterator

    MyIter OrgChart::begin_reverse_order() {return MyIter(*this, REVERSE_LEVEL_ORDER);} // return the iterator for reverse level_order traversal
 
    MyIter OrgChart::reverse_order() {return MyIter(*this, EMPTY_I);} // return empty iterator

}
