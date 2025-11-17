# XJTU 计算机系统综合设计实验

记录一下自己的解决方案。

# lab1

实验环境配置，我写了arch，unbuntu，和docker三个solution。如果你是符合运行环境的unbuntu系统（20.04-24.04），那么通过运行`build_script_ubuntu24.04.sh`就可以完成lab1的环境配置，如果你没有配置proxy，建议运行`build_script_ubuntu24.04_gitee.sh`获得更好的体验。

如果你和我一样使用arch，可以使用`build_script.sh`。（虽然我写了，但是玩arch应该是会用梯子的）。当然arch滚动更新很快，我也没有做版本限制，可能很快就无法运行了。

所以我更建议使用docker方案，使用`build_script_docker_ubuntu24.04.sh`，你可以在任何OS上获得完全一样的体验。(ubuntu 镜像版本为24.04.3 LTS，如镜像更新后无法成功运行在pull命令上加版本限制即可。)

# lab2

如果你把lab1中的环境打包为镜像`exp1:gitee`的话，那么你可以通过运行`run_lab2.sh`直接获得lab2的实验结果。

# lab3

直接运行`run_lab3.sh`就可以获得共计12种仿真结果，之后只需要对着分析一下就可以了。

# lab4

食用方法同上。

_另：如果你本身在ubuntu机器上面跑并且懒得折腾，只需要删除`run_labx.sh`关于启动docker那一行，然后删除`run.sh`第一行的cd，也可以完成运行。_
