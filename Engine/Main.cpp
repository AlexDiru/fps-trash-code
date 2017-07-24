#include <DarkGDK.h>
#include <SC_Collision.h>
#include <Free.h>
#include "GameStructs.h"
#include <ImageText.h>

//Always export maps with true left-hand data

//BUGS

//STUFF TO WORK ON
//---Positioning all guns
//---Muzzleflash positioning for all guns
//---Mouseclick show/hide muzzleflash
//---Add an extra frame for the muzzle flash

float TIMERUPDATE;

#define GUNNUMBER 9
#define MIDDLEOFSCREEN dbScreenWidth()/2,dbScreenHeight()/2

#define GUN_COLT 0 
#define GUN_SHOTGUN 1 //done
#define GUN_FAMAS 2 //done
#define GUN_AUG 3 //done
#define GUN_DEAGLE 4
#define GUN_AK 5
#define GUN_SNIPER 6 //done
#define GUN_LMG 7 //done

actor user[1];

float GetDist(int Obj1,int Obj2)
{
	float X,Y,Z;
	X = dbObjectPositionX(Obj1) - dbObjectPositionX(Obj2);
	Y = dbObjectPositionY(Obj1) - dbObjectPositionY(Obj2);
	Z = dbObjectPositionZ(Obj1) - dbObjectPositionZ(Obj2);
	return dbSqrt(X*X+Y*Y+Z*Z);
}

#pragma region TimerCommands

void tm_init ()
{
   user[0].tm_timer = dbTimer();
   user[0].tm_last = user[0].tm_timer;
   user[0].tm_factor = 1;
}

float tm_update ()
{
   user[0].tm_timer = dbTimer();
   user[0].tm_difference = user[0].tm_timer - user[0].tm_last;
   user[0].tm_last = user[0].tm_timer;
   user[0].tm_result = user[0].tm_difference * user[0].tm_factor;
   return user[0].tm_result;
}
void tm_setmultiplicator ( float f_flt )
{
   user[0].tm_factor = f_flt;
}
float tm_getfactor ()
{
   float f_flt = 0;
   f_flt = user[0].tm_result;
   return f_flt;
}

#pragma endregion

void DarkGDK()
{

#pragma region Should be loaded from files
	//Load the muzzleflash texture under MFT
	int MFT = FImg();
	dbLoadImage("Media//Guns//mflash.dds",MFT);

	weapon gun[8];

	gun[GUN_FAMAS].id = FObj();
	gun[GUN_FAMAS].tid = FImg();
	gun[GUN_FAMAS].moveup = -2;
	gun[GUN_FAMAS].moveleft = 1;
	gun[GUN_FAMAS].movefor = 1;
	gun[GUN_FAMAS].yrot = 180;
	gun[GUN_FAMAS].modelfile = "Media//Guns//famas.dbo";
	gun[GUN_FAMAS].textfile = "Media//Guns//famas_tex.dds";
	gun[GUN_FAMAS].sc = 9;
	gun[GUN_FAMAS].bobang = 0;
	gun[GUN_FAMAS].bobspd = 4;
	gun[GUN_FAMAS].bobmov = 0.15;
	gun[GUN_FAMAS].bobhgt = 0.1;
	gun[GUN_FAMAS].muzright = -1.35;
	gun[GUN_FAMAS].mtx = MFT;
	gun[GUN_FAMAS].scopefov = 0;

	gun[GUN_AUG].id = FObj();
	gun[GUN_AUG].tid = FImg();
	gun[GUN_AUG].moveup = -2.5;
	gun[GUN_AUG].moveleft = -1.5;
	gun[GUN_AUG].movefor = 0.2;
	gun[GUN_AUG].yrot = 180;
	gun[GUN_AUG].modelfile = "Media//Guns//aug.dbo";
	gun[GUN_AUG].textfile = "Media//Guns//aug_tex.dds";
	gun[GUN_AUG].sc = 9;
	gun[GUN_AUG].bobang = 0;
	gun[GUN_AUG].bobspd = 4;
	gun[GUN_AUG].bobmov = 0.15;
	gun[GUN_AUG].bobhgt = 0.1;
	gun[GUN_AUG].muzright = -0.96;
	gun[GUN_AUG].muzfor = -1;
	gun[GUN_AUG].muzup = -0.5;
	gun[GUN_AUG].mtx = MFT;
	gun[GUN_AUG].scopefov = 30;

	gun[GUN_SNIPER].id = FObj();
	gun[GUN_SNIPER].tid = FImg();
	gun[GUN_SNIPER].moveup = -3.4;
	gun[GUN_SNIPER].moveleft = 1.5;
	gun[GUN_SNIPER].movefor = -1.5;
	gun[GUN_SNIPER].yrot = 180;
	gun[GUN_SNIPER].modelfile = "Media//Guns//spr.dbo";
	gun[GUN_SNIPER].textfile = "Media//Guns//spr_tex.dds";
	gun[GUN_SNIPER].sc = 18;
	gun[GUN_SNIPER].bobang = 0;
	gun[GUN_SNIPER].bobspd = 4;
	gun[GUN_SNIPER].bobmov = 0.15;
	gun[GUN_SNIPER].bobhgt = 0.1;
	gun[GUN_SNIPER].muzright = -1.4;
	gun[GUN_SNIPER].muzfor = -5;
	gun[GUN_SNIPER].muzup = 0.65;
	gun[GUN_SNIPER].mtx = MFT;
	gun[GUN_SNIPER].scopefov = 10;

	gun[GUN_SHOTGUN].id = FObj();
	gun[GUN_SHOTGUN].tid = FImg();
	gun[GUN_SHOTGUN].moveup = -1.3;
	gun[GUN_SHOTGUN].moveleft = 0.95;
	gun[GUN_SHOTGUN].movefor = -1.8;
	gun[GUN_SHOTGUN].yrot = 180;
	gun[GUN_SHOTGUN].modelfile = "Media//Guns//shorty.dbo";
	gun[GUN_SHOTGUN].textfile = "Media//Guns//shorty_tex.dds";
	gun[GUN_SHOTGUN].sc = 20;
	gun[GUN_SHOTGUN].bobang = 0;
	gun[GUN_SHOTGUN].bobspd = 4;
	gun[GUN_SHOTGUN].bobmov = 0.15;
	gun[GUN_SHOTGUN].bobhgt = 0.1;
	gun[GUN_SHOTGUN].muzright = -1.5;
	gun[GUN_SHOTGUN].muzup = -0.8;
	gun[GUN_SHOTGUN].mtx = MFT;
	gun[GUN_SHOTGUN].scopefov = 0;

	gun[GUN_LMG].id = FObj();
	gun[GUN_LMG].tid = FImg();
	gun[GUN_LMG].moveup = -3.5;
	gun[GUN_LMG].moveleft = 1.7;
	gun[GUN_LMG].movefor = 2;
	gun[GUN_LMG].yrot = 180;
	gun[GUN_LMG].modelfile = "Media//Guns//lmg.dbo";
	gun[GUN_LMG].textfile = "Media//Guns//lmg_tex.dds";
	gun[GUN_LMG].sc = 45;
	gun[GUN_LMG].bobang = 0;
	gun[GUN_LMG].bobspd = 4;
	gun[GUN_LMG].bobmov = 0.15;
	gun[GUN_LMG].bobhgt = 0.1;
	gun[GUN_LMG].muzright = -1.8;
	gun[GUN_LMG].muzfor = 0;
	gun[GUN_LMG].muzup = -0.2;
	gun[GUN_LMG].mtx = MFT;
	gun[GUN_LMG].scopefov = 0;
	
	user[0].rtimer = 0;
	user[0].stimer = 0;
	user[0].vtimer = 0;
	user[0].gravity = -0.1f;
	user[0].slope = 0.5f;
	user[0].ground = 1;
	user[0].jumptimer = 0;
	user[0].vx = 0;
	user[0].vy = 0;
	user[0].vz = 0;
	user[0].angy = 0;
	user[0].oldx = 0;
	user[0].oldy = 0;
	user[0].oldz = 0;
	user[0].x = 0;
	user[0].y = 0;
	user[0].z = 0;
	user[0].radius = 6;
	user[0].ny = 0;
	user[0].usinggun = GUN_SNIPER;
	user[0].gunlookang = 90;
	user[0].gunturnang = 90;
#pragma endregion

#pragma region Setup, should use an array for gun pos etc
	dbSyncOn( );
	dbSyncRate( 60 );
	dbAutoCamOff( );
	dbRandomize( dbTimer() );
	SC_Start( );
	dbHideMouse();
	dbSetCameraRange(1,13000);
	dbSetImageColorKey(0,0,0);

	//Make the player - a sphere under the ID of: user[0].id
	user[0].id = FObj();
	dbMakeObjectSphere(user[0].id,user[0].radius*2.0f );
	//dbScaleObject(user[0].id,100,300,100);
	dbPositionObject(user[0].id,0,1000,0 );
	dbXRotateObject(user[0].id,-90);
	//Make the physics sphere shell
	SC_SetupObject(user[0].id,0,1 );

	int FO = FObj();
	int FM = FMes();
	dbMakeObjectSphere(FO,1);
	dbMakeMeshFromObject(FM,FO);
	dbDeleteObject(FO);
	dbAddLimb(user[0].id,1,FM);
	dbHideLimb(user[0].id,1);
	dbAddLimb(user[0].id,2,FM);
	dbHideLimb(user[0].id,2);

	dbOffsetLimb(user[0].id,2,0,0,5);
	dbDeleteMesh(FM);

	struct LEVEL
	{
		int id;
	};

	LEVEL lvl[8];
//	/*
	//NOKKAKUDAIHEIGHTS
	lvl[0].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart1.x",lvl[0].id);
	lvl[1].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart2.x",lvl[1].id);
	lvl[2].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart3.x",lvl[2].id);
	lvl[3].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart4.x",lvl[3].id);
	lvl[4].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart5.x",lvl[4].id);
	lvl[5].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart6.x",lvl[5].id);
	lvl[6].id = FObj();
	dbLoadObject("Media//Maps//NokkakuDaiHeightsPart7.x",lvl[6].id);


	int sky = FObj();
	dbMakeObjectSphere(sky,13000);
	dbColorObject(sky,dbRGB(204,102,0));
	dbSetObjectCull(sky,0);
	dbSetObjectFilter (sky,0);
//	*/
///*
	//lvl[0].id = FObj();
	//dbLoadObject("Media//Maps//ShibuyaTerminalBusStation1.x",lvl[0].id);
	for (int i=0;i<7;i++)
	{
		dbXRotateObject(lvl[i].id,90);
		SC_SetupObject( lvl[i].id,1,0);
	}
//*/
	//Make the FAMAS gun
	gun[GUN_FAMAS].id = FObj();
	gun[GUN_FAMAS].tid = FImg();
	dbLoadObject(gun[GUN_FAMAS].modelfile,gun[GUN_FAMAS].id);
	dbLoadImage(gun[GUN_FAMAS].textfile,gun[GUN_FAMAS].tid);
	dbScaleObject(gun[GUN_FAMAS].id,gun[GUN_FAMAS].sc,gun[GUN_FAMAS].sc,gun[GUN_FAMAS].sc); 
	dbYRotateObject(gun[GUN_FAMAS].id,gun[GUN_FAMAS].yrot);
	dbMoveObjectUp(gun[GUN_FAMAS].id,gun[GUN_FAMAS].moveup);
	dbMoveObjectLeft(gun[GUN_FAMAS].id,gun[GUN_FAMAS].moveleft);
	dbMoveObject(gun[GUN_FAMAS].id,gun[GUN_FAMAS].movefor);
	dbTextureObject(gun[GUN_FAMAS].id,gun[GUN_FAMAS].tid);
	dbSetObjectCull(gun[GUN_FAMAS].id,0);
	dbGlueObjectToLimb(gun[GUN_FAMAS].id,user[0].id,1);
	//Make the FAMAS muzzleflash
	gun[GUN_FAMAS].mid = FObj();
	dbMakeObjectPlain(gun[GUN_FAMAS].mid,2,2);
	//dbSetAlphaMappingOn(gun[GUN_FAMAS].mid,30);
	dbSetObjectTransparency(gun[GUN_FAMAS].mid,1);
	dbTextureObject(gun[GUN_FAMAS].mid,MFT);
	dbGlueObjectToLimb(gun[GUN_FAMAS].mid,user[0].id,2);
	dbSetObjectLight(gun[GUN_FAMAS].mid,0);
	dbMoveObjectRight(gun[GUN_FAMAS].mid,gun[GUN_FAMAS].muzright);
	dbHideObject(gun[GUN_FAMAS].mid);
	/**/
	//dbSetObjectCull(gun[GUN_FAMAS].mid,0);

	//Make the AUG gun
	gun[GUN_AUG].id = FObj();
	gun[GUN_AUG].tid = FImg();
	dbLoadObject(gun[GUN_AUG].modelfile,gun[GUN_AUG].id);
	dbLoadImage(gun[GUN_AUG].textfile,gun[GUN_AUG].tid);
	dbScaleObject(gun[GUN_AUG].id,gun[GUN_AUG].sc,gun[GUN_AUG].sc,gun[GUN_AUG].sc); 
	dbYRotateObject(gun[GUN_AUG].id,gun[GUN_AUG].yrot);
	dbMoveObjectUp(gun[GUN_AUG].id,gun[GUN_AUG].moveup);
	dbMoveObjectLeft(gun[GUN_AUG].id,gun[GUN_AUG].moveleft);
	dbMoveObject(gun[GUN_AUG].id,gun[GUN_AUG].movefor);
	dbTextureObject(gun[GUN_AUG].id,gun[GUN_AUG].tid);
	dbSetObjectCull(gun[GUN_AUG].id,0);
	dbGlueObjectToLimb(gun[GUN_AUG].id,user[0].id,1);
	//Make the AUG muzzleflash
	gun[GUN_AUG].mid = FObj();
	dbMakeObjectPlain(gun[GUN_AUG].mid,2,2);
	dbSetAlphaMappingOn(gun[GUN_AUG].mid,30);
	dbSetObjectTransparency(gun[GUN_AUG].mid,1);
	dbTextureObject(gun[GUN_AUG].mid,MFT);
	dbGlueObjectToLimb(gun[GUN_AUG].mid,user[0].id,2);
	dbSetObjectLight(gun[GUN_AUG].mid,0);
	dbMoveObjectRight(gun[GUN_AUG].mid,gun[GUN_AUG].muzright);
	dbMoveObject(gun[GUN_AUG].mid,gun[GUN_AUG].muzfor);
	dbMoveObjectUp(gun[GUN_AUG].mid,gun[GUN_AUG].muzup);
	dbHideObject(gun[GUN_AUG].mid);
	
	//Make the SNIPER gun
	gun[GUN_SNIPER].id = FObj();
	gun[GUN_SNIPER].tid = FImg();
	dbLoadObject(gun[GUN_SNIPER].modelfile,gun[GUN_SNIPER].id);
	dbLoadImage(gun[GUN_SNIPER].textfile,gun[GUN_SNIPER].tid);
	dbScaleObject(gun[GUN_SNIPER].id,gun[GUN_SNIPER].sc,gun[GUN_SNIPER].sc,gun[GUN_SNIPER].sc); 
	dbYRotateObject(gun[GUN_SNIPER].id,gun[GUN_SNIPER].yrot);
	dbMoveObjectUp(gun[GUN_SNIPER].id,gun[GUN_SNIPER].moveup);
	dbMoveObjectLeft(gun[GUN_SNIPER].id,gun[GUN_SNIPER].moveleft);
	dbMoveObject(gun[GUN_SNIPER].id,gun[GUN_SNIPER].movefor);
	dbTextureObject(gun[GUN_SNIPER].id,gun[GUN_SNIPER].tid);
	dbSetObjectCull(gun[GUN_SNIPER].id,0);
	dbGlueObjectToLimb(gun[GUN_SNIPER].id,user[0].id,1);
	//Make the SNIPER muzzleflash
	gun[GUN_SNIPER].mid = FObj();
	dbMakeObjectPlain(gun[GUN_SNIPER].mid,2,2);
	dbSetAlphaMappingOn(gun[GUN_SNIPER].mid,30);
	dbSetObjectTransparency(gun[GUN_SNIPER].mid,1);
	dbTextureObject(gun[GUN_SNIPER].mid,MFT);
	dbGlueObjectToLimb(gun[GUN_SNIPER].mid,user[0].id,2);
	dbSetObjectLight(gun[GUN_SNIPER].mid,0);
	dbMoveObjectRight(gun[GUN_SNIPER].mid,gun[GUN_SNIPER].muzright);
	dbMoveObject(gun[GUN_SNIPER].mid,gun[GUN_SNIPER].muzfor);
	dbMoveObjectUp(gun[GUN_SNIPER].mid,gun[GUN_SNIPER].muzup);
	dbHideObject(gun[GUN_SNIPER].mid);

	//Make the SHOTGUN gun
	gun[GUN_SHOTGUN].id = FObj();
	gun[GUN_SHOTGUN].tid = FImg();
	dbLoadObject(gun[GUN_SHOTGUN].modelfile,gun[GUN_SHOTGUN].id);
	dbLoadImage(gun[GUN_SHOTGUN].textfile,gun[GUN_SHOTGUN].tid);
	dbScaleObject(gun[GUN_SHOTGUN].id,gun[GUN_SHOTGUN].sc,gun[GUN_SHOTGUN].sc,gun[GUN_SHOTGUN].sc); 
	dbYRotateObject(gun[GUN_SHOTGUN].id,gun[GUN_SHOTGUN].yrot);
	dbMoveObjectUp(gun[GUN_SHOTGUN].id,gun[GUN_SHOTGUN].moveup);
	dbMoveObjectLeft(gun[GUN_SHOTGUN].id,gun[GUN_SHOTGUN].moveleft);
	dbMoveObject(gun[GUN_SHOTGUN].id,gun[GUN_SHOTGUN].movefor);
	dbTextureObject(gun[GUN_SHOTGUN].id,gun[GUN_SHOTGUN].tid);
	dbSetObjectCull(gun[GUN_SHOTGUN].id,0);
	dbGlueObjectToLimb(gun[GUN_SHOTGUN].id,user[0].id,1);
	//Make the SHOTGUN muzzleflash
	gun[GUN_SHOTGUN].mid = FObj();
	dbMakeObjectPlain(gun[GUN_SHOTGUN].mid,2,2);
	dbSetAlphaMappingOn(gun[GUN_SHOTGUN].mid,30);
	dbSetObjectTransparency(gun[GUN_SHOTGUN].mid,1);
	dbTextureObject(gun[GUN_SHOTGUN].mid,MFT);
	dbGlueObjectToLimb(gun[GUN_SHOTGUN].mid,user[0].id,2);
	dbSetObjectLight(gun[GUN_SHOTGUN].mid,0);
	dbMoveObjectRight(gun[GUN_SHOTGUN].mid,gun[GUN_SHOTGUN].muzright);
	dbMoveObject(gun[GUN_SHOTGUN].mid,gun[GUN_SHOTGUN].muzfor);
	dbMoveObjectUp(gun[GUN_SHOTGUN].mid,gun[GUN_SHOTGUN].muzup);
	dbHideObject(gun[GUN_SHOTGUN].mid);

	//Make the LMG gun
	gun[GUN_LMG].id = FObj();
	gun[GUN_LMG].tid = FImg();
	dbLoadObject(gun[GUN_LMG].modelfile,gun[GUN_LMG].id);
	dbLoadImage(gun[GUN_LMG].textfile,gun[GUN_LMG].tid);
	dbScaleObject(gun[GUN_LMG].id,gun[GUN_LMG].sc,gun[GUN_LMG].sc,gun[GUN_LMG].sc); 
	dbYRotateObject(gun[GUN_LMG].id,gun[GUN_LMG].yrot);
	dbMoveObjectUp(gun[GUN_LMG].id,gun[GUN_LMG].moveup);
	dbMoveObjectLeft(gun[GUN_LMG].id,gun[GUN_LMG].moveleft);
	dbMoveObject(gun[GUN_LMG].id,gun[GUN_LMG].movefor);
	dbTextureObject(gun[GUN_LMG].id,gun[GUN_LMG].tid);
	dbSetObjectCull(gun[GUN_LMG].id,0);
	dbGlueObjectToLimb(gun[GUN_LMG].id,user[0].id,1);
	//Make the LMG muzzleflash
	gun[GUN_LMG].mid = FObj();
	dbMakeObjectPlain(gun[GUN_LMG].mid,2,2);
	dbSetAlphaMappingOn(gun[GUN_LMG].mid,30);
	dbSetObjectTransparency(gun[GUN_LMG].mid,1);
	dbTextureObject(gun[GUN_LMG].mid,MFT);
	dbGlueObjectToLimb(gun[GUN_LMG].mid,user[0].id,2);
	dbSetObjectLight(gun[GUN_LMG].mid,0);
	dbMoveObjectRight(gun[GUN_LMG].mid,gun[GUN_LMG].muzright);
	dbMoveObject(gun[GUN_LMG].mid,gun[GUN_LMG].muzfor);
	dbMoveObjectUp(gun[GUN_LMG].mid,gun[GUN_LMG].muzup);
	dbHideObject(gun[GUN_LMG].mid);
#pragma endregion
	//Make the muzzleflash light
	user[0].lightid = FLig();
	dbMakeLight(user[0].lightid);
	dbColorLight(user[0].lightid,dbRGB(255,194,14));
	dbPositionLight(user[0].lightid,dbObjectPositionX(gun[user[0].usinggun].mid),dbObjectPositionY(gun[user[0].usinggun].mid),dbObjectPositionZ(gun[user[0].usinggun].mid));
	dbHideLight(user[0].lightid);
	dbSetLightRange (user[0].lightid,50);

	//Hide the default light
	dbHideLight(0);
	float Score = 0;
imageText Points(dbStr(Score),"Media//Text//RedNeon.png",16,16,0,0,16);

	tm_init();

	while( LoopGDK( ) )
	{
		//Position the muzzleflash light
		dbPositionLight(user[0].lightid,dbObjectPositionX(gun[user[0].usinggun].mid),dbObjectPositionY(gun[user[0].usinggun].mid),dbObjectPositionZ(gun[user[0].usinggun].mid));
		//Get the player's X and Z speeds for calculating speed
		//user[0].sx = dbObjectPositionX(user[0].id);
		//user[0].sz = dbObjectPositionZ(user[0].id);

		dbText(0,40,dbStr(dbObjectPositionX(user[0].id)));
		dbText(0,60,dbStr(dbObjectPositionY(user[0].id)));
		dbText(0,80,dbStr(dbObjectPositionZ(user[0].id)));
		if (dbKeyState(16))
		{
			dbMoveObjectUp(user[0].id,10);
		}
		if (dbKeyState(18))
		{
			dbMoveObjectDown(user[0].id,10);
		}
		//Points.showText();
		Points.setText(dbStr(Score));
		Points.setTextPosition(0,0);
		//dbText(0,200,dbStr(Score));
		
		if (dbMouseClick()==1)
		{
			Score = Score - 2;
			dbShowObject(gun[user[0].usinggun].mid);
			dbRotateObject(gun[user[0].usinggun].mid,0,0,dbObjectAngleZ(gun[user[0].usinggun].mid)+(dbRND(40)-20));
			dbShowLight(user[0].lightid);
		}
		else
		{
			dbHideObject(gun[user[0].usinggun].mid);
			dbHideLight(user[0].lightid);
		}

		//ZOOM IN
		if (dbMouseClick()==2)
		{
			if (gun[user[0].usinggun].scopefov > 0)
			{
				//dbHideObject(gun[user[0].usinggun].id);
				dbSetCameraFOV(gun[user[0].usinggun].scopefov);
			}
		}
		else 
		{
			dbShowObject(gun[user[0].usinggun].id);
			dbSetCameraFOV(61.9621);
		}

		//make this so it only checks through when the plr is changing wep
		for (int i = 0; i < GUNNUMBER; i++)
		{
			if (user[0].usinggun == i)
			{
				user[0].gunbobang = gun[i].bobang;
				user[0].gunbobspd = gun[i].bobspd;
				user[0].gunbobmov = gun[i].bobmov;
				user[0].gunbobhgt = gun[i].bobhgt;
			}
		}

		for (int j = 0; j < GUNNUMBER; j++)
		{
			if (j == user[0].usinggun)
			{
				dbShowObject(gun[j].id);
			}

			else
			{
				dbHideObject(gun[j].id);
			}
		}

		//dbText(0,0,dbStr(dbObjectPositionX(gun[GUN_FAMAS].id)));
		//dbText(0,20,dbStr(dbObjectPositionY(gun[GUN_FAMAS].id)));
		//dbText(0,40,dbStr(dbObjectPositionZ(gun[GUN_FAMAS].id)));
			
		dbCircle(MIDDLEOFSCREEN,5);
		//rotate player with mouse
		dbYRotateObject(user[0].id,dbObjectAngleY(user[0].id) + dbMouseMoveX()/3.0f );
		dbXRotateObject(user[0].id,dbObjectAngleX(user[0].id) + dbMouseMoveY()/3.0f );

		user[0].oldx = dbObjectPositionX(user[0].id);
		user[0].oldy = dbObjectPositionY(user[0].id);
		user[0].oldz = dbObjectPositionZ(user[0].id);
		
		//apply gravity, and user changes to movement
		user[0].angy = dbObjectAngleY(user[0].id);
		user[0].vx = 0;
		user[0].vz = 0;

		//if player is jumping or falling then apply 'normal' gravity
		//if not attempt to keep the player stuck to the floor
		if ( user[0].vy == 0 && user[0].jumptimer == 0 ) user[0].vy = user[0].vy + 10*user[0].gravity; 
		else user[0].vy = user[0].vy + user[0].gravity;

		if (dbKeyState(32)+dbKeyState(30)+dbKeyState(31)+dbKeyState(17) > 0)
		{
			if (dbKeyState(32) == 1 ) { user[0].vx = user[0].vx + (TIMERUPDATE/10)*dbCos(user[0].angy); user[0].vz = user[0].vz - (TIMERUPDATE/10)*dbSin(user[0].angy); }
			if (dbKeyState(30) == 1 ) { user[0].vx = user[0].vx - (TIMERUPDATE/10)*dbCos(user[0].angy); user[0].vz = user[0].vz + (TIMERUPDATE/10)*dbSin(user[0].angy); }
			if (dbKeyState(31) == 1 ) { user[0].vx = user[0].vx - (TIMERUPDATE/10)*dbSin(user[0].angy); user[0].vz = user[0].vz - (TIMERUPDATE/10)*dbCos(user[0].angy); }
			if (dbKeyState(17) == 1 ) { user[0].vx = user[0].vx + (TIMERUPDATE/10)*dbSin(user[0].angy); user[0].vz = user[0].vz + (TIMERUPDATE/10)*dbCos(user[0].angy); }
			//user[0].gunbobang = dbWrapValue(user[0].gunbobang+user[0].gunbobspd);
		}

		//user[0].gunturnang = dbCurveAngle(dbWrapValue(dbMouseMoveX()),user[0].gunturnang,10);
		//user[0].gunlookang = dbCurveAngle(dbWrapValue(dbMouseMoveY()),user[0].gunlookang,10);

		//dbOffsetLimb(user[0].id,1,dbLimbPositionX(user[0].id,1)+(dbSin(user[0].gunbobang)*user[0].gunbobmov),dbLimbPositionY(user[0].id,1)+(dbAbs(dbCos(user[0].gunbobang)))*3,dbLimbPositionZ(user[0].id,1));//dbSin(user[0].gunbobang)*user[0].gunbobmov,dbAbs(dbCos(user[0].gunbobang))*user[0].gunbobhgt,0);
		//dbRotateLimb(user[0].id,1,user[0].gunlookang,user[0].gunturnang,0);

		//only jump if on ground, and a certain time after last jump
		if ( user[0].ground == 1 ) 
		{
			if ( dbSpaceKey() == 1 && user[0].jumptimer == 0 ) 
			{
				user[0].vy = user[0].vy + 5.0f;
				user[0].jumptimer = 20;
			}
		}
		
		//this would be the player's final position without collision
		user[0].x = user[0].oldx + user[0].vx;
		user[0].y = user[0].oldy + user[0].vy;
		user[0].z = user[0].oldz + user[0].vz;
		
		user[0].collide = SC_SphereCastGroup( 1, user[0].oldx,user[0].oldy,user[0].oldz,user[0].oldx,user[0].oldy+user[0].vy,user[0].oldz,user[0].radius,0 );
		
		if ( user[0].collide > 0 )
		{
			//how flat is this ground
			user[0].ny = SC_GetCollisionNormalY();
			if ( dbAbs(user[0].ny) > user[0].slope )
			{
				//FLAT, stick
				user[0].oldy = SC_GetStaticCollisionY();
			}
			else
			{
				//STEEP, slide
				user[0].x = user[0].x - user[0].oldx; user[0].z = user[0].z - user[0].oldz;
				user[0].oldx = SC_GetCollisionSlideX();
				user[0].oldy = SC_GetCollisionSlideY();
				user[0].oldz = SC_GetCollisionSlideZ();
				user[0].x = user[0].x + user[0].oldx; user[0].z = user[0].z + user[0].oldz;
			}
			
			//ny#<0 means the player has hit a ceiling rather than a floor
			
			if ( user[0].ny > user[0].slope )
			{
				//only on ground if standing on flat ground
				user[0].ground = 1;
				user[0].vy = 0;
			}
			else 
			{
				user[0].ground = 0;
				//if player has hit a flat ceiling then stop vy# movement
				if ( user[0].ny < -user[0].slope ) user[0].vy = user[0].gravity;
			}
		}
		else
		{
			//nothing below player, not on ground, add vertical speed to player
			user[0].oldy = user[0].oldy + user[0].vy;
			user[0].ground = 0;
		}
		
		//jumptimer will decrease only when player is back on ground
		//creates a pause between two successive jumps
		if ( user[0].ground == 1 && user[0].jumptimer > 0 ) user[0].jumptimer--;
		
		//handle horizontal movement as sliding
		//player only collides with group 1 (level) objs and moves freely through others
		user[0].collide = SC_SphereSlideGroup( 1, user[0].oldx,user[0].oldy,user[0].oldz,user[0].x,user[0].oldy,user[0].z,user[0].radius,0 );
		
		if ( user[0].collide > 0 )
		{
			//if hit, reposition player, halt movement vector
			user[0].x = SC_GetCollisionSlideX();
			user[0].oldy = SC_GetCollisionSlideY();
			user[0].z = SC_GetCollisionSlideZ();
			user[0].vx = 0;
			user[0].vz = 0;
		}
		
		//x speed
		//if plr has moved
		

		//position the player
		dbPositionObject(user[0].id,user[0].x,user[0].oldy,user[0].z );
		
		SC_UpdateObject(user[0].id);
		
		dbPositionCamera( dbObjectPositionX(user[0].id),dbObjectPositionY(user[0].id),dbObjectPositionZ(user[0].id));
		dbRotateCamera( dbObjectAngleX(user[0].id),dbObjectAngleY(user[0].id),dbObjectAngleZ(user[0].id) );

		TIMERUPDATE = tm_update();
		dbSync( );
	}
}
 