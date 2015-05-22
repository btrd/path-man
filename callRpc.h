#ifndef CALLRPC_H
#define CALLRPC_H

#include "adn_exchange.grpc.pb.h"
using pathman::VillageP;
using pathman::PersonP;
using pathman::GeneP;

VillageP callRpc(std::string server, VillageP vil_client);

#endif
  