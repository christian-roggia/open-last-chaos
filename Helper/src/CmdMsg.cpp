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

#include "CmdMsg.hpp"

char g_buf[0x2000];
char g_buf2[0x2000];
char g_buf3[0x2000];

CMsgListNode *CMsgList::Add(int seq, bool a3, CDescriptor *desc, CNetMsg &msg)
{
    msg.MoveFirst();
    if ( a3 )
        msg.__ls(seq);
    else
        msg.__ls(-1);
    CMsgListNode *newlistnode = new CMsgListNode(seq, a3, desc, msg);

    if ( this->pMsgListNode )
        this->pMsgListNode->ActualListNode = newlistnode;
    newlistnode->NewListNode = this->pMsgListNode;
    newlistnode->ActualListNode = 0;
    this->pMsgListNode = newlistnode;
    return newlistnode;
}

CMsgList::CMsgList()
{
    this->pMsgListNode = 0;
}

void CMsgList::Remove(CMsgListNode *node)
{
    if ( node->ActualListNode )
    {
        node->ActualListNode->NewListNode = node->NewListNode;
        if ( node->NewListNode )
            node->NewListNode->ActualListNode = node->ActualListNode;
    }
    else
    {
        this->pMsgListNode = node->NewListNode;
        if ( node->NewListNode )
            node->NewListNode->ActualListNode = 0;
    }
    node->ActualListNode = 0;
    node->NewListNode = 0;
    if ( node )
        //CMsgListNode::_CMsgListNode(node, 3);
        delete node;
}

void CMsgList::RemoveServer(CDescriptor *a2)
{
    CMsgListNode *v2; // [sp+10h] [bp-8h]@1
    CMsgListNode *node; // [sp+14h] [bp-4h]@2

    v2 = this->pMsgListNode;
    while ( 1 )
    {
        node = v2;
        if ( !v2 )
            break;
        v2 = v2->NewListNode;
        if ( node->RemoveServer(a2) )
        {
            if ( node->ActualListNode )
            {
                node->ActualListNode->NewListNode = node->NewListNode;
                if ( node->NewListNode )
                    node->NewListNode->ActualListNode = node->ActualListNode;
            }
            else
            {
                this->pMsgListNode = node->NewListNode;
                if ( node->NewListNode )
                    node->NewListNode->ActualListNode = 0;
            }
            node->ActualListNode = 0;
            node->NewListNode = 0;
            if ( node )
                //CMsgListNode::_CMsgListNode(node, 3);
                delete node;
        }
    }
}

CMsgList::~CMsgList()
{
    CMsgListNode *v2; // [sp+14h] [bp-4h]@2

    while ( this->pMsgListNode )
    {
        v2 = this->pMsgListNode->NewListNode;
        if ( this->pMsgListNode )
            //CMsgListNode::_CMsgListNode(this->pMsgListNode, 3);
            delete this->pMsgListNode;
        this->pMsgListNode = v2;
    }
//  if ( a2 & 1 )
//    __builtin_delete();
}

void CMsgListNode::Add(CDescriptor *desc)
{
    CMsgListNodeServerNode *NewServerNode = new CMsgListNodeServerNode(desc);

    if ( this->ServerNode )
        this->ServerNode->servernode1 = NewServerNode;
    NewServerNode->servernode2 = this->ServerNode;
    NewServerNode->servernode1 = 0;
    this->ServerNode = NewServerNode;
}

CMsgListNode::CMsgListNode(int a2, bool a3, CDescriptor *desc, CNetMsg &msg)
{
    //CNetMsg::CNetMsg(&this->NetMsg);
    this->unk_dword = a2;
    this->char1[0] = a3;
    this->NetMsg.__as(msg);
    this->char2[0] = 0;
    this->dword20 = -1;
    this->desc = desc;
    this->ServerNode = 0;
}

bool CMsgListNode::RemoveServer(CDescriptor *Desc)
{
    bool result; // al@13
    CMsgListNodeServerNode *v3; // [sp+10h] [bp-8h]@1
    CMsgListNodeServerNode *v4; // [sp+14h] [bp-4h]@2

    v3 = this->ServerNode;
    while ( 1 )
    {
        v4 = v3;
        if ( !v3 )
            break;
        v3 = v3->servernode2;
        if ( v4->desc == Desc )
        {
            if ( v4->servernode1 )
            {
                v4->servernode1->servernode2 = v4->servernode2;
                if ( v4->servernode2 )
                    v4->servernode2->servernode1 = v4->servernode1;
            }
            else
            {
                this->ServerNode = v4->servernode2;
                if ( v4->servernode2 )
                    v4->servernode2->servernode1 = 0;
            }
            v4->servernode1 = 0;
            v4->servernode2 = 0;
            //__builtin_delete();
#warning il delete potrebbe essere errato
            delete v4;
        }
    }
    if ( this->ServerNode )
        result = 0;
    else
        result = 1;
    return result;
}

CMsgListNode::~CMsgListNode()
{
    CMsgListNodeServerNode *v2; // ST24_4@2

    while ( this->ServerNode )
    {
        v2 = this->ServerNode->servernode2;
        //__builtin_delete();
        delete this->ServerNode;
        this->ServerNode = v2;
    }
//  CNetMsg::_CNetMsg(&this->NetMsg, 2);
//  if ( a2 & 1 )
//    __builtin_delete();
}

CMsgListNodeServerNode::CMsgListNodeServerNode(CDescriptor *desc)
{
    this->desc = desc;
    this->unk_char[0] = 0;
    this->servernode1 = 0;
    this->servernode2 = 0;
}
