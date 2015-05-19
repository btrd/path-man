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
using pathman::Adn;

class AdnExchangeClient {
 public:
  AdnExchangeClient(std::shared_ptr<ChannelInterface> channel, std::vector<Adn> client_adn) : stub_(RouteGuide::NewStub(channel)) {
    adn_list = client_adn;
  }

  std::vector<Adn> Shuffle() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<Adn, Adn> > stream(stub_->Shuffle(&context));

    std::thread writer([stream]() {
      for (const Adn& a : adn_list) {
        std::cout << "Sending adn " << a.id_village() 
                  << " direct " << a.direct()
                  << " steps " << a.steps()
                  << std::endl;
        stream->Write(a);
      }
      stream->WritesDone();
    });

    std::vector<Adn> received_adn;
    Adn server_adn;
    while (stream->Read(&server_adn)) {
      received_adn.push_back(server_adn);
    }
    writer.join();
    Status status = stream->Finish();
    if (!status.IsOk()) {
      std::cout << "Shuffle rpc failed." << std::endl;
    }
    return received_adn;
  }

 private:
  std::vector<Adn> adn_list;
};

std::vector<Adn> callRpc(std::vector<Adn> client_adn) {
  AdnExchangeClient guide(grpc::CreateChannel("localhost:50051", grpc::InsecureCredentials(),ChannelArguments()), client_adn);
  std::vector<Adn> server_adn = guide.Shuffle();

  return server_adn;
}
