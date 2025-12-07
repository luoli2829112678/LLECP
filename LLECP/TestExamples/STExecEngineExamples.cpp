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
    STExecEngine_inst.STEE_PushCmd("INT A;");
    STExecEngine_inst.STEE_PushCmd("INT B;");
    STExecEngine_inst.STEE_PushCmd("INT C;");
    STExecEngine_inst.STEE_PushCmd("s:=b+REX(x.y[1].z,1*1.3)");
    printf("1111111\n");
    return 0;
}