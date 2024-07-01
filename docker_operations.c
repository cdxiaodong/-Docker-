#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // 检查参数数量
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_image>\n", argv[0]);
        return 1;
    }

    // 固定的源镜像地址的一部分
    const char *source_prefix = "m.daocloud.io/docker.io/";

    // 构建完整的源镜像名称
    char source_image[200];
    snprintf(source_image, sizeof(source_image), "%s%s", source_prefix, argv[1]);

    // 目标镜像的名称和标签
    const char *target_image = argv[1];

    // 构建命令字符串
    char pull_command[200];
    char tag_command[200];
    char rmi_command[200];

    // 执行 docker pull 命令
    snprintf(pull_command, sizeof(pull_command), "docker pull %s", source_image);
    printf("Running command: %s\n", pull_command);
    int pull_result = system(pull_command);
    if (pull_result != 0) {
        fprintf(stderr, "Error: Docker pull failed.\n");
        return 1;
    }

    // 执行 docker tag 命令
    snprintf(tag_command, sizeof(tag_command), "docker tag %s %s", source_image, target_image);
    printf("Running command: %s\n", tag_command);
    int tag_result = system(tag_command);
    if (tag_result != 0) {
        fprintf(stderr, "Error: Docker tag failed.\n");
        return 1;
    }

    // 执行 docker rmi 命令
    snprintf(rmi_command, sizeof(rmi_command), "docker rmi %s", source_image);
    printf("Running command: %s\n", rmi_command);
    int rmi_result = system(rmi_command);
    if (rmi_result != 0) {
        fprintf(stderr, "Error: Docker rmi failed.\n");
        return 1;
    }

    printf("Operations completed successfully.\n");

    return 0;
}
