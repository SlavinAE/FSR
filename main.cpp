#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
  long double x, y;
};

long double dist(point a, point b) {
  // эвклидово расстояние между точками на плоскости
  return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) );
}

vector<point> readData(){
  // vector<point> Data;
  // ...
  // return Data
}

int main(){
  vector<point> Data = readData();    // массив точек
  long int n = Data.size();           // число точек
  double long L = 0;                  // длина пути

  // Первое приближение решения задачи - соединение точек по порядку в векторе Data
  int it = 0;
  for (it; it < n; it++) {
    try {
      L += dist(Data[it], Data[it+1]);
    }
    catch(...){
      L += disy(Data[it], Data[0]);
}
