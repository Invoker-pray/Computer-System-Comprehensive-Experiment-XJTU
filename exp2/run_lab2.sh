git clone https://gitee.com/wlx419/gem5_assignment.git
cd gem5_assignment
git checkout assign-0
cd ..
sudo cp ../exp1/gem5 . -r

docker run -it -v "$(pwd)"/:/workstationhere exp1 bash -c " bash /workstationhere/hello_world.sh "
