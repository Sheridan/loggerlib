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
	sudo cp src/clogger.h /usr/local/include/loggerlib.h

install_debug: subdir=debug
install_debug: install_target

install_release: subdir=release
install_release: install_target

clean:
	rm -rf ${BUILD_DIR}
	sudo rm /usr/local/lib/liblogger.so
	sudo rm /usr/local/include/loggerlib.h
