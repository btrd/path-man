Installation des librairies

	SFML http://sfml-dev.org
		Debian
			sudo apt-get install libsfml-dev

		Mac OS
			brew install sfml

	Protobuf (dépendance de GRpc) https://github.com/google/protobuf
		
		wget https://github.com/google/protobuf/releases/download/v3.0.0-alpha-2/protobuf-cpp-3.0.0-alpha-2.tar.gz
		tar -xvzf protobuf-cpp-3.0.0-alpha-2.tar.gz 
		cd protobuf-3.0.0-alpha-2/
		./configure
		make
		sudo make install
		sudo ldconfig

	gRpc https://github.com/grpc/grpc

 		git clone https://github.com/grpc/grpc.git
 		cd grpc/
		git submodule update --init
		make
		sudo make install

Client
	Usage
		./Client <serveur> <idvillage> <population> <nbGeneration> <seed>

	Exemple
		./Client localhost 1 100 1000 12345

Server
	Usage
		./Server
