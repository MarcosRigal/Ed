#include <cassert>
#include "trie.hpp"

#ifdef assert
//We undefined this macro to not shadow our implementation of assert.
#undef assert
#endif

/**
 * @brief Check an assertion.
 * In Debug mode, if the assertion is not met, a segfault is generated.
 * @param assertion
 */
inline void assert(bool assertion)
{
#ifndef NDEBUG
    (void)((assertion) || (__assert("Assert violation!", __FILE__, __LINE__), 0));
#endif
}

TrieNode::TrieNode(){};

TrieNode::Ref TrieNode::create()
{
    return std::make_shared<TrieNode>();
}

bool TrieNode::has(char k) const
{
    bool ret_v = false;

    for (auto iterator = children_.begin(); iterator != children_.end(); iterator++)
    {
        if (iterator->first == k)
        {
            ret_v = true;
        }
    }

    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref ret_v;

    auto children = children_;
    ret_v = children[k];

    return ret_v;
}

std::string const &
TrieNode::value() const
{
    return value_;
}

const std::map<char, TrieNode::Ref> &TrieNode::children() const
{
    return children_;
}

void TrieNode::set_value(std::string const &new_v)
{
    value_ = new_v;
}

void TrieNode::insert(char k, Ref node)
{
    children_.insert(std::make_pair(k, node));
}

Trie::Trie(){}

Trie::Ref Trie::create()
{
    return std::make_shared<Trie>();
}

TrieNode::Ref Trie::root() const
{
    return root_;
}

bool Trie::has(std::string const &k) const
{
    bool found = false;

    if (root_ != nullptr)
    {
        auto auxiliar_node = find_node(k);
        found = (auxiliar_node != nullptr) && (auxiliar_node->value().size() == k.size());
    }

    return found;
}

std::vector<std::string>
Trie::keys(std::string const &pref) const
{
    std::vector<std::string> keys;

    auto searched_node = find_node(pref);
    if (searched_node != nullptr)
    {
        preorder_traversal(searched_node, keys);
    }

    return keys;
}

void Trie::insert(std::string const &k)
{

    if (root_ == nullptr)
    {
        root_ = std::make_shared<TrieNode>(TrieNode());
    }

    TrieNode::Ref iterator = root_;

    for (size_t i = 0; i < k.size(); i++)
    {
        if (iterator->has(k[i]))
        {
            iterator = iterator->child(k[i]);
        }
        else
        {
            auto new_Node = std::make_shared<TrieNode>(TrieNode());
            iterator->insert(k[i], new_Node);
            iterator = new_Node;
        }
    }

    iterator->set_value(k);

    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const &pref) const
{
    TrieNode::Ref node;

    node = root_;

    for (size_t i = 0; node->has(pref[i]) && i <= pref.length(); i++)
    {
        node = node->child(pref[i]);
    }

    return node;
}

void Trie::preorder_traversal(TrieNode::Ref const &node,
                              std::vector<std::string> &keys) const
{

    if (node->value() != "")
    {
        keys.push_back(node->value());
    }
    for (auto iterator = node->children().begin(); iterator != node->children().end(); iterator++)
    {
        preorder_traversal(iterator->second, keys);
    }

}
