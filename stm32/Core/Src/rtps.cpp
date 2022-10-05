/*
 * rtps.cpp
 *
 *  Created on: Apr 20, 2022
 *      Author: alex
 */


#include <rtps_test.h>
#include "rtps/rtps.h"


//Callback function to set the boolean to true upon a match
void setTrue(void* args){
	*static_cast<volatile bool*>(args) = true;
}

void message_callback(void* callee, const rtps::ReaderCacheChange& cacheChange){
	printf("Received data from Linux\r\n");
}


//Function to start the RTPS Test
void startRTPStest(){

	//Initialize variables and complete RTPS initialization
	bool subMatched = false;
	bool pubMatched = false;
	bool received_message = false;

	static rtps::Domain domain;

	//Create RTPS participant
	rtps::Participant* part = domain.createParticipant();
	if(part == nullptr){
		return;
	}

	//Register callback to ensure that a publisher is matched to the writer before sending messages
	part->registerOnNewPublisherMatchedCallback(setTrue, &pubMatched);
	part->registerOnNewSubscriberMatchedCallback(setTrue, &subMatched);

	//Create new writer to send messages
	rtps::Writer* writer = domain.createWriter(*part, "TOLINUX","TEST", false);
	rtps::Reader* reader = domain.createReader(*part, "TOSTM","TEST", false);
	reader->registerCallback(&message_callback, writer);

	domain.completeInit();

	//Check that writer creation was successful
	if(writer == nullptr || reader == nullptr){
		return;
	}

	//Wait for the subscriber on the Linux side to match
	while(!subMatched || !pubMatched){
		osDelay(500);
	}

	int i = 0;
	while(true){
		static std::array<uint8_t,10> data{};
		data[0] = i++;
		auto* change = writer->newChange(rtps::ChangeKind_t::ALIVE, data.data(), data.size());
		osDelay(1000);
	}
}
