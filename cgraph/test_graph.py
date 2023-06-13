import random
import unittest

import numpy as np

from cgraph.graph_lib import Graph as C_Graph


class TestGraph(unittest.TestCase):
    def testOps(self):
        num_nodes = 3000
        num_edges = 50000

        g = C_Graph()
        g.initGraph(num_nodes)
        for _ in range(num_edges):
            u = random.randint(0, num_nodes - 1)
            v = random.randint(0, num_nodes - 1)
            v = v if v != u else (v + 1) % num_nodes
            w = random.randint(0, 100)
            g.addEdge(u, v, w)
        spec = g.getSpec()
        self.assertEqual(spec, (num_nodes, num_edges))

        dist_all = g.getAllShortestPath()
        self.assertEqual(dist_all.shape, (num_nodes, num_nodes))
        self.assertEqual(dist_all.dtype, np.int64)

        num_tests = 50
        for _ in range(num_tests):
            src = random.randint(0, num_nodes - 1)
            dist_src = g.getShortestPathCond(src)
            self.assertTrue(np.allclose(dist_src, dist_all[src]))
        for _ in range(num_tests):
            src = random.randint(0, num_nodes - 1)
            dist_src = g.getShortestPath(src)
            self.assertTrue(np.allclose(dist_src, dist_all[src]))


if __name__ == "__main__":
    unittest.main()
