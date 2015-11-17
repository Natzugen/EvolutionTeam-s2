#ifndef __EVENTITEMBAG_H__
#define __EVENTITEMBAG_H__

// Event Item Bag
class CEventItemBagAttrExc
{
public:
	CEventItemBagAttrExc()
	{
		this->m_Type		= 0;
		this->m_Index		= 0;
		this->m_MinLevel	= 0;
		this->m_MaxLevel	= 0;
		this->m_IsSkill		= 0;
		this->m_IsLuck		= 0;
		this->m_IsOption	= 0;
		this->m_IsExcItem	= 0;
	}
	// ------
	char	m_Type;
	short	m_Index;
	char	m_MinLevel;
	char	m_MaxLevel;
	char	m_IsSkill;
	char	m_IsLuck;
	char	m_IsOption;
	char	m_IsExcItem;
};

class CItemBagDropMapInfo
{
public:
	CItemBagDropMapInfo()
	{
		this->Init();
	};
	// ------
	void Init()
	{
		this->m_bIsDrop			= false;
		this->m_MinMonsterLevel = 0;
		this->m_MaxMonsterLevel = 0;
	};
	// ------
	char m_bIsDrop;

	BYTE m_MinMonsterLevel;
	BYTE m_MaxMonsterLevel;
	BYTE m_MonsterLevel;
};

class CEventItemBag
{
public:

	void Init(char* File);
	void Load();
	void LoadFile(char* File);
	int DropEventItem(int aIndex);
	int DropItem(int aIndex);
	int MapDropItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);

	BYTE GetMinLevel(int n);
	BYTE GetMaxLevel(int n);
	int PickItem(CItem& objItem,int& nItemIndex);

private:

	int GetBagCount(){return this->m_iBagObjectCount;}
	int IsEnableEventItemDrop(int aIndex);
	BYTE GetLevel(int n);

private:

	BOOL m_bLoad;
	char m_sEventName[255];
	int m_iEventItemDropZen;
	int m_iEventItemType;
	int m_iEventItemLevel;
	int m_iEventItemDropRate;
	int m_iItemDropRate;
	int m_iExItemDropRate;
	int m_iBagObjectCount;

	CItemBagDropMapInfo	DropMapInfo[50];
	CEventItemBagAttrExc EventBagObject[200];
};

BYTE NewOptionRand(int level);

extern CEventItemBag * HatcheryDrop;
extern CEventItemBag * GoldenArcherDrop;
extern CEventItemBag * NightmareDrop;
extern CEventItemBag * MayaDrop;

#endif