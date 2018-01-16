#pragma once

#include "ofImage.h"
#include "pugixml.h"
#include "Definitions.h"

using namespace pugi;

namespace jsonxx {
	class Object;
}

namespace Cog {

	class SpriteSheet;

	/**
	 * Builds sprite sheets from various attributes. Some of them are calculated from others.
	 */
	class SpriteSheetBuilder {
	private:
		spt<ofImage> atlas = nullptr;
		string atlasName;
		int offsetPxX = 0;			// x-axis offset in sprite atlas in pixels
		int offsetPxY = 0;			// y-axis offset in sprite atlas in pixels
		int offsetBlockX = 0;		// x-axis offset in sprite atlas in number of blocks (width of a block is the same as width of a sprite)
		int offsetBlockY = 0;		// y-axis offset in sprite atlas in number of blocks (height of a block is the same as height of a sprite)
		int spriteWidth = 0;		// width of the sprite in pixels
		int spriteHeight = 0;		// height of the sprite in pixels
		int spriteSheetWidth = 0;	// width of the whole sprite sheet in pixels
		int spriteSheetHeight = 0;	// height of the whole sprite sheet in pixels
		int totalFrames = 0;		// total number of frames on the sprite sheet
		string name;				// name of the sprite sheet
	public:

		void LoadFromXml(xml_node& xml, string img, string atlasName);

		/**
		 * Appends a sprite atlas
		 */
		SpriteSheetBuilder& Atlas(spt<ofImage> atlas) {
			this->atlas = atlas;
			return *this;
		}

		SpriteSheetBuilder& AtlasName(string name) {
			this->atlasName = name;
		}

		/**
		 * Appends an offset in number of blocks
		 * Note that size of block is the same as size of one sprite declared with spriteWidth and spriteHeight
		 */
		SpriteSheetBuilder& Offset(int x, int y) {
			this->offsetBlockX = x;
			this->offsetBlockY = y;
			return *this;
		}

		/**
		 * Appends an offset in pixels
		 */
		SpriteSheetBuilder& OffsetPx(int x, int y) {
			this->offsetPxX = x;
			this->offsetPxY = y;
			return *this;
		}

		/**
		 * Appends a size of one sprite
		 */
		SpriteSheetBuilder& SpriteSize(int width, int height) {
			this->spriteWidth = width;
			this->spriteHeight = height;
			return *this;
		}

		/**
		 * Appends a size of the whole sprite sheet. If not specified, the algorithm
		 * tries to calculate it from other attributes
		 */
		SpriteSheetBuilder& SpriteSheetSize(int width, int height) {
			this->spriteSheetWidth = width;
			this->spriteSheetHeight = height;
			return *this;
		}

		/**
		 * Appends number of frames in the sprite sheet
		 */
		SpriteSheetBuilder& Frames(int totalFrames) {
			this->totalFrames = totalFrames;
			return *this;
		}

		/**
		 * Appends number of frames via columns and rows
		 */
		SpriteSheetBuilder& Frames(int columns, int rows) {
			this->totalFrames = columns * rows;
			return *this;
		}

		/**
		 * Appends name of the sprite sheet
		 */
		SpriteSheetBuilder& Name(string name) {
			this->name = name;
			return *this;
		}

		/**
		 * Creates a new sprite sheet
		 */
		SpriteSheet* Build();

		/**
		* Creates a new sprite sheet and resets all values
		*/
		SpriteSheet* BuildAndReset();

	private:
		void InitValues() {
			// reset all attributes
			atlas = nullptr;
			atlasName = "";
			offsetPxX = 0;
			offsetPxY = 0;
			spriteWidth = 0;
			spriteHeight = 0;
			spriteSheetWidth = 0;
			spriteSheetHeight = 0;
			totalFrames = 0;
			name = "";
		}
	};

} // namespace