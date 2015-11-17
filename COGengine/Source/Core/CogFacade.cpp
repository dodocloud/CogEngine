
#include "CogFacade.h"
#include "CogEngine.h"
#include "CogLogger.h"
#include "CogCache.h"

// =================== MENVIRONMENT ====================

void CogAddSound(spt<CogSound> sound){
	COGEngine.environmentCtrl->AddSound(sound);
}

void CogPlaySound(spt<CogSound> sound){
	COGEngine.environmentCtrl->PlaySound(sound);
}

vector<CogInputAct>& CogGetPressedKeys(){
	return COGEngine.environmentCtrl->GetPressedKeys();
}

vector<CogInputAct>& CogGetPressedPoints(){
	return COGEngine.environmentCtrl->GetPressedPoints();
}

vector<spt<CogSound>>& CogGetPlayedSounds(){
	return COGEngine.environmentCtrl->GetPlayedSounds();
}

int CogGetScreenRealWidth(){
	return COGEngine.environmentCtrl->GetRealWidth();
}

int CogGetScreenRealHeight(){
	return COGEngine.environmentCtrl->GetRealHeight();
}

int CogGetScreenWidth(){
	return COGEngine.environmentCtrl->GetWidth();
}

int CogGetScreenHeight(){
	return COGEngine.environmentCtrl->GetHeight();
}

float CogGetScreenRealAspectRatio(){
	return COGEngine.environmentCtrl->GetRealAspectRatio();
}

float CogGetScreenAspectRatio(){
	return COGEngine.environmentCtrl->GetAspectRatio();
}

void CogSetScreenAspectRatio(float ratio){
	COGEngine.environmentCtrl->SetAspectRatio(ratio);
}



ofVec2f CogGetScreenSize(){
	return COGEngine.environmentCtrl->GetSize();
}

void CogRunThread(ofThread* thread){
	COGEngine.environmentCtrl->RunThread(thread);
}

// =================== MFACTORY ========================

float CogTranslateSpeed(float speed){
	return COGEngine.factory->TranslateSpeed(speed);
}

// =================== MSTORAGE ========================

void CogRegisterListener(int action, CogBehavior* beh){
	COGEngine.storage->RegisterListener(action, beh);
}

void CogUnregisterListener(int action, CogBehavior* beh){
	COGEngine.storage->UnregisterListener(action, beh);
}

void CogSendMessage(CogMsg& msg, CogNode* actualNode){
	MLOGDEBUG("CORE", "Message %s:%s:%d", ofToString(msg.GetAction()).c_str(), actualNode->GetTag().c_str(), actualNode->GetSubType());
	COGEngine.storage->SendMessage(msg, actualNode);
}

void CogSendDirectMessageToBehavior(CogMsg& msg, int targetId){
	COGEngine.storage->SendDirectMessageToBehavior(msg, targetId);
}


CogNode* CogFindNodeById(int id) {
	return COGEngine.storage->FindNodeById(id);
}

int CogGetNodesCountByTag(string tag) {
	return COGEngine.storage->GetNodesCountByTag(tag);
}

CogNode* CogFindNodeByTag(string tag) {
	return COGEngine.storage->FindNodeByTag(tag);
}

vector<CogNode*> CogFindNodesByTag(char* tag) {
	return COGEngine.storage->FindNodesByTag(tag);
}

int CogGetNodesCountBySubType(int subtype) {
	return COGEngine.storage->GetNodesCountBySubType(subtype);
}

CogNode* CogFindNodeBySubType(int subtype) {
	return COGEngine.storage->FindNodeBySubType(subtype);
}

vector<CogNode*> CogFindNodesBySubType(int subtype) {
	return COGEngine.storage->FindNodesBySubType(subtype);
}

bool CogAddNode(CogNode* node){
	MLOGDEBUG("CORE", "Adding node %s", node->GetTag().c_str());
	return COGEngine.storage->AddNode(node);
}

void CogRemoveNode(CogNode* node){
	MLOGDEBUG("CORE", "Removing node %s", node->GetTag().c_str());
	COGEngine.storage->RemoveNode(node);
}

bool CogAddBehavior(CogBehavior* beh){
	MASSERT(beh->GetOwner() != nullptr, "CORE", "Behavior %s hasn't node assigned", typeid(*beh).name());
	MLOGDEBUG("CORE", "Adding behavior %s to node %s", typeid(*beh).name(), beh->GetOwner()->GetTag().c_str());
	return COGEngine.storage->AddBehavior(beh);
}

void CogRemoveBehavior(CogBehavior* beh){
	MASSERT(beh->GetOwner() != nullptr, "CORE", "Behavior %s hasn't node assigned", typeid(*beh).name());
	MLOGDEBUG("CORE", "Removing behavior %s from node %s", typeid(*beh).name(), beh->GetOwner()->GetTag().c_str());
	COGEngine.storage->RemoveBehavior(beh);
}

// =================== MLOGGER =========================

void CogLogError(const char* module, const char* format, ...){
	va_list args;
	va_start(args, format);
	COGEngine.logger->LogError(module, 0, format, args);
	va_end(args);
}

void CogLogInfo(const char* module, const char* format, ...){
	va_list args;
	va_start(args, format);
	COGEngine.logger->LogInfo(module, 0, format, args);
	va_end(args);
}

void CogLogDebug(const char* module, const char* format, ...){
	va_list args;
	va_start(args, format);
	COGEngine.logger->LogDebug(module, 0, format, args);
	va_end(args);
}

void CogLoggerFlush(){
	COGEngine.logger->Flush();
}


// =================== MRENDERER =========================
void CogPushNodeForRendering(CogNode* node){
	COGEngine.renderer->PushNode(node);
}

void CogRender(){
	COGEngine.renderer->Render();
}

// =================== MRESOURCE =======================

spt<ofImage> CogGet2DImage(string path){
	return COGEngine.resourceCtrl->Get2DImage(path);
}

spt<ofImage> CogPreload2DImage(string path){
	return COGEngine.resourceCtrl->Preload2DImage(path);
}

spt<ofVboMesh> CogGetMesh(string path){
	return COGEngine.resourceCtrl->GetMesh(path);
}

spt<ofTrueTypeFont> CogGetFont(string path, int size){
	return COGEngine.resourceCtrl->GetFont(path, size);
}

spt<CogSound> CogGetSound(string path){
	return COGEngine.resourceCtrl->GetSound(path);
}

spt<ofxXmlSettings> CogPreloadXMLFile(string path){
	return COGEngine.resourceCtrl->PreloadXMLFile(path);
}

spt<ofxXmlSettings> CogLoadXMLFile(string path){
	return COGEngine.resourceCtrl->LoadXMLFile(path);
}

spt<CogAnim> CogGetAnimation(string name){
	return COGEngine.resourceCtrl->GetAnimation(name);
}

void CogStoreAnimation(spt<CogAnim> anim){
	COGEngine.resourceCtrl->StoreAnimation(anim);
}