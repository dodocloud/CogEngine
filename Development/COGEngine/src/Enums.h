#pragma once

#include "ofMain.h"


/*! User input action enumerator */
enum class Act{
	NONE=0,		/*!< none */
	LEFT=1,		/*!< move left */
	RIGHT=2,	/*!< move right */
	UP=3,		/*!< move up */
	DOWN=4,		/*!< move down */
	FIRE=5,		/*!< fire/action */
	SWITCH=6	/*!< switch/action */
};

/*! Scope object for messaging */
enum class ScopeType{
	ROOT,				 /*!< root object scope */
	SCENE,				 /*!< scene object scope */
	OBJECT,				 /*!< source object scope */
	CHILDREN,			 /*!< children objects scope */
	DIRECT_NO_TRAVERSE   /*!< no traversation made, objects are obtained from map */
};

/*! Types of traversation */
namespace Traverses{
	extern int CHILD_FIRST;     /*!< child is updated first */
	extern int BEH_FIRST;		/*!< behaviors are updated first */
	extern int ROOT;			/*!< root is updated first */
	extern int SCENEROOT;		/*!< scene root is updated first */
}

/*! Action events */
namespace Actions{
	extern int BEHAVIOR_ADDED;
	extern int BEHAVIOR_REMOVED;
	extern int OBJECT_CREATED;
	extern int OBJECT_REMOVED;
	extern int USER_INPUT;
	extern int COLLISION_OCURRED;
	extern int GAMEOBJECT_DESTROYED;
	extern int ATTRIBUTE_CHANGED;
	extern int OBJECT_HIT;
	extern int OBJECT_RELEASED;
	extern int HEALTH_CHANGED;
	extern int PARA_GROUNDED;
	extern int PARA_KILLED;
	extern int COPTER_KILLED;
	extern int PLAYER_LOOSE;
	extern int GAME_FINISHED;
	extern int TWEEN_ENDED;
	extern int SLIDE_ENDED;

	extern const char* ToString(int act);
}


/*! Attribute keys */
namespace Attrs{
	extern int VELOCITY;
	extern int ACTIONS;
	extern int ALLOWED_ACTIONS;
	extern int IMGSOURCE;
	extern int BOUNDS;
	extern int SIZE;
	extern int POLYGON;
	extern int COLOR;
	extern int FRAME;
	extern int COLLISIONS;
	extern int HEALTH;
	extern int FONT;
	extern int TEXT;
	extern int SCORE;	

	extern const char* ToString(int act);
}

/*! States*/
namespace States{
	extern int HITTABLE;
	extern int TO_LEFT;
	extern int TO_RIGHT;
	extern int HIT;
	extern int COLLID_SOURCE;
	extern int COLLID_TARGET;
	extern int FLIPPED;

	extern const char* ToString(int act);
}

/*! Behavior state enumerator */
enum class BehState {
	ACTIVE_ALL,			/*!< active for all events */
	ACTIVE_MESSAGES,	/*!< active for message sending */
	ACTIVE_UPDATES,		/*!< active for update */
	DISABLED			/*!< disabled completely */
};	

/*! Element type enumerator */
enum class ElemType {
	ALL,				/*!< common type */
	VIEW,				/*!< view element - is not a part of game model */
	MODEL				/*!< model element - is a part of game machine */
};

/*! Game object type enumerator */
enum class ObjType{
	ROOT,				/*!< root object, usually the topmost parent */
	SCENE,				/*!< scene root object, topmost parent in the scene */
	OBJECT,				/*!< simple game object */
	HUD,				/*!< human interface object */
	INFO				/*!< info object */
};

