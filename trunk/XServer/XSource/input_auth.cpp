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

#include "input_auth.h"
#include "Server.h"
#include "XNPC.h"

int CInputAuth::Analyze(XDESC *descriptor, unsigned char header, const char *data, int len)
{
    XNPC *npc;

    switch(header)
    {
    case 3:
        this->RecvLoginMessage(descriptor, data, len);
        return 0;
    case 4:
        this->SendSelectMapIndex(descriptor);
        return 0;
    case 5:
        descriptor->xCharacter = new XPC();
        descriptor->xCharacter->xDesc = descriptor;

        npc = new XNPC();
        descriptor->xCharacter->SetPosition(1806.f, 369.f, 100.f, 0);
        npc->SetPosition(1806.f, 369.f, 100.f, 0);

        this->SendAtMessage(descriptor);
        this->SendStatusMessage(descriptor);
        this->SendStatPointsFree(descriptor);
        this->SendGameTime(descriptor);
        gserver.xMaps.at(0)->CharacterEnterMap(npc, 1806.f, 369.f);
        gserver.xMaps.at(0)->CharacterEnterMap(descriptor->xCharacter, 1806.f, 369.f);
        return 0;
    case 12:
        this->RecvMove(descriptor, data, len);
        return 0;
	case 38:
        this->RecvAliveMessage(descriptor, data, len);
        return 0;
    }

    sys_err(__FUNCTION__, __LINE__, "This phase does not handle this header %d (0x%x)(phase: AUTH)", header, header);
    return 0;
}

void CInputAuth::RecvLoginMessage(XDESC *xDesc, const char *data, int len)
{
    XPack xPacket(data, len);

    char szUsername[XCP_MAX_STRING_LENGTH], szPassword[XCP_MAX_STRING_LENGTH], szUnknown[XCP_MAX_STRING_LENGTH];
    int iClientVersion = -1;
    unsigned int iClientEncryptionSeed = 0;
    char eCountry = -1, zPadding = 0;

    xPacket >> iClientVersion;
    xPacket >> zPadding;
    xPacket >> szUsername; // (_pNetwork + 1086308) -> g_nmID
    xPacket >> szPassword; // (_pNetwork + 1086312) -> g_nmPW
    xPacket >> eCountry;
    xPacket >> iClientEncryptionSeed;
    xPacket >> szUnknown; // (_pNetwork + 1086316) -> g_nmCID

    sys_log(0, "Login client: Version %d Username %s Password %s Country %d Seed 0x%08x szUnknown %s", iClientVersion, szUsername, szPassword, eCountry, iClientEncryptionSeed, szUnknown);

    if(g_auth_server) this->SendServerListMessage(xDesc);
    else              this->SendCharacterSelectionScreen(xDesc);

    XDESManager::ElaborateDESKey(xDesc->DESDecryptKey, iClientEncryptionSeed);
    sys_log(0, "Generated login encrypt key 0x%08x 0x%08x seed %u(0x%08x)", xDesc->DESDecryptKey[0], xDesc->DESDecryptKey[1], iClientEncryptionSeed, iClientEncryptionSeed);
}

void CInputAuth::RecvMove(XDESC *xDesc, const char *data, int len)
{
    XPack xPacket(data, len);

    char SubHeader = -1, SubSubHeader = -1;
    int iCharacterID = -1, zPadding = 0;
    float X = 0.0f, Y = 0.0f, Z = 0.0f, R = 0.0f;
    char cUnk = -1; // + 1087096

    xPacket >> SubHeader;
    xPacket >> SubSubHeader;
    xPacket >> iCharacterID;
    xPacket >> zPadding;
    xPacket >> X;
    xPacket >> Y;
    xPacket >> Z;
    xPacket >> R;
    xPacket >> cUnk;

	xDesc->xCharacter->SetPosition(X, Y, Z, R);
	
    sys_log(0, "Move message: SubHeader %d SubSubHeader %d iCharacterID %d zPadding %d X %f Y %f Z %f fR %f cUnk %d Remain %d", SubHeader, SubSubHeader, iCharacterID, zPadding, X, Y, Z, R, cUnk);
}

void CInputAuth::RecvAliveMessage(XDESC *xDesc, const char *data, int len)
{
    XPack xPacket(data, len);
	char eCountry = -1;

    int iLastAliveMsg = -1;
    float iUnknown2 = -1;

    xPacket >> iLastAliveMsg;
    xPacket >> eCountry;
    xPacket >> iUnknown2;

    sys_log(0, "Alive message: iLastAliveMsg (%d seconds) eCountry %d iUnknown2 %f Remain %u", iLastAliveMsg, eCountry, iUnknown2);
}

void CInputAuth::SendCharacterSelectionScreen(XDESC *xDesc)
{
    this->SendCharacterInfo(xDesc);

    XPack xPacket(2, 3);
    int iServerEncryptionSeed = 0;

    srand(time(0));
    iServerEncryptionSeed = rand();

    xPacket << (int)0; // Unk
    xPacket << (int)0; // Unk
    xPacket << (int)iServerEncryptionSeed;

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());

    XDESManager::ElaborateDESKey(xDesc->DESEncryptKey, iServerEncryptionSeed);
    sys_log(0, "Generated login decrypt key 0x%08x 0x%08x seed %u(0x%08x)", xDesc->DESEncryptKey[0], xDesc->DESEncryptKey[1], iServerEncryptionSeed, iServerEncryptionSeed);
}

void CInputAuth::SendServerListMessage(XDESC *xDesc)
{
    XPack xPacket(34);

    xPacket << (int)0; // LastLoggedInServer
    xPacket << (int)0; // LastLoggedInChannel
    xPacket << (int)1; // ServerCount
    xPacket << (int)1;
    xPacket << (int)1; // ServerID
    xPacket << (int)1; // ChannelCount
    xPacket << (char)0; // RecommendedServer

    for(int i = 0; i < 8; i++)
    {
        xPacket << (int)(i + 1); // ChannelID
        xPacket << (int)(1999 + 2); // ChannelState, many other values
        xPacket << "94.23.2.112";
        xPacket << (int)(50101 + i);
    }

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

/** AFTER THIS PACKET THE EXIT THE _bLoginProcess **/
void CInputAuth::SendSelectMapIndex(XDESC *xDesc) // Client handler: ReceiveLoginMessage
{
    XPack xPacket(2, 1);

    xPacket << (int)4; // MapIndex

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

void CInputAuth::SendAtMessage(XDESC *xDesc)
{
    XPack xPacket(9);

    xPacket << (int)6; // CharID
    xPacket << "test123"; // CharID

    xPacket << (char)1; // Class
    xPacket << (char)1; // Job
    xPacket << (char)1; // Hair
    xPacket << (char)1; // Face
    xPacket << (int)4; // ZoneID
    xPacket << (int)100; // Unk
    xPacket << (float)1806.f; // X
    xPacket << (float)369.f; // Z
    xPacket << (float)100.f; // H
    xPacket << (float)0.f; // R

    xPacket << (char)0;
    xPacket << (float)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (char)0;
    xPacket << (int)0; // Title
    xPacket << (int)0;

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

// {int, (long long x2), (int x37), (float x3), (char x4), (int x3), float, (char x2), int, (char x4), int, char, (int x4)}
void CInputAuth::SendStatusMessage(XDESC *descriptor)
{
    XPack xPacket(6);

    xPacket << (int)20; // PlayerLevel
	
    xPacket << (long long)0; // CurrentEXP
    xPacket << (long long)1; // ExpToNextLevel
	
    xPacket << (int)100; // 1. CurrentHP
    xPacket << (int)200; // 2. MaxNormalHP
    xPacket << (int)200; // 3. MaxBoostedHP
    xPacket << (int)2000; // 4. CurrentMP
    xPacket << (int)2200; // 5. MaxNormalMP
    xPacket << (int)2400; // 6. MaxBoostedMP
	
    xPacket << (int)20; // 7. Strength
    xPacket << (int)20; // 8. Dexterity
    xPacket << (int)20; // 9. Intelligence
    xPacket << (int)20; // 10. Constitution
    xPacket << (int)20; // 11. EQStrength
    xPacket << (int)20; // 12. EQDexterity
    xPacket << (int)20; // 13. EQIntelligence
    xPacket << (int)20; // 14. EQConstitution
	
    xPacket << (int)20; // 15. PhysicalAttack1
	xPacket << (int)20; // 16. PhysicalAttack2
    xPacket << (int)20; // 17. MagicAttack1
	xPacket << (int)20; // 18. MagicAttack2
    xPacket << (int)20; // 19. PhysicalDefense1
	xPacket << (int)20; // 20. PhysicalDefense2
    xPacket << (int)20; // 21. MagicDefense
	xPacket << (int)20; // 22. MagicDefense2
    xPacket << (int)20; // 23. PhysicalEvasion1
    xPacket << (int)20; // 24. PhysicalEvasion2
    xPacket << (int)20; // 25. MagicEvasion1
    xPacket << (int)20; // 26. MagicEvasion2
    xPacket << (int)20; // 27. PhysicalHitrate1
    xPacket << (int)20; // 28. PhysicalHitrate2
    xPacket << (int)20; // 29. MagicHitrate1
    xPacket << (int)20; // 30. MagicHitrate2
    xPacket << (int)20; // 31. Critical1
    xPacket << (int)20; // 32. Critical2
    xPacket << (int)20; // 33. Deadly1
    xPacket << (int)20; // 34. Deadly2
	
    xPacket << (int)20000; // 35. SP
    xPacket << (int)0; // 36. Unk (17110) (Not used)
    xPacket << (int)0; // 37. Unk (14360) (Not used)
	
    xPacket << (float)5.f; // WalkSpeed (49215) (Not used)
    xPacket << (float)20.f; // RunSpeed
    xPacket << (float)0.f; //

    xPacket << (char)10; // AttackSpeed (_pNetwork + 1087184))
    xPacket << (char)0; // AttackSpeed (Maledition) (_pNetwork + 1088924)
	
    xPacket << (char)0; // Unk
    xPacket << (char)0; // Unk
	
    xPacket << (int)10; // Karma
    xPacket << (int)20; // PKValue
    xPacket << (int)30; // Reputation
	
    xPacket << (float)10.f; // AttackRange
	
    xPacket << (char)0; // GuildRange -> range (0 - 3) -> Lord (1) -> OpenGuildWarPortal
    xPacket << (char)0; // GuildRange2 -> range (0 - 3) -> Lord (1) -> OpenGuildWarPortalDratan -> NPC?
	
    xPacket << (int)0; // (Not Used) (_pNetwork + 271862)
    xPacket << (char)0; // (Value 60, 10, other)
    xPacket << (char)0; // (Not Used) Horse (13)
    xPacket << (char)0; // Something with pet
    xPacket << (char)0; // (_pNetwork + 1087344) (Value -1, other)
    xPacket << (int)0; // Something with UI
	
    xPacket << (char)0; // NameColor (0 = Blue, 1 = Green, 2 = Green, 3 = Green, 4 = Green, 255-(-1) Blue)
	
    xPacket << (int)0; // SkillCoolTime
    xPacket << (int)0; // DecraseMPConsumption
    xPacket << (int)66666; // (_pNetwork + 272254) EnergySkill
    xPacket << (int)0; // (_pNetwork + 272255) (Not Used)

    descriptor->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

void CInputAuth::SendStatPointsFree(XDESC *xDesc)
{
    XPack xPacket(36, 0);

    xPacket << (int)140;

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

void CInputAuth::SendGameTime(XDESC *xDesc)
{
    XPack xPacket(22, 2);

    //         (Year - 1) (Month - 1) (Day - 1) (Hour)
    xPacket << (int)2011 << (char)0 << (char)0 << (char)1;

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

void CInputAuth::SendCharacterInfo(XDESC *xDesc) // Client handler: ReceiveCharSlot
{
    XPack xPacket(2, 2);

    xPacket << (int)1; // CharacterID
    xPacket << "test123"; // CharacterName

    xPacket << (char)2; // Class
    xPacket << (char)1; // Job
    xPacket << (char)1; // Hair
    xPacket << (char)1; // Face

    xPacket << (int)200; // Level
    xPacket << (long long)10; // LevelCurrentExp
    xPacket << (long long)100; // ExpToNextLevel
    xPacket << (int)20; // SP
    xPacket << (int)2000; // CurrentHP
    xPacket << (int)2000; // MaxHP
    xPacket << (int)2000; // CurrentMP
    xPacket << (int)2000; // MaxMP

    xPacket << (int)0; // HelmetID
    xPacket << (int)0; // Upgrade

    xPacket << (int)26; // ShirtID
    xPacket << (int)15; // Upgrade

    xPacket << (int)0; // WeaponID
    xPacket << (int)0; // Upgrade

    xPacket << (int)28; // PantsID
    xPacket << (int)15; // Upgrade

    xPacket << (int)0; // ShieldID
    xPacket << (int)0; // Upgrade

    xPacket << (int)30; // GlovesID
    xPacket << (int)15; // Upgrade

    xPacket << (int)32; // BootsID
    xPacket << (int)15; // Upgrade

    xPacket << (int)0; // WingID
    xPacket << (int)0; // Upgrade

    xPacket << (int)0; // CharDeletedTime

    xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

enum eAppearType
{
	Character = 0,
	Mob = 1,
	Pet = 2,
	Summon = 3,
    WildPet = 4
};

void CInputAuth::SendAppearMessage(XDESC *xDesc, int NetworkID, int MobIndex, float X, float Y, float Z, float R)
{
	XPack xPacket(7);
	
	xPacket << (char)0; // Unk -> PetAppearMessage
	xPacket << (char)Mob; // Type of appear
	
	this->SendMobAppearMessage(xPacket, NetworkID, MobIndex, X, Y, Z, R);
	xDesc->Packet(xPacket.GetPackData(), xPacket.GetPackLength());
}

// {int, int, float, float, float, float, char, int, int, long long, char}
// Routine on last char {int, int, char, int}
// {char}
// If 2nd int == 482 {float, string, string}
// {int, float, float}

void CInputAuth::SendMobAppearMessage(XPack &xPacket, int NetworkID, int MobIndex, float X, float Y, float Z, float R)
{
	xPacket << (int)NetworkID; // NetworkID
	xPacket << (int)MobIndex; // MobIndex
	xPacket << (float)X; // X
    xPacket << (float)Y; // Y
    xPacket << (float)Z; // Z
    xPacket << (float)R; // R
	xPacket << (char)0; // Unknown (0)
	xPacket << (int)2000; // CurrentHP
	xPacket << (int)4000; // TotalHP
	xPacket << (long long)0; // Effect -> ? (0)
	xPacket << (char)0; // Unknown (0)
	
	xPacket << (char)0; // Unknown (60)
	
    xPacket << (int)-1; // Unknown (-1) -> 0 = Axe (Wood)
	xPacket << (float)0.f; // Unknown (0)
	xPacket << (float)0.f; // StretchModel()
}
