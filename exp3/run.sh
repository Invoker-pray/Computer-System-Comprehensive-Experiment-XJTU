cd workstationhere
mkdir result

source ~/python_venv/bin/activate

echo "step 1"
echo "HW1TimingSimpleCPU, 1GHz"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_1GHz_m5out

sed -i 's/clk = "1GHz"/clk = "2GHz"/' gem5_assignment/run.py
echo "HW1TimingSimpleCPU, 2Ghz"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_2GHz_m5out

sed -i 's/clk = "2GHz"/clk = "4GHz"/' gem5_assignment/run.py
echo "HW1TimingSimpleCPU, 4Ghz"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_4GHz_m5out

sed -i "s/cpu = HW1TimingSimpleCPU()/cpu = HW1MinorCPU()/" gem5_assignment/run.py
sed -i 's/clk = "4GHz"/clk = "1GHz"/' gem5_assignment/run.py
echo "HW1MinorCPU, 1GHz"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minor_1GHz_m5out

sed -i 's/clk = "1GHz"/clk = "2GHz"/' gem5_assignment/run.py
echo "HW1MinorCPU, 2GHz"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minor_2GHz_m5out

sed -i 's/clk = "2GHz"/clk = "4GHz"/' gem5_assignment/run.py
echo "HW1MinorCPU, 4GHz"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minor_4GHz_m5out

echo "step 2"

sed -i "s/cpu = HW1MinorCPU()/cpu = HW1TimingSimpleCPU()/" gem5_assignment/run.py
echo "HW1TimingSimpleCPU, HW1DDR3_1600_8x8"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_hw1ddr3_1600_8x8

sed -i "s/memory = HW1DDR3_1600_8x8()/memory = HW1DDR3_2133_8x8()/" gem5_assignment/run.py
echo "HW1TimingSimpleCPU, HW1DDR3_2133_8x8"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_hw1ddr3_2133_8x8

sed -i "s/memory = HW1DDR3_2133_8x8()/memory = HW1LPDDR3_1600_1x32()/" gem5_assignment/run.py
echo "HW1TimingSimpleCPU, HW1LPDDR3_1600_1x32"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/simple_hw1lpddr3_1600_1x32

sed -i "s/cpu = HW1TimingSimpleCPU()/cpu = HW1MinorCPU()/" gem5_assignment/run.py
sed -i "s/memory = HW1LPDDR3_1600_1x32()/memory = HW1DDR3_1600_8x8()/" gem5_assignment/run.py
echo "HW1MinorCPU, HW1DDR3_1600_8x8"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minor_hw1ddr3_1600_8x8

sed -i "s/memory = HW1DDR3_1600_8x8()/memory = HW1DDR3_2133_8x8()/" gem5_assignment/run.py
echo "HW1MinorCPU, HW1DDR3_2133_8x8"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minor_hw1ddr3_2133_8x8

sed -i "s/memory = HW1DDR3_1600_8x8()/memory = HW1LPDDR3_1600_1x32()/" gem5_assignment/run.py
echo "HW1MinorCPU, HW1LPDDR3_1600_1x32"
gem5/build/RISCV/gem5.opt -re gem5_assignment/run.py
mv m5out result/minor_hw1lpddr3_1600_1x32
