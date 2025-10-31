apt update && apt upgrade
apt install build-essential \
	git m4 scons \
	zlib1g libprotobuf-dev \
	libprotoc-dev \
	libgoogle-perftools-dev python3-pip python3 \
	zlib1g-dev protobuf-compiler python3-venv

echo "please select which one you want to use: git(option 1, proxy recommended) or gitee(option 2)?"

read -p "key in your choice:" choice

case "$choice" in
1)
	echo "use git."
	git clone git@github.com:gem5/gem5.git /workstationhere/gem5

	cd /workstationhere/gem5
	python3 -m venv --system-site-packages ~/python_venv
	source ~/python_venv/bin/activate
	pip install -r requirements.txt

	cd build_opts
	sed -i 's/PROTOCOL="MI_example"/PROTOCOL="MESI_Two_Level"/' RISCV
	cd ..
	scons build/RISCV/gem5.opt -j$(nproc) PROTOCOL="MESI_Two_Level"
	./build/RISCV/gem5.opt
	;;
2)
	echo "use gitee."
	git clone https://gitee.com/wlx419/gem5.git /workstationhere/gem5

	cd /workstationhere/gem5
	python3 -m venv --system-site-packages ~/python_venv
	source ~/python_venv/bin/activate
	pip install -r requirements.txt

	cd build_opts
	sed -i "s/PROTOCOL = 'MI_example'/PROTOCOL = 'MESI_Two_Level'/" RISCV
	cd ..
	scons build/RISCV/gem5.opt -j$(nproc) PROTOCOL="MESI_Two_Level"
	./build/RISCV/gem5.opt
	;;
*)
	echo "1 or 2 please. you really should read my hints."
	echo "just number 1 or 2 is acceptable."

	;;
esac
