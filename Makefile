BUILD_DIR = .build

mkpath:
	-@mkdir -p ${BUILD_DIR}/${subdir}

release: subdir=release
release: mkpath
	cd ${BUILD_DIR}/${subdir} && cmake -DCMAKE_BUILD_TYPE=Release ../..
	cd ${BUILD_DIR}/${subdir} && make -j`lscpu | grep "CPU(s)" | head -n1 | awk '{ print $$2 }'`

debug: subdir=debug
debug: mkpath
	cd ${BUILD_DIR}/${subdir} && cmake -DCMAKE_BUILD_TYPE=Debug ../..
	cd ${BUILD_DIR}/${subdir} && make -j`lscpu | grep "CPU(s)" | head -n1 | awk '{ print $$2 }'`

install_target:
	sudo cp ${BUILD_DIR}/${subdir}/liblogger.so /usr/local/lib
	-@sudo mkdir -p /usr/local/include/liblogger
	sudo cp src/clogger.h      /usr/local/include/liblogger/loggerlib.h
	sudo cp src/cloggerbase.h  /usr/local/include/liblogger/cloggerbase.h
	sudo cp src/clogstring.h   /usr/local/include/liblogger/clogstring.h
	sudo cp src/clogpriority.h /usr/local/include/liblogger/clogpriority.h

install_debug: subdir=debug
install_debug: install_target

install_release: subdir=release
install_release: install_target

clean:
	-rm -rf ${BUILD_DIR}/debug
	-rm -rf ${BUILD_DIR}/release
	sudo rm /usr/local/lib/liblogger.so
	sudo rm -rf /usr/local/include/liblogger
