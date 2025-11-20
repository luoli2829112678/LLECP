#define AnaInSlavePos 0, 0
#define ZeroErr 0x00009434, 0x0000001b
#define frequency 2000
#define MY_STACK_SIZE 8192
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include<vector>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include"SMbasic_stdafx.h"
#include"RT_Script.h"
#include"EtherCATMaster.h"

#define SM_Test main


int RT_ScripTest() 
{

    
    RT_ScriptSystem *p = new RT_ScriptSystem();
    p->InitRT_ScriptSystem();
    p->PushScriptCmd("X:DINT;");
    p->PushScriptCmd("X13r:DINT;");
    std::string cmd = "X13r:=X-(10*(10+10));";
    //cmd = "bTest:=Real;";
    //cmd = "IF X>=1 THEN";
    p->PushScriptCmd("X:=10;");
    p->PushScriptCmd("X13r:=5;");
    p->PushScriptCmd(cmd);
    p->StartRT_Script();
    while(true)
    {
        p->RT_ScriptTick();
    }
    printf("Hello World!!!\n");
    delete p;
    p = nullptr;
    return 0;
}


MC_PowerOn fbMC_PowerOn;
MC_Stop fbMC_Stop;
MC_Reset fbMC_Reset;
MC_PowerOff fbMC_PowerOff;
MC_FollowPosition fbFollowPosition;
MC_InitResetAxis fbMC_InitResetAxis;
MC_MoveAbsolute fbMoveAbsolute;
MC_MoveRelative fbMoveRelative;
MC_MoveVelocity fbMoveVelocity;
SoftMotion* pSoftMotion;
std::vector<CIA402Axis*> v_Axis;
bool Enabel,bBusy,bDone,bInVelocity, bError,bCommandAborted;int nErrorID;
timespec ti_Sleep;
int SM_Test()
{
    int c = 0;
    double pos = 0;
    v_Axis.clear();
    EtherCATMaster* pMaster = new EtherCATMaster(0);  
    pMaster->StartMaster();//启动主站
    pMaster->ConstructionCIA402AxisVec(&v_Axis);//主站从从站获取生成轴
    pSoftMotion = new SoftMotion(v_Axis);//使用轴初始化softmotion
    pSoftMotion->SetSoftMotionCycle(0.0005);//设置softmotion周期
    MC_PowerOn fbMC_PowerOn;
    struct timespec ts{0, 500000};   // 0 秒 + 1 000 000 纳秒 = 1 毫秒
    printf("InitReset\n");
    fbMC_InitResetAxis(v_Axis[0],false,bBusy,bDone,bError,nErrorID);//初始化初始复位功能块
    while (true)
    {
        fbMC_InitResetAxis(v_Axis[0],true,bBusy,bDone,bError,nErrorID);//执行功能块
        if(bDone)
        {
            c++;
            if(c>1000)//5000周期后使能
            {
                c = 0;
                fbMC_PowerOn(v_Axis[0],false,bBusy,bDone,bError,nErrorID);//初始化使能功能块
                break;
            }
        }
        pSoftMotion->SoftMotionRun();//softmotion实时执行
        nanosleep(&ts, nullptr);
    }
    while (true)
    {
        if(!bDone)
            fbMC_PowerOn(v_Axis[0],true,bBusy,bDone,bError,nErrorID);//执行使能功能块
        if(bDone)
        {
            break;
        }
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }

    while (true)
    {
        pos = v_Axis[0]->dActPosition - 0.01;
        printf("RunPos:%.6f\n",pos);
        fbFollowPosition(v_Axis[0],true,pos,bBusy,bError,nErrorID);
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }
    while (true)
    {
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }
}
int SM()
{
    v_Axis.clear();
    EtherCATMaster* pMaster = new EtherCATMaster(0);  
    pMaster->StartMaster();
    pMaster->ConstructionCIA402AxisVec(&v_Axis);
    pSoftMotion = new SoftMotion(v_Axis);
    pSoftMotion->SetSoftMotionCycle(0.0005);
    struct timespec ts{0, 500000};   // 0 秒 + 1 000 000 纳秒 = 1 毫秒
    printf("InitReset\n");
    fbMC_InitResetAxis(v_Axis[0],false,bBusy,bDone,bError,nErrorID);
    while (true)
    {
        fbMC_InitResetAxis(v_Axis[0],true,bBusy,bDone,bError,nErrorID);
        if(bDone)
        {
             break;
        }
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }
    printf("enable\n");
    fbMC_PowerOn(v_Axis[0],false,bBusy,bDone,bError,nErrorID);
    int c = 0;
    double rel = 5;
    double pos =0;
    while (true)
    {
        fbMC_PowerOn(v_Axis[0],true,bBusy,bDone,bError,nErrorID);
        if(bDone)
        {
            pos = v_Axis[0]->dActPosition;
            printf("AxisPos:%f\n",pos);
            //printf("SetMovePos:%f\n",rel);
            // fbMoveAbsolute(v_Axis[0],false,pos+rel,0.5,0.1,0.1,100,EN_Direction::enPositive,EN_BufferMode::enAborting,bDone,bBusy,bCommandAborted,bError,nErrorID);
            // fbMoveAbsolute(v_Axis[0],true,0,0.5,0.1,0.1,100,EN_Direction::enPositive,EN_BufferMode::enAborting,bDone,bBusy,bCommandAborted,bError,nErrorID);
            fbMoveRelative(v_Axis[0],false,rel,0.5,0.1,0.1,100,EN_Direction::enPositive,EN_BufferMode::enAborting,bDone,bBusy,bCommandAborted,bError,nErrorID);
            fbMoveRelative(v_Axis[0],true,rel,0.5,0.1,0.1,100,EN_Direction::enPositive,EN_BufferMode::enAborting,bDone,bBusy,bCommandAborted,bError,nErrorID);
            // fbMoveVelocity(v_Axis[0],false,0.5,0.1,10,100,EN_Direction::enPositive,bInVelocity,bBusy,bCommandAborted,bError,nErrorID);
            // fbMoveVelocity(v_Axis[0],true,0.5,0.1,10,100,EN_Direction::enPositive,bInVelocity,bBusy,bCommandAborted,bError,nErrorID);
            c = 0;
            break;
        }
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }
    // while (true)
    // {
    //     c = c+1;
    //     if(c>30000)
    //     {
    //         printf("Stop\n");
    //         fbMC_Stop(v_Axis[0],false,0.05,100,bDone,bBusy,bCommandAborted,bError,nErrorID);
    //         fbMC_Stop(v_Axis[0],true,0.05,100,bDone,bBusy,bCommandAborted,bError,nErrorID);
    //         c = 0;
    //         break;
    //     }

    //     pSoftMotion->SoftMotionRun();
    //     nanosleep(&ts, nullptr);
    // }
    // while (true)
    // {
    //     if(fbMC_Stop.Done())
    //     {
    //         fbMC_Stop(v_Axis[0],false,10,100,bDone,bBusy,bCommandAborted,bError,nErrorID);
    //         if(bDone)
    //         {
    //             printf("Stopfinish\n");
    //             break;
    //         }
    //     }
    //     pSoftMotion->SoftMotionRun();
    //     nanosleep(&ts, nullptr);
    // }
    // while (true)
    // {
    //     pSoftMotion->SoftMotionRun();
    //     nanosleep(&ts, nullptr);
    // }
    while (true)
    {
        //fbMoveAbsolute(v_Axis[0],true,pos+rel,0.5,0.1,0.1,100,EN_Direction::enPositive,EN_BufferMode::enAborting,bDone,bBusy,bCommandAborted,bError,nErrorID);
        fbMoveRelative(v_Axis[0],true,rel,0.5,0.1,10,100,EN_Direction::enPositive,EN_BufferMode::enAborting,bDone,bBusy,bCommandAborted,bError,nErrorID);
        printf("done:%d,busy:%d,error:%d\n",bDone,bBusy,bError);
        ///if(fbMoveAbsolute.Done())
        if(fbMoveRelative.Done())
        {
            c = c+1;
            if(c>5000)
            {
                printf("EndPos:%f\n",v_Axis[0]->dActPosition);
                printf("disable\n");
                fbMC_PowerOff(v_Axis[0],false,bBusy,bDone,bError,nErrorID);
                break;
            }
        }
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }
    while (true)
    {
        if(!bDone)
        {
            fbMC_PowerOff(v_Axis[0],true,bBusy,bDone,bError,nErrorID);
            if(bDone)
            {
                printf("finish\n");
            }
        }
        pSoftMotion->SoftMotionRun();
        nanosleep(&ts, nullptr);
    }
    return 0;
} 

