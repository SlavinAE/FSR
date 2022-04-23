#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

class dinge {
public:
    double price, weight;
    dinge& operator=(const  dinge& right) {
        this->price = right.price;
        this->weight = right.weight;
        return *this;
    }

    dinge() { price = 0;  weight = 0; }
    dinge(double _price, double _weight) { price = _price; weight = _weight; }
};
auto my_comp = [](dinge& l, dinge& r) {
    return l.price / l.weight < r.price / r.weight;
};

int main()
{
    ifstream file("ks_60_0");
    double weight, price, K;
    priority_queue<dinge, vector<dinge>, decltype(my_comp)> knapsack{ my_comp };

    int n;
    file >> n >> K;
    for (int it = 0; it < n; it++) {
        file >> price >> weight;
        knapsack.push(dinge(price, weight));
    }
 
    double w = 0, p = 0;
    for (int it = 0; it < n; it++) {
        dinge d = knapsack.top();
        if (w + d.weight <= K) {
            w = w + d.weight;
            p = p + d.price;
        }
        knapsack.pop();
    }
    cout << p << endl;
}
