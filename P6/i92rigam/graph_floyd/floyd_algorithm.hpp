#ifndef __FLOYD_ALGORITHM_HPP__
#define __FLOYD_ALGORITHM_HPP__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"

void road(size_t u, size_t v, IMatrix const& I, std::vector<size_t>& path)
{
 if(I[u][v]!=-1)
 {
     road(u,I[u][v],I,path);
     path.push_back(I[u][v]);
     road(I[u][v],v,I,path);
 }
}

/**
 * @brief Compute the weight matrix.
 * @arg[in] g is a weighted graph.
 * @arg[out] W is the Weight matrix.
 */
template<class T>
void compute_weight_matrix(WGraph<T>& g, FMatrix& W)
{
    W = FMatrix(g.size(), g.size(), std::numeric_limits<float>::infinity());

    //: compute the WMatrix.
    //Hint: scan all the edges. Use the node.label() to index the matrix.
    //Hint: Assume the graph is directed.
    //Hint: Review how to move the cursors.
    g.goto_first_node();
    while (g.has_current_node())
    {
        while (g.has_current_edge())
        {
            auto first = g.current_edge()->first();
            auto second = g.current_edge()->second();

            W[first->label()][second->label()] = g.weight(first, second);
            g.goto_next_edge();
        }
        g.goto_next_node();
    }

    //
}

/**
 * @brief Search for the minium path between vertices using the Floyd's algorithm.
 * @arg[in] g is a weighted graph.
 * @arg[out] D is the Distances matrix.
 * @arg[out] I is the Intermediate matrix.
 * @pre the weigths meet the triangular inequality: d(u,v) <= d(u,k) + d(k,v) for all u!=v!=k.
 * @post if none path between u,v exists then D[u][v]==inf and I[u][v]==-1
 * @post if an edge (u,v:w) exists then D[u][v]==w and I[u][v]==-1
 * @post if a path between u,v exits then D[u][v]<inf and D[u][v]==k, k is vertex in the minimum path linking u with v.
 */
template<class T>
void floyd_algorithm(WGraph<T>& g, FMatrix& D, IMatrix& I)
{
    compute_weight_matrix<T>(g, D);
    //Set self-distances to zero.
    for (size_t i=0;i<g.size();++i)
        D[i][i]=0.0;

    I = IMatrix(g.size(), g.size(), -1);

    for(size_t i = 0; i < g.size(); i++)
    {
        for(size_t j = 0; j < g.size(); j++)
        {
            for(size_t k = 0; k < g.size(); k++)
            {
                if(D[j][k] > (D[j][i] + D[i][k]))
                {
                    D[j][k] = (D[j][i] + D[i][k]);
                    I[j][k] = i;
                }
            }
        }

    }
}

/**
 * @brief Given the Floyd's Intermidiate matrix, compute the path.
 * @arg[in] u is the label of the start vertex.
 * @arg[in] v is the label of the end vertex.
 * @arg[in] I is the Floyd's Intermidiate matrix.
 * @arg[out] path is a vector with the sequence of vertex's labels for
 *           the minimum path linking u with v.
 * @pre Let D be the Floyd's D matrix corresponding with I, D[u][v]<inf.
 * @post u is the first item of path.
 * @post v is the last item of path.
 */
inline void
floyd_compute_path(size_t u, size_t v, IMatrix const& I,
                   std::vector<size_t>& path)
{
    //Prec: distance (u,v) < inf
    std::stack<std::pair<size_t, size_t>> s;
    path.resize(0);

    path.push_back(u);
    road(u, v, I, path);
    path.push_back(v);
}


#endif //__FLOYD_ALGORITHM_HPP__
