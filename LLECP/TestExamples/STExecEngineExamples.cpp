#include"STExecEngine.h"
int main()
{
    STExecEngine STExecEngine_inst;
    STExecEngine_inst.STEE_EnableBuffer(0,1);
    STExecEngine_inst.STEE_StartPushBuffer();
    STExecEngine_inst.STEE_StartPushLine();
    STExecEngine_inst.STEE_PushCmd("INT X;");
    STExecEngine_inst.STEE_PushCmd("INT Y;");
    STExecEngine_inst.STEE_PushCmd("INT Z;");
    STExecEngine_inst.STEE_PushCmd("LREAL A;");
    STExecEngine_inst.STEE_PushCmd("INT B;");
    STExecEngine_inst.STEE_PushCmd("INT C;");
    VariableUint* pvar = STExecEngine_inst.m_VariableManager.GetVariable(0,"A");
    STExecEngine_inst.STEE_PushCmd("A:=10.5;");
    STExecEngine_inst.STEE_PushCmd("B:=20;");
    STExecEngine_inst.STEE_PushCmd("C:=A+B");
    STExecEngine_inst.InitProgramManager();
    double* pA = (double*)pvar->pDataAddr;
    printf("A:%f\n",*pA);
    while(true)
    {
        STExecEngine_inst.ExecuteProgram();
        printf("A:%f\n",*pA);
    }
    printf("1111111\n");
    return 0;
}