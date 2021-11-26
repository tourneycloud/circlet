redirector_dev:
	clang++ -Wall -pedantic --std=c++20 -I./src /usr/lib/liburing.so src/log.cc src/store.cc src/redirector.cc -o build/circlet_redirector.dev

redirector_release:
	clang++ -O3 -Wall -pedantic --std=c++20 -I./src /usr/lib/liburing.so src/log.cc src/store.cc src/redirector.cc -o build/circlet_redirector.dev

redirector_mike_dev:
	clang++ -Wall -pedantic --std=c++20 -I./src /usr/lib/liburing.so src/log.cc src/store.cc src/redirector.cc -o ~/circlet_redirector.dev
