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

#include "BillingClient.h"
#include "Server.h"

CBillingClient::CBillingClient(void)
{
    this->isRunning    = false;
    this->isTrying     = false;
    this->Unk2         = true;
    this->Socket       = -1;
    this->Unk4         = 0;
}

bool CBillingClient::Create(void)
{
    struct sockaddr_in m_sockaddr;

    if(this->isRunning)
    {
        this->Close();
        this->isRunning = false;
    }
	
    this->Socket = socket(2, 1, 6);
    if(this->Socket >= 0)
    {
        memset(&m_sockaddr, 0, 16);
        m_sockaddr.sin_family = 2;
        m_sockaddr.sin_port          = htons(atoi(gserver.Configs.Find("Billing Server", "Port")));
        m_sockaddr.sin_addr.s_addr   = inet_addr(gserver.Configs.Find("Billing Server", "IP"));

        if(connect(this->Socket, (struct sockaddr *)&m_sockaddr, 16) >= 0)
        {
            this->Unk4 = 0;
            gserver.Nonblock(this->Socket);
            gserver.SetSendbuf(this->Socket);
            
            return true;
        }
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Create Socket");
        g_gamelogbuffer.__ls(end);
    }
    
    return false;
}

void CBillingClient::Close(void)
{
    this->isTrying = false;
	
    while(!this->Unk2)
        sleep(1);
	
    if(this->Socket > 0)
    {
        close(this->Socket);
        this->Socket = -1;
    }
}

void CBillingClient::BillingConnect(void *m_ptr)
{
    CBillingClient *m_bclient = (CBillingClient *)m_ptr;
    m_bclient->isTrying = true;
	
    while(m_bclient->isTrying)
    {
        if(m_bclient->Create())
        {
            m_bclient->SendHeader();
            m_bclient->isTrying = false;
        }
        else
        {
            m_bclient->Close();
            m_bclient->isTrying = true;
        }
		
        sleep(2);
    }
	
    pthread_exit(0);
}
