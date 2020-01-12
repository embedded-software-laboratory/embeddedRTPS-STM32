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

class SubListener : public ReaderListener {
    private:
        callback_t cb_;
        void* args_;
    public:
        SubListener(callback_t cb, void* args) : cb_(cb), args_(args) {}
        ~SubListener(){}

        bool reader_has_matched = false;

        void onNewCacheChangeAdded(RTPSReader* reader, const CacheChange_t* const change){
            cb_(change->serializedPayload.data, change->serializedPayload.length, args_);
            reader->getHistory()->remove_change((CacheChange_t*) change);
        }

        void onReaderMatched(RTPSReader* reader, MatchingInfo& info){
            std::cout << "Reader matched to remote Writer." << std::endl;
            std::cout << "Remote Endpoint GUID:" << info.remoteEndpointGuid << std::endl;
            std::cout << "Local  Endpoint GUID:" << reader->getGuid() << std::endl;
            reader_has_matched = true;
        }
};
void publish(RTPSWriter* writer, WriterHistory* history, uint8_t* msg, uint32_t msg_len);
SubListener* create_rtps_reader(const char* topic, const char* data_type_name, void* data, callback_t cb);
bool create_rtps_writer(RTPSWriter** writer, WriterHistory** history, const char* topic, const char* data_type_name);

#endif