#ifndef MULTITHREAD_H
#define MULTITHREAD_H

#include <iostream>
#include <vector>
#include "Map.h"

namespace wfc {

using std::vector;

template <typename T>
class MultiThread 
{
public:
    MultiThread() {}

    MultiThread(const Map<T>& map) {
        m_threadAmount = calculateThreadAmount();
        fragmentY(map, m_threadAmount);
    }
//private:
    int m_threadAmount;
    int m_clusterSize;
    vector<Map<T>> fragmentX(const Map<T>& map, const int amount) const ;

    vector<Map<T>> fragmentY(const Map<T>& map, const int amount) const {
        vector<Map<T>> maps(amount);
        for (int i = 0; i < amount; i++) {
            maps[i] = Map<T>(
                map.tiles[0], 
                map.x,
                map.y / amount,
                map.z
            );
            cout << maps[i] << endl;
        }
        return maps;
    }

    vector<Map<T>> fragmentZ(const Map<T>& map, const int amount) const ;

    bool isDivisibleBy(const int num, const int divisor) const{
        return (num % divisor == 0);
    }

    int calculateThreadAmount() const {
        return 2;
    }
};

};  // namespace wfc

#endif
