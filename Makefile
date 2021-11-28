redirector_dev:
	clang++ -Wall -pedantic --std=c++20 -I./src /usr/lib/liburing.so src/log.cc src/store.cc src/redirector.cc -o build/circlet_redirector.dev

redirector_release:
	clang++ -O3 -Wall -pedantic --std=c++20 -I./src /usr/lib/liburing.so src/log.cc src/store.cc src/redirector.cc -o build/circlet_redirector.dev

redirector_dev_mike:
	clang++ -Wall -pedantic --std=c++20 -I./src /usr/lib/liburing.so src/log.cc src/store.cc src/redirector.cc -o ~/circlet_redirector.dev

gen_protos:
	protoc -I ./src/protos --grpc_out=./gen --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./src/protos/redirectservice.proto
	protoc -I ./src/protos --cpp_out=./gen ./src/protos/redirectservice.proto

gen_protos_dev_mike:
	protoc -I ./src/protos --grpc_out=/etc/alpine-gen --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./src/protos/redirectservice.proto
	protoc -I ./src/protos --cpp_out=/etc/alpine-gen ./src/protos/redirectservice.proto

redirectservice_dev:
	clang++ -Wall -pedantic --std=c++20 \
		-I./src \
		-I./gen \
		-L/usr/local/lib `pkg-config --libs protobuf grpc++` \
		-lgrpc++_reflection \
		-ldl \
		gen/redirectservice.grpc.pb.cc \
		gen/redirectservice.pb.cc \
		src/log.cc \
		src/store.cc \
		src/urlgen.cc \
		src/redirectservice.cc \
		-o build/circlet_redirectservice.dev

redirectservice_release:
	clang++ -O3 -Wall -pedantic --std=c++20 \
		-I./src \
		-I./gen \
		-L/usr/local/lib `pkg-config --libs protobuf grpc++` \
		-lgrpc++_reflection \
		-ldl \
		/usr/lib/liburing.so \
		gen/redirectservice.grpc.pb.cc \
		gen/redirectservice.pb.cc \
		src/log.cc \
		src/store.cc \
		src/urlgen.cc \
		src/redirectservice.cc \
		-o build/circlet_redirectservice.dev

redirectservice_dev_mike:
	clang++ -Wall -pedantic --std=c++20 \
		-I./src \
		-I./gen \
		-L/usr/local/lib `pkg-config --libs protobuf grpc++` \
		-lgrpc++_reflection \
		-ldl \
		/usr/lib/liburing.so \
		gen/redirectservice.grpc.pb.cc \
		gen/redirectservice.pb.cc \
		src/log.cc \
		src/store.cc \
		src/urlgen.cc \
		src/redirectservice.cc \
		-o ~/circlet_redirectservice.dev
