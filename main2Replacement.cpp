#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <climits>

using namespace std;

class point {
public:
    long double x, y;
    point& operator=(const  point& right) {
        this->x = right.x;
        this->y = right.y;
        return *this;
    }

    point(long double _x, long double _y) { x = _x; y = _y; };
};
bool operator<(const point& l, const point& r) {
    return l.x < r.x;
}
long double dist(point A, point B) {
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

// Теперь попробуем работать непосредственно с положением точки в пути, а не с ребрами. Поэтому нужен класс Путь, а не Ребро
class Path {
public:
  vector<point> path;
  int size;        // теперь для каждой итерации добавления точки нужно знать размер цепи
  long double length() {
    long double L = 0;
    for (int i = 0; i < size; i++) {
      try {
        if (i == size - 1) {
          throw i;
        }
        L += dist(path[i], path[i + 1]);
      }
      catch (int i) {
        L += dist(path[i], path[0]);
      }
    }
    return L;
  }
  
void addPoint(point& A) {
    if (size < 2) {
      path.push_back(A); // тривиально
    }
    else {
      path.push_back(path[0]);
      auto it = path.begin(), jt = it + 1;
      long double minimalDist = dist(*it, A) + dist(A, *(it + 1));
      it++;

      // найдем лучшее место для точки в цепи в смысле этой метрики
      for (int i = 0; i < size - 1; i++) {
        long double possibleDist = dist(*it, A) + dist(A, *(it + 1));
        if (possibleDist < minimalDist) {
          minimalDist = possibleDist;
          jt = it + 1;
        }
        it++;
      }
      path.emplace(jt, A);
      path.pop_back();
    }

    size++;
  }
  
  Path() { size = 0; }
};


int main(){
  int n, i = 0;
  long double x, y, minimalDist, possibleDist;
  Path path;

   cin >> n;
    for (i; i < n; i++) {
      cin >> x >> y;
      point A(x, y);
      path.addPoint(A);
      cout << i << endl;
    }

  // попробуем обойтись только 2-заменой ребер, ведь тогда кристально ясно, какие у нас есть варианты
  bool flag = false;
  for (int i = 0; i < n - 2; i++)
    for (int j = i + 2; j < n; j++) {
      try {
	if (j == n - 1) {
	  throw j;
	}
	minimalDist  = dist(path.path[i], path.path[i + 1]) + dist(path.path[j], path.path[j + 1]);
	possibleDist = dist(path.path[i], path.path[j]) + dist(path.path[i + 1], path.path[j + 1]);
      }
      catch (int j) {
	minimalDist = dist(path.path[i], path.path[i + 1]) + dist(path.path[j], path.path[0]);
	possibleDist = dist(path.path[i], path.path[j]) + dist(path.path[i + 1], path.path[0]);
      }
      
      if (minimalDist > possibleDist) {
	auto it1 = next(path.path.begin(), i + 1);
	auto it2 = next(it1, j - i); ;
	reverse(it1, it2);
	flag = true;
      }
      // по идее надо вернуться, если улучшились
      if (flag == true){
	flag = false;
	j = i + 2;
      }
    }  
  cout << path.length();
}
