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


template <class T> class CMemPoolNode;
template <class T, int L> class CMemPool;

#ifndef MEMPOOL_H
#define MEMPOOL_H

#include "Utils.hpp"

/********************************************************************************
 * Pool Node
 ********************************************************************************/

template <class T> class CMemPoolNode {
public:
    T *p_array;                     // + 0
    CMemPoolNode<T> *p_sub_node;    // + 4
public:
    CMemPoolNode(T *m_array)
    {
        this->p_array = m_array;
        this->p_sub_node = 0;
    }
};

/********************************************************************************
 * Pool Class
 ********************************************************************************/

template <class T, int L> class CMemPool {
public:
    CMemPoolNode<T> *p_node;        // + 0
    CMutexObject p_mutex_object;    // + 4
    long p_node_count;              // + 32
public:
    CMemPool()
    {
        this->p_node = 0;
        this->p_node_count = 0;
        //this->p_mutex_object = CMutexObject();
    }

    ~CMemPool()
    {
        CMemPoolNode<T> *m_temp_node;

        while(this->p_node)
        {
            m_temp_node = this->p_node;
            this->p_node = this->p_node->p_sub_node;

            if(m_temp_node->p_array)
              delete m_temp_node->p_array;

            m_temp_node->p_array = 0;
            delete m_temp_node;
        }

        this->p_node_count = 0;
    }

    T *Get(bool m_clear)
    {
        CMutex(&this->p_mutex_object, false); // true

        T *m_array;
        CMemPoolNode<T> *m_temp_node;

        if(this->p_node)
        {
            m_temp_node = this->p_node;
            this->p_node = this->p_node->p_sub_node;
            m_array = m_temp_node->p_array;
            delete m_temp_node;

            if(m_clear)
                memset(m_array, 0, L);

            --this->p_node_count;
        }
        else
        {
          m_array = (T *)malloc(L);

          if (m_clear)
              memset(m_array, 0, L);
        }

        return m_array;
    }

    void Set(T *m_array)
    {
         CMutex(&this->p_mutex_object, false); // true

         if(this->p_node_count > 9999)
         {
           if(m_array)
             delete m_array;
         }
         else
         {
             CMemPoolNode<T> *m_node = new CMemPoolNode<T>(m_array);
             m_node->p_sub_node = this->p_node;
             this->p_node = m_node;
             this->p_node_count++;
         }
    }

};

#endif
