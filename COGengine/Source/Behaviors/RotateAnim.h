#pragma once

#include "Behavior.h"
#include "Node.h"

namespace Cog {

	/**x
	* Behavior for rotation animation
	*/
	class RotateAnim : public Behavior {
		OBJECT_PROTOTYPE(RotateAnim)
	private:
		// starting rotation
		float from = 0;
		// ending rotation
		float to = 0;
		// rotation speed in angles per second
		float speed = 0;
		// if true, rotation will be additive (doesn't override actual rotation)
		bool additive = false;
		// actual rotation value
		float actual = 0;

	public:
		/**
		* Creates a new behavior for rotation animation
		* @param from starting rotation
		* @param to ending rotation (if from == to, it is infinite rotation)
		* @param speed rotation speed in angles per second
		* @param additive if true, rotation will be additive
		*/
		RotateAnim(float from, float to, float speed, bool additive) :
			from(from), to(to), speed(speed), additive(additive){
		}


		void Update(const uint64 delta, const uint64 absolute) {

			// calculate differencial
			float diff = (float)((to == from ? 1 : (to - from)) * 0.001f * speed * delta);
			actual += diff;

			// if to == from, it is infinite rotation
			if (to != from && (actual - from > to - from)) {
				actual = to;
				Finish();
			}

			Trans& transform = owner->GetTransform();

			if (additive) transform.rotation += (diff);
			else transform.rotation = (actual);
		}
	};

}// namespace