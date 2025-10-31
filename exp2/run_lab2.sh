git clone https://gitee.com/wlx419/gem5_assignment.git

cd gem5_assignment
git checkout assign-0
cd ..
cp run.py gem5_assignment

sudo cp ../exp1/gem5 . -r

docker run -it -v "$(pwd)"/:/workstationhere exp1:gitee bash -c " bash /workstationhere/hello_world.sh "
