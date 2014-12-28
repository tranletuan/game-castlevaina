#ifndef QTTREE_H
#define QTTREE_H

#include "QTNode.h"
#include "CResourcesManager.h"
#include "CSniperStand.h"
#include "CItemStand.h"
#include "CWaterEffect.h"
#include "CWallTurret.h"
#include "CGroundCanon.h"
#include "CBoss1.h"
#include "CSniperHide.h"
#include "CAutoDestroyBridge.h"
#include "CStarEffect.h"
#include "CBoss1Gun.h"
#include "CGroundElectron.h"
#include "CFire.h"
#include "CRockRoll.h"
#include "CSniperBoss.h"
#include "CBoomThrow.h"
#include "CSniperBlock.h"
#include "CWaterFallE.h"
#include "CRockFly.h"
#include "CTank.h"
#include "CSniperWater.h"
#include "CBoss2.h"
#include "CBoss2Arm.h"
#include "CGroundGrass.h"
#include "CGroundWater.h"
#include "CBoss3.h"

class QTTree
{
private:	
	vector<CObject*> m_listObInView; // danh sach cac doi tuong trong view port
	QTNode* m_nodeRoot;
	int m_numSub; // so lan chia node

	CCamera *m_camera;

public:

	QTTree();
	~QTTree();

	void init();
	// lay cac doi tuong nam trong camera
	void getObjectInView();
	void update(int time);
	void draw();

	// update node leaf
	void updateNodeLeaf();
	// get doi tuong chinh xac
	CObject* getObjectTrust(CObject *x);
	// kiem tra va cham node va camera
	bool isCollWithCam(QTNode *node); 
	// lay cac node con va cham voi camera
	vector<QTNode*> getNodeCollWithCam(QTNode *node);
	// lay list doi tuong trong view port
	vector<CObject*> &getObsInView(){ return m_listObInView; }

};
#endif
