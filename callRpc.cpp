#include <grpc/grpc.h>
#include <grpc++/channel_arguments.h>
#include <grpc++/channel_interface.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/credentials.h>
#include <grpc++/status.h>
#include <grpc++/stream.h>
#include "adn_exchange.grpc.pb.h"

using grpc::ChannelArguments;
using grpc::ChannelInterface;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using pathman::VillageP;
using pathman::PersonP;
using pathman::GeneP;

class AdnExchangeClient {
 public:
  AdnExchangeClient(std::shared_ptr<ChannelInterface> channel) : stub_(AdnExchange::NewStub(channel)) {
  }

  VillageP Shuffle(VillageP vil_client) {
    ClientContext context;
    VillageP vil_server;
    Status status = stub_->GetFeature(&context, vil_client, vil_server);
    if (!status.IsOk()) {
      std::cout << "GetFeature rpc failed." << std::endl;
    }
    return vil_server;
  }

 private:
  std::unique_ptr<AdnExchange::Stub> stub_;
};

VillageP callRpc(VillageP vil_client) {
  AdnExchangeClient guide(grpc::CreateChannel("localhost:50051", grpc::InsecureCredentials(),ChannelArguments()));
  VillageP vil_server = guide.Shuffle(vil_client);
  return vil_server;
}
