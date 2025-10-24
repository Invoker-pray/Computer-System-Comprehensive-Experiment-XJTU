docker pull ubuntu
docker run -it -v "$(pwd)"/:/workstationhere/ ubuntu bash -c " bash workstationhere/docker_script.sh "
