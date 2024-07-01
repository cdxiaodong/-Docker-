#!/bin/bash

# Check if target image argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <target_image>"
    exit 1
fi

# Fixed prefix of source image
source_prefix="m.daocloud.io/docker.io/"

# Construct full source image name
source_image="${source_prefix}${1}"

# Target image name and tag
target_image="$1"

# Docker pull command
pull_command="docker pull ${source_image}"
echo "Running command: ${pull_command}"
${pull_command}
pull_result=$?
if [ $pull_result -ne 0 ]; then
    echo "Error: Docker pull failed."
    exit 1
fi

# Docker tag command
tag_command="docker tag ${source_image} ${target_image}"
echo "Running command: ${tag_command}"
${tag_command}
tag_result=$?
if [ $tag_result -ne 0 ]; then
    echo "Error: Docker tag failed."
    exit 1
fi

# Docker rmi command
rmi_command="docker rmi ${source_image}"
echo "Running command: ${rmi_command}"
${rmi_command}
rmi_result=$?
if [ $rmi_result -ne 0 ]; then
    echo "Error: Docker rmi failed."
    exit 1
fi

echo "Operations completed successfully."
exit 0
