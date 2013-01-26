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

#include "doFuncCommand.hpp"

void do_CommandCharacterDelete(CNetMsg &netmsg, CDescriptor *desc)
{
    CGuildMember *gmember;
    int index;
    netmsg.__rs(index);
    gmember = g_guildlist.findmember(index);

    if ( gmember )
    {
        if ( gmember->pos() )
            do_CommandGuildMemberOutReq_real(desc, gmember->guild()->index(), gmember->charindex());
        else
            do_CommandGuildBreakUpReq_real(desc, gmember->charindex(), gmember->guild()->index());
    }
}

void do_CommandGuildAppointOfficerReq(CNetMsg &netmsg, CDescriptor *desc)
{

    const char *v4; // ST70_4@33
    int v5; // ST58_4@33
    const char *v6; // ST28_4@33
    int v7; // ST10_4@33
    int v18; // eax@33
//    const CLogHeader v19; // [sp+8h] [bp-1060h]@33
    //CDBCmd dbcmd; // [sp+18h] [bp-1050h]@29
    int i; // [sp+1038h] [bp-30h]@21
    CGuildMember *p_gmember2; // [sp+103Ch] [bp-2Ch]@13
    CGuildMember *p_gmember; // [sp+1040h] [bp-28h]@5
    CGuild *p_guild; // [sp+1044h] [bp-24h]@1
    int val3; // [sp+1048h] [bp-20h]@1
    int retstr; // [sp+104Ch] [bp-1Ch]@1
    int guildid; // [sp+1050h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+1054h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(guildid);
    netmsg.__rs(retstr);
    netmsg.__rs(val3);
    p_guild = g_guildlist.findguild(guildid);
    if ( p_guild )
    {
        p_gmember = p_guild->findmember(retstr, 0);
        if ( p_gmember )
        {
            if ( p_gmember->pos() )
            {
                HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 10);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
                //delete v_netmsg;
            }
            else
            {
                p_gmember2 = p_guild->findmember(val3, 0);
                if ( p_gmember2 )
                {
                    if ( p_gmember2->pos() == 2 )
                    {
                        for ( i = 0; i <= 1 && p_guild->officer(i); ++i )
                            ;
                        if ( i == 2 )
                        {
                            HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 28);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                            //delete v_netmsg;
                        }
                        else
                        {
                            //CDBCmd::CDBCmd(&dbcmd);
                            CDBCmd dbcmd;
                            dbcmd.Init(&g_mysql);
                            sprintf(
                                g_buf,
                                "UPDATE t_guildmember SET a_pos=%d WHERE a_guild_index=%d AND a_char_index=%d",
                                1,
                                guildid,
                                val3);
                            dbcmd.SetQuery(g_buf);
                            if ( dbcmd.Update() )
                            {
                                sprintf(g_buf, "UPDATE t_guild SET a_recentdate=NOW() WHERE a_index=%d", guildid);
                                dbcmd.SetQuery(g_buf);
                                dbcmd.Update();
                                v4 = p_gmember2->name();
                                v5 = p_gmember2->charindex();
                                v6 = p_guild->name();
                                v7 = p_guild->index();
                                g_gamelogbuffer.__ls(init("GUILD APPOINT OFFICER"));
                                g_gamelogbuffer.__ls(v7);
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(v6);
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls("OFFICER");
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(v5);
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(v4);
                                g_gamelogbuffer.__ls(end);
                                v18 = p_gmember2->listindex();
                                p_guild->appoint(v18);
                                HelperGuildAppointOfficerNotifyMsg(v_netmsg, guildid, retstr, val3);
                                gserver.SendToAllGameServer(v_netmsg);
                                HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 0);
                                if ( desc )
                                    desc->WriteToOutput(v_netmsg);
                                //delete [] dbcmd;
                                //delete [] v_netmsg;
                            }
                            else
                            {
                                HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 22);
                                if ( desc )
                                    desc->WriteToOutput(v_netmsg);
                                //delete [] dbcmd;
                                //delete [] v_netmsg;
                            }
                        }
                    }
                    else
                    {
                        HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 26);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //delete [] v_netmsg;
                    }
                }
                else
                {
                    HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 22);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //delete [] v_netmsg;
                }
            }
        }
        else
        {
            HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 10);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //delete [] v_netmsg;
        }
    }
    else
    {
        HelperGuildAppointOfficerRepMsg(v_netmsg, guildid, retstr, val3, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //delete v_netmsg;
    }
}

void do_CommandGuildBreakUpReq(CNetMsg &netmsg, CDescriptor *desc)
{
//  CNetMsg *v2; // eax@1
    int a3; // [sp+Ch] [bp-1Ch]@1
    int dest; // [sp+10h] [bp-18h]@1
//  CNetMsg v_netmsg; // [sp+14h] [bp-14h]@1

//  CNetMsg::CNetMsg(&v5);
    netmsg.__rs(dest);
    netmsg.__rs(a3);
    do_CommandGuildBreakUpReq_real(desc, dest, a3);
//  CNetMsg::_CNetMsg(&v5, 2);
}

void do_CommandGuildBreakUpReq_real(CDescriptor *desc, int src, int a3)
{
    struct tm *v5; // eax@5
    int v6; // ST30_4@5
    int v7; // ST2C_4@5
    int v8; // ST28_4@5
    int v9; // ST24_4@5
    int v10; // ST20_4@5
    int v11; // ST1C_4@5
    const char *v12; // eax@5


    struct tm dest;
    time_t timer;
    CNetMsg netmsg; // [sp+1074h] [bp-14h]@1
    CGuild *t_guild;

    //CNetMsg::CNetMsg(&netmsg);
    t_guild = g_guildlist.findguild(a3);
    if (  t_guild->boss()->charindex() == src )
    {
        timer = time(0);
        v5 = localtime(&timer);
        memcpy(&dest, v5, 44u);
        v6 = dest.tm_sec;
        v7 = dest.tm_min;
        v8 = dest.tm_hour;
        v9 = dest.tm_mday;
        v10 = dest.tm_mon;
        v11 = dest.tm_year;
        v12 = t_guild->name();
        sprintf(
            g_buf,
            "UPDATE t_guild SET a_name='%s_%02d%02d%02d%02d%02d%02d', a_enable=0, a_recentdate=NOW() WHERE a_index=%d",
            v12,
            v11,
            v10,
            v9,
            v8,
            v7,
            v6,
            a3);
        CDBCmd dbcmd;
        dbcmd.Init(&g_mysql);
        dbcmd.SetQuery(g_buf);
        if ( dbcmd.Update() )
        {
            g_gamelogbuffer.__ls(init("GUILD BREAK"));
            g_gamelogbuffer.__ls(t_guild->index());
            g_gamelogbuffer.__ls(" : ");
            g_gamelogbuffer.__ls(t_guild->name());
            g_gamelogbuffer.__ls(end);
            g_guildlist.Remove(t_guild);
            HelperGuildBreakUpNotifyMsg(netmsg, a3);

            gserver.SendToAllGameServer(netmsg);
            HelperGuildBreakUpRepMsg(netmsg, src, 0);
            if ( desc )
                desc->WriteToOutput(netmsg);
//            CDBCmd::_CDBCmd(&dbcmd, 2);
//            CNetMsg::_CNetMsg(&netmsg, 2);
        }
        else
        {
            HelperGuildBreakUpRepMsg(netmsg, src, 10);
            if ( desc )
                desc->WriteToOutput(netmsg);
//            CDBCmd::_CDBCmd(&dbcmd, 2);
//            CNetMsg::_CNetMsg(&netmsg, 2);
        }
    }
    else
    {
        HelperGuildBreakUpRepMsg(netmsg, src, 10);
        if ( desc )
            desc->WriteToOutput(netmsg);
        //CNetMsg::_CNetMsg(&netmsg, 2);
    }
}

void do_CommandGuildChangeBossReq(CNetMsg &netmsg, CDescriptor *desc)
{
    CGuildMember *t_member2; // [sp+103Ch] [bp-2Ch]@13
    CGuildMember *t_member; // [sp+1040h] [bp-28h]@5
    CGuild *t_guild; // [sp+1044h] [bp-24h]@1
    int v28; // [sp+1048h] [bp-20h]@1
    int retstr; // [sp+104Ch] [bp-1Ch]@1
    int dest; // [sp+1050h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+1054h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);

    netmsg.__rs(dest);
    netmsg.__rs(retstr);
    netmsg.__rs(v28);
    t_guild = g_guildlist.findguild(dest);
    if ( t_guild )
    {
        t_member = t_guild->findmember(retstr, 0);
        if ( t_member )
        {
            if ( t_member->pos() == 2 )
            {
                HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 10);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
            else
            {
                t_member2 = t_guild->findmember(v28, 0);
                if ( t_member2 )
                {
                    if ( t_member2->pos() )
                    {
                        CDBCmd dbcmd;
                        //CDBCmd::CDBCmd(&dbcmd);
                        dbcmd.Init(&g_mysql);
                        dbcmd.BeginTrans();
                        sprintf(
                            g_buf,
                            "UPDATE t_guildmember SET a_pos=%d WHERE a_guild_index=%d AND a_char_index=%d",
                            2,
                            dest,
                            retstr);
                        dbcmd.SetQuery(g_buf);
                        if ( dbcmd.Update() )
                        {
                            sprintf(
                                g_buf,
                                "UPDATE t_guildmember SET a_pos=%d WHERE a_guild_index=%d AND a_char_index=%d",
                                0,
                                dest,
                                v28);
                            dbcmd.SetQuery(g_buf);
                            if ( dbcmd.Update() && dbcmd.NumRows > 0 )
                            {
                                dbcmd.Commit();
                                sprintf(g_buf, "UPDATE t_guild SET a_recentdate=NOW() WHERE a_index=%d", dest);
                                dbcmd.SetQuery(g_buf);
                                dbcmd.Update();
                                g_gamelogbuffer.__ls(init("GUILD CHANGE BOSS"));
                                g_gamelogbuffer.__ls( t_guild->index() );
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_guild->name());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_member->charindex());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_member->name());
                                g_gamelogbuffer.__ls(" ==> ");
                                g_gamelogbuffer.__ls(t_member2->charindex());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_member2->name());
                                g_gamelogbuffer.__ls(end);

                                t_guild->changeboss( t_member2->listindex() );
                                HelperGuildChangeBossNotifyMsg(v_netmsg, dest, retstr, v28);

                                gserver.SendToAllGameServer(v_netmsg);
                                HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 0);
                                if ( desc )
                                    desc->WriteToOutput(v_netmsg);
                                //CDBCmd::_CDBCmd(&dbcmd, 2);
                                //CNetMsg::_CNetMsg(&v_netmsg, 2);
                            }
                            else
                            {
                                dbcmd.Rollback();
                                HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 22);
                                if ( desc )
                                    desc->WriteToOutput(v_netmsg);
                                //CDBCmd::_CDBCmd(&dbcmd, 2);
                                //CNetMsg::_CNetMsg(&v_netmsg, 2);
                            }
                        }
                        else
                        {
                            dbcmd.Rollback();
                            HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 22);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CDBCmd::_CDBCmd(&dbcmd, 2);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                    }
                    else
                    {
                        HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 23);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                }
                else
                {
                    HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 22);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
            }
        }
        else
        {
            HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 10);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
        }
    }
    else
    {
        HelperGuildChangeBossRepMsg(v_netmsg, dest, retstr, v28, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandGuildChat(CNetMsg &netmsg, CDescriptor *desc)
{
    CGuild *t_guild; // [sp+Ch] [bp-Ch]@1
    int memb; // [sp+10h] [bp-8h]@1
    int idx; // [sp+14h] [bp-4h]@1

    netmsg.__rs(idx);
    netmsg.__rs(memb);
    t_guild = g_guildlist.findguild(idx);
    if ( t_guild )
    {
        if ( t_guild->findmember(memb, 0) )
        {

            gserver.SendToAllGameServer(netmsg);
        }
    }
}

void do_CommandGuildCreateReq(CNetMsg &netmsg, CDescriptor *desc)
{

    CGuild *t_guild; // STB0_4@10
    CGuildMember *t_boss; // eax@10
    int guildindex; // [sp+20h] [bp-10A8h]@6
    char guildname[52]; // [sp+1048h] [bp-80h]@1
    char charname[52]; // [sp+107Ch] [bp-4Ch]@1
    int charindex; // [sp+10B0h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+10B4h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(charindex);
    netmsg.__rs(charname);
    netmsg.__rs(guildname);
    if ( g_guildlist.findmember(charindex) )
    {
        HelperGuildCreateRepMsg(v_netmsg, charindex, 1);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //goto LABEL_15;
        return;
    }
    sprintf(g_buf, "INSERT INTO t_guild (a_name,a_createdate,a_recentdate) VALUES ('%s',NOW(),NOW())", (const char*)&guildname);
    CDBCmd dbcmd;
    dbcmd.Init(&g_mysql);
    dbcmd.BeginTrans();
    dbcmd.SetQuery(g_buf);
    if ( !dbcmd.Update() )
    {
        dbcmd.Rollback();
        HelperGuildCreateRepMsg(v_netmsg, charindex, 8);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CDBCmd::_CDBCmd(&dbcmd, 2);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
        return;
    }
    guildindex = dbcmd.insertid();
    sprintf(
        g_buf,
        "INSERT INTO t_guildmember (a_guild_index,a_char_index,a_char_name,a_pos,a_regdate) VALUES (%d,%d,'%s',%d,NOW())",
        guildindex,
        charindex,
        (const char*) &charname,
        0);
    dbcmd.SetQuery(g_buf);
    if ( dbcmd.Update() )
    {
        dbcmd.Commit();
        g_gamelogbuffer.__ls(init("GUILD CREATE"));
        g_gamelogbuffer.__ls(guildindex);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(guildname);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls("BOSS");
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(charindex);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(charname);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(end);

        //t_guild = CGuildList::create(guildindex, (const char*) &guildname, charindex, (const char*) &charname);
        t_guild = g_guildlist.create(guildindex, (const char*) &guildname, charindex, (const char*) &charname);
        g_guildlist.add(t_guild);
        t_boss = t_guild->boss();
        t_boss->online(1);
        HelperGuildCreateNotifyMsg(v_netmsg, t_guild);

        gserver.SendToAllGameServer(v_netmsg);
        t_boss = t_guild->boss();
        HelperGuildOnlineNotifyMsg(v_netmsg, t_boss);

        gserver.SendToAllGameServer(v_netmsg);
        HelperGuildCreateRepMsg(v_netmsg, charindex, 0);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CDBCmd::_CDBCmd(&dbcmd, 2);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
        return;
    }
    dbcmd.Rollback();
    HelperGuildCreateRepMsg(v_netmsg, charindex, 7);
    if ( desc )
        desc->WriteToOutput(v_netmsg);
    //CDBCmd::_CDBCmd(&dbcmd, 2);
    //CNetMsg::_CNetMsg(&v_netmsg, 2);
}

void do_CommandGuildFireOfficerReq(CNetMsg &netmsg, CDescriptor *desc)
{
    CDBCmd base; // [sp+1Ch] [bp-104Ch]@21
    CGuildMember *p_oldboss; // [sp+103Ch] [bp-2Ch]@13
    CGuildMember *t_member; // [sp+1040h] [bp-28h]@5
    CGuild *t_guild; // [sp+1044h] [bp-24h]@1
    int oldbossidx; // [sp+1048h] [bp-20h]@1
    int memberindex; // [sp+104Ch] [bp-1Ch]@1
    int guildindex; // [sp+1050h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+1054h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(guildindex);
    netmsg.__rs(memberindex);
    netmsg.__rs(oldbossidx);
    t_guild = g_guildlist.findguild(guildindex);
    if ( t_guild )
    {
        t_member = t_guild->findmember(memberindex, 0);
        if ( t_member )
        {
            if ( t_member->pos() )
            {
                HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 10);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
            else
            {
                p_oldboss = t_guild->findmember(oldbossidx, 0);
                if ( p_oldboss )
                {
                    if ( p_oldboss->pos() == 1 )
                    {
                        CDBCmd dbcmd;
                        //CDBCmd::CDBCmd(&base);
                        dbcmd.Init(&g_mysql);
                        sprintf(
                            g_buf,
                            "UPDATE t_guildmember SET a_pos=%d WHERE a_guild_index=%d AND a_char_index=%d",
                            2,
                            guildindex,
                            oldbossidx);
                        dbcmd.SetQuery(g_buf);
                        if ( dbcmd.Update() )
                        {
                            sprintf(g_buf, "UPDATE t_guild SET a_recentdate=NOW() WHERE a_index=%d", guildindex);
                            dbcmd.SetQuery(g_buf);
                            dbcmd.Update();
                            g_gamelogbuffer.__ls(init("GUILD FIRE OFFICER"));
                            g_gamelogbuffer.__ls(t_guild->index());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(t_guild->name());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls("OFFICER");
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(p_oldboss->charindex());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(p_oldboss->name());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(end);

                            t_guild->fire( p_oldboss->listindex() );
                            HelperGuildFireOfficerNotifyMsg(v_netmsg, guildindex, memberindex, oldbossidx);

                            gserver.SendToAllGameServer(v_netmsg);
                            HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 0);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CDBCmd::_CDBCmd(&base, 2);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                        else
                        {
                            HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 22);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CDBCmd::_CDBCmd(&base, 2);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                    }
                    else
                    {
                        HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 29);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                }
                else
                {
                    HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 22);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
            }
        }
        else
        {
            HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 10);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
        }
    }
    else
    {
        HelperGuildFireOfficerRepMsg(v_netmsg, guildindex, memberindex, oldbossidx, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandGuildLevelUpReq(CNetMsg &netmsg, CDescriptor *desc)
{
    CDBCmd dbcmd; // [sp+18h] [bp-1040h]@13
    CGuild *p_guild; // [sp+1038h] [bp-20h]@1
    int gcharindex; // [sp+103Ch] [bp-1Ch]@1
    int gindex; // [sp+1040h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+1044h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(gindex);
    netmsg.__rs(gcharindex);
    p_guild = g_guildlist.findguild(gindex);
    if ( p_guild )
    {
        if ( p_guild->level() <= 4 )
        {
            if ( p_guild->boss()->charindex() == gcharindex )
            {
                sprintf(g_buf, "UPDATE t_guild SET a_level=a_level+1, a_recentdate=NOW() WHERE a_index=%d", gindex);
                CDBCmd dbcmd;
                dbcmd.Init(&g_mysql);
                dbcmd.SetQuery(g_buf);
                if ( dbcmd.Update() )
                {
                    g_gamelogbuffer.__ls(init("GUILD LEVELUP"));
                    g_gamelogbuffer.__ls(p_guild->index());
                    g_gamelogbuffer.__ls(" : ");
                    g_gamelogbuffer.__ls(p_guild->name());
                    g_gamelogbuffer.__ls(" : ");
                    g_gamelogbuffer.__ls(p_guild->level());
                    g_gamelogbuffer.__ls(end);

                    p_guild->LevelUp();
                    HelperGuildLevelUpNotifyMsg(v_netmsg, gindex, p_guild->level());

                    gserver.SendToAllGameServer(v_netmsg);
                    HelperGuildLevelUpRepMsg(v_netmsg, gindex, gcharindex, 0);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CDBCmd::_CDBCmd(&dbcmd, 2);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
                else
                {
                    HelperGuildLevelUpRepMsg(v_netmsg, gindex, gcharindex, 7);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CDBCmd::_CDBCmd(&dbcmd, 2);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
            }
            else
            {
                HelperGuildLevelUpRepMsg(v_netmsg, gindex, gcharindex, 10);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
        }
        else
        {
            HelperGuildLevelUpRepMsg(v_netmsg, gindex, gcharindex, 11);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
        }
    }
    else
    {
        HelperGuildLevelUpRepMsg(v_netmsg, gindex, gcharindex, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandGuildLoadReq(CNetMsg &netmsg, CDescriptor *desc)
{
    char name[52]; // [sp+Ch] [bp-4Ch]@1
    int index; // [sp+40h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+44h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(name);
    netmsg.__rs(index);
    HelperGuildLoadRepMsg(v_netmsg, name, index, 0);
    if ( desc )
        desc->WriteToOutput(v_netmsg);
    //CNetMsg::_CNetMsg(&v_netmsg, 2);
}

void do_CommandGuildMemberAddReq(CNetMsg &netmsg, CDescriptor *desc)
{
    CGuildMember *t_member; // eax@25
    _tagGuildPositionType t_pos; // al@25
    int v31; // [sp+34h] [bp-1080h]@21
    //CDBCmd dbcmd; // [sp+38h] [bp-107Ch]@17
    CGuildMember *t_gmember; // [sp+1058h] [bp-5Ch]@9
    CGuild *t_guild; // [sp+105Ch] [bp-58h]@1
    char charname[52]; // [sp+1060h] [bp-54h]@1
    int charindex; // [sp+1094h] [bp-20h]@1
    int memberidx; // [sp+1098h] [bp-1Ch]@1
    int guildidx; // [sp+109Ch] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+10A0h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(guildidx);
    netmsg.__rs(memberidx);
    netmsg.__rs(charindex);
    netmsg.__rs(charname);
    t_guild = g_guildlist.findguild(guildidx);
    if ( t_guild )
    {
        if ( t_guild->maxmember() > t_guild->membercount() )
        {
            t_gmember = t_guild->findmember(memberidx, 0);
            if ( t_gmember )
            {
                if ( t_gmember->pos() == 2 )
                {
                    HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 15);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
                else
                {
                    sprintf(
                        g_buf,
                        "INSERT INTO t_guildmember (a_guild_index,a_char_index,a_char_name,a_pos,a_regdate) VALUES (%d,%d,'%s',%d,NOW())",
                        guildidx,
                        charindex,
                        charname,
                        2);
                    //CDBCmd::CDBCmd(&dbcmd);
                    CDBCmd dbcmd;
                    dbcmd.Init(&g_mysql);
                    dbcmd.SetQuery(g_buf);
                    if ( dbcmd.Update() )
                    {
                        v31 = t_guild->addmember(charindex, charname);
                        if ( v31 == -1 )
                        {
                            HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 18);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CDBCmd::_CDBCmd(&dbcmd, 2);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                        else
                        {
                            sprintf(g_buf, "UPDATE t_guild SET a_recentdate=NOW() WHERE a_index=%d", guildidx);
                            dbcmd.SetQuery(g_buf);
                            dbcmd.Update();
                            g_gamelogbuffer.__ls(init("GUILD MEMBER ADD"));
                            g_gamelogbuffer.__ls(t_guild->index());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(t_guild->name());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls("AGREE");
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(t_gmember->charindex());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(t_gmember->name());
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls("CHARACTER");
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(charindex);
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(charname);
                            g_gamelogbuffer.__ls(" : ");
                            g_gamelogbuffer.__ls(end);
                            t_member = t_guild->member(v31);
                            t_pos = t_member->pos();
                            HelperGuildMemberAddNotifyMsg(v_netmsg, guildidx, charindex, charname, t_pos);

                            gserver.SendToAllGameServer(v_netmsg);
                            HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 0);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CDBCmd::_CDBCmd(&dbcmd, 2);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                    }
                    else
                    {
                        HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 7);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //CDBCmd::_CDBCmd(&dbcmd, 2);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                }
            }
            else
            {
                HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 15);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
        }
        else
        {
            HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 18);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
        }
    }
    else
    {
        HelperGuildMemberAddRepMsg(v_netmsg, guildidx, memberidx, charindex, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandGuildMemberKickReq(CNetMsg &netmsg, CDescriptor *desc)
{
    CGuildMember *t_gmember; // [sp+103Ch] [bp-2Ch]@13
    CGuildMember *t_gmember2; // [sp+1040h] [bp-28h]@5
    CGuild *t_guild; // [sp+1044h] [bp-24h]@1
    int charindex; // [sp+1048h] [bp-20h]@1
    int memberidx; // [sp+104Ch] [bp-1Ch]@1
    int guildidx; // [sp+1050h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+1054h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(guildidx);
    netmsg.__rs(memberidx);
    netmsg.__rs(charindex);
    t_guild = g_guildlist.findguild(guildidx);
    if ( t_guild )
    {
        t_gmember2 = t_guild->findmember(memberidx, 0);
        if ( t_gmember2 )
        {
            if ( t_gmember2->pos() == 2 )
            {
                HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 10);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
            else
            {
                t_gmember = t_guild->findmember(charindex, 0);
                if ( t_gmember )
                {
                    if ( t_gmember->pos() )
                    {
                        if ( t_gmember2->pos() != 1 || t_gmember->pos() != 1 )
                        {
                            sprintf(
                                g_buf,
                                "DELETE FROM t_guildmember WHERE a_guild_index=%d AND a_char_index=%d",
                                guildidx,
                                charindex);
                            //CDBCmd::CDBCmd(&dbcmd);
                            CDBCmd dbcmd;
                            dbcmd.Init(&g_mysql);
                            dbcmd.SetQuery(g_buf);
                            if ( dbcmd.Update() )
                            {
                                sprintf(g_buf, "UPDATE t_guild SET a_recentdate=NOW() WHERE a_index=%d", guildidx);
                                dbcmd.SetQuery(g_buf);
                                dbcmd.Update();
                                g_gamelogbuffer.__ls(init("GUILD MEMBER KICK"));
                                g_gamelogbuffer.__ls(t_guild->index());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_guild->name());
                                g_gamelogbuffer.__ls("ADMIN");
                                g_gamelogbuffer.__ls(t_gmember2->charindex());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_gmember2->name());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls("CHARACTER");
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_gmember->charindex());
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(t_gmember->name());
                                g_gamelogbuffer.__ls(end);

                                HelperGuildMemberKickNotifyMsg(v_netmsg, guildidx, memberidx, charindex);

                                gserver.SendToAllGameServer(v_netmsg);
                                t_guild->removemember(t_gmember);
                                HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 0);
                                if ( desc )
                                    desc->WriteToOutput(v_netmsg);
                                //CDBCmd::_CDBCmd(&dbcmd, 2);
                                //CNetMsg::_CNetMsg(&v_netmsg, 2);
                            }
                            else
                            {
                                HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 22);
                                if ( desc )
                                    desc->WriteToOutput(v_netmsg);
                                //CDBCmd::_CDBCmd(&dbcmd, 2);
                                //CNetMsg::_CNetMsg(&v_netmsg, 2);
                            }
                        }
                        else
                        {
                            HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 23);
                            if ( desc )
                                desc->WriteToOutput(v_netmsg);
                            //CNetMsg::_CNetMsg(&v_netmsg, 2);
                        }
                    }
                    else
                    {
                        HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 23);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                }
                else
                {
                    HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 22);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
            }
        }
        else
        {
            HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 10);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
        }
    }
    else
    {
        HelperGuildMemberKickRepMsg(v_netmsg, guildidx, memberidx, charindex, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandGuildMemberOutReq(CNetMsg &netmsg, CDescriptor *desc)
{
    //CNetMsg *v2; // eax@1
    int gcharindex; // [sp+Ch] [bp-1Ch]@1
    int guildidx; // [sp+10h] [bp-18h]@1
    //int v5; // [sp+14h] [bp-14h]@1

    //CNetMsg::CNetMsg((CNetMsg *)&v5);
    netmsg.__rs(guildidx);
    netmsg.__rs(gcharindex);
    do_CommandGuildMemberOutReq_real(desc, guildidx, gcharindex);
    //CNetMsg::_CNetMsg((CNetMsg *)&v5, 2);
}

void do_CommandGuildMemberOutReq_real(CDescriptor *desc, int gindex, int gcharindex)
{

    CGuildMember *t_member; // [sp+103Ch] [bp-1Ch]@9
    CGuild *t_guild; // [sp+1040h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+1044h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    t_guild = g_guildlist.findguild(gindex);
    if ( t_guild )
    {
        if ( t_guild->boss()->charindex() == gcharindex )
        {
            HelperGuildMemberOutRepMsg(v_netmsg, gindex, gcharindex, 20);
            if ( desc )
                desc->WriteToOutput(v_netmsg);
            //CNetMsg::_CNetMsg(&v_netmsg, 2);
        }
        else
        {
            t_member = t_guild->findmember(gcharindex, 0);
            if ( t_member )
            {
                if ( t_member->pos() )
                {
                    sprintf(g_buf, "DELETE FROM t_guildmember WHERE a_guild_index=%d AND a_char_index=%d", gindex, gcharindex);
                    //CDBCmd::CDBCmd(&dbcmd);
                    CDBCmd dbcmd;
                    dbcmd.Init(&g_mysql);
                    dbcmd.SetQuery(g_buf);
                    if ( dbcmd.Update() )
                    {
                        sprintf(g_buf, "UPDATE t_guild SET a_recentdate=NOW() WHERE a_index=%d", gindex);
                        dbcmd.SetQuery(g_buf);
                        dbcmd.Update();
                        g_gamelogbuffer.__ls(init("GUILD MEMBER OUT"));
                        g_gamelogbuffer.__ls(t_guild->index());
                        g_gamelogbuffer.__ls(" : ");
                        g_gamelogbuffer.__ls(t_guild->name());
                        g_gamelogbuffer.__ls(" : ");
                        g_gamelogbuffer.__ls("CHARACTER");
                        g_gamelogbuffer.__ls(" : ");
                        g_gamelogbuffer.__ls(t_member->charindex());
                        g_gamelogbuffer.__ls(" : ");
                        g_gamelogbuffer.__ls(t_member->name());
                        g_gamelogbuffer.__ls(end);

                        HelperGuildMemberOutNotifyMsg(v_netmsg, gindex, gcharindex, t_member->name() );

                        gserver.SendToAllGameServer(v_netmsg);
                        t_guild->removemember(t_member);
                        HelperGuildMemberOutRepMsg(v_netmsg, gindex, gcharindex, 0);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //CDBCmd::_CDBCmd(&dbcmd, 2);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                    else
                    {
                        HelperGuildMemberOutRepMsg(v_netmsg, gindex, gcharindex, 22);
                        if ( desc )
                            desc->WriteToOutput(v_netmsg);
                        //CDBCmd::_CDBCmd(&dbcmd, 2);
                        //CNetMsg::_CNetMsg(&v_netmsg, 2);
                    }
                }
                else
                {
                    HelperGuildMemberOutRepMsg(v_netmsg, gindex, gcharindex, 20);
                    if ( desc )
                        desc->WriteToOutput(v_netmsg);
                    //CNetMsg::_CNetMsg(&v_netmsg, 2);
                }
            }
            else
            {
                HelperGuildMemberOutRepMsg(v_netmsg, gindex, gcharindex, 22);
                if ( desc )
                    desc->WriteToOutput(v_netmsg);
                //CNetMsg::_CNetMsg(&v_netmsg, 2);
            }
        }
    }
    else
    {
        HelperGuildMemberOutRepMsg(v_netmsg, gindex, gcharindex, 9);
        if ( desc )
            desc->WriteToOutput(v_netmsg);
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandGuildOnline(CNetMsg &netmsg, CDescriptor *desc)
{
    CGuildMember *t_member; // [sp+10h] [bp-28h]@3
    CGuild *t_guild; // [sp+14h] [bp-24h]@1
    char v6; // [sp+1Bh] [bp-1Dh]@1
    int memberidx; // [sp+1Ch] [bp-1Ch]@1
    int guildidx; // [sp+20h] [bp-18h]@1
    CNetMsg v_netmsg; // [sp+24h] [bp-14h]@1

    //CNetMsg::CNetMsg(&v_netmsg);
    netmsg.__rs(guildidx);
    netmsg.__rs(memberidx);
    netmsg.__rs(v6);
    t_guild = g_guildlist.findguild(guildidx);
    if ( t_guild )
    {
        t_member = t_guild->findmember(memberidx, 0);
        if ( t_member )
        {
            t_member->online(v6);
            HelperGuildOnlineNotifyMsg(v_netmsg, t_member);

            gserver.SendToAllGameServer(v_netmsg);
        }
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
    else
    {
        //CNetMsg::_CNetMsg(&v_netmsg, 2);
    }
}

void do_CommandShutdown(CNetMsg &netmsg, CDescriptor *desc)
{
    g_Shutdown = 1;
}
