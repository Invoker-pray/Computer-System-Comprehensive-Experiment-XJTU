mkdir result
docker run -it -v "$(pwd)"/:/workstationhere/ final_exp6:latest /bin/bash -c "bash /workstationhere/run.sh"
