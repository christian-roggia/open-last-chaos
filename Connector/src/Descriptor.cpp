/******************************************************************************************
  Copyright 2013 Christian Roggia

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

#include "Descriptor.h"

CDescriptor::CDescriptor(void)
{
  this->Socket = 0;
  memset(this->Hostname, 0, 31);
  this->Unk148 = -1;
  this->Unk152 = 0;
  this->Unk156 = 0;
  this->Unk160 = 0;
  this->Unk164 = 0;
  this->WasErrors = false;
  this->Unk169 = 0;
  this->IsTester = false;
  this->SubServerID = 0;
  this->NextNode = 0;
  this->Node = 0;
}

void CDescriptor::CloseSocket(void)
{
    close(this->Socket);
    this->FlushQueues();
}

void CDescriptor::FlushQueues(void)
{
    this->InputBuffer.Clear();
    this->InputQueue2.Clear();
    this->OutputBuffer.Clear();
}

void CDescriptor::WriteToOutput(CNetMsg &net_msg)
{
    if(net_msg.MsgType)
    {
        if(this->OutputBuffer.Add(net_msg))
        {
            this->ProcessOutput();
        }
        else
        {
            g_gamelogbuffer.__ls(init("OUTPUT OVERFLOW"));
            g_gamelogbuffer.__ls(end);

            this->WasErrors = true;
        }
    }
}

int CDescriptor::ProcessOutput(void)
{
  char *m_buffer;
  long m_ret;

  while(1)
  {
    m_buffer = this->OutputBuffer.GetNextPoint();

    if(!m_buffer)
      break;

    m_ret = this->WriteToDescriptor(this->Socket, m_buffer, this->OutputBuffer.GetRemain());

    if(m_ret < 0)
    {
      this->WasErrors = true;
      return -1;
    }

    if(!m_ret || this->OutputBuffer.Update(m_ret))
      return 0;
  }

  return 0;
}

int CDescriptor::WriteToDescriptor(long p_fd, char const *p_buf, long p_bytes)
{
    int m_write;

    if(!p_bytes)
        return 0;
    
    m_write = write(p_fd, p_buf, p_bytes);
    
    if(m_write > 0)
        return m_write;
    
    if (!m_write)
        return -1;
    
    if(errno == 11)
        return 0;
    
    if(errno != 104)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Write to descriptor: errno=");
        g_gamelogbuffer.__ls(errno);
        g_gamelogbuffer.__ls(end);
    }
    
    return -1;
}

int CDescriptor::ProcessInput(void)
{
    bool r_finished = false, r_finished2 = false, m_message_fail = false;
    int m_bytes = 0, m_get_message = 0;
    CNetMsg net_msg;

    do
    {
        if(this->InputBuffer.GetRemain() <= 0)
        {
            g_gamelogbuffer.__ls(init("SYS_WARN"));
            g_gamelogbuffer.__ls("m_input overflow");
            g_gamelogbuffer.__ls(end);
            
            return -1;
        }
        
        m_bytes = this->PerformSocketRead(this->Socket, this->InputBuffer.GetPoint(), this->InputBuffer.GetRemain());

        if(m_bytes < 0)
            return -1;
        
        if(!m_bytes)
            return 0;
        
        this->InputBuffer.SetPoint(m_bytes);
        
        
        r_finished2 = false;
        m_message_fail = false;
        
        while(!r_finished2)
        {
            m_get_message = this->InputBuffer.GetMessage(net_msg);
            
            if(m_get_message)
            {
                if(m_get_message > 0)
                {
                    if(m_get_message == 1)
                        r_finished2 = true;
                }
                else
                {
                    if(m_get_message == -1)
                    {
                        m_message_fail = true;
                        r_finished2 = true;
                    }
                }
            }
            else
            {
                this->InputQueue2.Add(net_msg);
                r_finished = true;
            }
        }
        
        if(m_message_fail)
            return -1;
    }
    while(!r_finished);
    
    return 1;
}

int CDescriptor::PerformSocketRead(long p_fd, char *p_buf, unsigned long p_bytes)
{
    long m_read = read(p_fd, p_buf, p_bytes);

    if(m_read > 0)
        return m_read;
    
    if(!m_read)
        return -1;
    
    if(errno == 4 || errno == 11 || errno == 11 || errno == 35)
        return 0;
    
    return -1;
}

bool CDescriptor::GetLogin(CNetMsg &m_msg)
{
    char src[32];
    int m_server_id, m_sub_server_id;
    char m_unk_char[20];
    CDescriptor *j, *v29;
    int v30, v33, dest, v35;

    // ======= [BEGIN ANTI-OVERFLOW] =======
    memset(src, 0, 32);
    memset(m_unk_char, 0, 20);
    m_server_id = m_sub_server_id = v30 = v33 = dest = v35 = 0;
    // ======= [END   ANTI-OVERFLOW] =======


    m_msg.MoveFirst();

    if(m_msg.MsgType != 110)
    {
        g_gamelogbuffer.__ls(init("BAD_CONNECTION", this->Hostname));
        g_gamelogbuffer.__ls(end);

        return false;
    }

    m_msg.__rs(dest);
    m_msg.__rs(m_server_id);
    m_msg.__rs(m_sub_server_id);
    m_msg.__rs(src);
    m_msg.__rs(v33);
    m_msg.__rs(v35);

    if(m_server_id == 9999)
    {
        m_msg.__rs(m_unk_char);

        if(strcmp(m_unk_char, "tjwjddnjsehd"))
        {
            g_gamelogbuffer.__ls(init("BAD_CONNECTION", this->Hostname));
            g_gamelogbuffer.__ls((int)dest);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls((int)m_server_id);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls((int)m_sub_server_id);
            g_gamelogbuffer.__ls(end);

            return false;
        }
    }

    if((dest <= 599 || dest > 700 || (m_server_id != gserver.Number || m_sub_server_id <= 0 || m_sub_server_id > gserver.MaxSubServer)) && m_server_id != 999 && m_server_id != 777 && m_server_id != 9999)
    {
        g_gamelogbuffer.__ls(init("BAD_CONNECTION", this->Hostname));
        g_gamelogbuffer.__ls((int)dest);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_server_id);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_sub_server_id);
        g_gamelogbuffer.__ls(end);
        return false;
    }

    if(m_server_id == 999 || m_server_id == 9999 || m_server_id == 888)
    {
        this->IsTester = true;
    }
    else
    {
      if(m_sub_server_id <= 0 || m_sub_server_id > gserver.MaxSubServer)
          return false;

      if(v35 <= 0)
          return false;

      for(int i = 0; i < v35; ++i)
      {
          m_msg.__rs(v30);

          gserver.Users[m_sub_server_id - 1].Count[v30] = 0;

          if(!v30)
              this->Unk169 = 1;
      }

      this->SubServerID = m_sub_server_id;
      j = gserver.ClientDescriptors;

      while(1)
      {
          v29 = j;

          if(!j)
              break;

          j = v29->Node;

          if(!v29->IsTester && v29->SubServerID > 0 && v29->SubServerID == this->SubServerID && this != v29)
              gserver.CloseSocket(v29);
      }
    }

    strcpy(this->Unk170, src);
    this->Unk204 = v33;
    this->Unk152 = 0;

    CNetMsg m_out_msg;
    PlayerRepMsg(m_out_msg);

    for(j = gserver.ClientDescriptors; j; j = j->Node)
    {
        if((j->IsTester || m_server_id == 9999) && j)
            j->WriteToOutput(m_out_msg);
    }

    return true;
}
