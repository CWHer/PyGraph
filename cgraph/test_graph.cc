#include <random>
#include <iostream>

#include <gtest/gtest.h>

#include "cgraph/graph.hpp"

TEST(Graph, Basic)
{
    auto g = Graph();
    EXPECT_TRUE(g.empty());

    g.initGraph(10);
    auto spec = g.getSpec();
    EXPECT_EQ(std::get<0>(spec), 10);

    for (int i = 0; i < 10; ++i)
        g.addEdge(i, (i + 1) % 10, 1);
    spec = g.getSpec();
    EXPECT_EQ(std::get<1>(spec), 10);

    g.clearGraph();
    EXPECT_TRUE(g.empty());

    g.initGraph(2);
    g.addEdge(0, 1, 1);
    spec = g.getSpec();
    EXPECT_EQ(std::get<0>(spec), 2);
    EXPECT_EQ(std::get<1>(spec), 1);
}

TEST(Graph, Ops)
{
    int num_nodes = 200, num_edges = 20000;

    std::mt19937 rng(0);
    std::uniform_int_distribution<int> dist(0, num_nodes - 1);

    auto g = Graph();
    g.initGraph(num_nodes);
    for (int i = 0; i < num_edges; ++i)
    {
        int from = dist(rng), to = dist(rng), weight = dist(rng) + 1;
        to = to == from ? (to + 1) % num_nodes : to;
        g.addEdge(from, to, weight);
        // std::cerr << "Add Edge: " << from << " " << to << " " << weight << std::endl;
    }
    auto spec = g.getSpec();
    EXPECT_EQ(std::get<0>(spec), num_nodes);
    EXPECT_EQ(std::get<1>(spec), num_edges);

    auto dist_all = g.getAllShortestPath();
    // for (int i = 0; i < num_nodes; ++i)
    // {
    //     for (int j = 0; j < num_nodes; ++j)
    //         std::cerr << dist_all[i * num_nodes + j] << " ";
    //     std::cerr << std::endl;
    // }
    int num_tests = 50;
    for (int i = 0; i < num_tests; ++i)
    {
        auto src = dist(rng);
        auto dist_src = g.getShortestPathCond(src);
        for (int k = 0; k < num_nodes; ++k)
            EXPECT_EQ(dist_all[src * num_nodes + k], dist_src[k]);
    }
    for (int i = 0; i < num_tests; ++i)
    {
        auto src = dist(rng);
        auto dist_src = g.getShortestPath(src);
        for (int k = 0; k < num_nodes; ++k)
            EXPECT_EQ(dist_all[src * num_nodes + k], dist_src[k]);
    }
}