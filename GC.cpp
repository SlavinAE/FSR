#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	ifstream file("gc_4_1");
	int V, E;
	file >> V >> E;

	vector<pair<int, int>> edges(E);
	for (int i = 0; i < E; i++) {
		file >> edges[i].first >> edges[i].second;
	}

	vector<int> color(V, 0);
	color[0] = 1;
	for (int i = 1; i < V; i++) {				// Определим цвет i-ой вершины.
	  std::set<int> colors;

	  for (int j = 0; j < E; j++) {				// Для этого рассмотрим все ребра.
	    if (edges[j].first == i) {				// Если вершина second j-ого ребра смежная i-той вершине
	      colors.insert(color[edges[j].second]);			// То цвет вершины second недоступен для i-ой вершины.
	    }
	    else if (edges[j].second == i) {		        // Иначе если вершина first j-ого ребра смежная i-той вершине
	      colors.insert(color[edges[j].first]);		        // То цвет вершины first недоступен для i-ой вершины.
	    }
	  }
	  // Итак, у нас есть множество цветов вершин, смежных i-ой.
	  // Дело за малым - определить минимальное число от 1 до V включительно (максимум цветов, необходимый для раскраски графа), которого нет в множестве.
	  for (int j = 1; j < V + 1; j++) {				// Рассмотрим цвета от 1 до V + 1
	    auto search = colors.find(j);				// Получим указатель на элемент j в множестве.
	    if (search != colors.end()) {				// Если цвет j найден, его нельзя использовать.
	    }
	    else {							// Иначе											
	      color[i] = j;						// Можем использовать для вершины i цвет j.
	      break;
	    }
	  }
	}
	
	//for (int i = 0; i < V; i++)
	//	cout << color[i] << " ";

	std::sort(color.begin(), color.end());
	cout << *(color.end() - 1);
}
