#include <iostream>

#include "WFC/Map.h"
#include "WFC/WFC.h"
#include "WFC/MultiThread.h"
#include "Debug/Obj.h"

using namespace std;

/* TODO
* multithreading(!)
*/

int main() {
    /*
    wfc::WFC<Obj> wfc(g_smartTile, 100, 10);
    auto map = wfc.run(0);
    map.draw();
    */
   
    wfc::MultiThread<Obj> mltThr(wfc::Map<Obj>(g_smartTile, 10, 10));

    /* 
    * size      | max time | function    |  total execution time
    * ----------+----------+-------------+------------------------------
    * 2.500     | 6  ms    | propagate() | 18.041 ms
    * 5.000     | 6  ms    | propagate() | 35.222 ms
    * 10.000    | 6  ms    | propagate() | 81.798 ms
    * 100.000   | 40 ms    | propagate() | llegue hasta 10.000/100.1000
    */


    return 0;
}
