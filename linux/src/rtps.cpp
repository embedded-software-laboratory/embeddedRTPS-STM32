#include <cmath>
#include <rtps.hpp>

using namespace eprosima;
using namespace fastrtps;
using namespace rtps;


RTPSParticipant* g_participant;

RTPSParticipant* create_participant(){
    log("creating Participant");
    driver_mutex_ = asoa::OS::mutex::create();

    // static avoids seg fault in destructor for petalinux
    PParam.builtin.use_SIMPLE_RTPSParticipantDiscoveryProtocol = true;
    PParam.builtin.use_SIMPLE_EndpointDiscoveryProtocol = true;

    PParam.builtin.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    PParam.builtin.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;

    PParam.builtin.domainId = 0;
    PParam.builtin.leaseDuration = c_TimeInfinite;
    PParam.setName("Participant_sub");

    log("PParam configuration done, about to create participant");
    g_participant = RTPSDomain::createParticipant(PParam);
    log("participant created.");

    return g_participant;
}


RTPSWriter* create_rtps_writer(const char* topic, const char* data_type_name){

    log("creating publisher, topic = " << topic << ", data type = " << data_type_name);

    HistoryAttributes hatt;
    hatt.payloadMaxSize = 15000;
    
    WriterHistory* history = new WriterHistory(hatt);
    log("Success creating history");
    WriterAttributes watt;
    RTPSWriter* writer;

    try{
        writer = RTPSDomain::createRTPSWriter(g_participant, watt, history);
    }catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        error_hook(RTPS_ERROR_WRITER_CREATE_FAILED);
	return nullptr;
    }

    log("Success creating writer: " << writer);
    // Register type
    log("Writer GUID:" << writer->getGuid() << std::endl);

    TopicAttributes tattr;
	tattr.topicKind = NO_KEY;
	tattr.topicDataType = data_type_name;
	tattr.topicName = topic;
    WriterQos wqos;

    if(!g_participant->registerWriter(writer,tattr, wqos)){
        log("failed to register writer!");
        error_hook(RTPS_ERROR_WRITER_CREATE_FAILED);
        return nullptr;
    }else{
        log("success registering writer");
    }

    return writer;
}

void publish(RTPSWriter* writer, uint8_t* msg, uint32_t msg_len){
    CacheChange_t * ch = writer->new_change([msg_len]() -> int32_t { return msg_len; }, ALIVE);
    ch->serializedPayload.data = msg;
    ch->serializedPayload.length = msg_len;
    info->history->add_change(ch);
}

class SubListener : public ReaderListener {
    private:
        callback_t cb_;
        void* args_;
    public:
        SubListener(callback_t cb, void* args) : cb_(cb), args_(args) {}
        ~SubListener(){}
        void onNewCacheChangeAdded(RTPSReader* reader, const CacheChange_t* const change){
            cb_(change->serializedPayload.data, change->serializedPayload.length, args_);
            reader->getHistory()->remove_change((CacheChange_t*) change);
        }

        void onReaderMatched(RTPSReader* reader, MatchingInfo& info){
            log( "Reader match"  << std::endl);
            log( "Remote Endpoint GUID" << info.remoteEndpointGuid  << std::endl);
            log("Local  Endpoint GUID" << reader->getGuid()  << std::endl);
        }
};
SubListener* rtps_create_subscriber(const char* topic, const char* data_type_name, void* data, callback_t cb){
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
