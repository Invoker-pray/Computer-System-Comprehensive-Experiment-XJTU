## 1  create share folder
#sudo apt install git gcc cmake make tar bzip2
#cd /
#sudo mount /dev/cdrom mnt
#sudo ./VBoxLinuxAdditions.run
#
#reboot
#
#sudo usermod -aG vboxsf $USER
#
#reboot

# 2 install essential

sudo apt install build-essential \
	git m4 scons \
	zlib1g libprotobuf-dev \
	libprotoc-dev \
	libgoogle-perftools-dev python3-pip python3 \
	zlib1g-dev protobuf-compiler python3-venv

git clone git@github.com:gem5/gem5.git

cd gem5
python3 -m venv --system-site-packages ~/python_venv
source ~/python_venv/bin/activate
pip install -r requirements.txt

cd build_opts
sed -i 's/PROTOCOL="MI_example"/PROTOCOL="MESI_Two_Level"/' RISCV
cd ..
scons build/RISCV/gem5.opt -j$(nproc) PROTOCOL="MESI_Two_Level"
./build/RISCV/gem5.opt
