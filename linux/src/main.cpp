
#include <rtps.hpp>
#include <unistd.h>


using namespace eprosima;
using namespace fastrtps;
using namespace rtps;

// Callback on message from STM32 
void callback(const uint8_t* msg, const uint32_t len, void* arg){
    std::cout << "Received message from STM32 with len:" << std::to_string(len) << std::endl;
    
    (*(bool*)arg) = true;
    
    for(uint32_t i = 0; i < len; i ++){
        std::cout << std::to_string(i) << " : " << std::to_string(msg[i]) << std::endl;
    }

    std::cout << std::endl;
}


// Create Subscriber to listen to messages form the STM32
int main(){
    
    std::cout << "Created subscriber on Topic: Test : Test" << std::endl;

    uint8_t TEST_COUNT = 10;
    const size_t BATCH_SIZE = 30; 

    bool received_response = false;
    std::array<uint8_t, BATCH_SIZE> test_data;

    auto* sub = create_rtps_reader("TEST","TEST",&received_response,&callback);
    
    RTPSWriter* writer;
    WriterHistory* history;

    bool writer_creation_success = create_rtps_writer(writer,history, "TESTRETURN","TESTRETURN");

    std::cout << "Looping main thread and waiting for message from STM32." << std::endl;
    
    while(TEST_COUNT > 0){
        usleep(50000); //sleep 50 milliseconds

        std::cout << "Conducting new Test..." << std::endl;

        received_response = false;
        memset(test_data.data, BATCH_SIZE, TEST_COUNT);
        publish(writer, history, test_data.data, BATCH_SIZE);

        std::cout << "Send message to the STM32." << std::endl;

        while(!received_response){
            usleep(100);
        }
        std::cout << "Received response from the STM32." << std::endl;

        TEST_COUNT--;
    }
    
    return 0;
}


