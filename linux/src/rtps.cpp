#include <cmath>
#include <rtps.hpp>

RTPSParticipant* g_participant;
std::mutex rtps_mutex;

RTPSParticipant* create_participant(){
    std::lock_guard<std::mutex> lock(rtps_mutex);
    std::cout << "Creating Participant..." << std::endl;
    
    RTPSParticipantAttributes PParam;

    PParam.builtin.use_SIMPLE_RTPSParticipantDiscoveryProtocol = true;
    PParam.builtin.use_SIMPLE_EndpointDiscoveryProtocol = true;

    PParam.builtin.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    PParam.builtin.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;

    PParam.builtin.domainId = 0;
    PParam.builtin.leaseDuration = c_TimeInfinite;
    PParam.setName("Participant_sub");

    g_participant = RTPSDomain::createParticipant(PParam);
    std::cout << "Created Participant succesfully." << std::endl;

    return g_participant;
}


bool create_rtps_writer(RTPSWriter** writer, WriterHistory** history, const char* topic, const char* data_type_name){
    std::lock_guard<std::mutex> lock(rtps_mutex);
    std::cout << "Creating FastRTPS Writer on topic " << topic << std::endl;

    HistoryAttributes hatt;
    hatt.payloadMaxSize = 15000;
    
    *history = new WriterHistory(hatt);
    WriterAttributes watt;

    try{
        *writer = RTPSDomain::createRTPSWriter(g_participant, watt, *history);
    }catch (const std::exception& e){
        std::cout << "Writer creation failed with error: " << e.what() << std::endl;
	    return false;
    }

    std::cout << "Successfully created writer." << std::endl;

    TopicAttributes tattr;
	tattr.topicKind = NO_KEY;
	tattr.topicDataType = data_type_name;
	tattr.topicName = topic;
    WriterQos wqos;

    if(!g_participant->registerWriter(*writer,tattr, wqos)){
        std::cout << "Failed to register Writer." << std::endl;
        return false;
    }

    return true;
}

void publish(RTPSWriter* writer, WriterHistory* history, uint8_t* msg, uint32_t msg_len){
    std::lock_guard<std::mutex> lock(rtps_mutex);
    CacheChange_t * ch = writer->new_change([msg_len]() -> int32_t { return msg_len; }, ALIVE);
    ch->serializedPayload.data = msg;
    ch->serializedPayload.length = msg_len;
    history->add_change(ch);
}

SubListener* create_rtps_reader(const char* topic, const char* data_type_name, void* data, callback_t cb){
    std::lock_guard<std::mutex> lock(rtps_mutex);
    std::cout << "Creating RTPS reader on topic:" << topic << std::endl;

    SubListener* listener = new SubListener(cb, data);

    HistoryAttributes hatt;
    hatt.payloadMaxSize = 15000;
    
    ReaderHistory* history = new ReaderHistory(hatt);
    ReaderAttributes ratt;
    RTPSReader * reader = RTPSDomain::createRTPSReader(g_participant, ratt, history, listener);

    if(!reader){
        std::cout << "Failed to create reader." << std::endl;
        return nullptr;
    }

    TopicAttributes tattr;
    tattr.topicKind = NO_KEY;
    tattr.topicDataType = data_type_name;
    tattr.topicName = topic;
    ReaderQos rqos;

    if(!g_participant->registerReader(reader, tattr, rqos)){
        std::cout << "Failed to create reader." << std::endl;
        return nullptr;
    }

    return listener;
}
