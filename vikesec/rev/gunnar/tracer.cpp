// C incs
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>

// C++ incs
#include <iostream>

// Push RAX
// Rax = 01
// Breakpoint
// Pop RAX



class Proc {
    public:
    pid_t childpid;
    enum class Status {RUNNING, STOPPED, KILLED};
    Status status;
    struct user_regs_struct regs;
    

    Proc(std::string filePath) {
        pid_t child = fork();

        if (child == 0) {
            ptrace(PTRACE_TRACEME, 0, NULL, NULL);
            raise(SIGINT);
            execve(filePath.c_str(), NULL, NULL);
        }else {
            this->childpid = child;
            this->status = Proc::Status::STOPPED;
        }
    }
    void getRegs();
    void wait();
    void singleStep();
    void sysCallStep();
    void kill();

};

void Proc::getRegs() {
    ptrace(PTRACE_GETREGS, this->childpid, NULL, &this->regs);
}

void Proc::wait() {
    int status;
    int i = waitpid(this->childpid, &status, 0);
    // Check status and return appropriate I guess?
}

void Proc::singleStep() {
    ptrace(PTRACE_SINGLESTEP, this->childpid, NULL, NULL);
}

void Proc::sysCallStep() {
    ptrace(PTRACE_SYSCALL, this->childpid, NULL, NULL);
}

void Proc::kill() {
    ptrace(PTRACE_KILL, this->childpid, NULL, NULL);
}


int main() {
    Proc target = Proc(std::string("./GunnarTheGatekeeper"));
    target.wait();
    target.getRegs();
    printf("%d", target.regs.rdx);
    fflush(stdout);
    int i = 0;
    while (i < 2000)
    {
        target.sysCallStep();
        target.getRegs();
        printf("%d\n", i);
        fflush(stdout);
        i++;
    }
    target.kill();
}