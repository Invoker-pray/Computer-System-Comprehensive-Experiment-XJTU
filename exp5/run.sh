cd workstationhere
mkdir -p result/step1
mkdir -p result/step2

source ~/python_venv/bin/activate

echo "step 1"
echo "HW3BigCore, DAXPY"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step1/HW3BigCore_DAXPY_m5out

echo "HW3LittleCore, DAXPY"
sed -i "s/cpu = HW3BigCore()/cpu = HW3LittleCore()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step1/HW3LittleCore_DAXPY_m5out

echo "HW3LittleCore, BFS"
sed -i "s/workload = DAXPYWorkload()/workload = BFSWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step1/HW3LittleCore_BFS_m5out

echo "HW3LittleCore, BubbleSortWorkload"
sed -i "s/workload = BFSWorkload()/workload = BubbleSortWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step1/HW3LittleCore_Bubble_m5out

echo "HW3BigCore, BubbleSortWorkload"
sed -i "s/cpu = HW3LittleCore()/cpu = HW3BigCore()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step1/HW3BigCore_Bubble_m5out

echo "HW3BigCore, BFS"
sed -i "s/workload = BubbleSortWorkload()/workload = BFSWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step1/HW3BigCore_BFS_m5out

echo "step 2"
echo "HW3MediumCore1, BFS"
sed -i "s/cpu = HW3BigCore()/cpu = HW3MediumCore1()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step2/HW3MediumCore1_BFS_m5out

echo "HW3MediumCore2, BFS"
sed -i "s/cpu = HW3MediumCore1()/cpu = HW3MediumCore2()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step2/HW3MediumCore2_BFS_m5out

echo "HW3MediumCore3, BFS"
sed -i "s/cpu = HW3MediumCore2()/cpu = HW3MediumCore3()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step2/HW3MediumCore3_BFS_m5out

echo "HW3MediumCore4, BFS"
sed -i "s/cpu = HW3MediumCore3()/cpu = HW3MediumCore4()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step2/HW3MediumCore4_BFS_m5out

echo "HW3LittleCore, BFS, area score"
sed -i "s/cpu = HW3MediumCore4()/cpu = HW3LittleCore()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step2/HW3LittleCore_BFS_m5out

echo "HW3BigCore, BFS, area score"
sed -i "s/cpu = HW3LittleCore()/cpu = HW3BigCore()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/step2/HW3BigCore_BFS_m5out
