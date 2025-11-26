#include <stdio.h>
#include"RT_Script.h"
int main() 
{
    RT_ScriptSystem *p = new RT_ScriptSystem();
    p->InitRT_ScriptSystem();
    std::string cmd = "X13r=x+1;";
    p->PushScriptCmd(cmd);
    printf("Hello World!!!\n");
    delete p;
    p = nullptr;
    return 0;
}
