import argparse
import pickle
from typing import Dict, List, Tuple

import pandas
import tqdm


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", type=str,
                        default="BIOGRID_xxx.txt", help="input file")
    parser.add_argument("--output", type=str,
                        default="graph.pkl", help="output file")
    args = parser.parse_args()

    # Read the input file
    df = pandas.read_table(args.input, sep="\t")
    print("[INFO]: Read {} lines".format(len(df)))
    print("[INFO]: Read {} columns".format(len(df.columns)))
    print("[INFO]: Head of the input file")
    print(df.head())

    nodes: Dict[str, int] = {}
    edges: List[Tuple[int, int]] = []

    SOURCE = "Official Symbol Interactor A"
    TARGET = "Official Symbol Interactor B"

    # Build the graph
    for i in tqdm.tqdm(range(len(df))):
        source = df.iloc[i][SOURCE]
        target = df.iloc[i][TARGET]
        if source not in nodes:
            nodes[source] = len(nodes)
        if target not in nodes:
            nodes[target] = len(nodes)
        edges.append((nodes[source], nodes[target]))

    print("[INFO]: Number of nodes: {}".format(len(nodes)))
    print("[INFO]: Number of edges: {}".format(len(edges)))

    # Save the graph
    graph = {"nodes": nodes, "edges": edges}
    with open(args.output, "wb") as f:
        pickle.dump(graph, f)
