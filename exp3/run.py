#from components.boards import HW0RISCVBoard
from components.boards import HW1RISCVBoard
#from components.processors import HW0TimingSimpleCPU
from components.processors import HW1TimingSimpleCPU
#from components.cache_hierarchies import HW0MESITwoLevelCache
from components.cache_hierarchies import HW1MESITwoLevelCache


#from components.memories import HW0DDR3_1600_8x8
from components.memories import HW1DDR3_1600_8x8
from components.memories import HW1DDR3_2133_8x8
from components.memories import HW1LPDDR3_1600_1x32

#from workloads.hello_world_workload import HelloWorldWorkload
from workloads.mat_mul_workload import MatMulWorkload
from gem5.simulate.simulator import Simulator




if __name__ == "__m5_main__":
    
    cpu = HW1TimingSimpleCPU()
    #cpu=HW1TimingSimpleCPU()
    #cpu=HW1MinorCPU()

    clk = "1GHz"
    #clk="1GHz"
    #clk="2GHz"
    #clk="4GHz"
    memory = HW1DDR3_1600_8x8()
    #memory=HW1DDR3_1600_8x8()
    #memory=HW1DDR3_2133_8x8()
    #memory=HW1LPDDR3_1600_1x32()

    cache = HW1MESITwoLevelCache()

    board = HW1RISCVBoard(
        clk_freq=clk, processor=cpu,
        cache_hierarchy=cache, memory=memory
    )
    workload = MatMulWorkload(224)
    
    board.set_workload(workload)

    simulator = Simulator(board=board, full_system=False)
    simulator.run()
    print("Finished simulation.")
    
