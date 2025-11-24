cd workstationhere
mkdir result

source ~/python_venv/bin/activate

echo "step 1"
echo "HW3BigCore, DAXPY"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/HW3BigCore_DAXPY_m5out

echo "HW3LittleCore, DAXPY"
sed -i "s/cpu = HW3BigCore()/cpu = HW3LittleCore()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/HW3LittleCore_DAXPY_m5out

echo "HW3LittleCore, BFS"
sed -i "s/workload = DAXPYWorkload()/workload = BFSWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/HW3LittleCore_BFS_m5out

echo "HW3LittleCore, BubbleSortWorkload"
sed -i "s/workload = BFSWorkload()/workload = BubbleSortWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/HW3LittleCore_Bubble_m5out

echo "HW3BigCore, BubbleSortWorkload"
sed -i "s/cpu = HW3LittleCore()/cpu = HW3BigCore()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/HW3BigCore_Bubble_m5out

echo "HW3BigCore, BFS"
sed -i "s/workload = BubbleSortWorkload()/workload = BFSWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/HW3BigCore_BFS_m5out
