#include "btree_utils.hpp"
#include "gtest/gtest.h"

TEST(BTree_Utils, empty_compute_height)
{
  std::istringstream in("[]");
  auto tree = BTree<int>::create(in);
  EXPECT_EQ(compute_height<int>(tree), -1);
}

TEST(BTree_Utils, one_node_compute_height)
{
  std::istringstream in("[ 1 [] [] ]");
  auto tree = BTree<int>::create(in);
  EXPECT_EQ(compute_height<int>(tree), 0);
}

TEST(BTree_Utils, six_node_compute_height)
{
  std::istringstream in("[ 2 [ 1 [] [] ] [ 3 [ 5 [] [] ] [ 4 [] [ 6 [] [] ] ] ] ]");
  auto tree = BTree<int>::create(in);
  EXPECT_EQ(compute_height<int>(tree), 3);
}

TEST(BTree_Utils, empty_compute_size)
{
  std::istringstream in("[]");
  auto tree = BTree<int>::create(in);
  EXPECT_EQ(compute_size<int>(tree), 0);
}

TEST(BTree_Utils, one_node_compute_size)
{
  std::istringstream in("[ 1 [] [] ]");
  auto tree = BTree<int>::create(in);
  EXPECT_EQ(compute_size<int>(tree), 1);
}

TEST(BTree_Utils, six_node_compute_size)
{
  std::istringstream in("[ 2 [ 1 [] [] ] [ 3 [ 5 [] [] ] [ 4 [] [ 6 [] [] ] ] ] ]");
  auto tree = BTree<int>::create(in);
  EXPECT_EQ(compute_size<int>(tree), 6);
}