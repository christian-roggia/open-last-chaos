/******************************************************************************************
  Copyright 2013 Andrea Ragusa

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************************/

#include "Cmd.hpp"

CDescriptor g_descriptor;
CMsgList g_msglist;
CCmdList gcmdlist;

CCmd::CCmd()
{
    ;
}

CCmd::~CCmd()
{
    ;
}

CCmdList::CCmdList()
{
    this->CmdCount = 0;
    CCmdList::Add(101, do_Request, 0);
    CCmdList::Add(102, do_Reply, 0);
    CCmdList::Sort();
}

void CCmdList::Add(__tagMessageType type, void (*pFunc)(CNetMsg &, CDescriptor *), int unk)
{
    if ( this->CmdCount <= 199 )
    {
        this->CmdArray[this->CmdCount] = new CCmd;
        this->CmdArray[this->CmdCount]->type = type;
        this->CmdArray[this->CmdCount]->pFunc = pFunc;
        this->CmdArray[this->CmdCount++]->unk = unk;
    }
}

int CCmdList::Find(__tagMessageType type)
{
    int v3; // [sp+1Ch] [bp-Ch]@1
    int v4; // [sp+24h] [bp-4h]@1

    v4 = 0;
    v3 = this->CmdCount;
    while ( 1 )
    {
        if ( this->CmdArray[(v3 + v4) / 2]->type == type )
            return (v3 + v4) / 2;
        if ( (v3 + v4) / 2 - v4 <= 0 )
            break;
        if ( this->CmdArray[(v3 + v4) / 2]->type - type <= 0 )
            v4 = (v3 + v4) / 2;
        else
            v3 = (v3 + v4) / 2;
    }
    return -1;
}

void CCmdList::Run(int val, CNetMsg &netmsg, CDescriptor *desc)
{
    this->CmdArray[val]->pFunc(netmsg, desc);
}

void CCmdList::Sort()
{
    qsort(this, this->CmdCount, 4u, (__compar_fn_t) CmdComp);
}

CCmdList::~CCmdList()
{
    int i;

    for ( i = 0; i < this->CmdCount; ++i )
    {
        if ( this->CmdArray[i] )
            //CCmd::_CCmd(this->CmdArray[i], 3);
            delete this->CmdArray[i];
    }
}

__compar_fn_t CmdComp(void *a1, void *a2)
{
    return (__compar_fn_t)(**(_DWORD **)a1 - **(_DWORD **)a2);
}

void CServer::CommandInterpreter(CDescriptor *desc, CNetMsg &netmsg)
{
  int cmd;

  cmd = gcmdlist.Find(netmsg.p_msg_type);
  if ( cmd >= 0 )
  {
    gcmdlist.Run(cmd, netmsg, desc);
  }
  else
  {
    g_gamelogbuffer.__ls(init("WARNING"));
    g_gamelogbuffer.__ls("INVALID COMMAND");
    g_gamelogbuffer.__ls(" : ");
    g_gamelogbuffer.__ls((int)netmsg.p_msg_type);
    g_gamelogbuffer.__ls(end);
  }
}

void do_Request(CNetMsg &netmsg, CDescriptor *desc)
{
    CDescriptor *v8; // [sp+8h] [bp-20h]@4
    CDescriptor *v9; // [sp+Ch] [bp-1Ch]@5
    CMsgListNode *msglistnode; // [sp+10h] [bp-18h]@2
    char v11; // [sp+17h] [bp-11h]@1
    int v12; // [sp+18h] [bp-10h]@1
    int v13; // [sp+1Ch] [bp-Ch]@1
    int v14; // [sp+20h] [bp-8h]@1
    int dest; // [sp+24h] [bp-4h]@1

    netmsg.MoveFirst();
    netmsg.__rs(dest);
    netmsg.__rs(v14);
    netmsg.__rs(v13);
    netmsg.__rs(v12);
    netmsg.__rs(v11);
    if ( dest == -1 )
    {
        msglistnode = g_msglist.Add(-1, 0, desc, netmsg);
    }
    else
    {
        msglistnode = g_msglist.Add(gserver.GetNextSeqNo(), 1, desc, netmsg);
    }
    v8 = &g_descriptor;
    while ( 1 )
    {
        v9 = v8;
        if ( !v8 )
            break;
        v8 = v8->SubDesc;
        if ( !v9->socket_ret && (v14 == -1 || v9->some_header == v14) && (v13 == -1 || v9->unk_integer == v13) )
        {
            if ( v12 == -1 || v9->FindZone(v12) != -1 )
                msglistnode->Add(v9);
        }
    }
}

void do_Reply(CNetMsg &netmsg, CDescriptor *desc)
{
  char v11[21]; // [sp+13h] [bp-4F5h]@25
  char v13[1000]; // [sp+28h] [bp-4E0h]@14
  char v14[100]; // [sp+410h] [bp-F8h]@14
  char v15[100]; // [sp+474h] [bp-94h]@14
  int v16; // [sp+4D8h] [bp-30h]@14
  CMsgListNodeServerNode *v17; // [sp+4DCh] [bp-2Ch]@4
  CMsgListNodeServerNode *v18; // [sp+4E0h] [bp-28h]@5
  char v19; // [sp+4E7h] [bp-21h]@4
  CDescriptor *v20; // [sp+4E8h] [bp-20h]@1
  CMsgListNode *g_pmsglistnode; // [sp+4ECh] [bp-1Ch]@1
  CMsgListNode *msg; // [sp+4F0h] [bp-18h]@2
  char v23; // [sp+4F7h] [bp-11h]@1
  int v24; // [sp+4F8h] [bp-10h]@1
  int v25; // [sp+4FCh] [bp-Ch]@1
  int v26; // [sp+500h] [bp-8h]@1
  int dest; // [sp+504h] [bp-4h]@1

  netmsg.MoveFirst();
  netmsg.__rs(dest);
  netmsg.__rs(v26);
  netmsg.__rs(v25);
  netmsg.__rs(v24);
  netmsg.__rs(v23);
  g_pmsglistnode = g_msglist.pMsgListNode;
  v20 = 0;
  while ( 1 )
  {
    msg = g_pmsglistnode;
    if ( !g_pmsglistnode )
      break;
    g_pmsglistnode = msg->NewListNode;
    if ( msg->unk_dword == dest )
    {
      v19 = 1;
      v17 = msg->ServerNode;
      while ( 1 )
      {
        v18 = v17;
        if ( !v17 )
          break;
        v17 = v18->servernode2;
        if ( v18->desc->some_header != desc->some_header || v18->desc->unk_integer != desc->unk_integer )
        {
          if ( !v18->unk_char[0] )
            v19 = 0;
        }
        else
        {
          v18->unk_char[0] = 1;
          v20 = v18->desc;
        }
      }
      if ( v20 )
      {
        switch ( v23 )
        {
          case 1: {
                      CNetMsg v_netmsg;
            netmsg.__rs(v16);
            netmsg.__rs(v15);
            netmsg.__rs(v14);
            netmsg.__rs(v13);
            MsgrWhisperRep(
              v_netmsg,
              dest,
              v26,
              v25,
              v24,
              v16,
              v15,
              v14,
              v13);
            if ( msg->desc )
              msg->desc->WriteToOutput(v_netmsg);
            v19 = 1;
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
            break;
          }
          case 3:
            if ( v19 )
            {
            CNetMsg v_netmsg;
              netmsg.__rs(v16);
              netmsg.__rs(v14);
              MsgrWhisperNotfoundMsg(v_netmsg, dest, v26, v25, v24, v16, (const char *)&v14);
              if ( msg->desc )
                       msg->desc->WriteToOutput(v_netmsg);
              //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
            break;
          case 8:
            if ( msg->desc )
                     msg->desc->WriteToOutput(netmsg);
            break;
          case 9: {
            netmsg.__rs(v11);
            netmsg.__rs(v14);
            CNetMsg v_netmsg;
            if ( v11 )
            {
              v19 = 1;
              MsgrLogoutRepMsg(v_netmsg, dest, v26, v25, v24, 1, v14);
              if ( msg->desc )
                       msg->desc->WriteToOutput(v_netmsg);
            }
            else
            {
              if ( v19 )
              {
                MsgrLogoutRepMsg(v_netmsg, dest, v26, v25, v24, 0, v14);
                if ( msg->desc )
                         msg->desc->WriteToOutput(v_netmsg);
              }
            }
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
            break;
          }
          case 0xB:
            v19 = 1;
            if ( msg->desc )
                    msg->desc->WriteToOutput(netmsg);
            break;
          default:
            break;
        }
        if ( v19 )
          g_msglist.Remove(msg);
        return;
      }
    }
  }
}
