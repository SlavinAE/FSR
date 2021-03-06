#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

class vehicle {
public:
    double capacity;       // вместимость машины
    double load;           // текущая загруженность машины
    int ID;             // destination ID

    vehicle(int c) { capacity = c; load = c; ID = 0; }
};
int numOfCompleted = 1;

class destination {
public:

    double demand, delivered;  // запрос, счетчик доставленного груза
    double  x, y;              // абсцисса, ордината
    bool completed;            // флаг удовлетворенности запроса

    void unload(vehicle* v) {
        double lack = this->demand - this->delivered;
        cout << "demand is " << this->demand << endl;
        cout << "lack is " << lack << endl;
        cout << "load is " << v->load << endl;
        if (v->load >= lack) {
            v->load -= lack;
            this->delivered = demand;
            this->completed = true;
            numOfCompleted++;
            cout << "completed: " << this->x << " " << this->y << endl << "_______________________________________________" << endl;
        }
        else {
            this->delivered += v->load;
            v->load = 0;
        }
    }
    destination() {}
    destination(int d_, int x_, int y_) {
        demand = d_;
        delivered = 0;
        x = x_; y = y_;
        if (d_ == 0) {
            completed = true;
        }
        else {
            completed = false;
        }
    }
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
    ifstream file("vrp_48_4_1");
    int N, V, capacity;
    double d_, x_, y_;
    file >> N >> V >> capacity;

    dest.resize(N);

    for (int i = 0; i < N; i++) {
        file >> d_ >> x_ >> y_;
        dest[i] = destination(d_, x_, y_);
    }

    for (int i = 0; i < N; i++) {
        cout << "demand:" << dest[i].demand << " x:" << dest[i].x << " y:" << dest[i].y << " already delivered:" << dest[i].delivered << " completed:" << dest[i].completed << endl;
    }

    
    double sumLoad = V * capacity;
    double sumDemand = 0;
    for (int i = 0; i < N; i++) {
        sumDemand += dest[i].demand;
    }
    double res = (sumLoad - sumDemand) / V;

    double price = 0;

    for (int i = 0; i < V; i++) {

        cout << endl << endl << "VEHICLE " << i << endl;
        vehicle v(capacity);

        while (v.load > res && numOfCompleted < N) {    // пока load > 0 и не все вопросы удовлетворены

            // найдем ближайшую вершину с ненулевым номером, в которой completed == false
            priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(comp)> sortedID{ comp };
            for (int j = 1; j < N; j++) {
                if (j != v.ID && dest[j].completed == false) {
                    sortedID.push(pair<int, double>(j, dist(v, j)));
                }
            }
            auto next = sortedID.top();//

            // едем в вершину, соответствующую sortedID.top()
            v.ID = next.first;
            price += next.second;

            // разгружаемся 
            dest[next.first].unload(&v);

        }
        // не забываем вернуться домой
            price += dist(v, 0);
    }
    cout << price;
}
