#from components.boards import HW0RISCVBoard
#from components.boards import HW1RISCVBoard
from components.boards import HW2RISCVBoard


#from components.processors import HW0TimingSimpleCPU
#from components.processors import HW1TimingSimpleCPU
from components.processors import HW2TimingSimpleCPU
from components.processors import HW2MinorCPU
#from components.processors import HW1MinorCPU


#from components.cache_hierarchies import HW0MESITwoLevelCache
#from components.cache_hierarchies import HW1MESITwoLevelCache
from components.cache_hierarchies import HW2MESITwoLevelCache


#from components.memories import HW0DDR3_1600_8x8
#from components.memories import HW1DDR3_1600_8x8
#from components.memories import HW1DDR3_2133_8x8
#from components.memories import HW1LPDDR3_1600_1x32
from components.memories import HW2DDR3_1600_8x8

from workloads.hello_world_workload import HelloWorkload
#from workloads.mat_mul_workload import MatMulWorkload
from workloads.daxpy_workload import DAXPYWorkload


from workloads.roi_manager import exit_event_handler


from gem5.simulate.simulator import Simulator




if __name__ == "__m5_main__":
    
    cpu = HW2TimingSimpleCPU()
    memory = HW2DDR3_1600_8x8()
    cache = HW2MESITwoLevelCache()
    board = HW2RISCVBoard(clk_freq="4GHz", processor=cpu, cache_hierarchy=cache, memory=memory)
    workload = DAXPYWorkload()
    board.set_workload(workload)
    simulator = Simulator(board=board, full_system=False, on_exit_event=exit_event_handler)
    simulator.run()
    print("Finished simulation.")
    
