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

class CMutex;
class CMutexObject;

#ifndef MUTEX_H
#define MUTEX_H

#include "Utils.h"

class CMutexObject {
protected:
    pthread_mutex_t mutex; // + 0
    bool p_init_fail;      // + 24
public:
    CMutexObject(void)    { this->p_init_fail = pthread_mutex_init(&this->mutex, 0) == 0; }
    ~CMutexObject()
    {
        if(!this->p_init_fail)
        {
            this->Unlock();
            pthread_mutex_destroy(&this->mutex);
        }
    }

    int Lock(void)      { return pthread_mutex_lock(&this->mutex); }
    int Try(void)       { return pthread_mutex_trylock(&this->mutex); }
    int Unlock(void)    { return pthread_mutex_unlock(&this->mutex); }
};

class CMutex {
private:
    CMutexObject *p_mutex_object;   // + 0
    int p_mutex_state;              // + 4
public:
    CMutex(CMutexObject *mutex_object, bool lock)
    {
        this->p_mutex_object = mutex_object;
        this->p_mutex_state = lock ? this->p_mutex_object->Lock() : this->p_mutex_object->Try();
    }

    ~CMutex()
    {
        if(!this->p_mutex_state)
            this->p_mutex_object->Unlock();
    }
};

#endif // MUTEX_H
