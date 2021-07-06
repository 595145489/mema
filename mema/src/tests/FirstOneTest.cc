#include "src/base/Buffer.h"
#include "src/base/ListBuffer.h"
using namespace mema;
#include <iostream>
using namespace std;

int main(){

    shared_ptr<ListBuffer> list_ = make_shared<ListBuffer>(10);
    shared_ptr<ListBuffer> list1_ = make_shared<ListBuffer>(10);
    list1_->EmplaceBack(list_,5);

    int i = 0;
    
    if(0){
        Buffer x;
        x << 12.22;
        x << ' ';
        x << 55555555;
        x << ' ';
        bool q = 1;
        x << q;
        x << ' ';
        x << "AACD";
        x << 3.12924;
        cout << x.GetString() << endl; 
    }

    return 0;
}
