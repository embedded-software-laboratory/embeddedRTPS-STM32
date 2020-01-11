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

typedef void (*callback_t)(const uint8_t* msg, const uint32_t len, void* arg);

RTPSParticipant* create_participant();

RTPSWriter* create_rtps_writer(const char* topic, const char* data_type_name);


#endif