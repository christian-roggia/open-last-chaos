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

#include "../doFunc.h"

void do_Event(CPC *a1, CNetMsg &a2)
{
    ;
}

/*// NOTE -> ASM Changed!

// ORIGINAL
int __cdecl do_Event(int a1, int a2)
{
  int result; // eax@1
  unsigned __int8 dest; // [sp+83h] [bp-1h]@1

  CNetMsg::MoveFirst(a2);
  CNetMsg::__rs(a2, &dest);
  result = dest;
  if ( dest == 1 && !gserver[452128] )
  {
    if ( *(_DWORD *)&gserver[16] )
      result = *(_DWORD *)&gserver[16];
  }
  return result;
}

// EDITED
void do_Event(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    __int64 v3; // qax@17
    __int64 v4; // qax@23
    char v5; // al@41
    char v6; // al@56
    int v7; // eax@87
    __int64 v8; // qax@105
    __int64 v9; // ST70_8@120
    signed int v10; // ST58_4@120
    signed int v11; // ST40_4@120
    const char *v12; // ST28_4@120
    const char *v13; // ST10_4@120
    const char *v14; // eax@120
    int v15; // eax@120
    int v16; // eax@120
    int v17; // eax@120
    int v18; // eax@120
    int v19; // eax@120
    int v20; // eax@120
    int v21; // eax@120
    int v22; // eax@120
    int v23; // eax@120
    int v24; // eax@120
    int v25; // eax@120
    int v26; // [sp+1Ch] [bp-68h]@113
    int v27; // [sp+30h] [bp-54h]@104
    int v28; // [sp+34h] [bp-50h]@103
    int v29; // [sp+38h] [bp-4Ch]@103
    char v30; // [sp+3Fh] [bp-45h]@101
    int v31; // [sp+40h] [bp-44h]@41
    int v32; // [sp+44h] [bp-40h]@32
    unsigned int v33; // [sp+48h] [bp-3Ch]@32
    int v34; // [sp+4Ch] [bp-38h]@23
    int v35; // [sp+60h] [bp-24h]@13
    int v36; // [sp+64h] [bp-20h]@9
    int v37; // [sp+68h] [bp-1Ch]@9
    int v38; // [sp+6Ch] [bp-18h]@9
    char v39; // [sp+82h] [bp-2h]@8
    unsigned __int8 dest; // [sp+83h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    CNetMsg::__rs(a2, &dest);
    result = dest;
    if(dest == 1)
    {
        if(!gserver.Unk452128 && dword_80FA490)
            result = dword_80FA490;
    }
    else
    {
        if(dest == 2)
        {
            result = CNetMsg::__rs(a2, &v39);
            if(v39 == 5)
            {
                CNetMsg::CNetMsg((int)&v38);
                if(CInventory::FindItem(a1 + 968, (int)&v37, (int)&v36, 507, 0, 0))
                {
                    v35 = CInventory::GetItem(a1 + 968, v37, v36);
                    if(v35)
                    {
                        v3 = CItem::Count(v35);
                        if(SHIDWORD(v3) > 0 || !HIDWORD(v3) && (_DWORD)v3)
                        {
                            CNetMsg::CNetMsg((int)&v34);
                            CInventory::Decrease(a1 + 968, v35, 1LL);
                            v4 = CItem::Count(v35);
                            if(SHIDWORD(v4) <= 0 && (HIDWORD(v4) || !(_DWORD)v4))
                            {
                                ItemDeleteMsg((int)&v34, v35);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v34);
                                CPC::RemoveItemFromQuickSlot(a1, v35);
                                CInventory::Remove(a1 + 968, v35, 1, 1);
                            }
                            else
                            {
                                ItemUpdateMsg((int)&v34, v35, -1LL);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v34);
                            }
                            v33 = GetRandom(1, 10000);
                            v32 = 0;
                            if((signed int)v33 > 800)
                            {
                                if((signed int)v33 > 900)
                                {
                                    if((signed int)v33 > 1000)
                                    {
                                        if((signed int)v33 > 1100)
                                        {
                                            if((signed int)v33 > 5300)
                                            {
                                                if((signed int)v33 > 9500)
                                                {
                                                    if((signed int)v33 <= 10000)
                                                    {
                                                        v32 = CItemList::CreateItem(gserver.Unk41208, 19, -1, 0, 0, 50000LL);
                                                        if(!v32)
                                                        {
                                                            CNetMsg::_CNetMsg((int)&v34, 2);
                                                            return CNetMsg::_CNetMsg((int)&v38, 2);
                                                        }
                                                        EventLattoMsg((int)&v38, 6, 6u, 0xFFFFFFFFu);
                                                    }
                                                }
                                                else
                                                {
                                                    v32 = CItemList::CreateItem(gserver.Unk41208, 511, -1, 0, 1, 1LL);
                                                    if(!v32)
                                                    {
                                                        CNetMsg::_CNetMsg((int)&v34, 2);
                                                        return CNetMsg::_CNetMsg((int)&v38, 2);
                                                    }
                                                    EventLattoMsg((int)&v38, 6, 5u, 0xFFFFFFFFu);
                                                }
                                            }
                                            else
                                            {
                                                v32 = CItemList::CreateItem(gserver.Unk41208, 510, -1, 0, 3, 1LL);
                                                if(!v32)
                                                {
                                                    CNetMsg::_CNetMsg((int)&v34, 2);
                                                    return CNetMsg::_CNetMsg((int)&v38, 2);
                                                }
                                                EventLattoMsg((int)&v38, 6, 4u, 0xFFFFFFFFu);
                                            }
                                        }
                                        else
                                        {
                                            v31 = -1;
                                            v6 = *(_BYTE *)(a1 + 477);
                                            if(v6 == 1)
                                            {
                                                v31 = 328;
                                            }
                                            else
                                            {
                                                if(v6 > 1)
                                                {
                                                    if(v6 == 2)
                                                    {
                                                        v31 = 347;
                                                    }
                                                    else
                                                    {
                                                        if(v6 == 3)
                                                            v31 = 370;
                                                    }
                                                }
                                                else
                                                {
                                                    if(!v6)
                                                        v31 = 313;
                                                }
                                            }
                                            v32 = CItemList::CreateItem(gserver.Unk41208, v31, -1, 0, 0, 1LL);
                                            if(!v32)
                                            {
                                                CNetMsg::_CNetMsg((int)&v34, 2);
                                                return CNetMsg::_CNetMsg((int)&v38, 2);
                                            }
                                            EventLattoMsg((int)&v38, 6, 3u, 0xFFFFFFFFu);
                                        }
                                    }
                                    else
                                    {
                                        v31 = -1;
                                        v5 = *(_BYTE *)(a1 + 477);
                                        if(v5 == 1)
                                        {
                                            v31 = 427;
                                        }
                                        else
                                        {
                                            if(v5 > 1)
                                            {
                                                if(v5 == 2)
                                                {
                                                    v31 = 462;
                                                }
                                                else
                                                {
                                                    if(v5 == 3)
                                                        v31 = 461;
                                                }
                                            }
                                            else
                                            {
                                                if(!v5)
                                                    v31 = 460;
                                            }
                                        }
                                        v32 = CItemList::CreateItem(gserver.Unk41208, v31, -1, 0, 0, 1LL);
                                        if(!v32)
                                        {
                                            CNetMsg::_CNetMsg((int)&v34, 2);
                                            return CNetMsg::_CNetMsg((int)&v38, 2);
                                        }
                                        EventLattoMsg((int)&v38, 6, 2u, 0xFFFFFFFFu);
                                    }
                                }
                                else
                                {
                                    v32 = CItemList::CreateItem(gserver.Unk41208, 85, -1, 0, 0, 1LL);
                                    if(!v32)
                                    {
                                        CNetMsg::_CNetMsg((int)&v34, 2);
                                        return CNetMsg::_CNetMsg((int)&v38, 2);
                                    }
                                    EventLattoMsg((int)&v38, 6, 1u, 0xFFFFFFFFu);
                                }
                            }
                            else
                            {
                                v32 = CItemList::CreateItem(gserver.Unk41208, 84, -1, 0, 26, 1LL);
                                if(!v32)
                                {
                                    CNetMsg::_CNetMsg((int)&v34, 2);
                                    return CNetMsg::_CNetMsg((int)&v38, 2);
                                }
                                EventLattoMsg((int)&v38, 6, 0, 0xFFFFFFFFu);
                            }
                            if(*(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) != 4
                                || *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) != 1)
                            {
                                v7 = a1 + 792;
                            }
                            else
                            {
                                if(*(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8))
                                {
                                    if(*(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) == 4
                                        && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8)
                                        && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) == 1)
                                        v7 = a1 + 968;
                                    else
                                        v7 = 0;
                                }
                                else
                                {
                                    v7 = a1 + 880;
                                }
                            }
                            v31 = v7;
                            if(v7)
                            {
                                v30 = 0;
                                if(CInventory::AddItem(v31, v32, a1, 1, 1, -1, -1))
                                {
                                    if(CItem::tab(v32) == -1)
                                    {
                                        v30 = 1;
                                        if(CInventory::FindItem(
                                                     v31,
                                                     (int)&v29,
                                                     (int)&v28,
                                                     *(_DWORD *)(v32 + 28),
                                                     *(_DWORD *)(v32 + 36),
                                                     *(_DWORD *)(v32 + 40)))
                                        {
                                            v27 = CInventory::GetItem(v31, v29, v28);
                                            if(v27)
                                            {
                                                v8 = CItem::Count(v32);
                                                ItemUpdateMsg((int)&v34, v27, v8);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        ItemAddMsg((int)&v34, v32);
                                        if(*(_DWORD *)(v32 + 28) == *(_DWORD *)dword_8104584 && !*(_DWORD *)(a1 + 1280))
                                            *(_DWORD *)(a1 + 1280) = v32;
                                    }
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v34);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                                    v9 = CItem::Count(v32);
                                    v10 = *(_DWORD *)(v32 + 40);
                                    v11 = *(_DWORD *)(v32 + 36);
                                    v12 = (const char *)(v32 + 44);
                                    v13 = (const char *)(*(_DWORD *)(v32 + 20) + 12);
                                    init((int)&v26, (int)"CHANGE_LUCKYBAG", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                    v14 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v26);
                                    v15 = (int)CLogBuffer::__ls(v14, v13);
                                    v16 = CLogBuffer::__ls(v15, (int (__cdecl *)(_DWORD))delim);
                                    v17 = (int)CLogBuffer::__ls((const char *)v16, v12);
                                    v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                                    v19 = (int)CLogBuffer::__ls((char *)v18, v11);
                                    v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                                    v21 = (int)CLogBuffer::__ls((char *)v20, v10);
                                    v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                                    v23 = (int)CLogBuffer::__ls((char *)v22, v9);
                                    v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
                                    v25 = (int)CLogBuffer::__ls((char *)v24, 0);
                                    CLogBuffer::__ls(v25, end);
                                    if(v30 && v32)
                                        (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v32 + 220) + 8))(v32, 3);
                                    CNetMsg::_CNetMsg((int)&v34, 2);
                                    result = CNetMsg::_CNetMsg((int)&v38, 2);
                                }
                                else
                                {
                                    v32 = CArea::DropItem(*(_DWORD *)(a1 + 412), v32, a1);
                                    if(v32)
                                    {
                                        CNetMsg::CNetMsg((int)&v26);
                                        ItemDropMsg((int)&v26, a1, v32);
                                        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v26, a1, 1, 4);
                                        *(_DWORD *)(v32 + 216) = *(_DWORD *)(a1 + 4);
                                        if(*(_DWORD *)(a1 + 768))
                                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                                        CNetMsg::_CNetMsg((int)&v26, 2);
                                        CNetMsg::_CNetMsg((int)&v34, 2);
                                        result = CNetMsg::_CNetMsg((int)&v38, 2);
                                    }
                                    else
                                    {
                                        CNetMsg::_CNetMsg((int)&v34, 2);
                                        result = CNetMsg::_CNetMsg((int)&v38, 2);
                                    }
                                }
                            }
                            else
                            {
                                CNetMsg::_CNetMsg((int)&v34, 2);
                                result = CNetMsg::_CNetMsg((int)&v38, 2);
                            }
                        }
                        else
                        {
                            EventLattoMsg((int)&v38, 6, 7u, 0xFFFFFFFFu);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                            result = CNetMsg::_CNetMsg((int)&v38, 2);
                        }
                    }
                    else
                    {
                        EventLattoMsg((int)&v38, 6, 7u, 0xFFFFFFFFu);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                        result = CNetMsg::_CNetMsg((int)&v38, 2);
                    }
                }
                else
                {
                    EventLattoMsg((int)&v38, 6, 7u, 0xFFFFFFFFu);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                    result = CNetMsg::_CNetMsg((int)&v38, 2);
                }
            }
        }
    }
    return result;
}

// DELETED JUMP AFTER if(dest == 1)
int __cdecl do_Event(int a1, int a2)
{
  int result; // eax@1
  __int64 v3; // qax@12
  __int64 v4; // qax@18
  char v5; // al@36
  char v6; // al@51
  int v7; // eax@82
  __int64 v8; // qax@100
  __int64 v9; // ST70_8@115
  signed int v10; // ST58_4@115
  signed int v11; // ST40_4@115
  const char *v12; // ST28_4@115
  const char *v13; // ST10_4@115
  const char *v14; // eax@115
  int v15; // eax@115
  int v16; // eax@115
  int v17; // eax@115
  int v18; // eax@115
  int v19; // eax@115
  int v20; // eax@115
  int v21; // eax@115
  int v22; // eax@115
  int v23; // eax@115
  int v24; // eax@115
  int v25; // eax@115
  int v26; // [sp+1Ch] [bp-68h]@108
  int v27; // [sp+30h] [bp-54h]@99
  int v28; // [sp+34h] [bp-50h]@98
  int v29; // [sp+38h] [bp-4Ch]@98
  char v30; // [sp+3Fh] [bp-45h]@96
  int v31; // [sp+40h] [bp-44h]@36
  int v32; // [sp+44h] [bp-40h]@27
  unsigned int v33; // [sp+48h] [bp-3Ch]@27
  int v34; // [sp+4Ch] [bp-38h]@18
  int v35; // [sp+60h] [bp-24h]@8
  int v36; // [sp+64h] [bp-20h]@4
  int v37; // [sp+68h] [bp-1Ch]@4
  int v38; // [sp+6Ch] [bp-18h]@4
  char v39; // [sp+82h] [bp-2h]@3
  unsigned __int8 dest; // [sp+83h] [bp-1h]@1

  CNetMsg::MoveFirst(a2);
  CNetMsg::__rs(a2, &dest);
  result = dest;
  if ( dest == 1 || dest == 2 )
  {
    result = CNetMsg::__rs(a2, &v39);
    if ( v39 == 5 )
    {
      CNetMsg::CNetMsg((int)&v38);
      if ( CInventory::FindItem(a1 + 968, (int)&v37, (int)&v36, 507, 0, 0) )
      {
        v35 = CInventory::GetItem(a1 + 968, v37, v36);
        if ( v35 )
        {
          v3 = CItem::Count(v35);
          if ( SHIDWORD(v3) > 0 || !HIDWORD(v3) && (_DWORD)v3 )
          {
            CNetMsg::CNetMsg((int)&v34);
            CInventory::Decrease(a1 + 968, v35, 1LL);
            v4 = CItem::Count(v35);
            if ( SHIDWORD(v4) <= 0 && (HIDWORD(v4) || !(_DWORD)v4) )
            {
              ItemDeleteMsg((int)&v34, v35);
              if ( *(_DWORD *)(a1 + 768) )
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v34);
              CPC::RemoveItemFromQuickSlot(a1, v35);
              CInventory::Remove(a1 + 968, v35, 1, 1);
            }
            else
            {
              ItemUpdateMsg((int)&v34, v35, -1LL);
              if ( *(_DWORD *)(a1 + 768) )
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v34);
            }
            v33 = GetRandom(1, 10000);
            v32 = 0;
            if ( (signed int)v33 > 800 )
            {
              if ( (signed int)v33 > 900 )
              {
                if ( (signed int)v33 > 1000 )
                {
                  if ( (signed int)v33 > 1100 )
                  {
                    if ( (signed int)v33 > 5300 )
                    {
                      if ( (signed int)v33 > 9500 )
                      {
                        if ( (signed int)v33 <= 10000 )
                        {
                          v32 = CItemList::CreateItem(gserver.Unk41208, 19, -1, 0, 0, 50000LL);
                          if ( !v32 )
                          {
                            CNetMsg::_CNetMsg((int)&v34, 2);
                            return CNetMsg::_CNetMsg((int)&v38, 2);
                          }
                          EventLattoMsg((int)&v38, 6, 6u, 0xFFFFFFFFu);
                        }
                      }
                      else
                      {
                        v32 = CItemList::CreateItem(gserver.Unk41208, 511, -1, 0, 1, 1LL);
                        if ( !v32 )
                        {
                          CNetMsg::_CNetMsg((int)&v34, 2);
                          return CNetMsg::_CNetMsg((int)&v38, 2);
                        }
                        EventLattoMsg((int)&v38, 6, 5u, 0xFFFFFFFFu);
                      }
                    }
                    else
                    {
                      v32 = CItemList::CreateItem(gserver.Unk41208, 510, -1, 0, 3, 1LL);
                      if ( !v32 )
                      {
                        CNetMsg::_CNetMsg((int)&v34, 2);
                        return CNetMsg::_CNetMsg((int)&v38, 2);
                      }
                      EventLattoMsg((int)&v38, 6, 4u, 0xFFFFFFFFu);
                    }
                  }
                  else
                  {
                    v31 = -1;
                    v6 = *(_BYTE *)(a1 + 477);
                    if ( v6 == 1 )
                    {
                      v31 = 328;
                    }
                    else
                    {
                      if ( v6 > 1 )
                      {
                        if ( v6 == 2 )
                        {
                          v31 = 347;
                        }
                        else
                        {
                          if ( v6 == 3 )
                            v31 = 370;
                        }
                      }
                      else
                      {
                        if ( !v6 )
                          v31 = 313;
                      }
                    }
                    v32 = CItemList::CreateItem(gserver.Unk41208, v31, -1, 0, 0, 1LL);
                    if ( !v32 )
                    {
                      CNetMsg::_CNetMsg((int)&v34, 2);
                      return CNetMsg::_CNetMsg((int)&v38, 2);
                    }
                    EventLattoMsg((int)&v38, 6, 3u, 0xFFFFFFFFu);
                  }
                }
                else
                {
                  v31 = -1;
                  v5 = *(_BYTE *)(a1 + 477);
                  if ( v5 == 1 )
                  {
                    v31 = 427;
                  }
                  else
                  {
                    if ( v5 > 1 )
                    {
                      if ( v5 == 2 )
                      {
                        v31 = 462;
                      }
                      else
                      {
                        if ( v5 == 3 )
                          v31 = 461;
                      }
                    }
                    else
                    {
                      if ( !v5 )
                        v31 = 460;
                    }
                  }
                  v32 = CItemList::CreateItem(gserver.Unk41208, v31, -1, 0, 0, 1LL);
                  if ( !v32 )
                  {
                    CNetMsg::_CNetMsg((int)&v34, 2);
                    return CNetMsg::_CNetMsg((int)&v38, 2);
                  }
                  EventLattoMsg((int)&v38, 6, 2u, 0xFFFFFFFFu);
                }
              }
              else
              {
                v32 = CItemList::CreateItem(gserver.Unk41208, 85, -1, 0, 0, 1LL);
                if ( !v32 )
                {
                  CNetMsg::_CNetMsg((int)&v34, 2);
                  return CNetMsg::_CNetMsg((int)&v38, 2);
                }
                EventLattoMsg((int)&v38, 6, 1u, 0xFFFFFFFFu);
              }
            }
            else
            {
              v32 = CItemList::CreateItem(gserver.Unk41208, 84, -1, 0, 26, 1LL);
              if ( !v32 )
              {
                CNetMsg::_CNetMsg((int)&v34, 2);
                return CNetMsg::_CNetMsg((int)&v38, 2);
              }
              EventLattoMsg((int)&v38, 6, 0, 0xFFFFFFFFu);
            }
            if ( *(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) != 4
              || *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) != 1 )
            {
              v7 = a1 + 792;
            }
            else
            {
              if ( *(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) )
              {
                if ( *(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) == 4
                  && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8)
                  && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) == 1 )
                  v7 = a1 + 968;
                else
                  v7 = 0;
              }
              else
              {
                v7 = a1 + 880;
              }
            }
            v31 = v7;
            if ( v7 )
            {
              v30 = 0;
              if ( CInventory::AddItem(v31, v32, a1, 1, 1, -1, -1) )
              {
                if ( CItem::tab(v32) == -1 )
                {
                  v30 = 1;
                  if ( CInventory::FindItem(
                         v31,
                         (int)&v29,
                         (int)&v28,
                         *(_DWORD *)(v32 + 28),
                         *(_DWORD *)(v32 + 36),
                         *(_DWORD *)(v32 + 40)) )
                  {
                    v27 = CInventory::GetItem(v31, v29, v28);
                    if ( v27 )
                    {
                      v8 = CItem::Count(v32);
                      ItemUpdateMsg((int)&v34, v27, v8);
                    }
                  }
                }
                else
                {
                  ItemAddMsg((int)&v34, v32);
                  if ( *(_DWORD *)(v32 + 28) == **(_DWORD **)&gserver[41220] && !*(_DWORD *)(a1 + 1280) )
                    *(_DWORD *)(a1 + 1280) = v32;
                }
                if ( *(_DWORD *)(a1 + 768) )
                  CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v34);
                if ( *(_DWORD *)(a1 + 768) )
                  CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                v9 = CItem::Count(v32);
                v10 = *(_DWORD *)(v32 + 40);
                v11 = *(_DWORD *)(v32 + 36);
                v12 = (const char *)(v32 + 44);
                v13 = (const char *)(*(_DWORD *)(v32 + 20) + 12);
                init((int)&v26, (int)"CHANGE_LUCKYBAG", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                v14 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v26);
                v15 = (int)CLogBuffer::__ls(v14, v13);
                v16 = CLogBuffer::__ls(v15, (int (__cdecl *)(_DWORD))delim);
                v17 = (int)CLogBuffer::__ls((const char *)v16, v12);
                v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                v19 = (int)CLogBuffer::__ls((char *)v18, v11);
                v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                v21 = (int)CLogBuffer::__ls((char *)v20, v10);
                v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                v23 = (int)CLogBuffer::__ls((char *)v22, v9);
                v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
                v25 = (int)CLogBuffer::__ls((char *)v24, 0);
                CLogBuffer::__ls(v25, end);
                if ( v30 && v32 )
                  (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v32 + 220) + 8))(v32, 3);
                CNetMsg::_CNetMsg((int)&v34, 2);
                result = CNetMsg::_CNetMsg((int)&v38, 2);
              }
              else
              {
                v32 = CArea::DropItem(*(_DWORD *)(a1 + 412), v32, a1);
                if ( v32 )
                {
                  CNetMsg::CNetMsg((int)&v26);
                  ItemDropMsg((int)&v26, a1, v32);
                  CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v26, a1, 1, 4);
                  *(_DWORD *)(v32 + 216) = *(_DWORD *)(a1 + 4);
                  if ( *(_DWORD *)(a1 + 768) )
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
                  CNetMsg::_CNetMsg((int)&v26, 2);
                  CNetMsg::_CNetMsg((int)&v34, 2);
                  result = CNetMsg::_CNetMsg((int)&v38, 2);
                }
                else
                {
                  CNetMsg::_CNetMsg((int)&v34, 2);
                  result = CNetMsg::_CNetMsg((int)&v38, 2);
                }
              }
            }
            else
            {
              CNetMsg::_CNetMsg((int)&v34, 2);
              result = CNetMsg::_CNetMsg((int)&v38, 2);
            }
          }
          else
          {
            EventLattoMsg((int)&v38, 6, 7u, 0xFFFFFFFFu);
            if ( *(_DWORD *)(a1 + 768) )
              CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
            result = CNetMsg::_CNetMsg((int)&v38, 2);
          }
        }
        else
        {
          EventLattoMsg((int)&v38, 6, 7u, 0xFFFFFFFFu);
          if ( *(_DWORD *)(a1 + 768) )
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
          result = CNetMsg::_CNetMsg((int)&v38, 2);
        }
      }
      else
      {
        EventLattoMsg((int)&v38, 6, 7u, 0xFFFFFFFFu);
        if ( *(_DWORD *)(a1 + 768) )
          CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v38);
        result = CNetMsg::_CNetMsg((int)&v38, 2);
      }
    }
  }
  return result;
}
*/
