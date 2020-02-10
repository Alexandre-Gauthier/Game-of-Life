#include "EcaActionKeyBinding.h"


#include "EcaModel.h"
#include "EcaController.h"




EcaActionKeyBinding::EcaActionKeyBinding()
	: EcaActionKeyBinding(std::numeric_limits<char>::min(), std::numeric_limits<char>::max())
{
}

EcaActionKeyBinding::EcaActionKeyBinding(key_t bindFromKey, key_t bindToKey)
	: mOffsetKey{ bindFromKey }, mBinding(bindToKey - bindFromKey + 1)
{
	std::fill(mBinding.begin(), mBinding.end(), nullptr);
}

void EcaActionKeyBinding::setAction(key_t key, action_t action)
{
	mBinding[key - mOffsetKey] = action;
}

void EcaActionKeyBinding::setDefaultAction(action_t action)
{
	mDefaultAction = action;
}

void EcaActionKeyBinding::setDefaultAction(key_t key)
{
	mDefaultAction = mBinding[key - mOffsetKey];
}

void EcaActionKeyBinding::doActionFromKey(key_t key, EcaModel & model, EcaController & controller) const
{
	int index{ key - mOffsetKey };
	if (index >= 0 && index < (int)mBinding.size() && mBinding[index]) {
		mBinding[key - mOffsetKey](model, controller);
	} else {
		doDefaultAction(model, controller);
	}
}

void EcaActionKeyBinding::doDefaultAction(EcaModel & model, EcaController & controller) const
{
	if (mDefaultAction) {
		mDefaultAction(model, controller);
	}
}
