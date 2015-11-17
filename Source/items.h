/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef ITEMS_H
	#define ITEMS_H

#define SLOT_EMPTY -1

#define MAKEITEMID(group, index) (group * 512 + index)
// Item Macros
#define ITEMGET(x,y) ((x) * 512 + (y)) 

enum PLAYER_WARDROBE 
{
	WEAPON_01	= 0,	
	WEAPON_02	= 1,	
	HELMET	= 2,	
	ARMOR		= 3,	
	PANTS		= 4,	
	GLOVES	= 5,	
	BOOTS		= 6,	
	WINGS		= 7,	
	GUARDIAN	= 8,	
	PENDANT	= 9,	
	RING_01	= 10,	
	RING_02	= 11,	
};

enum ITEMCREATE_PLACE 
{
	INVENTORY	= 0xeb,
	CHAOSBOX	= 0xff,
};

enum VIEWPORT_WINGS03 
{
	WINGS_OF_STORM		= 0x07,
	WINGS_OF_VORTEX		= 0x08,
	WINGS_OF_ILLUSION		= 0x0c,
	WINGS_OF_HURRICANE	= 0x10,
	MANTLE_OF_MONARCH		= 0x14,
};

enum VIEWPORT_FENRIR 
{
	FENRIR_TYPE		    	= 0x1a25,
	FENRIR_EMPTY	    	= 0x00,
	FENRIR_GOLD	        	= 0x03,
};

enum VIEWPORT_QUEST03_ITEMS 
{
	FLAME_OF_DEATH		= 0x1c41,
	HELL_MAINE_HORN	    	= 0x1c42,
	PHOENIX_FEATHER     	= 0x1c43,
};
struct ITEM_ATTRIBUTE // Size 0x6C
{
  /*<thisrel this+0x0>*/ /*|0x20|*/ char Name[32];
  /*<thisrel this+0x20>*/ /*|0x1|*/ unsigned char HaveItemInfo;
  /*<thisrel this+0x21>*/ /*|0x1|*/ unsigned char TwoHand;
  /*<thisrel this+0x22>*/ /*|0x1|*/ unsigned char Level;
  /*<thisrel this+0x23>*/ /*|0x1|*/ unsigned char Width;
  /*<thisrel this+0x24>*/ /*|0x1|*/ unsigned char Height;
  /*<thisrel this+0x25>*/ /*|0x1|*/ char Serial;
  /*<thisrel this+0x26>*/ /*|0x1|*/ unsigned char OptionFlag;
  /*<thisrel this+0x27>*/ /*|0x1|*/ unsigned char MondownFlag;
  /*<thisrel this+0x28>*/ /*|0x1|*/ unsigned char AttackSpeed;
  /*<thisrel this+0x29>*/ /*|0x1|*/ unsigned char WalkSpeed;
  /*<thisrel this+0x2a>*/ /*|0x1|*/ unsigned char DamageMin;
  /*<thisrel this+0x2b>*/ /*|0x1|*/ unsigned char DamageMax;
  /*<thisrel this+0x2c>*/ /*|0x1|*/ unsigned char SuccessfulBlocking;
  /*<thisrel this+0x2d>*/ /*|0x1|*/ unsigned char Defense;
  /*<thisrel this+0x2e>*/ /*|0x1|*/ unsigned char MagicDefense;
  /*<thisrel this+0x2f>*/ /*|0x1|*/ unsigned char Speed;
  /*<thisrel this+0x30>*/ /*|0x1|*/ unsigned char Durability;
  /*<thisrel this+0x31>*/ /*|0x1|*/ unsigned char MagicDurability;
  /*<thisrel this+0x32>*/ /*|0x1|*/ unsigned char AttackDur;
  /*<thisrel this+0x33>*/ /*|0x1|*/ unsigned char DefenceDur;
  /*<thisrel this+0x34>*/ /*|0x2|*/ unsigned short RequireStrength;
  /*<thisrel this+0x36>*/ /*|0x2|*/ unsigned short RequireDexterity;
  /*<thisrel this+0x38>*/ /*|0x2|*/ unsigned short RequireEnergy;
  /*<thisrel this+0x3a>*/ /*|0x2|*/ unsigned short RequireLevel;
  /*<thisrel this+0x3c>*/ /*|0x2|*/ unsigned short Value;
  /*<thisrel this+0x3e>*/ /*|0x5|*/ unsigned char RequireClass[5];
  /*<thisrel this+0x43>*/ /*|0x7|*/ unsigned char Resistance[7];
  /*<thisrel this+0x4a>*/ /*|0x2|*/ unsigned short RequireVitality;
  /*<thisrel this+0x4c>*/ /*|0x4|*/ int BuyMoney;
  /*<thisrel this+0x50>*/ /*|0x4|*/ int MagicPW;
  /*<thisrel this+0x54>*/ /*|0x4|*/ float RepaireMoneyRate;
  /*<thisrel this+0x58>*/ /*|0x4|*/ float AllRepaireMoneyRate;
  /*<thisrel this+0x5c>*/ /*|0x1|*/ unsigned char QuestItem;
  /*<thisrel this+0x5d>*/ /*|0x1|*/ unsigned char SetAttr;
  /*<thisrel this+0x5e>*/ /*|0x1|*/ unsigned char ResistanceType;
  /*<thisrel this+0x60>*/ /*|0x4|*/ int ItemSlot;
  /*<thisrel this+0x64>*/ /*|0x4|*/ int SkillType;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int RequireLeadership;
};

// Expand Item Attributes
extern ITEM_ATTRIBUTE ItemAttribute[16 * 512];
struct CItem // Size 0xB0
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ unsigned long m_Number;
  /*<thisrel this+0x4>*/ /*|0x1|*/ char m_serial;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short m_Type;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short m_Level;
  /*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char m_Part;
  /*<thisrel this+0xb>*/ /*|0x1|*/ unsigned char m_Class;
  /*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char m_TwoHand;
  /*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char m_AttackSpeed;
  /*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char m_WalkSpeed;
  /*<thisrel this+0x10>*/ /*|0x2|*/ unsigned short m_DamageMin;
  /*<thisrel this+0x12>*/ /*|0x2|*/ unsigned short m_DamageMax;
  /*<thisrel this+0x14>*/ /*|0x1|*/ unsigned char m_SuccessfulBlocking;
  /*<thisrel this+0x16>*/ /*|0x2|*/ unsigned short m_Defense;
  /*<thisrel this+0x18>*/ /*|0x2|*/ unsigned short m_MagicDefense;
  /*<thisrel this+0x1a>*/ /*|0x1|*/ unsigned char m_Speed;
  /*<thisrel this+0x1c>*/ /*|0x2|*/ unsigned short m_DamageMinOrigin;
  /*<thisrel this+0x1e>*/ /*|0x2|*/ unsigned short m_DefenseOrigin;
  /*<thisrel this+0x20>*/ /*|0x2|*/ unsigned short m_Magic;
  /*<thisrel this+0x24>*/ /*|0x4|*/ float m_Durability;
  /*<thisrel this+0x28>*/ /*|0x2|*/ unsigned short m_DurabilitySmall;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ float m_BaseDurability;
  /*<thisrel this+0x30>*/ /*|0x1|*/ unsigned char m_SpecialNum;
  /*<thisrel this+0x31>*/ /*|0x8|*/ unsigned char m_Special[8];
  /*<thisrel this+0x39>*/ /*|0x8|*/ unsigned char m_SpecialValue[8];
  /*<thisrel this+0x42>*/ /*|0x2|*/ unsigned short m_RequireStrength;
  /*<thisrel this+0x44>*/ /*|0x2|*/ unsigned short m_RequireDexterity;
  /*<thisrel this+0x46>*/ /*|0x2|*/ unsigned short m_RequireEnergy;
  /*<thisrel this+0x48>*/ /*|0x2|*/ unsigned short m_RequireLevel;
  /*<thisrel this+0x4a>*/ /*|0x2|*/ unsigned short m_RequireVitality;
  /*<thisrel this+0x4c>*/ /*|0x2|*/ unsigned short m_RequireLeaderShip;
  /*<thisrel this+0x4e>*/ /*|0x2|*/ unsigned short m_Leadership;
  /*<thisrel this+0x50>*/ /*|0x5|*/ unsigned char m_RequireClass[5];
  /*<thisrel this+0x55>*/ /*|0x7|*/ unsigned char m_Resistance[7];
  /*<thisrel this+0x5c>*/ /*|0x4|*/ int m_Value;
  /*<thisrel this+0x60>*/ /*|0x4|*/ unsigned long m_SellMoney;
  /*<thisrel this+0x64>*/ /*|0x4|*/ unsigned long m_BuyMoney;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int m_iPShopValue;
  /*<thisrel this+0x6c>*/ /*|0x1|*/ unsigned char m_bItemExist;
  /*<thisrel this+0x70>*/ /*|0x4|*/ int m_OldSellMoney;
  /*<thisrel this+0x74>*/ /*|0x4|*/ int m_OldBuyMoney;
  /*<thisrel this+0x78>*/ /*|0x1|*/ unsigned char m_Option1;
  /*<thisrel this+0x79>*/ /*|0x1|*/ unsigned char m_Option2;
  /*<thisrel this+0x7a>*/ /*|0x1|*/ unsigned char m_Option3;
  /*<thisrel this+0x7b>*/ /*|0x1|*/ unsigned char m_NewOption;
  /*<thisrel this+0x7c>*/ /*|0x10|*/ float m_DurabilityState[4];
  /*<thisrel this+0x8c>*/ /*|0x4|*/ float m_CurrentDurabilityState;
  /*<thisrel this+0x90>*/ /*|0x1|*/ unsigned char m_SkillChange;
  /*<thisrel this+0x91>*/ /*|0x1|*/ unsigned char m_QuestItem;
  /*<thisrel this+0x92>*/ /*|0x1|*/ unsigned char m_SetOption;
  /*<thisrel this+0x93>*/ /*|0x1|*/ unsigned char m_SetAddStat;
  /*<thisrel this+0x94>*/ /*|0x1|*/ unsigned char m_IsValidItem;
  /*<thisrel this+0x95>*/ /*|0x7|*/ unsigned char m_SkillResistance[7];
  /*<thisrel this+0x9c>*/ /*|0x4|*/ int m_IsLoadPetItemInfo;
  /*<thisrel this+0xa0>*/ /*|0x4|*/ int m_PetItem_Level;
  /*<thisrel this+0xa4>*/ /*|0x4|*/ int m_PetItem_Exp;
  /*<thisrel this+0xa8>*/ /*|0x1|*/ unsigned char m_JewelOfHarmonyOption;
  /*<thisrel this+0xaa>*/ /*|0x2|*/ unsigned short m_HJOpStrength;
  /*<thisrel this+0xac>*/ /*|0x2|*/ unsigned short m_HJOpDexterity;
  /*<thisrel this+0xae>*/ /*|0x1|*/ unsigned char m_ItemOptionEx;
};
struct ITEMSTRUCT 
{
	/*0x0>	|0x4|*/ unsigned long m_Number;
	/*0x4>	|0x1|*/ char m_serial;
	/*0x6>	|0x2|*/ short m_Type;
	/*0x8>	|0x2|*/ short m_Level;
	/*0xa>	|0x1|*/ unsigned char m_Part;
	/*0xb>	|0x1|*/ unsigned char m_Class;
	/*0xc>	|0x1|*/ unsigned char m_TwoHand;
	/*0xd>	|0x1|*/ unsigned char m_AttackSpeed;
	/*0xe>	|0x1|*/ unsigned char m_WalkSpeed;
	/*0x10>	|0x2|*/ unsigned short m_DamageMin;
	/*0x12>	|0x2|*/ unsigned short m_DamageMax;
	/*0x14>	|0x1|*/ unsigned char m_SuccessfulBlocking;
	/*0x16>	|0x2|*/ unsigned short m_Defense;
	/*0x18>	|0x2|*/ unsigned short m_MagicDefense;
	/*0x1a>	|0x1|*/ unsigned char m_Speed;
	/*0x1c>	|0x2|*/ unsigned short m_DamageMinOrigin;
	/*0x1e>	|0x2|*/ unsigned short m_DefenseOrigin;
	/*0x20>	|0x2|*/ unsigned short m_Magic;
	/*0x24>	|0x4|*/ float m_Durability;
	/*0x28>	|0x2|*/ unsigned short m_DurabilitySmall;
	/*0x2c>	|0x4|*/ float m_BaseDurability;
	/*0x30>	|0x1|*/ unsigned char m_SpecialNum;
	/*0x31>	|0x8|*/ unsigned char m_Special[8];
	/*0x39>	|0x8|*/ unsigned char m_SpecialValue[8];
	/*0x42>	|0x2|*/ unsigned short m_RequireStrength;
	/*0x44>	|0x2|*/ unsigned short m_RequireDexterity;
	/*0x46>	|0x2|*/ unsigned short m_RequireEnergy;
	/*0x48>	|0x2|*/ unsigned short m_RequireLevel;
	/*0x4a>	|0x2|*/ unsigned short m_RequireVitality;
	/*0x4c>	|0x2|*/ unsigned short m_RequireLeaderShip;
	/*0x4e>	|0x2|*/ unsigned short m_Leadership;
	/*0x50>	|0x5|*/ unsigned char m_RequireClass[5];
	/*0x55>	|0x7|*/ unsigned char m_Resistance[7];
	/*0x5c>	|0x4|*/ int m_Value;
	/*0x60>	|0x4|*/ unsigned long m_SellMoney;
	/*0x64>	|0x4|*/ unsigned long m_BuyMoney;
	/*0x68>	|0x4|*/ int m_iPShopValue;
	/*0x6c>	|0x1|*/ unsigned char m_bItemExist;
	/*0x70>	|0x4|*/ int m_OldSellMoney;
	/*0x74>	|0x4|*/ int m_OldBuyMoney;
	/*0x78>	|0x1|*/ unsigned char m_Option1;
	/*0x79>	|0x1|*/ unsigned char m_Option2;
	/*0x7a>	|0x1|*/ unsigned char m_Option3;
	/*0x7b>	|0x1|*/ unsigned char m_NewOption;
	/*0x7c>	|0x10|*/float m_DurabilityState[4];
	/*0x8c>	|0x4|*/ float m_CurrentDurabilityState;
	/*0x90>	|0x1|*/ unsigned char m_SkillChange;
	/*0x91>	|0x1|*/ unsigned char m_QuestItem;
	/*0x92>	|0x1|*/ unsigned char m_SetOption;
	/*0x93>	|0x1|*/ unsigned char m_SetAddStat;
	/*0x94>	|0x1|*/ unsigned char m_IsValidItem;
	/*0x95>	|0x7|*/ unsigned char m_SkillResistance[7];
	/*0x9c>	|0x4|*/ int m_IsLoadPetItemInfo;
	/*0xa0>	|0x4|*/ int m_PetItem_Level;
	/*0xa4>	|0x4|*/ int m_PetItem_Exp;
	/*0xa8>	|0x1|*/ unsigned char m_JewelOfHarmonyOption;
	/*0xaa>	|0x2|*/ unsigned short m_HJOpStrength;
	/*0xac>	|0x2|*/ unsigned short m_HJOpDexterity;
	/*0xae>	|0x1|*/ unsigned char m_ItemOptionEx;
};

#endif //~ITEMS_H
