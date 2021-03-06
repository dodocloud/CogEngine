#include "BehaviorLua.h"
#include "Node.h"
#include "ofxCogEngine.h"
#include "LuaScripting.h"
#include "ComponentStorage.h"
#include <LuaBridge.h>
#include "AttribAnimator.h"

using namespace luabridge;

namespace Cog {

	BehaviorLua::BehaviorLua() {
		// objects allocated in lua always have to be 
		//external (they aren't deallocated in Node's destructor)
		this->isExternal = true;

		auto scr = GETCOMPONENT(LuaScripting);
		L = scr->GetLua();
		scr->StoreBehavior(this);
	}

	void BehaviorLua::OnInit() {
		SetOwnerLua();

		lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
		LuaRef ref = LuaRef::fromStack(L, lua_gettop(L));
		COGASSERT(!ref.isNil(), "BehaviorLua", "Wrong lua object; expected reference");
		
		// call OnInit function
		auto init = ref["OnInit"];
		COGASSERT(!init.isNil(), "BehaviorLua", "Wrong lua object; expected reference");
		init(ref);
	}

	int BehaviorLua::RegisterDelegateCt(luabridge::lua_State* L) {
		COGASSERT(lua_gettop(L) == 2, "BehaviorLua", "Wrong registration call! Expected one parameter: registered object");
				
		// get reference from Lua stack
		int r = luaL_ref(L, LUA_REGISTRYINDEX);
		lua_rawgeti(L, LUA_REGISTRYINDEX, r);
		this->reference = r;
		return 0; // number of return values
	}

	void BehaviorLua::SendMessage(StrId msg) {
		Behavior::SendMessage(msg);
	}

	void BehaviorLua::SendMessageWithData(StrId msg, RefCountedObjectPtr<MsgPayload> data) {
		Behavior::SendMessage(msg, data);
	}

	void BehaviorLua::SetOwnerLua() {
		lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
		LuaRef ref = LuaRef::fromStack(L, lua_gettop(L));
		if (ref.isNil()) {
			ofLogError("Lua", "Wrong lua object; expected reference!");
		}
		auto ownerLua = ref["owner"];
		ownerLua.rawset(owner);
	}

	void BehaviorLua::OnMessage(Msg& msg) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
		LuaRef ref = LuaRef::fromStack(L, lua_gettop(L));
		COGASSERT(!ref.isNil(), "BehaviorLua", "Wrong lua object; expected reference");
		auto method = ref["OnMessage"];
		COGASSERT(!method.isNil(), "BehaviorLua", "Wrong lua object; expected method OnMessage");
		method(ref, msg);
	}

	void BehaviorLua::Update(const uint64 delta, const uint64 absolute) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
		LuaRef ref = LuaRef::fromStack(L, lua_gettop(L));
		
		COGASSERT(!ref.isNil(), "BehaviorLua", "Wrong lua object; expected reference");
		auto method = ref["Update"];
		COGASSERT(!method.isNil(), "BehaviorLua", "Wrong lua object; expected method Update");

		// uint64_t doesn't work here 
		method(ref, (unsigned)delta, (unsigned)absolute);
	}

	void BehaviorLua::SubscribeForMessagesLua(StrId action) {
		SubscribeForMessages(action);
	}

} // namespace