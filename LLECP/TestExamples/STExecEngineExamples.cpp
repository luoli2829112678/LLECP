#include"STExecEngine.h"
#include <iostream>
#include <chrono>
int main()
{
    STExecEngine STExecEngine_inst;
    STExecEngine_inst.STEE_EnableBuffer(0,1);
    STExecEngine_inst.STEE_StartPushBuffer();
    STExecEngine_inst.STEE_StartPushLine();
    STExecEngine_inst.STEE_PushCmd("LREAL A;");
    STExecEngine_inst.STEE_PushCmd("INT B;");
    STExecEngine_inst.STEE_PushCmd("INT C;");
    VariableUint* pvarA = STExecEngine_inst.m_VariableManager.GetVariable(0,"A");
    VariableUint* pvarB = STExecEngine_inst.m_VariableManager.GetVariable(0,"B");
    STExecEngine_inst.STEE_PushCmd("A:=0;");
    STExecEngine_inst.STEE_PushCmd("B:=0;");
    STExecEngine_inst.STEE_PushCmd("IF A > 2 THEN");
        STExecEngine_inst.STEE_PushCmd("IF A > 5 THEN");
            STExecEngine_inst.STEE_PushCmd("B:=2;");
        STExecEngine_inst.STEE_PushCmd("ELSE");
            STExecEngine_inst.STEE_PushCmd("B:=1;");
        STExecEngine_inst.STEE_PushCmd("END_IF;");
    STExecEngine_inst.STEE_PushCmd("ELSE");
        STExecEngine_inst.STEE_PushCmd("B:=B-1;");
    STExecEngine_inst.STEE_PushCmd("END_IF;");
    STExecEngine_inst.InitProgramManager();
    double* pA = (double*)pvarA->pDataAddr;
    int* pB = (int*)pvarB->pDataAddr;
    printf("A:%f  B:%d\n",*pA,*pB);
    while(true)
    {
        auto start = std::chrono::steady_clock::now();
        STExecEngine_inst.ExecuteProgram();
        auto end = std::chrono::steady_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "test_func 执行时间: " << us << " us" << std::endl;
        printf("A:%f  B:%d\n",*pA,*pB);
    }
    printf("1111111\n");
    return 0;
}