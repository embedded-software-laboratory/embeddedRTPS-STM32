#include <cmath>
#include <rtps.hpp>

RTPSParticipant* g_participant;

RTPSParticipant* create_participant(){
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


RTPSWriter* create_rtps_writer(const char* topic, const char* data_type_name){

    std::cout << "Creating FastRTPS Writer on topic " << topic << std::endl;

    HistoryAttributes hatt;
    hatt.payloadMaxSize = 15000;
    
    WriterHistory* history = new WriterHistory(hatt);
    WriterAttributes watt;
    RTPSWriter* writer;

    try{
        writer = RTPSDomain::createRTPSWriter(g_participant, watt, history);
    }catch (const std::exception& e){
        std::cout << "Writer creation failed with error: " << e.what() << std::endl;
	return nullptr;
    }

    std::cout << "Successfully created writer." << std::endl;

    TopicAttributes tattr;
	tattr.topicKind = NO_KEY;
	tattr.topicDataType = data_type_name;
	tattr.topicName = topic;
    WriterQos wqos;

    if(!g_participant->registerWriter(writer,tattr, wqos)){
        std::cout << "Failed to register Writer." << std::endl;
        return nullptr;
    }

    return writer;
}

void publish(RTPSWriter* writer, uint8_t* msg, uint32_t msg_len){
    CacheChange_t * ch = writer->new_change([msg_len]() -> int32_t { return msg_len; }, ALIVE);
    ch->serializedPayload.data = msg;
    ch->serializedPayload.length = msg_len;
    writer->
    info->history->add_change(ch);
}

SubListener* create_rtps_subscriber(const char* topic, const char* data_type_name, void* data, callback_t cb){
    log("creating subscriber, topic=" << topic << ", data_type=" << data_type_name);

    SubListener* listener = new SubListener(cb, data);

    HistoryAttributes hatt;
    hatt.payloadMaxSize = 15000;
    
    ReaderHistory* history = new ReaderHistory(hatt);
    ReaderAttributes ratt;
    RTPSReader * reader = RTPSDomain::createRTPSReader(g_participant, ratt, history, listener);

    if(!reader){
        log("Failed to create reader.");
        error_hook(RTPS_ERROR_SUBSCRIBER_CREATE_FAILED);
	asoa::OS::mutex::unlock(driver_mutex_);
        return nullptr;
    }

    log("Reader GUID:" << reader->getGuid() << std::endl);

    TopicAttributes tattr;
    tattr.topicKind = NO_KEY;
    tattr.topicDataType = data_type_name;
    tattr.topicName = topic;
    ReaderQos rqos;

    if(!g_participant->registerReader(reader, tattr, rqos)){
        log("failed to register reader");
        error_hook(RTPS_ERROR_SUBSCRIBER_CREATE_FAILED);
	asoa::OS::mutex::unlock(driver_mutex_);
        return nullptr;
    }else{
        log("success registering reader");
    }

    return listerner;
}
