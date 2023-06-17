import pickle

import numpy as np
import tqdm
from cgraph.graph_lib import Graph as C_Graph


if __name__ == "__main__":
    with open("graph.pkl", "rb") as f:
        graph = pickle.load(f)

    nodes = graph["nodes"]
    edges = graph["edges"]
    num_nodes = len(nodes)
    num_edges = len(edges)

    print("[INFO]: Build graph")
    g = C_Graph()
    g.initGraph(num_nodes)
    for edge in tqdm.tqdm(edges):
        u, v = edge
        g.addEdge(u, v, 1)
    spec = g.getSpec()
    assert spec == (num_nodes, num_edges)
    print(f"[INFO]: Number of nodes: {num_nodes}")
    print(f"[INFO]: Number of edges: {num_edges}")

    dist_all = np.zeros((num_nodes, num_nodes), dtype=np.float64)
    for src in tqdm.trange(num_nodes):
        dist_src = g.getShortestPathCond(src)
        dist_all[src, :] = dist_src[:]

    # print("[INFO]: Statistics of the distance matrix")
    # print(f"[INFO]: Min: {np.min(dist_all)}")
    # print(f"[INFO]: Max: {np.max(dist_all)}")
    # print(f"[INFO]: Mean: {np.mean(dist_all)}")
    # print(f"[INFO]: Std: {np.std(dist_all)}")

    print("[INFO]: Save the distance matrix")
    with open("dist_all.pkl", "wb") as f:
        pickle.dump(dist_all, f)
