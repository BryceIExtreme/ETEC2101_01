#pragma once

#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <random>

namespace example {

	class VisualGraph {
	public:
		VisualGraph();
		void clear();
		void add_node(const std::string& node_id, const std::string& node_data);
		void add_edge(const std::string& from_node, const std::string& to_node, float weight);
		void remove_node(const std::string& node_id);
		void remove_edge(const std::string& from_node, const std::string& to_node);
		friend std::ostream& operator<<(std::ostream& os, const VisualGraph& graph);
		void load(const std::string& filename);
		void save(const std::string& filename);
		void breadth_first_search(const std::string& start_node);
		void colorize();

	private:
		std::map<std::string, std::string> nodes;
		std::map<std::string, std::map<std::string, float>> edges;
	};

}

#endif // VISUALGRAPH_H
