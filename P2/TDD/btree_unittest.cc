#include "btree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"

TEST(BTNode, create_no_childs)
{
   auto node = BTNode<int>::create(3);
   EXPECT_EQ(node->item(), 3);
}

TEST(BTNode, create_one_child)
{
   auto node = BTNode<int>::create(3);
   EXPECT_EQ(node->item(), 3);

   auto node1 = BTNode<int>::create(5, node);
   EXPECT_EQ(node1->has_left(), true);
   EXPECT_EQ(node1->has_right(), false);
   
   auto node2 = BTNode<int>::create(7, nullptr ,node1);
   EXPECT_EQ(node2->has_left(), false);
   EXPECT_EQ(node2->has_right(), true);
}

TEST(BTNode, create_two_childs)
{
   auto node2 = BTNode<int>::create(7);
   auto node1 = BTNode<int>::create(5);
   auto node = BTNode<int>::create(3, node1, node2);
   
   EXPECT_EQ(node->item(), 3);

   EXPECT_EQ(node->has_left(), true);
   EXPECT_EQ(node->left(), node1);
   
   EXPECT_EQ(node->has_right(), true);
   EXPECT_EQ(node->right(), node2);
}

TEST(BTNode, set_item)
{
   auto node = BTNode<int>::create(3);
   
   EXPECT_EQ(node->item(), 3);

   node->set_item(5);

   EXPECT_EQ(node->item(), 5);
}

TEST(BTNode, set_left)
{
   auto node = BTNode<int>::create(3);
   auto node1 = BTNode<int>::create(5);

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);

   node->set_left(node1);

   EXPECT_EQ(node->has_left(), true);
   EXPECT_EQ(node->left(), node1);
   
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);
}

TEST(BTNode, set_right)
{
   auto node = BTNode<int>::create(3);
   auto node1 = BTNode<int>::create(5);

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);

   node->set_right(node1);

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   
   EXPECT_EQ(node->has_right(), true);
   EXPECT_EQ(node->right(), node1);
}

TEST(BTNode, remove_left)
{
   auto node = BTNode<int>::create(3);
   auto node1 = BTNode<int>::create(5);

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);

   node->set_left(node1);

   EXPECT_EQ(node->has_left(), true);
   EXPECT_EQ(node->left(), node1);
   
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);
   
   node->remove_left();

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);
}

TEST(BTNode, remove_right)
{
   auto node = BTNode<int>::create(3);
   auto node1 = BTNode<int>::create(5);

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);

   node->set_right(node1);

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   
   EXPECT_EQ(node->has_right(), true);
   EXPECT_EQ(node->right(), node1);

   node->remove_right();

   EXPECT_EQ(node->has_left(), false);
   EXPECT_EQ(node->left(), nullptr);
   EXPECT_EQ(node->has_right(), false);
   EXPECT_EQ(node->right(), nullptr);
}

TEST(BTree, empty_tree_constructor)
{
   BTree<int> tree;
   EXPECT_EQ(tree.is_empty(), true);
}

TEST(BTree, one_leaf_constructor)
{
   auto tree = BTree<int>::create(4);
   EXPECT_EQ(tree->item(), 4);
   EXPECT_TRUE(tree->left()->is_empty());
   EXPECT_TRUE(tree->right()->is_empty());
}

TEST(BTree, set_item)
{
   auto tree = BTree<int>::create(3);
   tree->set_item(5);
   EXPECT_EQ(tree->item(), 5);
}

TEST(BTree, create_root)
{
   BTree<int> tree;
   EXPECT_EQ(tree.is_empty(), true);

   tree.create_root(5);
   EXPECT_EQ(tree.is_empty(), false);
   EXPECT_EQ(tree.item(), 5);
}

TEST(BTree, set_left)
{
   auto tree = BTree<int>::create(3);
   auto leftTree = BTree<int>::create(5);
   tree->set_left(leftTree);
   EXPECT_EQ(tree->left()->item(), leftTree->item());
   EXPECT_TRUE(tree->right()->is_empty());
}

TEST(BTree, set_right)
{
   auto tree = BTree<int>::create(3);
   auto rightTree = BTree<int>::create(5);
   tree->set_right(rightTree);
   EXPECT_EQ(tree->right()->item(), rightTree->item());
   EXPECT_TRUE(tree->left()->is_empty());
}

TEST(BTree, remove_left)
{
   auto tree = BTree<int>::create(3);
   auto leftTree = BTree<int>::create(5);
   tree->set_left(leftTree);
   EXPECT_EQ(tree->left()->item(), leftTree->item());
   EXPECT_TRUE(tree->right()->is_empty());

   tree->remove_left();
   EXPECT_TRUE(tree->right()->is_empty());
   EXPECT_TRUE(tree->left()->is_empty());
}

TEST(BTree, remove_right)
{
   auto tree = BTree<int>::create(3);
   auto rightTree = BTree<int>::create(5);
   tree->set_right(rightTree);
   EXPECT_EQ(tree->right()->item(), rightTree->item());
   EXPECT_TRUE(tree->left()->is_empty());

   tree->remove_right();
   EXPECT_TRUE(tree->right()->is_empty());
   EXPECT_TRUE(tree->left()->is_empty());
}

TEST(BTree, create_empty)
{
   std::istringstream in("[]");
   auto tree = BTree<int>::create(in);
   EXPECT_EQ(tree->is_empty(), true);
}

TEST(BTree, create_one_node)
{
   std::istringstream in("[ 1 [] [] ]");
   auto tree = BTree<int>::create(in);
   EXPECT_EQ(tree->is_empty(), false);
   EXPECT_EQ(tree->item(), 1);
   auto leftTree = tree->left(); 
   EXPECT_EQ(leftTree->is_empty(), true);
   auto rightTree = tree->right(); 
   EXPECT_EQ(rightTree->is_empty(), true);

}

TEST(BTree, create_three_nodes)
{
   std::istringstream in("[ 2 [ 1 [] [] ] [ 3 [] [] ] ]");
   auto tree = BTree<int>::create(in);
   EXPECT_EQ(tree->is_empty(), false);
   EXPECT_EQ(tree->item(), 2);

   auto leftTree = tree->left(); 
   EXPECT_EQ(leftTree->is_empty(), false);
   EXPECT_EQ(leftTree->item(), 1);
   EXPECT_EQ(leftTree->left()->is_empty(), true);
   EXPECT_EQ(leftTree->right()->is_empty(), true);
   
   auto rightTree = tree->right(); 
   EXPECT_EQ(rightTree->is_empty(), false);
   EXPECT_EQ(rightTree->item(), 3);
   EXPECT_EQ(rightTree->left()->is_empty(), true);
   EXPECT_EQ(rightTree->right()->is_empty(), true);
}

TEST(BTree, fold_empty_tree)
{
  std::filebuf fb;
  fb.open ("empty.txt",std::ios::out);
  std::ostream os(&fb);
  BTree<int> tree;
  EXPECT_EQ(tree.is_empty(), true);
  tree.fold(os);
  fb.close();

  std::ifstream f("empty.txt");
  if (!f) 
  {
    std::cout<<"Error al abrir el archivo\n";
    EXIT_FAILURE; 
  }
  std::string cadena;
  getline(f, cadena);
  EXPECT_TRUE(cadena.compare("[]\n"));
}

TEST(BTree, fold_one_node_tree)
{
  std::filebuf fb;
  fb.open ("one_node.txt",std::ios::out);
  std::ostream os(&fb);
  std::istringstream in("[ 1 [] [] ]");
  auto tree = BTree<int>::create(in);
  tree->fold(os);
  fb.close();

  std::ifstream f("one_node.txt");
  if (!f) 
  {
    std::cout<<"Error al abrir el archivo\n";
    EXIT_FAILURE; 
  }
  std::string cadena;
  getline(f, cadena);
  EXPECT_TRUE(cadena.compare("[ 1 [] [] ]\n"));
}

TEST(BTree, fold_three_node_tree)
{
  std::filebuf fb;
  fb.open ("three_node.txt",std::ios::out);
  std::ostream os(&fb);
  std::istringstream in("[ 2 [ 1 [] [] ] [ 3 [] [] ] ]");
  auto tree = BTree<int>::create(in);
  tree->fold(os);
  fb.close();

  std::ifstream f("three_node.txt");
  if (!f) 
  {
    std::cout<<"Error al abrir el archivo\n";
    EXIT_FAILURE; 
  }
  std::string cadena;
  getline(f, cadena);
  EXPECT_TRUE(cadena.compare("[ 2 [ 1 [] [] ] [ 3 [] [] ] ]\n"));
}
