cd workstationhere
mkdir result

source ~/python_venv/bin/activate

echo "step 1"
echo "HW2TimingSimpleCPU, 4GHz, HW2DDR3_1600_8x8, HW2MESITwoLevelCache, DAXPYWorkload"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_DAX_m5out

echo "HW2TimingSimpleCPU, 4GHz, HW2DDR3_1600_8x8, HW2MESITwoLevelCache, HelloWorldWorkload"
sed -i "s/workload = DAXPYWorkload()/workload = HelloWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_Hello_m5out

echo "step 2"
echo "MinorCPU, 4GHz, HW2DDR3_1600_8x8, HW2MESITwoLevelCache, DAXPYWorkload"
echo "issue_latency=3, fp_operation_latency=2"
sed -i "s/cpu = HW2TimingSimpleCPU()/cpu = HW2MinorCPU(issue_latency=3, fp_operation_latency=2)/" gem5_assignment/run.py
sed -i "s/workload = HelloWorkload()/workload = DAXPYWorkload()/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minorCPU_issue_3_fp_2_dax_m5out

echo "MinorCPU, 4GHz, HW2DDR3_1600_8x8, HW2MESITwoLevelCache, DAXPYWorkload"
echo "issue_latency=2, fp_operation_latency=3"
sed -i "s/issue_latency=3/issue_latency=2/" gem5_assignment/run.py
sed -i "s/fp_operation_latency=2/fp_operation_latency=3/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minorCPU_issue_2_fp_3_dax_m5out

echo "MinorCPU, 4GHz, HW2DDR3_1600_8x8, HW2MESITwoLevelCache, DAXPYWorkload"
echo "issue_latency=6, fp_operation_latency=1"
sed -i "s/issue_latency=2/issue_latency=6/" gem5_assignment/run.py
sed -i "s/fp_operation_latency=3/fp_operation_latency=1/" gem5_assignment/run.py
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minorCPU_issue_6_fp_1_dax_m5out

echo "step 3"
