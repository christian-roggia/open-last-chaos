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
#include "../Server.h"

void do_Stash(CPC *a1, CNetMsg &a2)
{
    char dest = -1; // [sp+13h] [bp-15h]@10

    if(a1->Unk76 <= 0 || gserver.Unk41248 - a1->Unk788 <= 29 || a1->Unk424 || a1->IsSetPlayerState(4) || a1->Unk1328 || a1 ->Unk1324)
    {
        CNetMsg v4;

        StashErrorMsg(v4, 1);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v4);

        return;
    }

    a2.MoveFirst();
    a2.__rs(dest); // (char)

    switch(dest)
    {
        case 1:
            do_StashIsSetPassword(a1, a2);
            break;
        case 2:
            do_StashListReq(a1, a2);
            break;
        case 4:
            do_StashKeep(a1, a2);
            break;
        case 6:
            do_StashTake(a1, a2);
            break;
        case 8:
            do_StashChangePassword(a1, a2);
            break;
        case 10:
            do_StashSeal(a1, a2);
            break;
        default:
            break;
    }
}

void do_StashIsSetPassword(CPC *a1, CNetMsg &a2)
{
    CNetMsg v3;

    ConnStashState(v3, a1->Unk768->Unk0, a1->Unk4);

    if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
    {
        CNetMsg v2;

        StashErrorMsg(v2, 1);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v2);

        return;
    }

    if(gserver.Unk16)
        gserver.Unk16->WriteToOutput(v3);

    a1->Unk1260.Init();
}

void do_StashListReq(CPC *a1, CNetMsg &a2)
{
    if(a1->Unk1260.MsgType) // CHECK
    {
        CNetMsg v4;

        StashErrorMsg(v4, 2);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v4);
    }
    else
    {
        g_buf[0] = 0;
        a2.__rs(g_buf);
        TrimString(g_buf);

        CNetMsg v4;

        ConnStashCheckPassword(v4, a1->Unk768->Unk0, a1->Unk4, g_buf);

        if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
        {
            CNetMsg v3;

            StashErrorMsg(v3, 1);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v3);
        }
        else
        {
            if(gserver.Unk16)
                gserver.Unk16->WriteToOutput(v4);

            a1->Unk1260.Init(a2);
        }
    }
}

void do_StashListReq_real(CPC *a1)
{
    CItem *v3; // [sp+24h] [bp-D4h]@3
    int v5; // [sp+2Ch] [bp-CCh]@1
    CItem *v6[50]; // [sp+30h] [bp-C8h]@4

    v5 = 0;
    for(int i = 0; i <= 49; ++i)
    {
        v3 = a1->Unk1056.item(i);

        if(v3)
            v6[v5++] = v3;
    }

    CNetMsg v2;

    if(v5)
    {
        for(int i = 0; i < v5; ++i)
        {
            StashListRepMsg(v2, v6[i], i == 0, i == v5 - 1, 0);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v2);
        }
    }
    else
    {
        StashListRepMsg(v2, 0, 1, 1, 1);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v2);
    }
}

void do_StashKeep(CPC *a1, CNetMsg &a2)
{
    if(a1->Unk1260.MsgType)
    {
        CNetMsg v4;

        StashErrorMsg(v4, 2);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v4);
    }
    else
    {
        g_buf[0] = 0;
        a2.__rs(g_buf);
        TrimString(g_buf);

        CNetMsg v4;

        ConnStashCheckPassword(v4, a1->Unk768->Unk0, a1->Unk4, g_buf);

        if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
        {
            CNetMsg v3;

            StashErrorMsg(v3, 1);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v3);
        }
        else
        {
            if(gserver.Unk16)
                gserver.Unk16->WriteToOutput(v4);

            a1->Unk1260.Init(a2);
        }
    }
}

/*void do_StashKeep_real(CPC *a1)
{
    int v1; // eax@2
    int v2; // eax@9
    int v3; // eax@9
    int v4; // eax@9
    __int64 v5; // qax@17
    int v6; // eax@26
    int v7; // edi@26
    unsigned int v8; // eax@29
    unsigned int v9; // esi@29
    unsigned __int64 v10; // qax@29
    __int64 v11; // STA0_8@29
    __int64 v12; // qax@35
    __int64 v13; // qax@43
    int v14; // eax@51
    signed __int64 v15; // ST70_8@55
    const char *v16; // eax@55
    int v17; // eax@55
    int v18; // eax@55
    int v19; // eax@55
    signed int v20; // ST7C_4@57
    signed __int64 v21; // ST64_8@57
    signed int v22; // ST4C_4@57
    signed int v23; // ST34_4@57
    const char *v24; // ST1C_4@57
    int v25; // eax@57
    int v26; // eax@57
    int v27; // eax@57
    int v28; // eax@57
    int v29; // eax@57
    int v30; // eax@57
    int v31; // eax@57
    int v32; // eax@57
    int v33; // eax@57
    int v34; // eax@57
    signed int v35; // ST7C_4@60
    signed int v36; // ST64_4@60
    int v37; // eax@60
    int v38; // eax@60
    int v39; // eax@60
    __int64 v40; // ST70_8@70
    __int64 v41; // qax@77
    int v43; // [sp+2Ch] [bp-118h]@55
    int v44[10]; // [sp+3Ch] [bp-108h]@50
    char v45[12]; // [sp+64h] [bp-E0h]@48
    char v46[12]; // [sp+70h] [bp-D4h]@44
    int j; // [sp+7Ch] [bp-C8h]@20
    int k; // [sp+80h] [bp-C4h]@15
    __int64 dest; // [sp+84h] [bp-C0h]@9
    int v50; // [sp+8Ch] [bp-B8h]@9
    __int16 v51; // [sp+92h] [bp-B2h]@9
    int i; // [sp+94h] [bp-B0h]@7
    __int64 v53; // [sp+98h] [bp-ACh]@7
    __int64 v54; // [sp+A0h] [bp-A4h]@7
    int v55[20]; // [sp+A8h] [bp-9Ch]@26
    char v56[43]; // [sp+F8h] [bp-4Ch]@22
    char v57; // [sp+123h] [bp-21h]@7
    uint32_t src; // [sp+124h] [bp-20h]@2
    char v59; // [sp+12Bh] [bp-19h]@1
    int v60; // [sp+12Ch] [bp-18h]@1
    int v61; // [sp+130h] [bp-14h]@1

    CNetMsg v61;

    v60 = a1->Unk1260;
    CNetMsg::MoveFirst(a1->Unk1260);
    v59 = -1;
    CNetMsg::__rs(a1->Unk1260, &v59);
    if(v59 == 4)
    {
        g_buf[0] = 0;
        src = 0;
        v1 = CNetMsg::__rs(v60, g_buf);
        CNetMsg::__rs(v1, &src);
        if((signed int)src > 0 && (signed int)src <= 10)
        {
            v57 = 0;
            v54 = 0LL;
            v53 = 0LL;
            for(i = 0; i < (signed int)src; ++i)
            {
                v51 = -1;
                v50 = -1;
                dest = -1LL;
                v2 = CNetMsg::__rs(v60, (char *)&v51 + 1);
                v3 = CNetMsg::__rs(v2, &v51);
                v4 = CNetMsg::__rs(v3, &v50);
                CNetMsg::__rs(v4, &dest);
                if(v51 < 0 || v50 <= 0 || SHIDWORD(dest) <= 0 && (HIDWORD(dest) || !(_DWORD)dest))
                {
                    v57 = 1;
                    break;
                }
                k = CInventory::GetItem(a1->Unk792, SHIBYTE(v51), (char)v51);
                if(!k || *(_DWORD *)(k + 24) != v50 || (v5 = CItem::Count(k), dest > v5) || *(_BYTE *)(k + 32) != -1)
                {
                    v57 = 1;
                    break;
                }
                for(j = 0; j < i; ++j)
                {
                    if(*(_DWORD *)(*(_DWORD *)&v56[4 * j] + 24) == v50)
                    {
                        v57 = 1;
                        break;
                    }
                }
                if(v57)
                    break;
                *(_DWORD *)&v56[4 * i] = k;
                v6 = 2 * i;
                v7 = HIDWORD(dest);
                v55[2 * i] = dest;
                v55[v6 + 1] = v7;
                if(*(_DWORD *)(k + 28) == *unk_8104584)
                {
                    v53 += dest;
                }
                else
                {
                    if(*(_DWORD *)(*(_DWORD *)(k + 20) + 96) > 0)
                    {
                        v8 = *(_DWORD *)(*(_DWORD *)(k + 20) + 96);
                        v9 = v8;
                        v10 = (unsigned int)dest * (unsigned __int64)v8;
                        HIDWORD(v11) = (*(_DWORD *)(*(_DWORD *)(k + 20) + 96) >> 31) * dest + HIDWORD(dest) * v9 + HIDWORD(v10);
                        LODWORD(v11) = v10;
                        v54 += v11;
                    }
                }
            }
            if(v57)
            {
                StashErrorMsg((int)&v61, 5);
                if(*(_DWORD *)(a1->Unk768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
            }
            else
            {
                v12 = v53 + v54;
                if(((signed int)((unsigned __int64)(v53 + v54) >> 32) <= 0 && (HIDWORD(v12) || !(_DWORD)v12)
                     || !*(_DWORD *)(a1->Unk1280)
                     || v53 + v54 > CItem::Count(*(_DWORD *)(a1->Unk1280)))
                    && v53 + v54)
                {
                    StashErrorMsg((int)&v61, 6);
                    if(*(_DWORD *)(a1->Unk768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                }
                else
                {
                    j = 0;
                    for(i = 0; i < (signed int)src; ++i)
                    {
                        v13 = CItem::Count(*(_DWORD *)&v56[4 * i]);
                        v46[i] = v13 == *(_QWORD *)&v55[2 * i];
                        if(*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v56[4 * i] + 20) + 68) & 1
                            && CStash::find(
                                     a1->Unk1056,
                                     *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 28),
                                     *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 36),
                                     *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 40)) != -1)
                        {
                            v45[i] = 0;
                        }
                        else
                        {
                            v45[i] = 1;
                            ++j;
                        }
                        v44[i] = *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 28);
                    }
                    v14 = CStash::space(a1->Unk1056);
                    if(v14 >= j)
                    {
                        v15 = v54;
                        init((int)&v43, (int)"STASH KEEP", a1->Unk8, *(_DWORD *)(a1->Unk768) + 4);
                        v16 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v43);
                        v17 = (int)CLogBuffer::__ls(v16, "NEED");
                        v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                        v19 = (int)CLogBuffer::__ls((char *)v18, v15);
                        CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                        for(i = 0; i < (signed int)src; ++i)
                        {
                            v20 = *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 168);
                            v21 = *(_QWORD *)&v55[2 * i];
                            v22 = *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 40);
                            v23 = *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 36);
                            v24 = (const char *)(*(_DWORD *)&v56[4 * i] + 44);
                            v25 = (int)CLogBuffer::__ls(
                                                     g_gamelogbuffer,
                                                     (const char *)(*(_DWORD *)(*(_DWORD *)&v56[4 * i] + 20) + 12));
                            v26 = CLogBuffer::__ls(v25, (int (__cdecl *)(_DWORD))delim);
                            v27 = (int)CLogBuffer::__ls((const char *)v26, v24);
                            v28 = CLogBuffer::__ls(v27, (int (__cdecl *)(_DWORD))delim);
                            v29 = (int)CLogBuffer::__ls((char *)v28, v23);
                            v30 = CLogBuffer::__ls(v29, (int (__cdecl *)(_DWORD))delim);
                            v31 = (int)CLogBuffer::__ls((char *)v30, v22);
                            v32 = CLogBuffer::__ls(v31, (int (__cdecl *)(_DWORD))delim);
                            v33 = (int)CLogBuffer::__ls((char *)v32, v21);
                            v34 = CLogBuffer::__ls(v33, (int (__cdecl *)(_DWORD))delim);
                            CLogBuffer::__ls((char *)v34, v20);
                            for(k = 0; k < *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 168); ++k)
                            {
                                if(*(_DWORD *)(20 * k + *(_DWORD *)&v56[4 * i] + 68))
                                {
                                    v35 = *(_DWORD *)(20 * k + *(_DWORD *)&v56[4 * i] + 76);
                                    v36 = *(_DWORD *)(20 * k + *(_DWORD *)&v56[4 * i] + 72);
                                    v37 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                    v38 = (int)CLogBuffer::__ls((char *)v37, v36);
                                    v39 = CLogBuffer::__ls(v38, (int (__cdecl *)(_DWORD))delim);
                                    CLogBuffer::__ls((char *)v39, v35);
                                }
                            }
                            CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                            if(v46[i])
                            {
                                ItemDeleteMsg((int)&v61, *(_DWORD *)&v56[4 * i]);
                                if(*(_DWORD *)(a1->Unk768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                                CInventory::Remove(a1->Unk792, *(_DWORD *)&v56[4 * i], 0, 1);
                                if(v45[i])
                                {
                                    CStash::add(a1->Unk1056, *(_DWORD *)&v56[4 * i]);
                                }
                                else
                                {
                                    CStash::add(
                                        a1->Unk1056,
                                        *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 28),
                                        *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 36),
                                        *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 40),
                                        *(_QWORD *)&v55[2 * i]);
                                    if(*(_DWORD *)&v56[4 * i])
                                        (*(void (__cdecl **)(_DWORD, signed int))(*(_DWORD *)(*(_DWORD *)&v56[4 * i] + 220) + 8))(
                                            *(_DWORD *)&v56[4 * i],
                                            3);
                                }
                            }
                            else
                            {
                                CInventory::Decrease(a1->Unk792, *(_DWORD *)&v56[4 * i], *(_QWORD *)&v55[2 * i]);
                                HIDWORD(v40) = -*(_QWORD *)&v55[2 * i] >> 32;
                                LODWORD(v40) = -v55[2 * i];
                                ItemUpdateMsg((int)&v61, *(_DWORD *)&v56[4 * i], v40);
                                if(*(_DWORD *)(a1->Unk768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                                CStash::add(
                                    a1->Unk1056,
                                    *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 28),
                                    *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 36),
                                    *(_DWORD *)(*(_DWORD *)&v56[4 * i] + 40),
                                    *(_QWORD *)&v55[2 * i]);
                            }
                        }
                        CLogBuffer::__ls((int)g_gamelogbuffer, end);
                        if(SHIDWORD(v54) > 0 || !HIDWORD(v54) && (_DWORD)v54)
                        {
                            v41 = CItem::Count(*(_DWORD *)(a1->Unk1280));
                            if(v41 == v54)
                            {
                                ItemDeleteMsg((int)&v61, *(_DWORD *)(a1->Unk1280));
                                if(*(_DWORD *)(a1->Unk768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                                CPC::AddMoney(a1, -v54);
                            }
                            else
                            {
                                CPC::AddMoney(a1, -v54);
                                ItemUpdateMsg((int)&v61, *(_DWORD *)(a1->Unk1280), -v54);
                                if(*(_DWORD *)(a1->Unk768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                            }
                        }
                        StashKeepRepMsg((int)&v61, src, (int)v44, (int)v55);
                        if(*(_DWORD *)(a1->Unk768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                        CPC::SaveNow(a1, 1);
                    }
                    else
                    {
                        StashErrorMsg((int)&v61, 7);
                        if(*(_DWORD *)(a1->Unk768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
                    }
                }
            }
        }
        else
        {
            StashErrorMsg((int)&v61, 5);
            if(*(_DWORD *)(a1->Unk768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v61);
        }
    }
    return CNetMsg::_CNetMsg((int)&v61, 2);
}*/

void do_StashTake(CPC *a1, CNetMsg &a2)
{
    if(a1->Unk1260.MsgType)
    {
        CNetMsg v4;

        StashErrorMsg(v4, 2);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v4);
    }
    else
    {
        g_buf[0] = 0;
        a2.__rs(g_buf);
        TrimString(g_buf);

        CNetMsg v4;

        ConnStashCheckPassword(v4, a1->Unk768->Unk0, a1->Unk4, g_buf);

        if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
        {
            CNetMsg v3;

            StashErrorMsg(v3, 1);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v3);
        }
        else
        {
            if(gserver.Unk16)
                gserver.Unk16->WriteToOutput(v4);

            a1->Unk1260.Init(a2);
        }
    }
}

/*void do_StashTake_real(CPC *a1)
{
    int v1; // eax@2
    int v2; // eax@9
    signed int v3; // eax@14
    __int64 v4; // qax@15
    int v5; // eax@20
    int v6; // eax@23
    int v7; // edi@23
    __int64 v8; // qax@34
    int v9; // eax@42
    signed int v10; // ST7C_4@48
    signed __int64 v11; // ST64_8@48
    signed int v12; // ST4C_4@48
    signed int v13; // ST34_4@48
    const char *v14; // ST1C_4@48
    int v15; // eax@48
    int v16; // eax@48
    int v17; // eax@48
    int v18; // eax@48
    int v19; // eax@48
    int v20; // eax@48
    int v21; // eax@48
    int v22; // eax@48
    int v23; // eax@48
    int v24; // eax@48
    signed int v25; // ST7C_4@51
    signed int v26; // ST64_4@51
    int v27; // eax@51
    int v28; // eax@51
    int v29; // eax@51
    int v30; // STAC_4@58
    int v31; // STA8_4@67
    int v33; // [sp+30h] [bp-114h]@63
    int k; // [sp+34h] [bp-110h]@48
    int v35; // [sp+38h] [bp-10Ch]@46
    int v36[10]; // [sp+48h] [bp-FCh]@41
    char v37[12]; // [sp+70h] [bp-D4h]@39
    _BYTE v38[16]; // [sp+7Ch] [bp-C8h]@20
    int j; // [sp+8Ch] [bp-B8h]@17
    int v40; // [sp+90h] [bp-B4h]@14
    __int64 dest; // [sp+94h] [bp-B0h]@9
    int v42; // [sp+9Ch] [bp-A8h]@9
    int i; // [sp+A0h] [bp-A4h]@7
    int v44; // [sp+A4h] [bp-A0h]@7
    int v45[20]; // [sp+A8h] [bp-9Ch]@23
    char v46[43]; // [sp+F8h] [bp-4Ch]@19
    char v47; // [sp+123h] [bp-21h]@7
    uint32_t src; // [sp+124h] [bp-20h]@2
    char v49; // [sp+12Bh] [bp-19h]@1
    int v50; // [sp+12Ch] [bp-18h]@1
    int v51; // [sp+130h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v51);
    v50 = a1->Unk1260;
    CNetMsg::MoveFirst(a1->Unk1260);
    v49 = -1;
    CNetMsg::__rs(a1->Unk1260, &v49);
    if(v49 == 6)
    {
        g_buf[0] = 0;
        src = 0;
        v1 = CNetMsg::__rs(v50, g_buf);
        CNetMsg::__rs(v1, &src);
        if((signed int)src > 0 && (signed int)src <= 10)
        {
            v47 = 0;
            v44 = 0;
            for(i = 0; i < (signed int)src; ++i)
            {
                v42 = -1;
                dest = -1LL;
                v2 = CNetMsg::__rs(v50, &v42);
                CNetMsg::__rs(v2, &dest);
                if(v42 <= 0 || SHIDWORD(dest) <= 0 && (HIDWORD(dest) || !(_DWORD)dest))
                {
                    v47 = 1;
                    break;
                }
                v3 = CStash::find(a1->Unk1056, v42);
                v40 = CStash::item(a1->Unk1056, v3);
                if(!v40 || (v4 = CItem::Count(v40), dest > v4))
                {
                    v47 = 1;
                    break;
                }
                for(j = 0; j < i; ++j)
                {
                    if(*(_DWORD *)(*(_DWORD *)&v46[4 * j] + 24) == v42)
                    {
                        v47 = 1;
                        init((int)v38, (int)"HACK STASH", a1->Unk8, *(_DWORD *)(a1->Unk768) + 4);
                        v5 = (int)CLogBuffer::__ls(g_gamelogbuffer, (int)v38);
                        CLogBuffer::__ls(v5, end);
                        break;
                    }
                }
                if(v47)
                    break;
                *(_DWORD *)&v46[4 * i] = v40;
                v6 = 2 * i;
                v7 = HIDWORD(dest);
                v45[2 * i] = dest;
                v45[v6 + 1] = v7;
                v44 += dest * *(_DWORD *)(*(_DWORD *)(v40 + 20) + 96);
            }
            if(v47)
            {
                StashErrorMsg((int)&v51, 5);
                if(*(_DWORD *)(a1->Unk768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
            }
            else
            {
                if(v44 + *(_DWORD *)(a1->Unk724) < 15 * *(_DWORD *)(a1->Unk728) / 10)
                {
                    j = 0;
                    for(i = 0; i < (signed int)src; ++i)
                    {
                        v8 = CItem::Count(*(_DWORD *)&v46[4 * i]);
                        v38[i] = v8 == *(_QWORD *)&v45[2 * i];
                        if(*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v46[4 * i] + 20) + 68) & 1
                            && CInventory::FindItem(
                                     a1->Unk792,
                                     (int)&v40,
                                     (int)&v42,
                                     *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 28),
                                     *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 36),
                                     *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 40)))
                        {
                            v37[i] = 0;
                        }
                        else
                        {
                            v37[i] = 1;
                            ++j;
                        }
                        v36[i] = *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 28);
                    }
                    v9 = CInventory::GetSpace(a1->Unk792);
                    if(v9 >= j)
                    {
                        init((int)&v35, (int)"STASH TAKE", a1->Unk8, *(_DWORD *)(a1->Unk768) + 4);
                        CLogBuffer::__ls(g_gamelogbuffer, (int)&v35);
                        for(i = 0; i < (signed int)src; ++i)
                        {
                            v10 = *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 168);
                            v11 = *(_QWORD *)&v45[2 * i];
                            v12 = *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 40);
                            v13 = *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 36);
                            v14 = (const char *)(*(_DWORD *)&v46[4 * i] + 44);
                            v15 = (int)CLogBuffer::__ls(
                                                     g_gamelogbuffer,
                                                     (const char *)(*(_DWORD *)(*(_DWORD *)&v46[4 * i] + 20) + 12));
                            v16 = CLogBuffer::__ls(v15, (int (__cdecl *)(_DWORD))delim);
                            v17 = (int)CLogBuffer::__ls((const char *)v16, v14);
                            v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                            v19 = (int)CLogBuffer::__ls((char *)v18, v13);
                            v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                            v21 = (int)CLogBuffer::__ls((char *)v20, v12);
                            v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                            v23 = (int)CLogBuffer::__ls((char *)v22, v11);
                            v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
                            CLogBuffer::__ls((char *)v24, v10);
                            for(k = 0; k < *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 168); ++k)
                            {
                                if(*(_DWORD *)(20 * k + *(_DWORD *)&v46[4 * i] + 68))
                                {
                                    v25 = *(_DWORD *)(20 * k + *(_DWORD *)&v46[4 * i] + 76);
                                    v26 = *(_DWORD *)(20 * k + *(_DWORD *)&v46[4 * i] + 72);
                                    v27 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                    v28 = (int)CLogBuffer::__ls((char *)v27, v26);
                                    v29 = CLogBuffer::__ls(v28, (int (__cdecl *)(_DWORD))delim);
                                    CLogBuffer::__ls((char *)v29, v25);
                                }
                            }
                            CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                            if(v38[i])
                            {
                                CStash::remove(a1->Unk1056, *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 24));
                                if(v37[i])
                                {
                                    CInventory::AddItem(a1->Unk792, *(_DWORD *)&v46[4 * i], a1, 0, 1, -1, -1);
                                    ItemAddMsg((int)&v51, *(_DWORD *)&v46[4 * i]);
                                    if(*(_DWORD *)(a1->Unk768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                                }
                                else
                                {
                                    CInventory::AddItem(a1->Unk792, *(_DWORD *)&v46[4 * i], a1, 0, 1, -1, -1);
                                    CInventory::FindItem(
                                        a1->Unk792,
                                        (int)&v40,
                                        (int)&v42,
                                        *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 28),
                                        *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 36),
                                        *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 40));
                                    v30 = CInventory::GetItem(a1->Unk792, v40, v42);
                                    ItemUpdateMsg((int)&v51, v30, *(_QWORD *)&v45[2 * i]);
                                    if(*(_DWORD *)(a1->Unk768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                                    if(*(_DWORD *)&v46[4 * i])
                                        (*(void (__cdecl **)(_DWORD, signed int))(*(_DWORD *)(*(_DWORD *)&v46[4 * i] + 220) + 8))(
                                            *(_DWORD *)&v46[4 * i],
                                            3);
                                }
                            }
                            else
                            {
                                CStash::remove(a1->Unk1056, *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 24), *(_QWORD *)&v45[2 * i]);
                                v33 = CItemList::CreateItem(
                                                gserver.Unk41208,
                                                *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 28),
                                                -1,
                                                *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 36),
                                                *(_DWORD *)(*(_DWORD *)&v46[4 * i] + 40),
                                                *(_QWORD *)&v45[2 * i]);
                                if(v37[i])
                                {
                                    CInventory::AddItem(a1->Unk792, v33, a1, 0, 1, -1, -1);
                                    ItemAddMsg((int)&v51, v33);
                                    if(*(_DWORD *)(a1->Unk768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                                }
                                else
                                {
                                    CInventory::AddItem(a1->Unk792, v33, a1, 0, 1, -1, -1);
                                    CInventory::FindItem(
                                        a1->Unk792,
                                        (int)&v40,
                                        (int)&v42,
                                        *(_DWORD *)(v33 + 28),
                                        *(_DWORD *)(v33 + 36),
                                        *(_DWORD *)(v33 + 40));
                                    v31 = CInventory::GetItem(a1->Unk792, v40, v42);
                                    ItemUpdateMsg((int)&v51, v31, *(_QWORD *)&v45[2 * i]);
                                    if(*(_DWORD *)(a1->Unk768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                                    if(v33)
                                        (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v33 + 220) + 8))(v33, 3);
                                }
                            }
                        }
                        CLogBuffer::__ls((int)g_gamelogbuffer, end);
                        StashTakeRepMsg((int)&v51, src, (int)v36, (int)v45);
                        if(*(_DWORD *)(a1->Unk768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                        CPC::SaveNow(a1, 1);
                    }
                    else
                    {
                        StashErrorMsg((int)&v51, 9);
                        if(*(_DWORD *)(a1->Unk768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                    }
                }
                else
                {
                    StashErrorMsg((int)&v51, 8);
                    if(*(_DWORD *)(a1->Unk768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
                }
            }
        }
        else
        {
            StashErrorMsg((int)&v51, 5);
            if(*(_DWORD *)(a1->Unk768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v51);
        }
    }
    return CNetMsg::_CNetMsg((int)&v51, 2);
}*/

void do_StashChangePassword(CPC *a1, CNetMsg &a2)
{
    if(a1->Unk1260.MsgType)
    {
        CNetMsg v5;

        StashErrorMsg(v5, 2);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v5);
    }
    else
    {
        g_buf[0] = 0;
        g_buf2[0] = 0;

        a2.__rs(g_buf);
        a2.__rs(g_buf2);

        TrimString(g_buf);
        TrimString(g_buf2);

        if(strinc(g_buf2, "'") || strinc(g_buf2, "%"))
        {
            CNetMsg v5;

            StashErrorMsg(v5, 10);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v5);
        }
        else
        {
            CNetMsg v5;

            ConnStashChangePassword(v5, a1->Unk768->Unk0, a1->Unk4, g_buf, g_buf2);

            if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
            {
                CNetMsg v4;

                StashErrorMsg(v4, 1);

                if(a1->Unk768)
                    a1->Unk768->WriteToOutput(v4);
            }
            else
            {
                if(gserver.Unk16)
                    gserver.Unk16->WriteToOutput(v5);

                a1->Unk1260.Init(a2);
            }
        }
    }
}

void do_StashSeal(CPC *a1, CNetMsg &a2)
{
    CNetMsg v4;

    ConnStashSeal(v4, a1->Unk768->Unk0, a1->Unk4);

    if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
    {
        CNetMsg v3;

        StashErrorMsg(v3, 11);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v3);
    }
    else
    {
        if(gserver.Unk16)
            gserver.Unk16->WriteToOutput(v4);

        a1->Unk1260.Init(a2);
    }
}
