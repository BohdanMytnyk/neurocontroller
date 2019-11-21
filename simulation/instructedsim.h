#ifndef INSTRUCTREDSIM_H
#define INSTRUCTREDSIM_H
#include "simulation.h"
#include "instruction.h"
#include <vector>

//instructed sim is used, when you have direct instructions of changing the speed for a satellite
class InstructedSim :public Simulation
{
private:
    std::vector<Instruction*> instructions;
public:
    InstructedSim(Satellite* sat, double t);
    void putInstruction(Instruction* inst);
    void run() override;
};

#endif // INSTRUCTREDSIM_H
