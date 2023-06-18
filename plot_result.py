import pickle

import matplotlib.pyplot as plt
import numpy as np


if __name__ == "__main__":
    # SELECTED_NODES = ["TNF", "TP53", "APOE"]

    # Load graph
    with open("graph.pkl", "rb") as f:
        graph = pickle.load(f)
    num_nodes = len(graph["nodes"])
    # for node_name in graph["nodes"].keys():
    #     for selected in SELECTED_NODES:
    #         if selected in node_name:
    #             print("[INFO]: {} = {}".format(
    #                 node_name, graph["nodes"][node_name]))

    num_edges = len(graph["edges"])
    print("[INFO]: load graph.pkl")
    print("[INFO]: num_nodes = {}".format(num_nodes))
    print("[INFO]: num_edges = {}".format(num_edges))

    # Load dist_all.pkl
    with open("dist_all.pkl", "rb") as f:
        dist_all = pickle.load(f)
    assert isinstance(dist_all, np.ndarray)
    print("[INFO]: load dist_all.pkl")

    # Plot histogram (remove 0 & inf)
    dist_without_inf = dist_all[dist_all <= num_nodes]
    dist_between_without_inf = dist_without_inf[dist_without_inf > 0]
    print("[INFO]: dist_all = {}".format(dist_all[:10]))
    num_inf = dist_all.size - dist_without_inf.size
    print("[INFO]: number of inf = {}".format(num_inf))
    print("[INFO]: inf ratio = {:.4f}".format(num_inf / dist_all.size))
    num_zero = dist_without_inf.size - dist_between_without_inf.size
    # print("[INFO]: number of zero = {}".format(num_zero))
    assert num_zero == num_nodes

    # Show statistics
    print("[INFO]: dist_all.shape = {}".format(dist_between_without_inf.shape))
    print("[INFO]: mean = {:.4f}".format(np.mean(dist_between_without_inf)))
    print("[INFO]: std = {:.4f}".format(np.std(dist_between_without_inf)))
    dist_max = int(np.max(dist_between_without_inf))
    dist_min = int(np.min(dist_between_without_inf))
    print("[INFO]: min = {:.4f}".format(dist_min))
    print("[INFO]: max = {:.4f}".format(dist_max))

    plt.figure()
    plt.hist(
        dist_between_without_inf,
        bins=dist_max, range=(dist_min, dist_max)
    )
    plt.xlabel("Distance")
    plt.ylabel("Frequency")
    plt.yscale("log")
    plt.title("Distance between two points")
    plt.savefig("dist_all.pdf")
