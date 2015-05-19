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
using pathman::Adn;

class Population {
 public:
  Population(std::vector<Adn> list) {
    adn_list = list;
    id = list[0].id_village();
  }
  std::vector<Adn> adn_list;
  int id;
};

class AdnExchangeImpl final : public pathman::AdnExchange::Service {
 public:
  explicit AdnExchangeImpl() {
  }

  Status Shuffle(ServerContext* context, ServerReaderWriter<Adn, Adn>* stream) override {
    std::vector<Adn> received_adn;
    Adn a;
    while (stream->Read(&a)) {
      received_adn.push_back(a);
    }
    std::vector<Adn> send_adn = getNextPop(received_adn);
    for (const Adn& a2 : send_adn) {
      stream->Write(a2);
    }
    return Status::OK;
  }

 private:
  std::vector<Adn> getNextPop(std::vector<Adn> received_adn) {
    Population received_pop(received_adn);

    int res = -1;
    for (int i = 0; i < population_list.size(); ++i) {
      if (population_list.at(i).id == received_pop.id) {
        res = i+1;
        population_list.at(i) = received_pop;
      }
    }
    if(res == population_list.size()){
      res = 0;
    }
    if (res == -1) {
      population_list.push_back(received_pop);
      res = 0;
    }
    return population_list.at(res).adn_list;
  }

  std::vector<Population> population_list;
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
