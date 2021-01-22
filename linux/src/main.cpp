
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
    std::cout << "Creating RTPS Participant..." << std::endl;

    create_participant();

    uint32_t number_of_tests = 10;
    const size_t test_data_size = 30; 

    bool received_response = false;
    std::array<uint8_t, test_data_size> test_data;

    auto* sub = create_rtps_reader("TOLINUX","TEST",&received_response,&callback);
    
    RTPSWriter* writer;
    WriterHistory* history;

    bool writer_creation_success = create_rtps_writer(&writer,&history, "TOSTM","TEST");

    std::cout << "Waiting for reader match with STM32..." << std::endl;
    while(!sub->reader_has_matched){}

    std::cout << "Got Reader match - starting tests..." << std::endl;
    
    while(number_of_tests > 0){
        usleep(50000); //sleep 50 milliseconds

        std::cout << "Conducting new Test: " << number_of_tests << std::endl;

        received_response = false;
        test_data.fill(15);
        publish(writer, history, test_data.data(), test_data_size);

        std::cout << "Send message to the STM32." << std::endl;

        while(!received_response){
            usleep(100);
        }

        number_of_tests--;
    }
    
    return 0;
}


