apt-get update
apt-get install -yqq \
	apt-utils sudo build-essential cmake git \
	libssl-dev pkg-config python3 python3-pip zlib1g zlib1g-dev m4 \
	scons libprotobuf-dev protobuf-compiler \
	libprotoc-dev libgoogle-perftools-dev \
	gcc-multilib g++-multilib \
	python3-dev python-is-python3 python3-yaml libboost-all-dev gcc-arm-none-eabi \
	llvm-12 clang-12

cd /workstationhere/gem5-salam
export M5_PATH=/workstationhere/gem5-salam
bash docs/update-alternatives.sh

scons build/ARM/gem5."$BUILD_TYPE" -j$(nproc)
