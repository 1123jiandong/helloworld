#ifndef CFG_ARGS_H
#define CFG_ARGS_H

enum CmdType
{
	CmdType_Space = 0x00,
	CmdType_HightLight = 0x01,
	CmdType_UnHighLight = 0x02,
	CmdType_Display = 0x04,
	CmdType_Hide = 0x08,
};

enum TarGets
{
	Targets_Unknow = 0x00,
	TarGets_Servere = 0x01,
	TarGets_Client = 0x02,
	TarGets_3D = 0x04,
	TarGets_GIS = 0x08
};

#endif