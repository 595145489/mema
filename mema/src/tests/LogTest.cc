#include "src/base/Log.h"
using namespace mema;

//more thread condition such be added.
int main(){
    LOG_DEBUG(1);
    LOG_DEBUG("123");
    LOG_DEBUG(1.453);
    LOG_ERROR("the masseages");
    return 0;
}
