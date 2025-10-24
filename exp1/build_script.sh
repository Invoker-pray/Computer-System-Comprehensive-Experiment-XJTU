sudo pacman -S m4 git base-devel scons zlib protobuf gperftools python

git clone git@github.com:gem5/gem5.git
cd gem5

source ~/python_venv/bin/activate
pip install -r requirements.txt

cd build_opts
sed -i 's/PROTOCOL="MI_example"/PROTOCOL="MESI_Two_Level"/' RISCV
cd ..
scons build/RISCV/gem5.opt -j$(nproc)
./build/RISCV/gem5.opt
