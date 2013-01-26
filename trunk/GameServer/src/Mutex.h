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

#ifndef MUTEX_H
#define MUTEX_H

class CMutexObject;
class CMutex;

class CMutexObject {
protected:
        pthread_mutex_t Mutex;  // + 0
        bool State;             // + 24
public:
        CMutexObject(void)      { this->State = pthread_mutex_init(&this->Mutex, 0) == 0; }
        ~CMutexObject()
        {
            if(!this->State)
            {
                this->Unlock();
                pthread_mutex_destroy(&this->Mutex);
            }
        }

        int Lock(void)		{ return pthread_mutex_lock(&this->Mutex); }
        int Try(void)		{ return pthread_mutex_trylock(&this->Mutex); }
        int Unlock(void)	{ return pthread_mutex_unlock(&this->Mutex); }
};

class CMutex {
private:
        CMutexObject *MutexObject;   // + 0
        int MutexState;             // + 4
public:
        CMutex(CMutexObject *m_mutex_object, bool m_lock)
        {
            this->MutexObject = m_mutex_object;
            this->MutexState = m_lock ? this->MutexObject->Lock() : this->MutexObject->Try();
        }

        ~CMutex()
        {
            if(!this->MutexState)
                this->MutexObject->Unlock();
        }

        bool IsLock(void)
        {
           return this->MutexState == 0;
        }
};

#endif // MUTEX_H
