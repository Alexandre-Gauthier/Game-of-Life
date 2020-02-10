#include "../h/GoLActionKeyBinding.h"


//#include "EcaModel.h"
#include "../h/GoLController.h"




GoLActionKeyBinding::GoLActionKeyBinding()
	: GoLActionKeyBinding(std::numeric_limits<char>::min(), std::numeric_limits<char>::max())
{
}

GoLActionKeyBinding::GoLActionKeyBinding(key_t bindFromKey, key_t bindToKey)
	: mOffsetKey{ bindFromKey }, mBinding(bindToKey - bindFromKey + 1)
{
	std::fill(mBinding.begin(), mBinding.end(), nullptr);
}

void GoLActionKeyBinding::setAction(key_t key, action_t action)
{
	mBinding[key - mOffsetKey] = action;
}

void GoLActionKeyBinding::setDefaultAction(action_t action)
{
	mDefaultAction = action;
}

void GoLActionKeyBinding::setDefaultAction(key_t key)
{
	mDefaultAction = mBinding[key - mOffsetKey];
}

void GoLActionKeyBinding::doActionFromKey(key_t key, GoLModel & model, GoLController & controller) const
{
	int index{ key - mOffsetKey };
	if (index >= 0 && index < (int)mBinding.size() && mBinding[index]) {
		mBinding[key - mOffsetKey](model, controller);
	}
	else {
		doDefaultAction(model, controller);
	}
}

void GoLActionKeyBinding::doDefaultAction(GoLModel & model, GoLController & controller) const
{
	if (mDefaultAction) {
		mDefaultAction(model, controller);
	}
}
