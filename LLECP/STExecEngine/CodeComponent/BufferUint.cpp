#include"BufferUint.h"

BufferUint::BufferUint(/* args */)
{
    uint32_t m_nLineRunIndex = 0;
}

BufferUint::~BufferUint()
{
}


int BufferUint::EnableBuffer(bool bEnable)
{
    m_bBuffEnable = bEnable;
    return 0;
}

int BufferUint::CleanBuffer()
{
    m_nLineRunIndex = 0;

    m_bBufferRunDone=false;
    m_vLineList.clear();
    return 0;
}


int BufferUint::StartPushLine()
{
    //新增一行
    LineUint T_LineUint;
    m_vLineList.push_back(T_LineUint);
    return 0;
}

int BufferUint::PushCmd(uint16_t nLineID,CmdUint cmd)
{
    return m_vLineList.back().PushCmd(cmd);
}

int BufferUint::InitBuffer()
{
    InitCmdType();
    StatementMatching();
    return 0;
}


int BufferUint::InitCmdType()
{
    //遍历每一行
    for(auto &line : m_vLineList)
    {
        //遍历每一行的每一条命令
        for(auto &cmd : line.m_vCmd)
        {
            //对于每一条命令，进行类型初始化
            cmd.InitCmd();
        }
    }
    return 0;
}

int BufferUint::StatementMatching()
{
    struct ST_PosIndex
    {
        uint32_t nLinePos;
        uint32_t nCmdPos;
        ST_PosIndex(int line,int cmd)
        {
            nLinePos = line;
            nCmdPos = cmd;
        }
    };
    //遍历每一行
    for (size_t i = 0; i < m_vLineList.size(); i++)
    {
        for (size_t j = 0; j < m_vLineList[i].m_vCmd.size(); j++)
        {
            //监测到IF，查找对应的非满足跳转位置
            if ((m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_IF) || 
                (m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_ELSEIF) ||
                (m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_ELSE))
            {
                if ((m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_ELSEIF) ||
                    (m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_ELSE))
                {
                    //初始化状态大小为1
                    vector<UN_TransitionParam>vTCmdParam;
                    UN_TransitionParam CmdParam;
                    CmdParam.nParam = 0;//为1就是该else/elsif不需要执行，直接跳，因为if执行了
                    vTCmdParam.push_back(CmdParam);
                    m_vLineList[i].m_vCmd[j].SetCmdState(vTCmdParam);
                }

                //无法判断是否为行最后一句，因此从当前开始
                int nLevel = 0;
                bool bFind = false;
                vector<ST_PosIndex> v_pos;
                v_pos.push_back(ST_PosIndex(i,j));

                size_t it = i;
                size_t jt = j;
                //从下一句开始执行
                if(jt +1 < m_vLineList[it].m_vCmd.size())
                {
                    jt++;
                }
                else
                {
                    it++;
                    jt = 0;
                }
                //从当前位置开始遍历
                for (; it < m_vLineList.size(); it++)
                {
                    for (; jt < m_vLineList[it].m_vCmd.size(); jt++)
                    {
                        if ((m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_ELSEIF)&&(0 == nLevel))
                        {
                            v_pos.push_back(ST_PosIndex(it,jt));
                            bFind = true;
                            continue;
                        }
                        if ((m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_ELSE)&&(0 == nLevel))
                        {
                            //ELSE 不匹配else
                            if(m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_ELSE)
                                continue;
                            v_pos.push_back(ST_PosIndex(it,jt));
                            bFind = true;
                            break;
                        }
                        if ((m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_ENDIF)&&(0 == nLevel))
                        {
                            v_pos.push_back(ST_PosIndex(it,jt));
                            bFind = true;
                            break;
                        }
                        //首次必加
                        if (m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_IF)
                        {
                            nLevel++;
                            continue;
                        }
                        if (m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_ENDIF)
                        {
                            nLevel--;
                            continue;
                        }
                        if(bFind)
                            continue;
                    }
                    jt = 0;
                    if(bFind)
                        break;
                }
                //查找完成现在赋值
                for (size_t n = 0; n < v_pos.size()-1; n++)//最后一个是endif
                {
                    vector<UN_TransitionParam> v_param;
                    UN_TransitionParam param;
                    param.nParam = v_pos[n+1].nLinePos;
                    v_param.push_back(param);
                    param.nParam = v_pos[n+1].nCmdPos;
                    v_param.push_back(param);
                    m_vLineList[v_pos[n].nLinePos].m_vCmd[v_pos[n].nCmdPos].SetCmdParam(v_param);
                }
            }
            else if (m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_WHILE)
            {
                int nLevel = -1;
                bool bFind = false;
                vector<ST_PosIndex> v_pos;//to CmdType_WHILE
                for (size_t it = i; it < m_vLineList.size(); it++)
                {
                    for (size_t jt = j; jt < m_vLineList[it].m_vCmd.size(); jt++)
                    {
                        if (m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_WHILE)
                        {
                            nLevel++;
                        }
                        if (m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_ENDWHILE)
                        {
                            if(nLevel == 0)
                            {
                                bFind = true;
                                UN_TransitionParam param;
                                param.nParam = i;
                                std::vector<UN_TransitionParam> v_Param;//to CmdType_end WHILE
                                v_Param.push_back(param);
                                param.nParam = j;
                                v_Param.push_back(param);
                                //初始化ENDWHILE的跳转位置(WHILE的位置)
                                m_vLineList[it].m_vCmd[jt].SetCmdParam(v_Param);
                                v_pos.push_back(ST_PosIndex(it,jt));
                                break;
                            }
                            else
                            {
                                nLevel--;
                            }
                        }
                        if(bFind)
                            break;
                        
                    }
                    if(bFind)
                        break;
                }
                ST_PosIndex pos_endwhile = v_pos[0];
                //最后一行处理
                if(pos_endwhile.nCmdPos == m_vLineList[pos_endwhile.nLinePos].m_vCmd.size())
                {
                    //在下一行添加跳转命令
                    pos_endwhile.nLinePos +=1;
                    pos_endwhile.nCmdPos = 0;
                }
                else
                {
                    pos_endwhile.nCmdPos +=1;
                }
                vector<UN_TransitionParam> v_param;
                UN_TransitionParam param;
                param.nParam = pos_endwhile.nLinePos;
                v_param.push_back(param);
                param.nParam = pos_endwhile.nCmdPos;
                v_param.push_back(param);
                //WHILE语句初始化指向ENDWHILE的跳转位置
                m_vLineList[i].m_vCmd[j].SetCmdParam(v_param);
            }
            else if (m_vLineList[i].m_vCmd[j].GetCmdType() == CmdType_LOOP)
            {
                int nLevel = -1;
                bool bFind = false;
                vector<ST_PosIndex> v_pos;//to CmdType_LOOP
                for (size_t it = i; it < m_vLineList.size(); it++)
                {
                    for (size_t jt = j; jt < m_vLineList[it].m_vCmd.size(); jt++)
                    {
                        if (m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_LOOP)
                        {
                            nLevel++;
                        }
                        if (m_vLineList[it].m_vCmd[jt].GetCmdType() == CmdType_ENDLOOP)
                        {
                            if(nLevel == 0)
                            {
                                bFind = true;
                                UN_TransitionParam param;
                                param.nParam = i;
                                std::vector<UN_TransitionParam> v_Param;//to CmdType_end LOOP
                                v_Param.push_back(param);
                                param.nParam = j;
                                v_Param.push_back(param);
                                //初始化ENDLOOP的跳转位置(LOOP的位置)
                                m_vLineList[it].m_vCmd[jt].SetCmdParam(v_Param);
                                v_pos.push_back(ST_PosIndex(it,jt));
                                break;
                            }
                            else
                            {
                                nLevel--;
                            }
                        }
                        if(bFind)
                            break;
                        
                    }
                    if(bFind)
                        break;
                }
                ST_PosIndex pos_endwhile = v_pos[0];
                //最后一行处理
                if(pos_endwhile.nCmdPos == m_vLineList[pos_endwhile.nLinePos].m_vCmd.size())
                {
                    //在下一行添加跳转命令
                    pos_endwhile.nLinePos +=1;
                    pos_endwhile.nCmdPos = 0;
                }
                else
                {
                    pos_endwhile.nCmdPos +=1;
                }
                vector<UN_TransitionParam> v_param;
                UN_TransitionParam param;
                param.nParam = pos_endwhile.nLinePos;
                v_param.push_back(param);
                param.nParam = pos_endwhile.nCmdPos;
                v_param.push_back(param);
                //LOOP语句初始化指向ENDLOOP的跳转位置
                m_vLineList[i].m_vCmd[j].SetCmdParam(v_param);
            }
        }
    }
    
    return 0;
}