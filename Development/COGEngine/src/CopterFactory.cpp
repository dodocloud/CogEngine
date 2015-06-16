#include "CopterFactory.h"
#include "BeTranslateAnim.h"
#include "BeRotateAnim.h"
#include "BeMove.h"
#include "BeHitEvent.h"
#include "BeCollider.h"
#include "BeRender.h"
#include "SmartPointer.h"
#include "BeTween.h"

void OnBackgroundhit(const uint64 delta, const uint64 absolute, const ofMatrix4x4& absMatrix, GNode* owner){
MEngine.factory->SwitchToScene(0);
}


GNode* CopterFactory::CreateRoot(){
	//return MGameFactory::CreateRoot();
	 root = new GNode(ObjType::ROOT, 12, "fof�k");
	 splash = new GNode(ObjType::SCENE, 13, "sc�na");

	this->SetSingleBackground(splash, "images/intro.png", true);
	splash->AddBehavior(new BeHitEvent(OnBackgroundhit));

	root->AddChild(splash);
	return root;
}

void CopterFactory::SwitchToScene(int sc){
	GNode* scene = new GNode(ObjType::SCENE, 14, "scene");
	scene->AddBehavior(new BeRender(RenderType::IMAGE));
	spt<ofImage> img = MEngine.resourceCtrl->Get2DImage("images/background.png");
	scene->AddAttr(Attrs::IMGSOURCE, img);
	float sceneScale = MEngine.environmentCtrl->GetWidth() / img->getWidth();

	int width = MEngine.environmentCtrl->GetWidth();
	int height = MEngine.environmentCtrl->GetHeight();

	scene->GetTransform().LocalPos = Vectorf3(width/2+width, height/2);
	scene->GetTransform().Scale = Vectorf3(sceneScale, sceneScale, sceneScale);

	root->AddChild(scene);
	scene->AddBehavior(new BeSlideTween(TweenDirection::LEFT, scene, splash,1));


	GNode* leftBut = new GNode(ObjType::OBJECT, 50, "b");
	leftBut->AddBehavior(new BeRender(RenderType::IMAGE));
	img = MEngine.resourceCtrl->Get2DImage("images/butLeft.png");
	leftBut->AddAttr(Attrs::IMGSOURCE, img);
	leftBut->SetState(States::HITTABLE);
	leftBut->GetTransform().LocalPos = Vectorf3(RelPosX(10,scene), RelPosY(50,scene),2);
	leftBut->GetTransform().Scale = CalcScale(img, 10,scene);
	scene->AddChild(leftBut);


	GNode* rightBut = new GNode(ObjType::OBJECT, 50, "b");
	rightBut->AddBehavior(new BeRender(RenderType::IMAGE));
	img = MEngine.resourceCtrl->Get2DImage("images/butRight.png");
	rightBut->AddAttr(Attrs::IMGSOURCE, img);
	rightBut->SetState(States::HITTABLE);
	rightBut->GetTransform().LocalPos = Vectorf3(RelPosX(21,scene), RelPosY(50,scene),2);
	rightBut->GetTransform().Scale = CalcScale(img, 10,scene);
	scene->AddChild(rightBut);

	GNode* fireBut = new GNode(ObjType::OBJECT, 50, "b");
	fireBut->AddBehavior(new BeRender(RenderType::IMAGE));
	img = MEngine.resourceCtrl->Get2DImage("images/butFire.png");
	fireBut->AddAttr(Attrs::IMGSOURCE, img);
	fireBut->SetState(States::HITTABLE);
	fireBut->GetTransform().LocalPos = Vectorf3(RelPosX(80,scene), RelPosY(50,scene),2);
	fireBut->GetTransform().Scale = CalcScale(img, 10,scene);
	scene->AddChild(fireBut);

	GNode* copter = nullptr;

	for(int i=0; i<10; i++){
		copter = new GNode(ObjType::OBJECT, 50, "b");
		copter->AddBehavior(new BeRender(RenderType::IMAGE));
		img = MEngine.resourceCtrl->Get2DImage("images/copter1.png");
		copter->AddAttr(Attrs::IMGSOURCE, img);
		copter->SetState(States::HITTABLE);

		int randX = ofRandom(-50,50);
		int randY = ofRandom(10,30);
		int randM = ofRandom(0,2);
		if(randM == 1) randX = 150+randX;

		copter->GetTransform().LocalPos = Vectorf3(RelPosX(randX,scene), RelPosY(randY,scene),2);
		copter->GetTransform().Scale = CalcScale(img, 10,scene);
		copter->AddBehavior(new BeTranslateAnim(Vectorf3(RelPosX(randX,scene),RelPosY(randY,scene),2),Vectorf3(RelPosX(randM == 0 ? 130 : -130,scene),RelPosY(randY,scene),2),0.1f,false,true));
		copter->AddBehavior(new CopterBeh());
		scene->AddChild(copter);
	}
}