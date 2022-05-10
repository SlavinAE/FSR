#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

class vehicle{
public:
  double capacity;      // вместимость машины
  double load;          // текущая загруженность машины
  int ID;               // текущее местоположение машины

  vehicle(double capacity_) {capacity = capacity_; load = capacity_; ID = 0;}
};

int numOfCompleted = 0;
class destination {
public:
  double demand, delivered;   // запрос, счетчик доставленного груза
  double x, y;                // координаты
  bool completed;             // флаг удовлетворенности запроса

  void unload(vehicle* v) {
    double lack = this->demand - this->delivered;
    // cout << "demand is " << this-> demand << endl;
    // cout << "lack is " << lack << endl;
    // cout << "load is " << v->load << endl;
    if (v->load >= lack){
      v->load -= lack;
      this->delivered = demand;
      this->completed = true;
      numOfCompleted++;
      cout << "completed: " << this->x << " " << this->y << endl;
    }
    else {
      this ->delivered += v->load;
      v->load = 0;
    }
  }

  destination() {demand = 0; delivered = 0; x = 0; y = 0; completed = true;}   // база
  destination(double d_, double x_, double y_) {
    demand = d_;
    delivered = 0;
    x = x_;
    y = y_;
    completed = false;}   // пункт назначения
};

vector<destination> dest;
double dist(vehicle v, int nextID) {
  return sqrt(pow(dest[v.ID].x - dest[nextID].x, 2) + pow(dest[v.ID].y - dest[nextID].y, 2));
}

auto comp = [](pair<int, double> p1, pair<int, double> p2) {
	      return p1.second > p2.second;
	    };

int main()
{
  ifstream file ("vrp_5_4_1");
  int N, V;
  double capacity, d_, x_, y_;
  file >> N >> V >> capacity;

  dest.resize(N + 1);
  dest[0] = destination();
  for (int i = 1; i < N + 1; i++){
    file >> d_ >> x_ >> y_;
    dest[i] = destination(d_, x_, y_);
  }
  // for (int i = 0; i < N + 1; i++){
  //   cout << "demand: " << dest[i].demand << " x:" << dest[i].x << " y:" << dedst[i].y << endl;

  double price = 0;
  for (int i = 0; i < V; i++){
    cout << endl << endl << "VEHICLE " << i << endl;
    vehicle v(capacity);

    while (v.load > 0 && numOfCompleted < N){
      // найдем ближайшую вершину с ненулевым номером, в оторой completed == false
      priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(comp)> sortedID{ comp };
      for (int j = 1; j < N + 1; j++) {
	if (j != v.ID && dest[j].completed == false) {
	  sortedID.push(pair<int, double>(j, dist(v, j)));
	}
      }
      auto next = sortedID.top();
      // едем в вершину, соответствующую sortedID.top()
      v.ID = next.first;
      price += next.second;

      // разгружаемся
      dest[v.ID].unload(&v);
    }
    // возвращаемся домой
    price += dist(v, 0);
  }
  cout << price;
}
