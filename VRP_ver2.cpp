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
    int ID;                // destination ID

    vehicle(int c) { capacity = c; load = c; ID = 0; }
};

class destination {
public:
    double demand, delivered;  // запрос, счетчик доставленного груза
    double  x, y;              // абсцисса, ордината
    bool completed;            // флаг удовлетворенности запроса


    destination(int d_, int x_, int y_) {
        demand = d_;
        delivered = 0;
        x = x_;
        y = y_;
        if (d_ == 0) {
            completed = true;   // база
        }
        else {
            completed = false;  // пункты назначения
        }
    }
};
double dist(destination A, destination B) {
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}
class Path {
public:
    vector<destination> path;
    int size;

    void addDestination(destination& A) {
        if (size < 2) {
            path.push_back(A);
        }
        else {
            path.push_back(path[0]);
            auto it = path.begin(), jt = it + 1;
            long double minimalDist = dist(*it, A) + dist(A, *(it + 1));
            it++;

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

auto comp = [](pair<int, double> p1, pair<int, double> p2) {
    return p1.second > p2.second;
};

int main()
{
    ifstream file("vrp_48_4_1");
    int N, V, capacity;
    double d_, x_, y_;
    file >> N >> V >> capacity;

    Path path;
    for (int i = 0; i < N; i++) {
        file >> d_ >> x_ >> y_;
        destination A(d_, x_, y_);
        path.addDestination(A);
    }


    for (int i = 0; i < N; i++) {
        cout << "demand:" << path.path[i].demand << " x:" << path.path[i].x << " y:" << path.path[i].y << " already delivered:" << path.path[i].delivered << " completed:" << path.path[i].completed << endl;
    }   
    // получено решение, если бы была задача тсп
    // будем гонять машины в этом порядке

    double price = 0;
    int numOfCompleted = 1;

    for (int i = 0; i < V; i++) {
        cout << endl << endl << "VEHICLE " << i << endl;
        vehicle v(capacity);

        while (v.load > 0 && numOfCompleted < N) {

            // едем в вершину numOfCompleted
            v.ID = numOfCompleted;
            price += dist(path.path[v.ID], path.path[v.ID - 1]);
            cout << "ID " << numOfCompleted << endl;
            cout << path.path[numOfCompleted].x << " " << path.path[numOfCompleted].y << endl;

            // разгружаемся в ней
            double lack = path.path[numOfCompleted].demand - path.path[numOfCompleted].delivered;
            cout << "demand is " << path.path[numOfCompleted].demand << endl;
            cout << "lack is " << lack << endl;
            cout << "load is " << v.load << endl;
            if (v.load >= lack) {
                  v.load -= lack;
                  path.path[numOfCompleted].delivered = path.path[numOfCompleted].demand;
                  path.path[numOfCompleted].completed = true;
                  cout << "completed: " << path.path[numOfCompleted].x << " " << path.path[numOfCompleted].y << endl << "_______________________________________________" << endl;
                  numOfCompleted++;  
            }
             else {
                path.path[numOfCompleted].delivered += v.load;
                v.load = 0;
             }
        }
        // возвращаемся домой
        price += dist(path.path[v.ID], path.path[0]);
    }
   cout << price;
}
