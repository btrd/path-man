#include <iostream>

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/server_credentials.h>
#include <grpc++/status.h>
#include <grpc++/stream.h>
#include "adn_exchange.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using pathman::VillageP;
using pathman::PersonP;
using pathman::GeneP;

class AdnExchangeImpl final : public pathman::AdnExchange::Service {
 public:
  explicit AdnExchangeImpl() {
  }

  Status Shuffle(ServerContext* context, const VillageP* vil_client,
                    VillageP* vil_server) override {
    vil_server = getNextVil(*vil_client);
    return Status::OK;
  }

 private:
  VillageP* getNextVil(VillageP vil_client) {

    int res = -1;
    for (int i = 0; i < village_list.size(); ++i) {
      if (village_list.at(i).id() == vil_client.id()) {
        res = i+1;
        village_list.at(i) = vil_client;
      }
    }
    if(res == village_list.size()){
      res = 0;
    }
    if (res == -1) {
      village_list.push_back(vil_client);
      res = 0;
    }
    return &village_list.at(res);
  }

  std::vector<VillageP> village_list;
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  AdnExchangeImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
