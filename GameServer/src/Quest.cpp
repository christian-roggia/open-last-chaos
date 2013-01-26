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

#include "Quest.h"
#include "Server.h"

CQuestProto::CQuestProto(void)
{
    this->Unk0 = 0;
    this->Unk4 = -1;
    this->Unk8 = -1;
    this->Unk12 = -1;
    this->Unk16 = 0;
    this->Unk20 = -1;
    this->Unk24 = 1;
    this->Unk28 = 60;
    this->Unk32 = -1;
    memset(this->Unk36, -1,  20);
    memset(this->Unk56, 0,   20);
    memset(this->Unk76, -1,  12);
    memset(this->Unk88, 0,   12);
    memset(this->Unk100, 0,  12);
    memset(this->Unk112, 0,  48);
    memset(this->Unk160, -1, 20);
    memset(this->Unk180, 0,  20);
    memset(this->Unk200, 0,  20);
}

CQuestProtoList::CQuestProtoList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
}

CQuestProtoList::~CQuestProtoList()
{
    if(this->Unk0 && this->Unk0)
        delete [] this->Unk0;
    this->Unk0 = 0;
}

bool CQuestProtoList::Load(void)
{
    CDBCmd v11;

    v11.Init(&gserver.Unk41816);
    v11.SetQuery("SELECT * FROM t_quest WHERE a_enable=1 ORDER BY a_index");

    if(!v11.Open())
        return false;

    this->Unk4 = v11.AffectedRows;
    this->Unk0 = new CQuestProto[this->Unk4]; // CHECK THIS!!!

    if(v11.MoveFirst())
    {
        for(int i = 0; i < this->Unk4; ++i)
        {
            v11.GetRec("a_index", this->Unk0[i].Unk0);
            v11.GetRec("a_type1", this->Unk0[i].Unk4);
            v11.GetRec("a_type2", this->Unk0[i].Unk8);
            v11.GetRec("a_start_type", this->Unk0[i].Unk12);
            v11.GetRec("a_start_data", this->Unk0[i].Unk16);
            v11.GetRec("a_prize_npc", this->Unk0[i].Unk20);
            v11.GetRec("a_need_min_level", this->Unk0[i].Unk24);
            v11.GetRec("a_need_max_level", this->Unk0[i].Unk28);
            v11.GetRec("a_need_job", this->Unk0[i].Unk32);

            for(int j = 0; j <= 4; ++j)
            {
                strcpy(g_buf, "a_need_item");
                IntCat(g_buf, j, 0);
                v11.GetRec(g_buf, this->Unk0[i].Unk36[j]);
                strcpy(g_buf, "a_need_item_count");
                IntCat(g_buf, j, 0);
                v11.GetRec(g_buf, this->Unk0[i].Unk56[j]);
            }

            for(int k = 0; k <= 2; ++k)
            {
                strcpy(g_buf, "a_condition");
                IntCat(g_buf, k, 0);
                strcat(g_buf, "_type");
                v11.GetRec(g_buf, this->Unk0[i].Unk76[k]);
                strcpy(g_buf, "a_condition");
                IntCat(g_buf, k, 0);
                strcat(g_buf, "_index");
                v11.GetRec(g_buf, this->Unk0[i].Unk88[k]);
                strcpy(g_buf, "a_condition");
                IntCat(g_buf, k, 0);
                strcat(g_buf, "_num");
                v11.GetRec(g_buf, this->Unk0[i].Unk100[k]);

                for(int l = 0; l <= 3; ++l)
                {
                    strcpy(g_buf, "a_condition");
                    IntCat(g_buf, k, 0);
                    strcat(g_buf, "_data");
                    IntCat(g_buf, l, 0);
                    v11.GetRec(g_buf, this->Unk0[i].Unk112[k][l]);
                }
            }

            for(int m = 0; m <= 4; ++m)
            {
                strcpy(g_buf, "a_prize_type");
                IntCat(g_buf, m, 0);
                v11.GetRec(g_buf, this->Unk0[i].Unk160[m]);
                strcpy(g_buf, "a_prize_index");
                IntCat(g_buf, m, 0);
                v11.GetRec(g_buf, this->Unk0[i].Unk180[m]);
                strcpy(g_buf, "a_prize_data");
                IntCat(g_buf, m, 0);
                v11.GetRec(g_buf, this->Unk0[i].Unk200[m]);
            }
            v11.MoveNext();
        }
    }

    return true;
}

CQuestProto *CQuestProtoList::FindProto(int a2)
{
    CQuestProto key;//CQuestProto key = a2;
    key.Unk0 = a2;

    return (CQuestProto *)bsearch(&key, this->Unk0, this->Unk4, 220, CQuestProtoList::CompIndex);
}

int CQuestProtoList::CompIndex(void const *a1, void const *a2)
{
    return ((CQuestProto *)a1)->Unk0 - ((CQuestProto *)a2)->Unk0;
}

CQuest *CQuestProtoList::Create(int a2)
{
    CQuestProto *v6 = this->FindProto(a2);

    return v6 ? new CQuest(v6) : 0;
}

CQuest::CQuest(CQuestProto *a2)
{
    this->Unk0 = a2;
    memset(this->Unk4, 0, 12);
}

//*************** TODO ****************

//long off_80D0EA8 = {0x08088A30, 0x08089125, 0x08088BF5, 0x08088353,
//                    0x08088353, 0x08088353, 0x08089985, 0x08089985};
// 0x08088A30 = jmp loc_80891D0
//long off_80D0EA8 = {L_080891D0, 0x08089125, L_08088BF5, 0x08088353,
//                    0x08088353, 0x08088353, 0x08089985, 0x08089985};

int CQuest::QuestUpdateData(CPC *a2, CNPC *a3)
{
    /*char s[3]; // [sp+70h] [bp-10h]@4
    int v4; // [sp+74h] [bp-Ch]@1

    v4 = a2->Unk1900.FindQuest(this->Unk0);
    if(v4 >= 0)
    {
        if(!a2->Unk1900.Unk50[v4])
        {
            memset(s, 0, 3);
            if(this->Unk4 <= 7)
                JUMPOUT(__CS__, off_80D0EA8[*(_DWORD *)(v4 + 4)]);
        }
    }*/
    // DIFFICULT TO REWRITE
    return 0;
}

/*int *__cdecl CQuest::QuestUpdateData(int **a1, int a2, int a3)
{
  int *result; // eax@1
  unsigned int v4; // eax@18
  int v5; // eax@26
  __int64 v6; // qax@44
  __int64 v7; // ST70_8@59
  signed int v8; // ST58_4@59
  signed int v9; // ST40_4@59
  const char *v10; // ST28_4@59
  const char *v11; // ST10_4@59
  const char *v12; // eax@59
  int v13; // eax@59
  int v14; // eax@59
  int v15; // eax@59
  int v16; // eax@59
  int v17; // eax@59
  int v18; // eax@59
  int v19; // eax@59
  int v20; // eax@59
  int v21; // eax@59
  int v22; // eax@59
  int v23; // eax@59
  signed int v24; // ST88_4@74
  const char *v25; // eax@74
  int v26; // eax@74
  int v27; // eax@74
  int v28; // eax@74
  int v29; // [sp+1Ch] [bp-64h]@59
  int v30; // [sp+2Ch] [bp-54h]@52
  int v31; // [sp+40h] [bp-40h]@43
  int v32; // [sp+44h] [bp-3Ch]@42
  int v33; // [sp+48h] [bp-38h]@42
  char v34; // [sp+4Fh] [bp-31h]@40
  int v35; // [sp+50h] [bp-30h]@38
  int v36; // [sp+54h] [bp-2Ch]@21
  int v37; // [sp+68h] [bp-18h]@18
  char v38; // [sp+6Fh] [bp-11h]@10
  char s[4]; // [sp+70h] [bp-10h]@4
  int *v40; // [sp+74h] [bp-Ch]@1
  int j; // [sp+78h] [bp-8h]@10
  int i; // [sp+7Ch] [bp-4h]@5

  result = (int *)CQuestList::FindQuest(a2 + 1900, **a1);
  v40 = result;
  if ( (signed int)result >= 0 )
  {
    result = v40;
    if ( !*((_BYTE *)v40 + a2 + 1950) )
    {
      memset(s, 0, 3u);
      result = *a1;
      if ( (unsigned int)(*a1)[1] <= 7 )
      {
L_8088BF5:
        for ( i = 0; i <= 2; ++i )
        {
          if ( (*a1)[i + 19] == -1 )
          {
            s[i] = 1;
          }
          else
          {
            result = *a1 + 19;
            if ( result[i] == 1 )
            {
              v38 = 0;
              for ( j = 0; j <= 2; ++j )
              {
                result = (int *)*(&(*a1)[4 * i + 28] + j);
                if ( result == **(int ***)(a3 + 464) )
                {
                  v38 = 1;
                  break;
                }
              }
              if ( !v38 )
                return result;
              if ( (signed int)a1[i + 1] < (*a1)[i + 25] )
              {
                v37 = 0;
                v4 = GetRandom(1, 10000);
                if ( (signed int)v4 <= (*a1)[4 * i + 31] )
                  v37 = CItemList::CreateItem(gserver.Unk41208, (*a1)[i + 22], -1, 0, 0, 1LL);
                if ( v37 )
                {
                  CNetMsg::CNetMsg((int)&v36);
                  if ( *(_DWORD *)(*(_DWORD *)(v37 + 20) + 4) != 4
                    || *(_DWORD *)(*(_DWORD *)(v37 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v37 + 20) + 8) != 1 )
                  {
                    v5 = a2 + 792;
                  }
                  else
                  {
                    if ( *(_DWORD *)(*(_DWORD *)(v37 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v37 + 20) + 8) )
                    {
                      if ( *(_DWORD *)(*(_DWORD *)(v37 + 20) + 4) == 4
                        && *(_DWORD *)(*(_DWORD *)(v37 + 20) + 8)
                        && *(_DWORD *)(*(_DWORD *)(v37 + 20) + 8) == 1 )
                        v5 = a2 + 968;
                      else
                        v5 = 0;
                    }
                    else
                    {
                      v5 = a2 + 880;
                    }
                  }
                  v35 = v5;
                  if ( v5 )
                  {
                    v34 = 0;
                    if ( !CInventory::AddItem(v35, v37, a2, 1, 1, -1, -1) )
                    {
                      if ( v37 )
                        (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v37 + 220) + 8))(v37, 3);
                      v37 = 0;
                      CNetMsg::CNetMsg((int)&v30);
                      SysFullInventoryMsg((int)&v30, *(_BYTE *)(v35 + 4));
                      if ( *(_DWORD *)(a2 + 768) )
                        CDescriptor::WriteToOutput(*(_DWORD *)(a2 + 768), (int)&v30);
                      CNetMsg::_CNetMsg((int)&v30, 2);
                      return (int *)CNetMsg::_CNetMsg((int)&v36, 2);
                    }
                    if ( CItem::tab(v37) == -1 )
                    {
                      v34 = 1;
                      if ( CInventory::FindItem(
                             v35,
                             (int)&v33,
                             (int)&v32,
                             *(_DWORD *)(v37 + 28),
                             *(_DWORD *)(v37 + 36),
                             *(_DWORD *)(v37 + 40)) )
                      {
                        v31 = CInventory::GetItem(v35, v33, v32);
                        if ( v31 )
                        {
                          v6 = CItem::Count(v37);
                          ItemUpdateMsg((int)&v36, v31, v6);
                        }
                      }
                    }
                    else
                    {
                      ItemAddMsg((int)&v36, v37);
                      if ( *(_DWORD *)(v37 + 28) == **(_DWORD **)&gserver[41220] && !*(_DWORD *)(a2 + 1280) )
                        *(_DWORD *)(a2 + 1280) = v37;
                    }
                    a1[i + 1] = (int *)((char *)a1[i + 1] + 1);
                    s[i] = 0;
                    if ( *(_DWORD *)(a2 + 768) )
                      CDescriptor::WriteToOutput(*(_DWORD *)(a2 + 768), (int)&v36);
                    CNetMsg::CNetMsg((int)&v30);
                    QuestStatusMsg((int)&v30, *(uint32_t ***)(4 * (_DWORD)v40 + a2 + 1900));
                    if ( *(_DWORD *)(a2 + 768) )
                      CDescriptor::WriteToOutput(*(_DWORD *)(a2 + 768), (int)&v30);
                    v7 = CItem::Count(v37);
                    v8 = *(_DWORD *)(v37 + 40);
                    v9 = *(_DWORD *)(v37 + 36);
                    v10 = (const char *)(v37 + 44);
                    v11 = (const char *)(*(_DWORD *)(v37 + 20) + 12);
                    init((int)&v29, (int)"ITEM_PICK", a2 + 8, *(_DWORD *)(a2 + 768) + 4);
                    v12 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v29);
                    v13 = (int)CLogBuffer::__ls(v12, v11);
                    v14 = CLogBuffer::__ls(v13, (int (__cdecl *)(_DWORD))delim);
                    v15 = (int)CLogBuffer::__ls((const char *)v14, v10);
                    v16 = CLogBuffer::__ls(v15, (int (__cdecl *)(_DWORD))delim);
                    v17 = (int)CLogBuffer::__ls((char *)v16, v9);
                    v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                    v19 = (int)CLogBuffer::__ls((char *)v18, v8);
                    v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                    v21 = (int)CLogBuffer::__ls((char *)v20, v7);
                    v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                    v23 = (int)CLogBuffer::__ls((char *)v22, 0);
                    CLogBuffer::__ls(v23, end);
                    if ( v34 && v37 )
                      (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v37 + 220) + 8))(v37, 3);
                    if ( a1[i + 1] == (int *)(*a1)[i + 25] )
                    {
                      s[i] = 1;
                      CNetMsg::_CNetMsg((int)&v30, 2);
                      CNetMsg::_CNetMsg((int)&v36, 2);
                    }
                    else
                    {
                      if ( (signed int)a1[i + 1] >= (*a1)[i + 25] )
                      {
                        CNetMsg::_CNetMsg((int)&v30, 2);
                        CNetMsg::_CNetMsg((int)&v36, 2);
                      }
                      else
                      {
                        s[i] = 0;
                        CNetMsg::_CNetMsg((int)&v30, 2);
                        CNetMsg::_CNetMsg((int)&v36, 2);
                      }
                    }
                  }
                  else
                  {
                    CNetMsg::_CNetMsg((int)&v36, 2);
                  }
                }
              }
              else
              {
                s[i] = 1;
              }
            }
          }
        }
L_080891D0:
        for ( i = 0; i <= 2; ++i )
        {
          result = (int *)s;
          if ( !s[i] )
            return result;
        }
        result = v40;
        if ( !*((_BYTE *)v40 + a2 + 1950) )
        {
          v24 = ***(_DWORD ***)(4 * (_DWORD)v40 + a2 + 1900);
          init((int)&v29, (int)"QUEST COMPLETE");
          v25 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v29);
          v26 = (int)CLogBuffer::__ls(v25, (const char *)(a2 + 8));
          v27 = CLogBuffer::__ls(v26, (int (__cdecl *)(_DWORD))delim);
          v28 = (int)CLogBuffer::__ls((char *)v27, v24);
          CLogBuffer::__ls(v28, end);
          CNetMsg::CNetMsg((int)&v30);
          QuestCompleteMsg((int)&v30, *(uint32_t ***)(4 * (_DWORD)v40 + a2 + 1900));
          if ( *(_DWORD *)(a2 + 768) )
            CDescriptor::WriteToOutput(*(_DWORD *)(a2 + 768), (int)&v30);
          *((_BYTE *)v40 + a2 + 1950) = 1;
          result = (int *)CNetMsg::_CNetMsg((int)&v30, 2);
        }
      }
    }
  }
  return result;
}*/

CQuestList::CQuestList(void)
{
    memset(this->Unk0, 0, 40);
    memset(this->Unk40, 0, 10);
    memset(this->Unk50, 0, 10);
    this->Unk60  = 0;
    memset(this->Unk64, -1, 400);
    this->Unk464 = 0;
}

CQuestList::~CQuestList()
{
    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk0[i])
        {
            delete this->Unk0[i];
            this->Unk0[i] = 0;
        }
    }
}

int CQuestList::AddQuest(CQuest *a2)
{
    for(int i = 0; i <= 9; ++i)
    {
        if(!this->Unk0[i])
        {
            this->Unk0[i] = a2;
            ++this->Unk60;
            this->Unk50[i] = 0;
            this->Unk40[i] = 0;

            return i;
        }
    }

    return -1;
}

int CQuestList::FindQuest(int a2)
{
    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk0[i] && this->Unk0[i]->Unk0->Unk0 == a2 && this->Unk40[i])
        return i;
    }

    return -1;
}

bool CQuestList::DelQuest(CPC *a2, CQuest *a3)
{
    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk0[i] && this->Unk0[i]->Unk0->Unk0 == a3->Unk0->Unk0)
        {
            delete this->Unk0[i];
            this->Unk0[i] = 0;
            --this->Unk60;
            this->Unk50[i] = 0;
            this->Unk40[i] = 0;

            return true;
        }
    }

    return false;
}

char *CQuestList::GetIndexString(char *dest)
{
    *dest = 0;

    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk0[i] && this->Unk40[i] && this->Unk0[i]->Unk0->Unk4 != 4)
        {
            if(this->Unk0[i]->Unk0->Unk4 != 3)
                IntCat(dest, this->Unk0[i]->Unk0->Unk0, true);
        }
    }

    return dest;
}

char *CQuestList::GetValueString(char *dest)
{
    *dest = 0;

    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk0[i] && this->Unk40[i] && this->Unk0[i]->Unk0->Unk4 != 4 && this->Unk0[i]->Unk0->Unk4 != 3)
        {
            for(int j = 0; j <= 2; ++j)
                ;//IntCat(dest, *(_DWORD *)(this->Unk0[i]->Unk4[j] + 4), true);
        }
    }

    return dest;
}

char *CQuestList::GetCompleteIndexString(char *dest)
{
    *dest = 0;

    for(int i = 0; i <= 99 && this->Unk64[i] != -1; ++i)
        IntCat(dest, this->Unk64[i], true);

    return dest;
}

void CQuestList::CheckComplete(CPC *a2)
{
    char v5, s[3];

    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk0[i])
        {
            if(this->Unk40[i])
            {
                if((this->Unk0[i]->Unk0->Unk0 + 1) <= 7)
                {
                    v5 = 1;
                    memset(s, 0, 3);

                    for(int j = 0; j <= 2; ++j)
                    {
                        if(this->Unk0[i]->Unk0->Unk76[j] == -1)
                        {
                            s[j] = 1;
                        }
                        else
                        {
                            //if(*(void **)(this->Unk0[i]->Unk4[j] + 4) >= this->Unk0[i]->Unk0->Unk100[j])
                                s[j] = 1;
                        }
                    }

                    for(int j = 0; j <= 2; ++j)
                    {
                        if(!s[j])
                            v5 = 0;
                    }

                    if(v5)
                    {
                        CNetMsg v4;

                        //QuestCompleteMsg(v4, this->Unk0[i]); // *(uint32_t ***)(4 * i + a1)
                        if(a2->Unk768)
                            a2->Unk768->WriteToOutput(v4);
                        this->Unk50[i] = 1;
                    }
                }
            }
        }
    }
}
