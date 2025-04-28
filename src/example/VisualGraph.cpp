
#include "VisualGraph.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <random>
#include <sstream>
namespace example
{

	VisualGraph::VisualGraph() {}

	void VisualGraph::clear() {
		nodes.clear();
		edges.clear();
	}

	void VisualGraph::add_node(const std::string& node_id, const std::string& node_data) {
		nodes[node_id] = node_data;
		edges[node_id] = std::map<std::string, float>();
	}

	void VisualGraph::add_edge(const std::string& from_node, const std::string& to_node, float weight) {
		if (nodes.find(from_node) != nodes.end() && nodes.find(to_node) != nodes.end()) {
			edges[from_node][to_node] = weight;
		}
	}

	void VisualGraph::remove_node(const std::string& node_id) {
		nodes.erase(node_id);
		edges.erase(node_id);
		for (auto& edge : edges) {
			edge.second.erase(node_id);
		}
	}

	void VisualGraph::remove_edge(const std::string& from_node, const std::string& to_node) {
		if (edges.find(from_node) != edges.end()) {
			edges[from_node].erase(to_node);
		}
	}

	std::ostream& operator<<(std::ostream& os, const VisualGraph& graph) {
		for (const auto& node : graph.edges) {
			os << node.first << "\n";
			for (const auto& edge : node.second) {
				os << "  (" << edge.first << ", " << edge.second << ")\n";
			}
		}
		return os;
	}

	void VisualGraph::load(const std::string& filename) {
		std::ifstream file(filename);
		clear();
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string part1, part2;
			float part3;

			// Attempt to parse three parts (edge case)
			if (iss >> part1 >> part2 >> part3) {
				add_edge(part1, part2, part3);
			}
			// Attempt to parse two parts (node case)
			else {
				iss.clear(); // Clear any error flags
				iss.str(line); // Reset the stream with the same line

				// Manually parse the line for two parts
				std::size_t space_pos = line.find(' ');
				if (space_pos != std::string::npos) {
					part1 = line.substr(0, space_pos);
					part2 = line.substr(space_pos + 1);
					add_node(part1, part2);
				}
			}
		}
	}

	void VisualGraph::save(const std::string& filename) {
		std::ofstream file(filename);
		for (const auto& node : nodes) {
			file << node.first << " " << node.second << "\n";
		}
		for (const auto& edge : edges) {
			for (const auto& adj : edge.second) {
				file << edge.first << " " << adj.first << " " << adj.second << "\n";
			}
		}
	}

	void VisualGraph::breadth_first_search(const std::string& start_node) {
		std::set<std::string> visited;
		std::queue<std::string> queue;
		float total_weight = 0;
		queue.push(start_node);
		while (!queue.empty()) {
			std::string node = queue.front();
			queue.pop();
			if (visited.find(node) == visited.end()) {
				visited.insert(node);
				for (const auto& adj : edges[node]) {
					total_weight += adj.second;
					queue.push(adj.first);
				}
			}
		}
		std::cout << "Visited nodes: ";
		for (const auto& node : visited) {
			std::cout << node << " ";
		}
		std::cout << "\nTotal weight: " << total_weight << "\n";
	}

	void VisualGraph::colorize() {
		std::map<std::string, std::string> colors;
		std::vector<std::string> color_options = { "red", "green", "blue", "yellow", "purple" };
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, color_options.size() - 1);
		for (const auto& node : nodes) {
			colors[node.first] = color_options[dis(gen)];
		}
		std::cout << "Node colors: \n";
		for (const auto& color : colors) {
			std::cout << color.first << ": " << color.second << "\n";
		}
	}
}
