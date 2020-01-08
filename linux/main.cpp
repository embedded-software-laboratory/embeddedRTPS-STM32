# include <asoa/driver/os.h>
#include <asoa/driver/rtps.h>
#include <unistd.h>
#include <iostream>

void callback(const uint8_t* msg, const uint32_t len, void* arg){
    std::cout << "got callback" << std::endl;
}

int main(){
    
    rtps_init();
    std::cout << "created subscribr" << std::endl;
    rtps_subscriber_t* sub = rtps_create_subscriber("TEST","TEST",nullptr,&callback);
    std::cout << "looping" << std::endl;
    while(true){
        usleep(1000);
    }
    return 0;
}


