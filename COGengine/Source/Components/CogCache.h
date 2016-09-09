#pragma once

#include "ofxCogMain.h"
#include "CogSoundFile.h"
#include "CogAnim.h"
#include "CogSpriteSheet.h"

namespace Cog {

	/**
	* Resource controller that holds images, 3D objects and sounds
	*/
	class CogCache {
	private:
		// cached images
		map<string, spt<ofImage>> loadedImages;
		// cached meshes
		map<string, spt<ofVboMesh>> loadedMeshes;
		// cached sounds and music
		map<string, spt<CogSound>> loadedSounds;
		// cached xml files
		map<string, spt<ofxXmlSettings>> loadedXMLs;
		// cached animation
		map<string, spt<CogAnim>> loadedAnimations;
		// cached spritesheets
		map<string, spt<CogSpriteSheet>> loadedSpriteSheets;

	public:

		/**
		* Initializes controller
		*/
		void Init();

		/**
		* Loads 2D image from file
		* @param path path to file
		*/
		spt<ofImage> Get2DImage(string path);

		/**
		* Preloads 2D image from file; doesn't use texture so before first render,
		* the image must be copied onto texture; very usefull for ofxThread
		* @param path path to file
		*/
		spt<ofImage> Preload2DImage(string path);

		/**
		* Loads mesh from file
		* @param path path to file
		*/
		spt<ofVboMesh> GetMesh(string path);

		/**
		* Loads font from file
		* @param path path to file
		* @size font size
		*/
		spt<ofTrueTypeFont> GetFont(string path, int size);

		/**
		* Loads sound from file
		* @param path path to file
		*/
		spt<CogSound> GetSound(string path);

		/**
		* Preloads xml file; if the file is in the cache, returns cached xml
		* @param path path to file
		*/
		spt<ofxXmlSettings> PreloadXMLFile(string path);

		/**
		* Loads xml file
		* @param path path to file
		*/
		spt<ofxXmlSettings> LoadXMLFile(string path);

		/**
		* Gets animation
		* @param name animation name
		*/
		spt<CogAnim> GetAnimation(string name);

		/**
		* Stores animation
		* @param anim animation to store
		*/
		void StoreAnimation(spt<CogAnim> anim);

		/**
		* Gets spritesheet by name
		* @param name name of spritesheet
		*/
		spt<CogSpriteSheet> GetSpriteSheet(string name);

		/**
		* Stores spritesheet
		* @param spriteSheet spritesheet to store
		*/
		void StoreSpriteSheet(spt<CogSpriteSheet> spriteSheet);
	};

}