#pragma once
#include <string>
#include <unordered_map>

class CLI
{
public:
    CLI();

    void run();

private:
    void CmdAdd();
    void CmdExit();
private:
    bool bRunning;
    using CommandMethod = void(CLI::*)(void);
    std::unordered_map<std::string, CommandMethod> commands_;
};

