cd /gem5-SALAM

rm -rf /gem5-SALAM/benchmarks/sys_validation/qkv
cp /workstationhere/run_sim.sh /gem5-SALAM

cp -r /workstationhere/transformer_dimention_64_head_4 /gem5-SALAM/benchmarks/sys_validation/qkv

cd /gem5-SALAM

echo "transformer dimention 64 head 4 DerivO3CPU"
bash run.sh

mv BM_ARM_OUT /workstationhere/result/DerivO3CPU_transformer_dimention_64_head_4

echo "transformer dimention 64 head 4 MinorCPU"
sed -i "s/cpu-type=DerivO3CPU/cpu-type=MinorCPU/" tools/run_system.sh
bash run.sh

mv BM_ARM_OUT /workstationhere/result/MinorCPU_transformer_dimention_64_head_4

echo "transformer dimention 64 head 4 TimingSimpleCPU"
sed -i "s/cpu-type=MinorCPU/cpu-type=TimingSimpleCPU/" tools/run_system.sh
bash run.sh

mv BM_ARM_OUT /workstationhere/result/TimingSimpleCPU_transformer_dimention_64_head_4

cd /gem5-SALAM
rm -rf /gem5-SALAM/benchmarks/sys_validation/qkv
cp /workstationhere/without_transformer_dimention_64_head_4 /gem5-SALAM/benchmarks/sys_validation/qkv

echo "without transformer dimention 64 head 4 DerivO3CPU"
bash run.sh

mv BM_ARM_OUT /workstationhere/result/DerivO3CPU_without_transformer_dimention_64_head_4

echo "without transformer dimention 64 head 4 MinorCPU"
sed -i "s/cpu-type=DerivO3CPU/cpu-type=MinorCPU/" tools/run_system.sh
bash run.sh

mv BM_ARM_OUT /workstationhere/result/MinorCPU_without_transformer_dimention_64_head_4

echo "without transformer dimention 64 head 4 TimingSimpleCPU"
sed -i "s/cpu-type=MinorCPU/cpu-type=TimingSimpleCPU/" tools/run_system.sh
bash run.sh

mv BM_ARM_OUT /workstationhere/result/TimingSimpleCPU_without_transformer_dimention_64_head_4
