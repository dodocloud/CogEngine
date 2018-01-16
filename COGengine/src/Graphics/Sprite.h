#pragma once

#include "SpriteSheet.h"
#include "Transform.h"
#include "BoundingBox.h"

namespace Cog {

	/**
	* Sprite entity, a part of a texture image called sprite sheet
	* Identified by frame index, pointing to the area on the sheet
	*/
	class Sprite {
	private:
		int frame;		// frame index
		int offsetX;	// x-axis offset on sprite sheet 
		int offsetY;	// y-axis offset on sprite sheet
		int width;		// width in pixels
		int height;		// height in pixels
		Trans transform = Trans(0, 0);
		spt<SpriteSheet> spriteSheet;	// pointer to parent sprite sheet

	public:

		/**
		* Creates a new sprite
		* @param spriteSheet collection of sprites
		* @param row index of a row in which this sprite is located
		* @param column index of a column in which this sprite is located
		*/
		Sprite(spt<SpriteSheet> spriteSheet, int row, int column);

		/**
		* Creates a new sprite
		* @param spriteSheet collection of sprites
		* @param frame index of a frame on the sprite sheet
		*/
		Sprite(spt<SpriteSheet> spriteSheet, int frame);

		/**
		* Creates a new sprite
		* @param spriteSheet collection of sprites
		* @param row index of a row in which this sprite is located
		* @param column index of a column in which this sprite is located
		* @param transform sprite transformation
		*/
		Sprite(spt<SpriteSheet> spriteSheet, int row, int column, const Trans& transform);

		/**
		* Creates a new sprite
		* @param spriteSheet collection of sprites
		* @param frame index of a frame on the sprite sheet
		* @param transform sprite transformation
		*/
		Sprite(spt<SpriteSheet> spriteSheet, int frame, const Trans& transform);

		int GetFrame() const {
			return frame;
		}

		void SetFrame(int frame) {
			this->frame = frame;
			this->Recalc();
		}

		/**
		 * Gets x-axis offset on sprite sheet in pixels
		 */
		int GetOffsetX() const {
			return offsetX;
		}

		/**
		* Gets y-axis offset on sprite sheet in pixels
		*/
		int GetOffsetY() const {
			return offsetY;
		}

		/**
		 * Gets width of the sprite in pixels
		 */
		int GetWidth() const {
			return width;
		}

		/**
		 * Gets height of the sprite in pixels
		 */
		int GetHeight() const {
			return height;
		}

		/**
		 * Gets transformation entity
		 */
		Trans& GetTransform() {
			return transform;
		}

		/**
		 * Gets z-index
		 */
		int GetZIndex() const {
			return static_cast<int>(transform.localPos.z);
		}

		void CalcBoundingBox(BoundingBox& output) const {
			auto absPos = ofVec2f(this->transform.absPos.x, this->transform.absPos.y);
			output.topLeft = absPos;
			output.topRight = ofVec2f(absPos.x + this->GetWidth() * this->transform.absScale.x, absPos.y);
			output.bottomLeft = ofVec2f(absPos.x, absPos.y + this->GetHeight() * this->transform.absScale.y);
			output.bottomRight = ofVec2f(output.bottomLeft.x + this->GetWidth()* this->transform.absScale.x, output.bottomLeft.y);
		}

		// this is for Lua scripts
		void CalcBoundingBoxPtr(BoundingBox* output) const {
			auto absPos = ofVec2f(this->transform.absPos.x, this->transform.absPos.y);
			output->topLeft = absPos;
			output->topRight = ofVec2f(absPos.x + this->GetWidth() * this->transform.absScale.x, absPos.y);
			output->bottomLeft = ofVec2f(absPos.x, absPos.y + this->GetHeight() * this->transform.absScale.y);
			output->bottomRight = ofVec2f(output->bottomLeft.x + this->GetWidth()* this->transform.absScale.x, output->bottomLeft.y);
		}
	protected:
		/**
		* Recalculates attributes (width, height), according to values in sprite sheet
		*/
		void Recalc();
	};

} // namespace