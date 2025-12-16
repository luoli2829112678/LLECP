#include"STExecEngine.h"
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
    STExecEngine_inst.STEE_PushCmd("A:=10.0+1;");
    STExecEngine_inst.STEE_PushCmd("IF A > 2 THEN");
    STExecEngine_inst.STEE_PushCmd("B:=20;");
    STExecEngine_inst.STEE_PushCmd("ELSE");
    STExecEngine_inst.STEE_PushCmd("B:=30;");
    STExecEngine_inst.STEE_PushCmd("END_IF;");
    STExecEngine_inst.STEE_PushCmd("C:=A+B");
    STExecEngine_inst.InitProgramManager();
    double* pA = (double*)pvarA->pDataAddr;
    int* pB = (int*)pvarB->pDataAddr;
    printf("A:%f  B:%d\n",*pA,*pB);
    while(true)
    {
        STExecEngine_inst.ExecuteProgram();
        printf("A:%f  B:%d\n",*pA,*pB);
    }
    printf("1111111\n");
    return 0;
}