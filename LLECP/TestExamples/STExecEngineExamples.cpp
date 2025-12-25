#include"STExecEngine.h"
#include <iostream>
#include <chrono>
#include <unistd.h>
#define NEXT_LINE STExecEngine_inst.STEE_StartPushLine();
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
    STExecEngine_inst.STEE_PushCmd("A:=20;");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("B:=1;");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("C:=7;");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("IF A>10 THEN");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("AXIS_ENABLE(B);");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("AXIS_ENABLE(B,2+2);");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("ELSE");NEXT_LINE
    STExecEngine_inst.STEE_PushCmd("AXIS_ENABLE(C);");NEXT_LINE
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
        printf("ExecuteProgram 执行时间: %ld us\n", us);
        printf("A:%f  B:%d\n",*pA,*pB);
    }
    printf("1111111\n");
    return 0;
}