#pragma once

#include "AIAgent.h"
#include "ofMath.h"

namespace Cog {

	/**
	* Random agent that selects at each step
	* a random action from the collection of possible actions
	*/
	template<class S, class A>
	class RandomAgent : public AIAgent<S,A> {
	protected:
	public:

		RandomAgent() {

		}

		RandomAgent(string name) : AIAgent<S,A>(name) {

		}

		virtual A ChooseAction(spt<Simulator<S,A>> simulator) {
			auto& actions = simulator->GetPossibleActions();
			int randIndex = (int)ofRandom(0, actions.size());
			return actions[randIndex];
		}
	};

} // namespace