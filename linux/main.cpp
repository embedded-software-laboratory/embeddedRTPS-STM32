#include <unistd.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/attributes/TopicAttributes.h>
#include <fastrtps/log/Log.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/qos/ReaderQos.h>
#include <fastrtps/qos/WriterQos.h>
#include <fastrtps/rtps/RTPSDomain.h>
#include <fastrtps/rtps/attributes/HistoryAttributes.h>
#include <fastrtps/rtps/attributes/RTPSParticipantAttributes.h>
#include <fastrtps/rtps/attributes/WriterAttributes.h>
#include <fastrtps/rtps/history/WriterHistory.h>
#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/rtps_all.h>
#include <fastrtps/rtps/writer/RTPSWriter.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/transport/TCPv4TransportDescriptor.h>
#include <fastrtps/transport/TCPv6TransportDescriptor.h>
#include <fastrtps/transport/UDPv4TransportDescriptor.h>
#include <fastrtps/transport/UDPv6TransportDescriptor.h>

using namespace eprosima;
using namespace fastrtps;
using namespace rtps;

RTPSWriter* writer;
WriterHistory* writer_history;

std::array<uint8_t, 10> msg;

bool sent = false;

class SubListener : public ReaderListener {
 public:
 uint8_t send_idx = 0;
  ~SubListener() {}
  void onNewCacheChangeAdded(RTPSReader* reader,
                             const CacheChange_t* const change) {
    change->serializedPayload.data;
    change->serializedPayload.length;
    uint8_t data = change->serializedPayload.data[0];
    std::cout << "Received Hello World Data " << (int)data << ", " << change->serializedPayload.length << " byte" << std::endl;
    reader->getHistory()->remove_change((CacheChange_t*)change);

    CacheChange_t* ch = writer->new_change([]() -> uint32_t { return msg.size(); }, ALIVE);
    if(ch == nullptr){
	std::cout << "History is full, clearing 100 samples from history" << std::endl;
	writer->remove_older_changes(100);
	return;
    }

    msg[0] = send_idx++;
    ch->serializedPayload.data[0] = send_idx++;
    ch->serializedPayload.length = msg.size();
    writer_history->add_change(ch);

    std::cout << "Sending data" << std::endl;
  }

  void onReaderMatched(RTPSReader* reader, MatchingInfo& info) { }
};


int main(){

  RTPSParticipantAttributes PParam;

  PParam.builtin.discovery_config.discoveryProtocol =
      eprosima::fastrtps::rtps::DiscoveryProtocol::SIMPLE;
  PParam.builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
  PParam.builtin.discovery_config.leaseDuration = Duration_t(5);
  PParam.setName("Participant_sub");
  auto participant = RTPSDomain::createParticipant(0, PParam);

  SubListener* listener = new SubListener();

  HistoryAttributes hatt;
  hatt.payloadMaxSize = 15000;
  hatt.maximumReservedCaches = 500;

  ReaderHistory* history = new ReaderHistory(hatt);
  ReaderAttributes ratt;
  RTPSReader* reader = RTPSDomain::createRTPSReader(participant, ratt, history, listener);

  TopicAttributes tattr_reader;
  tattr_reader.topicKind = NO_KEY;
  tattr_reader.topicDataType = "TEST";
  tattr_reader.topicName = "TOLINUX";

  ReaderQos rqos;
  rqos.m_durability.kind = eprosima::fastrtps::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS;
  rqos.m_reliability.kind = eprosima::fastrtps::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS;

  participant->registerReader(reader, tattr_reader, rqos);

  TopicAttributes tattr_writer;
  tattr_writer.topicKind = NO_KEY;
  tattr_writer.topicDataType = "TEST";
  tattr_writer.topicName = "TOSTM";

  writer_history = new WriterHistory(hatt);
  WriterAttributes watt;
  watt.endpoint.durabilityKind = DurabilityKind_t::VOLATILE;
  watt.endpoint.reliabilityKind = ReliabilityKind_t::BEST_EFFORT;
  writer = RTPSDomain::createRTPSWriter(participant, watt, writer_history);

  WriterQos wqos;
  wqos.m_durability.kind =
      eprosima::fastrtps::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS;
  wqos.m_reliability.kind =
      eprosima::fastrtps::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS;

  participant->registerWriter(writer, tattr_writer, wqos);

  while(1){
     usleep(1000000);
  }
  return 0;
}
