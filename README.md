# Graph-Ext

A high-performance graph library with basic shortest path algorithms implemented in C++ and exposed to Python.

## Description

This repo implements a graph data structure and basic shortest path algorithms on it, including Dijkstra algorithm, Bellman-Ford algorithm and Floyd-Warshall algorithm.

For the sake of performance, the graph operations are implemented in C++ and use pybind11 to expose the interface to Python.

## Usage

```python
from graph_lib import Graph as C_Graph

# Create a graph and initialize its properties
g = C_Graph()
assert g.empty()  # True
g.initGraph(num_nodes)

# Get graph specs
# Returns: (num_nodes, num_edges)
spec = g.getSpec()

# Add edges to the graph
# Args: u, v are i32, weight is f32
for _ in range(num_edges):
    g.addEdge(u, v, weight)  # directed edge

# Run Dijkstra algorithm
# NOTE: Dijkstra algorithm only works on non-negative weights, i.e., conditioned graph
# Returns: np.ndarray, shape=(num_nodes,), dtype=np.float64
dist_src = g.getShortestPathCond(src)

# Run Bellman-Ford algorithm
# NOTE: Bellman-Ford algorithm works on negative weights
# Returns: np.ndarray, shape=(num_nodes,), dtype=np.float64
dist_src = g.getShortestPath(src)

# Run Floyd-Warshall algorithm
# Returns: np.ndarray, shape=(num_nodes, num_nodes), dtype=np.float64
dist_all = g.getAllShortestPath()

# Clear graph for next use
g.clearGraph()
```

## Getting Started

For users,
```bash
# Download .whl file according to your python version
# e.g., python3.8
pip install cgraph-1.0-cp38-cp38-linux_x86_64.whl
```

For developers,
```bash
# Dependencies
#  - bazel
#    ref: https://bazel.build/install/ubuntu

# Clone the repo
git clone git@github.com:CWHer/Graph-Ext.git

# Run tests
make bazel-test

# Build the library with different options
make bazel-debug   # debug mode
make bazel-release # release mode
```
