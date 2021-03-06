#include "TransformAnim.h"
#include "ofxCogEngine.h"
#include "Scene.h"
#include "EnumConverter.h"
#include "Node.h"
#include "ResourcesMgr.h"
#include "TransformMath.h"
#include "Definitions.h"
#include "TransformEnt.h"
#include "Stage.h"
#include "ComponentStorage.h"
#include "EnumConverter.h"
#include "Transform.h"

namespace Cog {

	void TransformAnim::Load(Setting& setting) {
		string from = setting.GetItemVal("from");
		string to = setting.GetItemVal("to");
		this->duration = setting.GetItem("duration").GetValFloat();
		this->delayAfter = setting.GetItem("delayAfter").GetValFloat();
		this->repeat = setting.GetItemValBool("repeat");

		auto resCache = GETCOMPONENT(Resources);
		this->from = resCache->GetEntity<TransformEnt>(from);
		this->to = resCache->GetEntity<TransformEnt>(to);
		this->blend = EnumConverter::StrToAnimBlend(setting.GetItemVal("blend"));

		string easing = setting.GetItemVal("easefunc");
		if (!easing.empty()) {
			this->fadeFunction = EnumConverter::StrToFadeFunction(easing);
		}
	}

	void TransformAnim::OnStart() {

		TransformMath math;

		// get scene settings and calculate transformations 
		Settings& sceneSettings = owner->GetScene()->GetSceneSettings();
		int gridWidth = sceneSettings.GetSettingVal<int>("transform", "grid_width");
		int gridHeight = sceneSettings.GetSettingVal<int>("transform", "grid_height");

		fromTrans = Trans();
		toTrans = Trans();


		if (from) math.CalcTransform(fromTrans, owner, owner->GetParent(), *from, gridWidth, gridHeight);
		else fromTrans = owner->GetTransform();

		if (to) math.CalcTransform(toTrans, owner, owner->GetParent(), *to, gridWidth, gridHeight);
		else toTrans = owner->GetTransform();
		actual = 0;
		lastPercent = 0;
	}

	void TransformAnim::Update(const uint64 delta, const uint64 absolute) {

		actual += delta;

		float actualCropped = actual;

		if (actual >= duration) {
			// value exceeded
			actualCropped = duration;
		}

		float actualPercent = actualCropped / duration;
		if (fadeFunction != nullptr) actualPercent = fadeFunction(actualPercent);

		Trans actualTrans(0, 0);
		Trans& ownerTrans = owner->GetTransform();

		if (blend == AnimBlend::ADDITIVE) {
			// add calculated values with the current
			actualTrans.localPos = (toTrans.localPos - fromTrans.localPos)*(actualPercent - lastPercent);
			actualTrans.rotation = (toTrans.rotation - fromTrans.rotation)*(actualPercent - lastPercent);
			actualTrans.scale = (toTrans.scale - fromTrans.scale)*(actualPercent - lastPercent);

			ownerTrans.localPos += (actualTrans.localPos);
			ownerTrans.rotation += (actualTrans.rotation);

			if (actualTrans.scale != ofVec3f(1)) {
				ownerTrans.scale *= (1 + (actualTrans.scale));
			}
		}
		else if (blend == AnimBlend::OVERLAY) {
			// overlay current values with the calculated
			ownerTrans.localPos = fromTrans.localPos + (toTrans.localPos - fromTrans.localPos)*(actualPercent);
			ownerTrans.rotation = fromTrans.rotation + (toTrans.rotation - fromTrans.rotation)*(actualPercent);
			ownerTrans.scale = fromTrans.scale + (toTrans.scale - fromTrans.scale)*(actualPercent);
			ownerTrans.rotationCentroid = fromTrans.rotationCentroid;
		}

		lastPercent = actualPercent;

		if (actual >= (duration + delayAfter)) {
			if (repeat) {
				actual = 0;
				lastPercent = 0;

				if (blend == AnimBlend::ADDITIVE) {
					// return transformation back
					ownerTrans.localPos -= (toTrans.localPos - fromTrans.localPos);
					ownerTrans.rotation -= (toTrans.rotation - fromTrans.rotation);
					ownerTrans.scale /= (1 + (toTrans.scale - fromTrans.scale));
				}
			}
			else {
				Finish();
				SendMessage(ACT_TRANSFORM_ENDED);
			}
		}
	}


}// namespace