#include <cmath>

#include <asoa/driver/rtps.h>
#include <asoa/driver/os.h>

#include <fastrtps/Domain.h>
#include <fastrtps/attributes/TopicAttributes.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/rtps_all.h>


#include <fastrtps/qos/ReaderQos.h>
#include <fastrtps/qos/WriterQos.h>
#include <fastrtps/utils/eClock.h>
#include <fastrtps/log/Log.h>

using namespace eprosima;
using namespace fastrtps;
using namespace rtps;

#define EPROSIMA_MAX_PUBLISHER 100
#define EPROSIMA_MAX_SUBSCRIBER 100

#define log(X) // std::cout << "[EPROSIMA] " << X << std::endl;

RTPSParticipant* g_participant;

asoa::OS::mutex::mutex_t* driver_mutex_;

typedef struct eprosima_writer_t{
    RTPSWriter* writer;
    WriterHistory* history;
} eprosima_writer_t;

struct rtps_publisher_t g_publisher[EPROSIMA_MAX_PUBLISHER];
uint32_t g_publisher_cnt = 0;

struct rtps_subscriber_t g_subscriber[EPROSIMA_MAX_SUBSCRIBER];
uint32_t g_subscriber_cnt = 0;

extern "C"{

bool rtps_finalize_init(){
    return true;
    // not necessary for x86
}

typedef enum{
    RTPS_ERROR_SUBSCRIBER_CREATE_FAILED,
    RTPS_ERROR_WRITER_CREATE_FAILED
} rtps_driver_error_t;

void error_hook(rtps_driver_error_t error){
    switch(error){
        case RTPS_ERROR_SUBSCRIBER_CREATE_FAILED:
        case RTPS_ERROR_WRITER_CREATE_FAILED:
        default:
            log("error code: " << error);
            std::exit(-1);
    }
}

RTPSParticipantAttributes PParam;

struct rtps_driver_t* rtps_init(){
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

    rtps_driver_t* driver = new rtps_driver_t();
    driver->ptr_ = (void*)g_participant;
    return driver;
}


struct rtps_publisher_t* rtps_create_publisher(const char* topic, const char* data_type_name){

    asoa::OS::mutex::lock(driver_mutex_);

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

    struct eprosima_writer_t* info = (eprosima_writer_t*)malloc(sizeof(eprosima_writer_t));

    info->writer = writer;
    info->history = history;

    g_publisher[g_publisher_cnt].ptr_ = (void*) info;
    g_publisher_cnt++;

    asoa::OS::mutex::unlock(driver_mutex_);

    return &(g_publisher[g_publisher_cnt-1]);
}

void rtps_publish(struct rtps_publisher_t* publisher, uint8_t* msg, uint32_t msg_len){
    struct eprosima_writer_t* info = (eprosima_writer_t*)publisher->ptr_;
    CacheChange_t * ch = info->writer->new_change([msg_len]() -> int32_t { return msg_len; }, ALIVE);
    ch->serializedPayload.data = msg;
    ch->serializedPayload.length = msg_len;
    info->history->add_change(ch);
}

class SubListener : public ReaderListener {
    private:
        rtps_subscriber_cb_t cb_;
        void* args_;
    public:
        SubListener(rtps_subscriber_cb_t cb, void* args) : cb_(cb), args_(args) {}
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

struct rtps_subscriber_t* rtps_create_subscriber(const char* topic, const char* data_type_name, void* data, rtps_subscriber_cb_t cb){

    asoa::OS::mutex::lock(driver_mutex_);

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

    g_subscriber[g_subscriber_cnt].ptr_ = (void*)reader;
    g_subscriber_cnt++;

    asoa::OS::mutex::unlock(driver_mutex_);

    return &(g_subscriber[g_subscriber_cnt-1]);
}

}
