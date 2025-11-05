git clone https://gitee.com/wlx419/gem5_assignment.git
cd gem5_assignment
git checkout assign-1

cd ..
sudo cp run.py gem5_assignment/run.py
sudo cp -r ../exp1/gem5 . -r

docker run -it -v "$(pwd)"/:/workstationhere exp1:gitee bash -c "bash /workstationhere/run.sh"
