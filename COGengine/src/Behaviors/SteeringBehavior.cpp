
#include "SteeringBehavior.h"
#include "ofxCogEngine.h"
#include "Node.h"

namespace Cog {


	float SteeringBehavior::ClampAngle(float x) {
		x = fmod(x + 180, 360);
		if (x < 0)
			x += 360;
		return x - 180;
	}

	void SteeringBehavior::SetRotationDirection(Dynamics* dynamics, Trans& transform, ofVec2f destination, float maxAcceleration, uint64 delta) {
		float actualRotation = transform.rotation;
		float neededRotation = transform.CalcAngle(destination);

		actualRotation = ClampAngle(actualRotation);
		neededRotation = ClampAngle(neededRotation);

		auto diff = DEG_TO_RAD*(actualRotation - neededRotation);
		// calculate difference between actual and desired rotation
		float rotDiff = -RAD_TO_DEG*atan2(sin(diff), cos(diff));

		if (isnan(rotDiff)) rotDiff = 0;

		// rotate to the desired rotation
		dynamics->SetAngularSpeed(rotDiff*maxAcceleration);
	}


	void SeekBehavior::OnStart() {
		if (!owner->HasAttr(seekDest)) {
			owner->AddAttr(seekDest, ofVec2f(0));
		}
	}

	void SeekBehavior::Update(const uint64 delta, const uint64 absolute) {
		auto& transform = owner->GetTransform();
		Dynamics* movement = owner->GetAttr<Dynamics*>(attrMovement);
		ofVec2f dest = owner->GetAttr<ofVec2f>(seekDest);
		ofVec2f force = steeringMath.Seek(transform, movement, dest, maxAcceleration);
		movement->SetForce(forceId, force);
		this->SetRotationDirection(movement, transform, dest, maxAcceleration, delta);
	}


	void ArriveBehavior::OnStart() {
		if (!owner->HasAttr(seekDest)) {
			owner->AddAttr(seekDest, ofVec2f(0));
		}

		if (!owner->HasAttr(attrMovement)) {
			owner->AddAttr(attrMovement, new Dynamics());
		}
	}

	void ArriveBehavior::Update(const uint64 delta, const uint64 absolute) {

		auto& transform = owner->GetTransform();
		Dynamics* movement = owner->GetAttr<Dynamics*>(attrMovement);
		ofVec2f dest = owner->GetAttr<ofVec2f>(seekDest);
		ofVec2f acceleration = steeringMath.Arrive(transform, movement, dest, decelerationSpeed, pointTolerance);
		if (acceleration != ofVec2f(INT_MIN)) {
			movement->SetForce(forceId, acceleration);
			this->SetRotationDirection(movement, transform, dest, rotationSpeed, delta);
		}
		else {
			movement->SetForce(forceId, ofVec2f(0));
			Finish();
		}
	}


	void FleeBehavior::OnStart() {
		if (!owner->HasAttr(seekDest)) {
			owner->AddAttr(seekDest, ofVec2f(0));
		}
	}

	void FleeBehavior::Update(const uint64 delta, const uint64 absolute) {
		auto& transform = owner->GetTransform();
		Dynamics* movement = owner->GetAttr<Dynamics*>(attrMovement);

		ofVec2f dest = owner->GetAttr<ofVec2f>(seekDest);
		ofVec2f acceleration = steeringMath.Flee(transform, movement, dest, fleeDistance, maxAcceleration);
		movement->SetForce(forceId, acceleration);

		this->SetRotationDirection(movement, transform, dest, maxAcceleration, delta);
	}

	void FollowBehavior::OnStart() {
		if (!owner->HasAttr(attrMovement)) {
			owner->AddAttr(attrMovement, new Dynamics());
		}
	}

	void FollowBehavior::Update(const uint64 delta, const uint64 absolute) {
		if (!PathFinished()) {
			auto& transform = owner->GetTransform();
			Dynamics* dynamics = owner->GetAttr<Dynamics*>(attrMovement);

			ofVec2f force = steeringMath.Follow(transform, dynamics, path, currentPathIndex,
				pointTolerance, finalPointTolerance, maxAcceleration, 20);

			if (force == ofVec2f(INT_MAX)) {
				// finish
				dynamics->Stop();
				pathFinished = true;
				return;
			}

			dynamics->SetForce(forceId, force * forceStrength);

			this->SetRotationDirection(dynamics, transform, transform.localPos + dynamics->GetVelocity(), maxRadialAcceleration, delta);
		}
	}


	void WanderBehavior::OnStart() {
		if (!owner->HasAttr(wanderDest)) {
			owner->AddAttr(wanderDest, ofVec2f(0));
		}
	}

	void WanderBehavior::Update(const uint64 delta, const uint64 absolute) {
		auto& transform = owner->GetTransform();
		Dynamics* dynamics = owner->GetAttr<Dynamics*>(attrMovement);

		ofVec2f behWander = owner->GetAttr<ofVec2f>(StrId(wanderDest));
		ofVec2f force = steeringMath.Wander(transform, dynamics, behWander, wanderRadius, wanderDistance, wanderJitter, delta);
		owner->ChangeAttr(StrId(wanderDest), behWander);

		// add velocity dependency
		dynamics->SetForce(forceId, force);
		this->SetRotationDirection(dynamics, transform, transform.localPos + dynamics->GetVelocity(), 20, delta);
	}

}// namespace