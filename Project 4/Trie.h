#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <list>

template<class ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
 
      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node
    {
        //default constructor/destructor
        
        //char key to identify
        char ckey;
        
        //list of Nodes of children (list bc insertion)
        std::list<Node*> children;
        
        //vector of values (vector bc find's return type)
        std::vector<ValueType> values;
        Node* hasChild(char key) const;
        
        void insertHelper(const std::string& key, const ValueType& value, int pos);
        void findHelper(const std::string& key, bool exactMatchOnly, int pos, std::vector<ValueType>& allVals) const;
    };
    Node* root;
    void clear(Node* node);
};

//must be O(1)
template<typename ValueType>
Trie<ValueType>::Trie()
{
    root  = new Node;
}

//must be O(N)
template<typename ValueType>
Trie<ValueType>::~Trie()
{
    clear(root);
}

//must be O(N)
template<typename ValueType>
void Trie<ValueType>::reset()
{
    clear();
    root = new Node;
}

//must be O(N)
template<typename ValueType>
void Trie<ValueType>::clear(Node* node)
{
    if (node != nullptr)
    {
        typename std::list<Node*> :: iterator it = node->children.begin();
        while (it != node->children.end())
        {
            clear((*it));
            it++;
        }
        delete node;
    }
}

//must be O(L*C) or O(L)
template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    root->insertHelper(key, value, 0);
}

template<typename ValueType>
void Trie<ValueType>::Node::insertHelper(const std::string& key, const ValueType& value, int pos)
{
    if (key.empty())
        return;
    else if (pos == key.size()) //keys all inserted, add values to lead
    {
        values.push_back(value);
    }
    else
    {
        Node* next = hasChild(key[pos]);
        if (next != nullptr)
            next->insertHelper(key, value, pos+1);
        else
        {
            Node* child = new Node;
            child->ckey = key[pos];
            children.push_back(child);
            child->insertHelper(key, value, pos+1);
        }
    }
}

//returns pointer to child of root with key of key[0] or nullptr if none
template<typename ValueType>
typename Trie<ValueType>::Node* Trie<ValueType>::Node::hasChild(char key) const
{
    typename std::list<Node*> :: const_iterator it = children.begin();
    while (it != children.end())
    {
        if ((*it)->ckey == key)
            return (*it);
        it++;
    }
    return nullptr;
}

template <typename ValueType>
void Trie<ValueType>::Node::findHelper(const std::string& key, bool exactMatchOnly, int pos, std::vector<ValueType>& allVals) const
{
    if (pos == key.size()) //end of key
    {
        //add all elements in values to allVals
        for (ValueType val: values)
            allVals.push_back(val);
        return;
    }
    typename std::list<Node*> :: const_iterator it = children.begin();
    while (it != children.end())
    {
        //if similar matches allowed and not exact match, all successive must be exact
        if (!exactMatchOnly && (*it)->ckey != key[pos])
            (*it)->findHelper(key, true, pos+1, allVals);
        else if ( (*it)->ckey == key[pos] ) //always continue if match
            (*it)->findHelper(key, exactMatchOnly, pos+1, allVals);
        it++;
    }
}

//must be O(LC) for exactMatchOnly
//must be O(L^2 * C^2 + V) for !exactMatchOnly
//must be recursive
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    std::vector<ValueType> allValues;
    Node* next = root->hasChild(key[0]);
    if (next != nullptr)
        next->findHelper(key, exactMatchOnly, 1, allValues);
    return allValues;
}

#endif // TRIE_INCLUDED
//bigO of substring??
//check bigOs
