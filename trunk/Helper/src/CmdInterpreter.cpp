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

#include "CmdInterpreter.hpp"

CDescriptor g_descriptor;
CMsgList g_msglist;

void do_Command(CNetMsg &netmsg, CDescriptor *desc)
{
    unsigned int cmd; // [sp+14h] [bp-4h]@1

    cmd = -1;
    netmsg.MoveFirst();
    netmsg.__rs(cmd);
    if ( cmd <= 0x22 )
    {
#warning probabile off by one, da controllare a runtime
        switch ( cmd )
        {
        case 0:
            do_CommandShutdown(netmsg, desc);
            break;
        case 1:
            do_CommandGuildCreateReq(netmsg, desc);
            break;
        case 6:
            do_CommandGuildOnline(netmsg, desc);
            break;
        case 7:
            do_CommandGuildLoadReq(netmsg, desc);
            break;
        case 9:
            do_CommandGuildLevelUpReq(netmsg, desc);
            break;
        case 12:
            do_CommandGuildBreakUpReq(netmsg, desc);
            break;
        case 15:
            do_CommandGuildMemberAddReq(netmsg, desc);
            break;
        case 18:
            do_CommandGuildMemberOutReq(netmsg, desc);
            break;
        case 21:
            do_CommandGuildMemberKickReq(netmsg, desc);
            break;
        case 24:
            do_CommandGuildChangeBossReq(netmsg, desc);
            break;
        case 27:
            do_CommandGuildAppointOfficerReq(netmsg, desc);
            break;
        case 30:
            do_CommandGuildChat(netmsg, desc);
            break;
        case 31:
            do_CommandGuildFireOfficerReq(netmsg, desc);
            break;
        case 33:
            do_CommandCharacterDelete(netmsg, desc);
            break;
        default:
            break;

        }
    }
}

void do_Reply(CNetMsg &netmsg, CDescriptor *desc)
{
    char v11[1000]; // [sp+28h] [bp-4E0h]@19
    char v12[100]; // [sp+410h] [bp-F8h]@19
    char v13[100]; // [sp+474h] [bp-94h]@19
    int v14; // [sp+4D8h] [bp-30h]@19
    CMsgListNodeServerNode *v15; // [sp+4DCh] [bp-2Ch]@4
    CMsgListNodeServerNode *v16; // [sp+4E0h] [bp-28h]@5
    char v17; // [sp+4E7h] [bp-21h]@4
    int v18; // [sp+4E8h] [bp-20h]@1
    CMsgListNode *pmsglistnode; // [sp+4ECh] [bp-1Ch]@1
    CMsgListNode *msg; // [sp+4F0h] [bp-18h]@2
    unsigned __int8 v21; // [sp+4F7h] [bp-11h]@1
    int v22; // [sp+4F8h] [bp-10h]@1
    int v23; // [sp+4FCh] [bp-Ch]@1
    int v24; // [sp+500h] [bp-8h]@1
    int dest; // [sp+504h] [bp-4h]@1

    netmsg.MoveFirst();
    netmsg.__rs(dest);
    netmsg.__rs(v24);
    netmsg.__rs(v23);
    netmsg.__rs(v22);
    netmsg.__rs(v21);
    pmsglistnode = g_msglist.pMsgListNode;
    v18 = 0;
    while ( 1 )
    {
        msg = pmsglistnode;
        if ( !pmsglistnode )
            break;
        pmsglistnode = msg->NewListNode;
        if ( msg->unk_dword == dest )
        {
            v17 = 1;
            v15 = msg->ServerNode;
            while ( 1 )
            {
                v16 = v15;
                if ( !v15 )
                    break;
                v15 = v16->servernode2;
                if ( v16->desc->some_header != desc->some_header || v16->desc->unk_integer != desc->unk_integer )
                {
                    if ( !v16->unk_char[0] )
                        v17 = 0;
                }
                else
                {
                    v16->unk_char[0] = 1;
                    v18 = v16->desc->some_header;
                }
            }
            if ( v18 )
            {
                if ( v21 == 3 )
                {
                    if ( v17 )
                    {
                        //CNetMsg::CNetMsg(&v_netmsg);
                        CNetMsg v_netmsg;
                        netmsg.__rs(v14);
                        netmsg.__rs(v12);
                        HelperWhisperNotfoundMsg(v_netmsg, dest, v24, v23, v22, v14, v12);
                        if ( msg->desc )
                            msg->desc->WriteToOutput(v_netmsg);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                }
                else
                {
                    if ( (signed int)v21 > 3 )
                    {
                        if ( v21 == 6 )
                        {
                            v17 = 1;
                            if ( msg->desc )
                                msg->desc->WriteToOutput(netmsg);
                        }
                    }
                    else
                    {
                        if ( v21 == 1 )
                        {
                            netmsg.__rs(v14);
                            netmsg.__rs(v13);
                            netmsg.__rs(v12);
                            netmsg.__rs(v11);
                            CNetMsg v_netmsg;
                            HelperWhisperRepMsg(v_netmsg, dest, v24, v23, v22, v14, v13, v12, v11);
                            if ( msg->desc )
                                msg->desc->WriteToOutput(v_netmsg);
                            v17 = 1;
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                    }
                }
                if ( v17 )
                    g_msglist.Remove(msg);
                return;
            }
        }
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

void CServer::CommandInterpreter(CDescriptor *desc, CNetMsg &netmsg)
{
    if ( netmsg.p_msg_type == 122 )
    {
        do_Reply(netmsg, desc);
        return;
    }
    if ( netmsg.p_msg_type > 122 )
    {
        if ( netmsg.p_msg_type == 123 )
        {
            do_Command(netmsg, desc);
            return;
        }
    }
    else
    {
        if ( netmsg.p_msg_type == 121 )
        {
            do_Request(netmsg, desc);
            return;
        }
    }
    g_gamelogbuffer.__ls(init("WARNING"));
    g_gamelogbuffer.__ls("INVALID COMMAND");
    g_gamelogbuffer.__ls(" : ");
    g_gamelogbuffer.__ls((int)netmsg.p_msg_type);
    g_gamelogbuffer.__ls(end);
}
