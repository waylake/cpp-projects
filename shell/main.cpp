#include <iostream>
#include <sstream>
#include <string>
#include <sys/wait.h> // For wait()
#include <unistd.h>   // For fork(), execvp()
#include <vector>

void executeCommand(const std::string &command) {
  // 문자열을 공백으로 구분하여 파싱
  std::istringstream iss(command);
  std::vector<std::string> args;
  std::string arg;
  while (iss >> arg) {
    args.push_back(arg);
  }

  // 명령어와 인자를 C 스타일의 문자열 배열로 변환
  char **argv =
      new char *[args.size() + 1]; // +1은 마지막에 NULL을 추가하기 위함
  for (size_t i = 0; i < args.size(); ++i) {
    argv[i] = const_cast<char *>(args[i].c_str());
  }
  argv[args.size()] = NULL;

  // fork를 사용하여 자식 프로세스 생성
  pid_t pid = fork();
  if (pid == 0) {
    // 자식 프로세스에서 명령어 실행
    execvp(argv[0], argv);
    // execvp가 실패했을 경우 아래 코드가 실행됨
    std::cerr << "Error: Failed to execute " << argv[0] << std::endl;
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    // 부모 프로세스에서 자식 프로세스의 종료를 기다림
    waitpid(pid, NULL, 0);
  } else {
    // fork 실패
    std::cerr << "Error: Failed to fork" << std::endl;
  }

  // 동적 할당한 메모리 해제
  delete[] argv;
}

int main() {
  std::string input;
  while (true) {
    // 사용자로부터 명령어 입력 받기
    std::cout << "> ";
    std::getline(std::cin, input);

    // "exit" 입력 시 셸 종료
    if (input == "exit") {
      break;
    }

    // 명령어 실행
    executeCommand(input);
  }

  return 0;
}
