Installation des librairies (sous ubuntu) :

	SFML pour l'affichage :

		sudo apt-get install libsfml-dev

	Protobuf-cpp 3.0.0 alpha 2 (dépendance de GRpc) :
		
		wget https://github.com/google/protobuf/releases/download/v3.0.0-alpha-2/protobuf-cpp-3.0.0-alpha-2.tar.gz
		tar -xvzf protobuf-cpp-3.0.0-alpha-2.tar.gz 
		cd protobuf-3.0.0-alpha-2/
		./configure
		make
		sudo make install
		sudo ldconfig

	GRpc : 

		sudo apt-get install build-essential autoconf libtool
 		git clone https://github.com/grpc/grpc.git
 		cd grpc/
		git submodule update --init
		make
		sudo make install


Client :
	Usage : ./Client <serveur> <idvillage> <population> <nbGeneration> <seed>

	Exemple : ./Client 127.0.0.1 1 100 100 12345

Server :
	Usage : ./Server