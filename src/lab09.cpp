// lab09.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "VisualGraph.h"
#include <iostream>

int main() {
    example::VisualGraph graph;

    // Test: Add nodes
    graph.add_node("A", "Node A");
    graph.add_node("B", "Node B");
    graph.add_node("C", "Node C");
    graph.add_node("D", "Node D");
    std::cout << "Nodes added:\n" << graph;

    // Test: Add edges
    graph.add_edge("A", "B", 1.5f);
    graph.add_edge("B", "C", 2.0f);
    graph.add_edge("C", "A", 3.0f);
    graph.add_edge("A", "D", 4.5f);
    std::cout << "\nEdges added:\n" << graph;

    // Test: Check for non-existent edge addition
    std::cout << "\nAttempting to add an edge from non-existent node E to A:\n";
    graph.add_edge("E", "A", 1.0f); // Should not add anything
    std::cout << graph;

    // Test: Remove a node
    graph.remove_node("B");
    std::cout << "\nAfter removing node B:\n" << graph;

    // Test: Remove an edge
    graph.remove_edge("C", "A");
    std::cout << "\nAfter removing edge C -> A:\n" << graph;

    // Test: Save graph to a file
    graph.save("graph.txt");
    std::cout << "\nGraph saved to 'graph.txt'.\n";

    // Test: Clear the graph
    graph.clear();
    std::cout << "\nGraph cleared:\n" << graph;

    // Test: Load graph from a file
    graph.load("graph.txt");
    std::cout << "\nGraph loaded from 'graph.txt':\n" << graph;

    // Test: Breadth-first search
    std::cout << "\nBreadth-first search starting from node A:\n";
    graph.breadth_first_search("A");

    // Test: Colorize nodes
    std::cout << "\nColorizing nodes:\n";
    graph.colorize();

    // Test: Add more nodes and edges
    graph.add_node("E", "Node E");
    graph.add_node("F", "Node F");
    graph.add_edge("E", "F", 5.0f);
    graph.add_edge("F", "A", 6.0f);
    std::cout << "\nAfter adding nodes E and F, and edges E -> F and F -> A:\n" << graph;

    // Test: Save updated graph to a new file
    graph.save("updated_graph.txt");
    std::cout << "\nUpdated graph saved to 'updated_graph.txt'.\n";

    // Test: Load updated graph
    graph.clear();
    graph.load("updated_graph.txt");
    std::cout << "\nUpdated graph loaded from 'updated_graph.txt':\n" << graph;

    // Test: Breadth-first search on updated graph
    std::cout << "\nBreadth-first search starting from node E:\n";
    graph.breadth_first_search("E");

    // Test: Attempt to remove non-existent node
    std::cout << "\nAttempting to remove non-existent node G:\n";
    graph.remove_node("G"); // Should not affect the graph
    std::cout << graph;

    // Test: Attempt to remove non-existent edge
    std::cout << "\nAttempting to remove non-existent edge E -> G:\n";
    graph.remove_edge("E", "G"); // Should not affect the graph
    std::cout << graph;

    return 0;
}