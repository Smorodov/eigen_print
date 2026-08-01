#pragma once
#include <cstdio>
#include <functional>
#include <string>
#ifdef _WIN32
#include <io.h>
#ifndef O_BINARY
#define O_BINARY 0x8000
#endif
#define pipe _pipe
#else
#include <unistd.h>
#endif
inline std::string capture_output(std::function<void()> func) {
int pipefd[2];
#ifdef _WIN32
pipe(pipefd, 4096, O_BINARY);
#else
pipe(pipefd);
#endif
int old_stdout = dup(1);
dup2(pipefd[1], 1);
close(pipefd[1]);
func();
fflush(stdout);
char buffer[4096];
int n = read(pipefd[0], buffer, sizeof(buffer) - 1);
buffer[n > 0 ? n : 0] = '\0';
dup2(old_stdout, 1);
close(old_stdout);
close(pipefd[0]);
return std::string(buffer);
}