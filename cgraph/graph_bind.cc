#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "cgraph/graph.hpp"

namespace py = pybind11;

class PyGraph : public Graph
{
public:
    py::array getAllShortestPathPy()
    {
        auto dist = getAllShortestPath();
        return py::array({num_nodes, num_nodes}, dist.data());
    }

    py::array getShortestPathCondPy(i32 src)
    {
        auto dist = getShortestPathCond(src);
        return py::array(dist.size(), dist.data());
    }

    py::array getShortestPathPy(i32 src)
    {
        auto dist = getShortestPath(src);
        return py::array(dist.size(), dist.data());
    }
};

PYBIND11_MODULE(graph_lib, m)
{
    py::class_<PyGraph>(m, "Graph")
        .def(py::init<>())
        .def("initGraph", &PyGraph::initGraph)
        .def("clearGraph", &PyGraph::clearGraph)
        .def("empty", &PyGraph::empty)
        .def("getSpec", &PyGraph::getSpec)
        .def("addEdge", &PyGraph::addEdge)
        .def("getAllShortestPath", &PyGraph::getAllShortestPathPy)
        .def("getShortestPath", &PyGraph::getShortestPathPy)
        .def("getShortestPathCond", &PyGraph::getShortestPathCondPy);
}