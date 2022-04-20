#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <climits>
//#define INT_MAX  2147483647

using namespace std;

class point{
public:
  long double x, y;
  point& operator=(const  point& right){
    this->x = right.x;
    this->y = right.y;
    return *this;
  }
};
bool operator<(const point& l, const point& r){
  return l.x < r.x;  // порядок вершин в мапе нам не важен
}


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
  Edge() {};
};

int  main(){
  
  long double  n = 0, it = 0, jt = 0, kt = 0;
  long double  L = 0;
  cin >> n;
  vector<point> allVerts(n);
  vector<long double> x(n);
  vector<long double> y(n);
  for (it = 0; it < n; it++){
    cin >> x[it] >> y[it];
  }  
  for(it = 0; it < n; it++) {
    point A;
    A.x = x[it]; A.y = y[it];
    allVerts[it] = A;
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
    catch (long double  it){
      Edge e(x[it], y[it], x[0], y[0]);
      path.push(e);
      status[e.A_value()] = 2;
      status[e.B_value()] = 2;
      L += e.dist_value();
    }
  }


  
  long double Lnew = 0;
  vector<Edge> poped(n);
  for (it = 3; it < n - 3; it += 3) {
        //cout << "Starting new cicle. it " << it << endl;

        // удалим ребра [0; it)
        for (jt = 0; jt < it; jt++) {
            const Edge maxEdge = path.top();    // берем наибольшее ребро
            path.pop();                         // удаляем его
            poped[jt] = maxEdge;
            //cout << "deleted " << poped[jt].dist_value() << endl;

            // вершинам, образующим его, понижаем число инцидентных ребер на один
            status[poped[jt].A_value()]--;
            status[poped[jt].B_value()]--;
            L -= poped[jt].dist_value();   // уменьшаем длину пути
        }

        // вернем ребра [0; it - 3)
        for (jt = 0; jt < it - 3; jt++) {
            path.push(poped[jt]);
            //cout << poped[jt].dist_value() << " returns" << endl;

            // вершинам, образующим возвращенное ребро, повышаем число инцидентных ребер на один
            status[poped[jt].A_value()]++;
            status[poped[jt].B_value()]++;
            L += poped[jt].dist_value();   // увеличиваем длину пути
        }

         //теперь рассматриваются только вершины, образующие три удаленных ребра
         //
         // ищем новые ребра три раза
        for (int k = 0; k < 3; k++) {
            long double l = INT_MAX;
            long double jtOfMin = -1, ktOfMin = -1;
            for (jt = 0; jt < n - 1; jt++) {
                for (kt = jt + 1; kt < n; kt++) {
                    // если у каждой из двух вершин не два инцидентных ребра
                    if (status[allVerts[jt]] != 2 && status[allVerts[kt]] != 2) {
                        Edge e(allVerts[jt], allVerts[kt]);
                        // есть шанс добавить ребро, образованное этими вершинами
                        //cout << "maybe we will push " << e.dist_value() << endl;
                        if (e.dist_value() < l) {                                   // Ищем наименьшее
                            l = e.dist_value();
                            jtOfMin = jt;
                            ktOfMin = kt;
                        }
                    }
                }
            }
            // нашли индексы вершин, образующих наименьшее ребро
            // проводим его, значит число инцидентных ребер дляэтих вершин увеличено на 1
            status[allVerts[jtOfMin]]++;
            status[allVerts[ktOfMin]]++;
            Edge edge2add(allVerts[jtOfMin], allVerts[ktOfMin]);
            // добавляем ребро в путь
            path.push(edge2add);
            //cout << "pushed " << edge2add.dist_value() << " current it is " << it << endl;
            L += l; // увеличиваем длину пути
        }
        //cout << "now L is " << L << endl;
    }
    cout << L;   //посмотрим насколько хорошо работает сейчас
    return 0;
}
