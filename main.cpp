#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>

#define INT_MAX = 2147483647

using namespace std;

class point{
public:
  long double x, y;
  point& operator=(const point& right){
    this->x = right.x;
    this->y = right.y;
    return *this;
  }
};

class Edge {
private:
  point A, B;

  long double dist(point A, point B){
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
  }

public:
  point A_value() {
    return A;
  }

  point B_value() {
    return B;
  }
  
  long double dist_value(){
    return dist(A, B);
  }

  Edge(long double Ax, long double Ay, long double Bx, long double By) {
    this->A.x = Ax; this->A.y = Ay;
    this->B.x = Bx; this->B.y = By;
  }
  Edge(point _A, point _B) { A = _A; B = _B;}
};

int main(){
  
  int  n = 7, it = 0, jt = 0, kt = 0;
  long double L = 0;
  vector<long double> x(n), y(n);
  vector<point> allVerts(n);
  for(it = 0; it < n; it++) {
    x[it] = 3 * pow(it, 2);
    y[it] = 4 * pow(it, 2);

    point A;
    A.x = x[it]; A.y = y[it];
    allVerts.push_back(A);
  }


  using my_value_t = Edge;
  using my_container_t = vector<Edge>;
  auto my_comp = [] (Edge& e1, Edge& e2) {
		   return e1.dist_value() < e2.dist_value();
		 };

  priority_queue<my_value_t, my_container_t, decltype(my_comp)> path{ my_comp};
  map<point, int> status;
  
  for (it = 0; it < n;  it++){ 
    try {
      if (it == n-1){
	throw it;
      }
      Edge e(x[it], y[it], x[it+1], y[it+1]);
      path.push(e);
      status[e.A_value()] = 2;
      status[e.B_value()] = 2;
      L += e.dist_value();
    }
    catch (long double it){
      Edge e(x[it], y[it], x[0], y[0]);
      path.push(e);
      status[e.A_value()] = 2;
      status[e.B_value()] = 2;
      L += e.dist_value();
    }
  }


  
  long double Lnew = 0;
  vector<Edge> poped(3)
  for (it = 0; it < n - n%3; it++) {

    for (jt = 0; jt < 3; jt++){
      const Edge maxEdge = path.top();    // Берем наибольшее ребро
      path.pop();                         // Удаляем его
      poped[jt] = maxEdge;
      // Вершинам, образующим его, понижаем число инцидентных ребер на один
      status[poped[jt]].A_value()--;
      status[poped[jt]].B_value()--;
      L -= poped[jt].dist_value();   // Уменьшаем длину пути
    }

    for (int k = 0; k < 3; k++){
      long double l = INT_MAX;
      long double jtOfMin = -1, ktOfMin = -1;

      // Просто повторим операцию три раза, пока что идейно криво по ключам
      for (jt = 0; jt < n - 1; jt++){
	for (kt = jt + 1; kt < n; kt++){
	  if (status[allVerts[jt]] != 2 && status[allVerts[kt]] != 2) { // Если у пары вершин не два инцидентных ребра
	    Edge e(allVerts[jt], allVerts[kt]);                         // расмотрим ребро между ними
	    if (e.dist_value() < l) {                                   // Ищем наименьшее 
	      l = e.dist_value();           
	      jtOfMin = jt;
	      ktOfMin = kt;
	    }
	  }
	}
      }
      status[allVerts[jtOfMin]]++;
      status[allVerts[ktOfMin]]++;
      Edge edge2add(allVerts[jtOfMin], allVerts[ktOfMin]);
      path.push(edge2add);
      L += l;
    }
  }
  cout << L;   //посмотрим насколько хорошо работает сейчас
}
