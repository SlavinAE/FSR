#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

class Edge {
private:
  struct point {
    long double x, y;
  };
  point A, B;

  long double dist(point A, point B){
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
  }

public:
  long double dist_value(){
    return dist(A, B);
  }

  Edge(long double Ax, long double Ay, long double Bx, long double By) {
    this->A.x = Ax; this->A.y = Ay;
    this->B.x = Bx; this->B.y = By;
  }
};

//vector<point> readData(){
  // vector<point> Data;
  // ...
  // return Data
//}

int main(){
  
  // vector<point> Data = readData();    // массив точек
  // long int n = Data.size();           // число точек
  // double long L = 0;                  // длина пути

  // Первое приближение решения задачи - соединение точек по порядку в векторе Data
  // int it = 0;
  // for (it; it < n; it++) {
  //  try {
  //    L += dist(Data[it], Data[it+1]);
  //  }
  //  catch(...){
  //    L += dist(Data[it], Data[0]);
  vector<double long> x(5), y(5);
  long double it = 0;

  for(it = 0; it < 5; it++) {
    x[it] = 3 * pow(it, 2);
    y[it] = 4 * pow(it, 2);
  }

  using my_value_t = Edge;
  using my_container_t = vector<Edge>;
  auto my_comp = [] (Edge& e1, Edge& e2) {
		   return e1.dist_value() < e2.dist_value();
		 };

  priority_queue<my_value_t, my_container_t, decltype(my_comp)> path{ my_comp};

  for (it = 0; it < 5;  it++){
    try {
      path.push(Edge(x[it], y[it], x[it+1], y[it+1]));
    }
    catch (...){
      path.push(Edge(x[it], y[it], x[0], y[0]));
    }
  }

  for (it = 0; it < 5; it++){
    const Edge maxEdge = path.top();
    path.pop();
    Edge e = maxEdge;
    cout << e.dist_value() << endl;
  }
}
