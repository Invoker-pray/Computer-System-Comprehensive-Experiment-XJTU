git clone https://gitee.com/wlx419/gem5-salam.git

#sudo cp -r ../exp1/gem5 .

docker build . --file Dockerfile --build-arg BUILD_TYPE="opt"

#docker pull ubuntu:20.04
#docker run -it -v "$(pwd)"/:/workstationhere ubuntu:20.04 bash -c "bash /workstationhere/run20.04.sh"
