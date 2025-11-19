#pragma once
#define SMC_TIME_OUT 500 * 1000
//Functional Status of MC_InitResetAxis 

enum FS_InitResetAxis
{
    ReadyInitResetAxis,
    InitResetting,
    InitResetFinish,
    InitResetError,
};
//Functional Status of MC_ClearFault
enum FS_ClearFault
{
    ReadyClearFault,
    StartClearFault,
    ClearFaulting,
    ClearFaultFinish,
    ClearFaultError,
};
//Functional Status of MC_Reset
enum FS_Reset
{
    ReadyReset,
    StartReset,
    Reseting,
    ResetFinish,
    ResetError,
};
//Functional Status of MC_PowerOn
enum FS_PowerOn
{
    ReadyPowerOn,
    StartPowerOn,
    PowerOning_0x06,
    PowerOning_0x07,
    PowerOning_0x0F,
    PowerOnFinish,
    PowerOnError,
};
//Functional Status of MC_PowerOff
enum FS_PowerOff
{
    ReadyPowerOff,
    StartPowerOff,
    PowerOff_0x07,
    PowerOff_0x06,
    PowerOffFinish,
    PowerOffError,
};

enum FS_Motion
{
    ReadyMotion,
    InMotion,
    MotionFinish,
    MotionError,
};
//Functional Status of MC_Home
enum FS_Home
{
    ReadyHome,
    StartHome,
    Home_0x1F,
    Home_0x06,
    HomeFinish,
    HomeError,
};

