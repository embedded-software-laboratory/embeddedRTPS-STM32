#ifndef RTPS_H
#define RTPS_H

#include <fastrtps/Domain.h>
#include <fastrtps/attributes/TopicAttributes.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/rtps_all.h>

#include <fastrtps/qos/ReaderQos.h>
#include <fastrtps/qos/WriterQos.h>
#include <fastrtps/utils/eClock.h>
#include <fastrtps/log/Log.h>

#include <iostream>

using namespace eprosima;
using namespace fastrtps;
using namespace rtps;

typedef void (*callback_t)(const uint8_t* msg, const uint32_t len, void* arg);

RTPSParticipant* create_participant();

RTPSWriter* create_rtps_writer(const char* topic, const char* data_type_name);

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

SubListener* create_rtps_subscriber(const char* topic, const char* data_type_name, void* data, callback_t cb);

#endif