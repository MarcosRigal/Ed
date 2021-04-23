#pragma once

#include "avltree.hpp"

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

/****
 * AVLTNode class implementation.
****/

template <class T>
AVLTNode<T>::AVLTNode(T const &it, AVLTNode<T>::Ref parent,
                      AVLTNode<T>::Ref left, AVLTNode<T>::Ref right) : item_(it), parent_(parent), left_(left), right_(right), height_(0)
{

    compute_height();

    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const &it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared<AVLTNode<T>>(it, parent, left, right);
}

template <class T>
const T &AVLTNode<T>::item() const
{
    return item_;
}

template <class T>
int AVLTNode<T>::height() const
{
    return height_;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;

    int left_tree_height = 0;
    int right_tree_height = 0;

    if (has_left())
    {
        left_->compute_height();
        left_tree_height = left_->height() + 1;
    }

    if (has_right())
    {
        right_->compute_height();
        right_tree_height = right_->height() + 1;
    }

    bf = right_tree_height - left_tree_height;

    return bf;
}

template <class T>
bool AVLTNode<T>::has_parent() const
{
    return parent_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    return parent_;
}

template <class T>
bool AVLTNode<T>::has_left() const
{
    return left_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    return left_;
}

template <class T>
bool AVLTNode<T>::has_right() const
{
    return right_ != nullptr;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    return right_;
}

template <class T>
bool AVLTNode<T>::check_height_invariant() const
{
    bool ret_val = false;

    int left_tree_height = -1;
    int right_tree_height = -1;
    int highest;

    if (has_left())
    {
        left_tree_height = left_->height_;
    }

    if (has_right())
    {
        right_tree_height = right_->height_;
    }

    (right_tree_height > left_tree_height) ? (highest = right_tree_height + 1) : (highest = left_tree_height + 1);

    if (height_ == highest)
    {
        ret_val = true;
    }

    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T &new_it)
{

    item_ = new_it;

    assert(item() == new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref const &new_parent)
{

    parent_ = new_parent;
    compute_height();

    assert(parent() == new_parent);
}

template <class T>
void AVLTNode<T>::remove_parent()
{

    parent_ = nullptr;
    compute_height();

    assert(!has_parent());
}

template <class T>
void AVLTNode<T>::set_left(AVLTNode<T>::Ref const &new_child)
{

    left_ = new_child;
    compute_height();

    assert(check_height_invariant());
    assert(left() == new_child);
}

template <class T>
void AVLTNode<T>::remove_left()
{

    left_ = nullptr;
    compute_height();

    assert(check_height_invariant());
    assert(!has_left());
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref const &new_child)
{

    right_ = new_child;
    compute_height();

    assert(check_height_invariant());
    assert(right() == new_child);
}

template <class T>
void AVLTNode<T>::remove_right()
{

    right_ = nullptr;
    compute_height();

    assert(check_height_invariant());
    assert(!has_right());
}

template <class T>
void AVLTNode<T>::compute_height()
{

    if (!has_right() && !has_left())
    {
        height_ = 0;
        if (has_parent())
        {
            parent_->compute_height();
        }
    }

    else
    {
        int left_tree_height = 0;
        int right_tree_height = 0;

        if (has_left())
        {
            left_tree_height = left_->height() + 1;
        }

        if (has_right())
        {
            right_tree_height = right_->height() + 1;
        }

        (left_tree_height > right_tree_height) ? (height_ = left_tree_height) : (height_ = right_tree_height);

        if (has_parent())
        {
            parent_->compute_height();
        }
    }

    assert(check_height_invariant());
}

/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree()
{

    root_ = nullptr;
    parent_ = nullptr;
    current_ = nullptr;

    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
AVLTree<T>::AVLTree(T const &item)
{

    root_ = AVLTNode<T>::create(item);

    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create()
{
    return std::make_shared<AVLTree<T>>();
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(T const &item)
{
    return std::make_shared<AVLTree<T>>(item);
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::istream &in) noexcept(false)
{
    auto tree = AVLTree<T>::create();
    std::string token;
    in >> token;
    if (!in)
        throw std::runtime_error("Wrong input format");

    T new_item;

    if(token != "[]" && token == "[")
    {
        while (in >> token && token != "]")
        {
            std::istringstream inputstream(token);
            inputstream >> new_item;
            tree = AVLTree<T>::create(new_item);
            auto left_subtree = AVLTree<T>::create(in);
            tree->set_left(left_subtree);
            auto right_subtree = AVLTree<T>::create(in);
            tree->set_right(right_subtree);
        }
    }
    else if (token != "[]" && token != "[")
    {
        throw std::runtime_error("Wrong input format");
    }

    if (!tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (!tree->is_a_balanced_tree())
        throw std::runtime_error("It is not an avl bstree");

    return tree;
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create a BSTree by inserting the median of an ordered sequence.
 * @param data is an ordered sequence of keys.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of data to use.
 * @pre data values are in order.
 * @pre 0 <= begin <= end <=data.size()
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             typename AVLTree<T>::Ref &tree)
{
    assert(begin <= end);
    assert(end <= data.size());

    if ((end - begin) > 0)
    {
        tree->insert(data[begin + ((end - begin) / 2)]);
        create_inserting_median(data, begin, begin + ((end - begin) / 2), tree);
        create_inserting_median(data, (begin + ((end - begin) / 2)) + 1, end, tree);
    }
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::vector<T> &data)
{
    assert(data.size() > 0);
    auto tree = AVLTree<T>::create();
    std::sort(data.begin(), data.end());
    create_inserting_median(data, 0, data.size(), tree);
    return tree;
}
#endif //#ifdef __ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty() const
{
    return root_ == nullptr;
}

template <class T>
T const &AVLTree<T>::item() const
{
    return root_->item();
}

template <class T>
std::ostream &AVLTree<T>::fold(std::ostream &out) const
{

    out << "[";

    if(!is_empty())
    {
        out << " " << item() << " ";
        left()->fold(out);
        out << " ";
        right()->fold(out);
        out << " ";
    }

    out << "]";

    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{

    auto aux = root_;
    bool exists = false;
    bool exit = false;

    while (!exit)
    {
        if (current_ == nullptr)
        {
            exit = true;
        }

        else if (current_->item() > aux->item())
        {
            if (aux->has_right())
            {
                aux = aux->right();
            }
            else
            {
                exit = true;
            }
        }
        else if (current_->item() < aux->item())
        {
            if (aux->has_left())
            {
               aux = aux->left();
            }
            else
            {
                exit = true;
            }
        }
        else
        {
            exists = true;
            exit = true;
        }
    }
    return exists;
}

template <class T>
T const &AVLTree<T>::current() const
{
    assert(current_exists());

    return current_->item();
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;

    auto aux = root_;

    while (aux != current_)
    {
        if (aux->item() > current_->item())
        {
            aux = aux->left();
        }

        else if (aux->item() < current_->item())
        {
            aux = aux->right();
        }

        level++;
    }

    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());

    auto left_tree = AVLTree<T>::create();

    if (root_->has_left())
    {
        left_tree->create_root(root_->left()->item());
        left_tree->root_->set_left(root_->left()->left());
        left_tree->root_->set_right(root_->left()->right());
        left_tree->root_->set_parent(nullptr);
    }

    return left_tree;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());

    auto right_tree = AVLTree<T>::create();

    if (root_->has_right())
    {
        right_tree->create_root(root_->right()->item());
        right_tree->root_->set_left(root_->right()->left());
        right_tree->root_->set_right(root_->right()->right());
        right_tree->root_->set_parent(nullptr);
    }

    return right_tree;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;

    if (!is_empty())
    {
        s = 1 + left()->size() + right()->size();
    }

    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = -1;

    if (!is_empty())
    {
        h = root_->height();
    }

    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;

    if (!is_empty())
    {
        bf = root_->balance_factor();
    }

    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif
    bool found = true;

    auto aux = root_;
    bool exit = false;

    while (!exit)
    {
        if (k < aux->item())
        {
            if (aux->has_left())
            {
                aux = aux->left();
            }
            else
            {
                found = false;
                exit = true;
            }
        }
        else if (k > aux->item())
        {
            if (aux->has_right())
            {
                aux = aux->right();
            }
            else
            {
                found = false;
                exit = true;
            }
        }
        else
        {
            exit = true;
        }
    }

#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;

    if (!is_empty())
    {
        if (root_->has_left())
        {
            is_bst = is_bst && (item() > left()->item());
        }

        if (root_->has_right())
        {
            is_bst = is_bst && (item() < right()->item());
        }

        is_bst = is_bst && left()->is_a_binary_search_tree() && right()->is_a_binary_search_tree();
    }

    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;

    if (root_ != nullptr)
    {
        is_balanced = (std::abs(root_->balance_factor()) <= 1) && left()->is_a_balanced_tree() && right()->is_a_balanced_tree();
    }

    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const &item)
{
    assert(is_empty());

    root_ = AVLTNode<T>::create(item, nullptr, nullptr, nullptr);

    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(this->item() == item);
}

template <class T>
bool AVLTree<T>::search(T const &k)
{
    bool found = false;

    current_ = root_;
    parent_ = nullptr;
    while (!found && current_ != nullptr)
    {
        if (current_->item() == k)
        {
            found = true;
        }

        else
        {
            parent_ = current_;
            (current_->item() > k) ? (current_ = current_->left()) : (current_ = current_->right());
        }
    }

    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const &k)
{
    if (!search(k))
    {

        if (is_empty())
        {
            current_ = AVLTNode<T>::create(k, nullptr, nullptr, nullptr);
            root_ = current_;
        }
        else
        {
            current_ = AVLTNode<T>::create(k, parent_, nullptr, nullptr);
            (parent_->item() > k) ? (parent_->set_left(current_)) : (parent_->set_right(current_));
        }

#ifdef __ONLY_BSTREE__
        assert(is_a_binary_search_tree());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
#endif
    }

    //check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void AVLTree<T>::remove()
{
    //check preconditions.
    assert(current_exists());

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    if (!current_->has_left() && !current_->has_right())
    {
        subtree = nullptr;
    }

    else if (!current_->has_right())
    {
        subtree = current_->left();
    }

    else if (!current_->has_left())
    {
        subtree = current_->right();
    }

    else
    {
        replace_with_subtree = false;
    }

    if (replace_with_subtree)
    {
        if (parent_ == nullptr)
        {
            root_ = subtree;
        }
        else if (parent_->right() == current_)
        {
            parent_->set_right(subtree);
        }
        else
        {
            parent_->set_left(subtree);
        }

        current_ = nullptr;

#ifdef _ONLY_BSTREE_
        assert(is_a_binary_search_tree());
        assert(!current_exists());
#else
        assert(is_a_binary_search_tree());
        make_balanced();
        assert(is_a_balanced_tree());
        assert(!current_exists());
#endif
    }
    else
    {
        auto tmp = current_;
        find_inorder_sucessor();
        tmp->set_item(current_->item());
        remove();
    }
}

template <class T>
AVLTree<T>::AVLTree(typename AVLTNode<T>::Ref root_node)
{

}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(typename AVLTNode<T>::Ref root)
{
    AVLTree<T>::Ref ret_v(new AVLTree<T>(root));
    return ret_v;
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::root() const
{
    return root_;
}

template <class T>
void AVLTree<T>::set_left(typename AVLTree<T>::Ref &subtree)
{
    assert(!is_empty());

    (!subtree->is_empty()) ? (root_->set_left(AVLTNode<T>::create(subtree->root_->item(), root_, subtree->root_->left(), subtree->root_->right()))) : (root_->set_left(nullptr));

    assert(subtree->is_empty() || left()->item() == subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void AVLTree<T>::set_right(typename AVLTree<T>::Ref &subtree)
{
    assert(!is_empty());

    (!subtree->is_empty()) ? (root_->set_right(AVLTNode<T>::create(subtree->root_->item(), root_, subtree->root_->left(), subtree->root_->right()))) : (root_->set_right(nullptr));

    assert(subtree->is_empty() || right()->item() == subtree->item());
    assert(!subtree->is_empty() || right()->is_empty());
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
#ifndef NDEBUG
    T old_curr = current();
#endif

    parent_ = current_;
    current_ = current_->right();

    while (current_->has_left())
    {
        parent_ = current_;
        current_ = current_->left();
    }

    assert(current_exists());
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
void AVLTree<T>::rotate_left(typename AVLTNode<T>::Ref node)
{
    auto left_node = node->left();

    if (!node->has_parent())
    {
        root_ = left_node;
    }

    else if (node->parent()->right() == node)
    {
        node->parent()->set_right(left_node);
    }

    else
    {
        node->parent()->set_left(left_node);
    }

    left_node->set_parent(node->parent());

    if (left_node->has_right())
    {
        node->set_left(left_node->right());
        left_node->right()->set_parent(node);
    }

    else
    {
        node->remove_left();
    }

    left_node->set_right(node);
    node->set_parent(left_node);

    node->compute_height();
    left_node->compute_height();
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{

    auto right_node = node->right();

    if (not node->has_parent())
    {
        root_ = right_node;
    }

    else if (node->parent()->right() == node)
    {
        node->parent()->set_right(right_node);
    }
    else
    {
        node->parent()->set_left(right_node);
    }

    right_node->set_parent(node->parent());

    if (right_node->has_left())
    {
        node->set_right(right_node->left());
        right_node->left()->set_parent(node);
    }

    else
    {
        node->remove_right();
    }

    right_node->set_left(node);
    node->set_parent(right_node);

    node->compute_height();
    right_node->compute_height();
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    while (parent_)
    {
        parent_->compute_height();
        int balance_factor = parent_->balance_factor();

        if (balance_factor < -1)
        {
            auto child = parent_->left();
            int balance_factor_child = child->balance_factor();

            if (balance_factor_child <= 0)
            {
                rotate_left(parent_);
            }
            else
            {
                rotate_right(child);
                rotate_left(parent_);
            }
        }
        else if (balance_factor > 1)
        {
            auto child = parent_->right();
            int balance_factor_child = child->balance_factor();

            if (balance_factor_child >= 0)
            {
                rotate_right(parent_);
            }
            else
            {
                rotate_left(child);
                rotate_right(parent_);
            }
        }
        else
        {
            parent_ = parent_->parent();
        }
    }

#endif //__ONLY_BSTREE__
}
