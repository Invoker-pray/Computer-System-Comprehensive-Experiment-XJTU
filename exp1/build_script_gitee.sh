sudo pacman -S m4 git base-devel scons zlib protobuf gperftools python

sudo pacman -S --needed \
	python python-pip python-setuptools \
	scons gcc make \
	hdf5 capstone

git clone https://gitee.com/wlx419/gem5.git

cd gem5
python3 -m venv --system-site-packages ~/python_venv
source ~/python_venv/bin/activate
pip install -r requirements.txt

cd build_opts
sed -i "s/PROTOCOL = 'MI_example'/PROTOCOL = 'MESI_Two_Level'/" RISCV
cd ..
scons build/RISCV/gem5.opt -j$(nproc) PROTOCOL="MESI_Two_Level"
./build/RISCV/gem5.opt
