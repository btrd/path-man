CXX = g++
CXXFLAGS += -std=c++11

LDFLAGS += -L/usr/local/lib -lgrpc++_unsecure -lgrpc -lgpr -lprotobuf -lpthread -ldl
LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -Wall

SOURCES = adn_exchange.pb.o adn_exchange.grpc.pb.o Genome.o Map.o Person.o Point.o Village.o
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = .

vpath %.proto $(PROTOS_PATH)

all: Server Client

Server: adn_exchange.pb.o adn_exchange.grpc.pb.o $(SOURCES) Server.o
	$(CXX) $^ $(LDFLAGS) -o $@

Client: adn_exchange.pb.o adn_exchange.grpc.pb.o $(SOURCES) Client.o
	$(CXX) $^ $(LDFLAGS) -o $@
	
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean :
	rm -f *.o *.pb.cc *.pb.h Server Client