#ifndef QTTREE_H
#define QTTREE_H

#include "QTNode.h"
#include "CResourcesManager.h"
#include "CGround.h"
#include "CSniperStand.h"
#include "CItemStand.h"
#include "CGroundEffect.h"
#include "CWallTurret.h"
#include "CGroundCanon.h"
#include "CBoss1.h"
#include "CSniperHide.h"
#include "CAutoDestroyBridge.h"
#include "CGroundStar.h"
#include "CBossGun.h"
#include "CGroundElectron.h"
#include "CFire.h"
#include "CRockRoll.h"

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
