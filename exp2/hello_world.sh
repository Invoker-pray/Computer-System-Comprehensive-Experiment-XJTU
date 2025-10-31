cd workstationhere
#cd gem5_assignment
source ~/python_venv/bin/activate

gem5/build/RISCV/gem5.opt gem5_assignment/run.py

gem5/build/RISCV/gem5.opt -r gem5_assignment/run.py

cat m5out/simout

gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
