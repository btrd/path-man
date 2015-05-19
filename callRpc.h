#ifndef CALLRPC_H
#define CALLRPC_H

#include "adn_exchange.grpc.pb.h"
using pathman::Adn;

std::vector<Adn> callRpc(std::vector<Adn> client_adn);

#endif
  