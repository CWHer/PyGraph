#pragma once

#include <vector>
#include <tuple>
#include <cassert>
#include <queue>
#include <limits>
#include <iostream>

#include "omp.h"

class Graph
{
protected:
    using i32 = int;
    using u32 = unsigned int;
    using i64 = long long;

    i32 num_nodes, num_edges;

    struct Edge
    {
        i32 from, to, weight;
    };
    std::vector<std::vector<Edge>> edges_per_node;

public:
    Graph() : num_nodes(0),
              num_edges(0) {}

    void initGraph(i32 num_nodes)
    {
        clearGraph();
        this->num_nodes = num_nodes;
        edges_per_node.resize(num_nodes);
    }

    void clearGraph()
    {
        num_nodes = 0;
        num_edges = 0;
        edges_per_node.clear();
    }

    bool empty()
    {
        return num_nodes == 0;
    }

    std::tuple<i32, i32> getSpec()
    {
        return std::make_tuple(num_nodes, num_edges);
    }

    void addEdge(i32 from, i32 to, i32 weight)
    {
        assert(!empty());
        assert(0 <= from && from < num_nodes);
        assert(0 <= to && to < num_nodes);

        num_edges++;
        edges_per_node[from].emplace_back(Edge{from, to, weight});
    }

    // Graph Ops
    std::vector<i64> getAllShortestPath()
    {
#ifdef _OPENMP
        std::cout << "[INFO]: OMP enabled, "
                  << "OMP_NUM_THREADS=" << std::getenv("OMP_NUM_THREADS")
                  << std::endl;
#else
        std::cout << "[WARN]: OMP not enabled" << std::endl;
#endif
        // Use Floyd Algorithm
        std::vector<i64> dist(
            num_nodes * num_nodes, std::numeric_limits<i64>::max());
        // clang-format off
        auto arrIdx = [&](i32 i, i32 j){ return i * num_nodes + j; };
        // clang-format on
        for (i32 i = 0; i < num_nodes; i++)
        {
            dist[arrIdx(i, i)] = 0;
            for (const auto &e : edges_per_node[i])
                dist[arrIdx(i, e.to)] = std::min(dist[arrIdx(i, e.to)], (i64)e.weight);
        }
        for (i32 k = 0; k < num_nodes; k++)
#pragma omp parallel for schedule(dynamic)
            for (i32 i = 0; i < num_nodes; i++)
                for (i32 j = 0; j < num_nodes; j++)
                    if (dist[arrIdx(i, k)] < std::numeric_limits<i64>::max() &&
                        dist[arrIdx(k, j)] < std::numeric_limits<i64>::max())
                    {
                        dist[arrIdx(i, j)] = std::min(dist[arrIdx(i, j)],
                                                      dist[arrIdx(i, k)] + dist[arrIdx(k, j)]);
                    }

        return dist;
    }

    std::vector<i64> getShortestPathCond(i32 src)
    {
        assert(!empty());
        assert(0 <= src && src < num_nodes);

        // Use Dijsktra's Algorithm
        std::vector<i64> dist(
            num_nodes, std::numeric_limits<i64>::max());
        std::vector<bool> visited(num_nodes, false);
        std::priority_queue<std::pair<i64, i32>> pq;

        dist[src] = 0;
        pq.push(std::make_pair(0, src));

        while (!pq.empty())
        {
            auto x = pq.top().second;
            pq.pop();
            if (visited[x])
                continue;
            visited[x] = true;
            for (const auto &e : edges_per_node[x])
            {
                i32 to = e.to, w = e.weight;
                if (dist[to] > dist[x] + w)
                {
                    dist[to] = dist[x] + w;
                    pq.push(std::make_pair(-dist[to], to));
                }
            }
        }

        return dist;
    }

    std::vector<i64> getShortestPath(i32 src)
    {
        assert(!empty());
        assert(0 <= src && src < num_nodes);

        // Use SPFA Algorithm
        std::vector<i64> dist(
            num_nodes, std::numeric_limits<i64>::max());
        std::vector<bool> in_queue(num_nodes, false);
        std::queue<i32> q;

        dist[src] = 0;
        in_queue[src] = true;
        q.push(src);

        while (!q.empty())
        {
            auto x = q.front();
            q.pop();
            in_queue[x] = false;
            for (const auto &e : edges_per_node[x])
            {
                i32 to = e.to, w = e.weight;
                if (dist[to] > dist[x] + w)
                {
                    dist[to] = dist[x] + w;
                    if (!in_queue[to])
                    {
                        in_queue[to] = true;
                        q.push(to);
                    }
                }
            }
        }

        return dist;
    }
};