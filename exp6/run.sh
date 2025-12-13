rm -rf /gem5-SALAM/benchmarks/sys_validation/qkv
cp /workstationhere/run_sim.sh /gem5-SALAM

cp -r /workstationhere/qkv_dimention_64_head_4 /gem5-SALAM/benchmarks/sys_validation/qkv

cd /gem5-SALAM
bash run.sh

mv BM_ARM_OUT /workstationhere/result/DerivO3CPU
